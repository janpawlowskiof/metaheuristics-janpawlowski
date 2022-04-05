using System;
using System.Linq;
using EvaluationsCLI;
using StopConditions;

namespace Optimizers
{
    public class R_CMAES : CMAES
    {
        protected double stepSize;
        protected double prevMeanFitness; 
        public R_CMAES(IEvaluation<double> evaluation, AStopCondition stopCondition, double initSigma, double stepSize, int? seed = null) : base(evaluation, stopCondition, initSigma, seed)
        {
            this.stepSize = stepSize;
        }

        protected override void Initialize(DateTime startTime)
        {
            base.Initialize(startTime);
            prevMeanFitness = evaluation.dEvaluate(means);
        }

        protected override void AdaptMeans()
        {
            previousMeans.SetSubVector(0, means.Count, means);
            double meanFitness = sampledPopulation.Average(x => x.Fitness);
            double fitnessStd = Math.Sqrt(sampledPopulation.Average(x => Math.Pow(x.Fitness - meanFitness, 2))) + 0.001;

            for (int i = 0; i < sampledPopulation.Count; ++i)
            {
                double dist2 = 0;
                for (int j = 0; j < means.Count; j++)
                {
                    dist2 += Math.Pow(sampledPopulation[i].Genotype[j] - means[j], 2);
                }

                var dist = Math.Sqrt(dist2);

                for (int j = 0; j < means.Count; j++)
                {
                    var offsetOnAxis = (sampledPopulation[i].Genotype[j] - means[j]) / dist;
                    var weight = (sampledPopulation[i].Fitness - meanFitness) / fitnessStd;
                    means[j] += offsetOnAxis * weight / sampledPopulation.Count * stepSize;
                }
            }

            if (meanFitness > prevMeanFitness)
            {
                stepSize *= 1.01;
            }
            else
            {
                stepSize *= 0.95;
            }

            prevMeanFitness = meanFitness;
        }
    }
}