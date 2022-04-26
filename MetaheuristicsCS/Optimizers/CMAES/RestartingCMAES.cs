using System;
using System.Collections.Generic;
using EvaluationsCLI;
using StopConditions;
using Utility;

namespace Optimizers
{
    class RestartingCMAES : CMAES
    {
        private int numIterationsWithoutImprovement = 0;
        private int numIterationsWithoutImprovementThreshold = 0;
        public OptimizationResult<double> ResultAfterReset = null;

        public RestartingCMAES(IEvaluation<double> evaluation, AStopCondition stopCondition, double initSigma, int numIterationsWithoutImprovementThreshold, int? seed = null) : base(evaluation, stopCondition, initSigma, seed)
        {
            this.numIterationsWithoutImprovementThreshold = numIterationsWithoutImprovementThreshold;
        }

        protected override bool RunIteration(long itertionNumber, DateTime startTime)
        {
            bool improvement = base.RunIteration(itertionNumber, startTime);
            
            
            numIterationsWithoutImprovement = improvement ? 0 : numIterationsWithoutImprovement + 1;

            if (numIterationsWithoutImprovement > numIterationsWithoutImprovementThreshold)
            {
                Restart();
            }

            return improvement;
        }

        protected override bool CheckNewBest(List<double> solution, double value, bool onlyImprovements = true)
        {
            base.CheckNewBest(solution, value, onlyImprovements);
            
            if (ResultAfterReset == null || value > ResultAfterReset.BestValue || value == ResultAfterReset.BestValue && !onlyImprovements)
            {
                ResultAfterReset = new OptimizationResult<double>(value, solution, iterationNumber, evaluation.iFFE, TimeUtils.DurationInSeconds(startTime));
                return true;
            }

            return false;
        }


        protected void Restart()
        {
            ResultAfterReset = null;
            numIterationsWithoutImprovement = 0;
            Initialize(startTime);
        }
    }
}