using System;
using System.Collections.Generic;

using EvaluationsCLI;
using Generators;
using StopConditions;
using Utility;

namespace Optimizers.Simple
{
    sealed class RealRandomSearch
    {
        public OptimizationResult<double> Result { get; private set; }

        private IEvaluation<double> evaluation;
        private AStopCondition stopCondition;

        private readonly AGenerator<double> generator;

        private long iterationNumber;
        private DateTime startTime;

        public RealRandomSearch(IEvaluation<double> evaluation, AStopCondition stopCondition, int? seed = null)
        {
            Result = null;
            this.evaluation = evaluation;
            this.stopCondition = stopCondition;
            generator = new RealRandomGenerator(evaluation.pcConstraint, seed);
        }

        public void Initialize()
        {
            Result = null;
            iterationNumber = 0;
            startTime = DateTime.UtcNow;

            Initialize(startTime);
        }

        public bool RunIteration()
        {
            return RunIteration(iterationNumber++, startTime);
        }

        public bool ShouldStop()
        {
            return stopCondition.Stop((Result != null) ? Result.BestValue : double.NegativeInfinity, iterationNumber, evaluation.iFFE, startTime);
        }

        public void Run()
        {
            Initialize();

            while (!ShouldStop())
            {
                RunIteration();
            }
        }

        private bool CheckNewBest(List<double> solution, double value, bool onlyImprovements = true)
        {
            if (Result == null || value > Result.BestValue || value == Result.BestValue && !onlyImprovements)
            {
                Result = new OptimizationResult<double>(value, solution, iterationNumber, evaluation.iFFE, TimeUtils.DurationInSeconds(startTime));

                return true;
            }

            return false;
        }

        private void Initialize(DateTime startTime)
        {

        }

        private bool RunIteration(long itertionNumber, DateTime startTime)
        {
            List<double> solution = generator.Create(evaluation.iSize);

            return CheckNewBest(solution, evaluation.dEvaluate(solution));
        }
    }
}
