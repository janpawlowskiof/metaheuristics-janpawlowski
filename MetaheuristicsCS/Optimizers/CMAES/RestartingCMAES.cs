using MathNet.Numerics.LinearAlgebra;
using MathNet.Numerics.LinearAlgebra.Factorization;
using System;
using System.Collections.Generic;
using EvaluationsCLI;
using Generators;
using Optimizers.CMAESImpl;
using StopConditions;
using Utility;

namespace Optimizers
{
    class RestartingCMAES : CMAES
    {
        private int numIterationsWithoutImprovement = 0;
        private int numIterationsWithoutImprovementThreshold = 0;

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

        protected void Restart()
        {
            numIterationsWithoutImprovement = 0;
            Initialize(startTime);
        }
    }
}