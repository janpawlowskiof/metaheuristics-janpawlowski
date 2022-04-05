using System;
using EvaluationsCLI;
using MathNet.Numerics.LinearAlgebra;
using StopConditions;

namespace Optimizers
{
    public class R_JumpingCMAES : R_CMAES
    {
        private int numIterationsWithoutImprovement = 0;
        private int numIterationsWithoutImprovementThreshold = 0;
        private double startStepSize;

        public R_JumpingCMAES(IEvaluation<double> evaluation, AStopCondition stopCondition, double initSigma, double stepSize, int? seed = null) : base(evaluation, stopCondition, initSigma, stepSize, seed)
        {
            startStepSize = stepSize;
        }

        protected override bool RunIteration(long itertionNumber, DateTime startTime)
        {
            if (numIterationsWithoutImprovement > numIterationsWithoutImprovementThreshold)
            {
                stepSize = startStepSize;
            }

            return base.RunIteration(itertionNumber, startTime);
        }
    }
}