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
    public class JumpingCMAES : CMAES
    {
        private int numIterationsWithoutImprovement = 0;
        private int numIterationsWithoutImprovementThreshold = 0;
        private double sigmaScale = 1.0;
        private double sigmaMultiplier = 1.01;

        public JumpingCMAES(IEvaluation<double> evaluation, AStopCondition stopCondition, double initSigma, int numIterationsWithoutImprovementThreshold, double sigmaMultiplier, int? seed = null) : base(evaluation, stopCondition, initSigma, seed)
        {
            this.numIterationsWithoutImprovementThreshold = numIterationsWithoutImprovementThreshold;
            this.sigmaMultiplier = sigmaMultiplier;
        }

        protected override bool RunIteration(long itertionNumber, DateTime startTime)
        {
            if (numIterationsWithoutImprovement > numIterationsWithoutImprovementThreshold)
            {
                sigmaScale *= sigmaMultiplier;
            }
            else
            {
                sigmaScale = 1.0;
            }

            bool improvement = base.RunIteration(itertionNumber, startTime);

            if (numIterationsWithoutImprovement > numIterationsWithoutImprovementThreshold && sampledPopulation.Count > 0)
            {
                var newMean = sampledPopulation[0].Genotype.ToArray();
                Initialize(startTime);
                means.SetValues(newMean);
                
                if (improvement)
                    Console.WriteLine("Jumping gave an improvement!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
            }


            numIterationsWithoutImprovement = improvement ? 0 : numIterationsWithoutImprovement + 1;
            return improvement;
        }


        protected override Vector<double> MultivariateNormalDistributionSample(Matrix<double> samplingTransform)
        {
            Vector<double> independentN01Sample = Vector<double>.Build.Dense(evaluation.iSize, i => normalRNG.Next(0.0, sigmaScale));
            return means + stepSizeParameters.Sigma * samplingTransform * independentN01Sample;
        }
    }
}