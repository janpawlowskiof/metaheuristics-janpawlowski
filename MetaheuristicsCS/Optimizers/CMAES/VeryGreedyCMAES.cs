using System.Linq;
using EvaluationsCLI;
using StopConditions;

namespace Optimizers
{
    class VeryGreedyCMAES : CMAES
    {
        public VeryGreedyCMAES(IEvaluation<double> evaluation, AStopCondition stopCondition, double initSigma, int? seed = null) : base(evaluation, stopCondition, initSigma, seed)
        {
        }

        protected override void AdaptMeans()
        {
            previousMeans.SetSubVector(0, means.Count, means);
            means.SetValues(sampledPopulation.First().Genotype.ToArray());
        }
    }
}