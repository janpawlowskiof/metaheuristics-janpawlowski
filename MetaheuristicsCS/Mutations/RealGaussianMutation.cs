using System;
using System.Collections.Generic;

using EvaluationsCLI;
using Utility;

namespace Mutations
{
    class RealGaussianMutation : ARandomMutation<double>
    {
        private readonly BoolRandom uniformRNG;
        private readonly NormalRealRandom gaussianRNG;

        private readonly List<double> sigmas;

        private double maxSigma = 100.0; 
        
        public RealGaussianMutation(double sigma, IEvaluationProfile<double> evaluationProfile, int? seed = null, double probability = 1.0)
            : base(probability, evaluationProfile)
        {
            uniformRNG = new BoolRandom(seed);
            gaussianRNG = new NormalRealRandom(seed);

            sigmas = new List<double>(evaluationProfile.iSize);
            for(int i = 0; i < evaluationProfile.iSize; ++i)
            {
                sigmas.Add(sigma);
            }
        }

        public RealGaussianMutation(List<double> sigmas, IEvaluationProfile<double> evaluationProfile, int? seed = null, double probability = 1.0)
            : base(probability, evaluationProfile)
        {
            uniformRNG = new BoolRandom(seed);
            gaussianRNG = new NormalRealRandom(seed);

            this.sigmas = new List<double>(sigmas);
        }

        public override bool Mutate(List<double> solution)
        {
            bool successfulMutation = false;

            for(int i = 0; i < solution.Count; ++i)
            {
                if (uniformRNG.Next(Probability))
                {
                    double newSolution;
                    do
                    {
                        newSolution = solution[i] + gaussianRNG.Next(0.0, sigmas[i]); 
                    } while (!evaluationProfile.pcConstraint.bIsFeasible(i, newSolution));

                    solution[i] = newSolution;
                    successfulMutation = true;
                }
            }

            return successfulMutation;
        }

        public void MultiplySigmas(double multiplier)
        {
            for (int i = 0; i < sigmas.Count; ++i)
            {
                sigmas[i] = Math.Min(Math.Max(sigmas[i] * multiplier, -maxSigma), maxSigma);
            }
        }

        public double Sigmas(int index)
        {
            return sigmas[index];
        }

        public void Sigmas(int index, double value)
        {
            sigmas[index] = value;
        }

        public void Sigmas(double sigma)
        {
            for (int i = 0; i < sigmas.Count; ++i)
            {
                sigmas[i] = sigma;
            }
        }
        
        public int NumSigmas()
        {
            return sigmas.Count;
        }
    }
}
