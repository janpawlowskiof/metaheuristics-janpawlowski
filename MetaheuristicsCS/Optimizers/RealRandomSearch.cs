using EvaluationsCLI;
using Generators;
using StopConditions;

namespace Optimizers
{
    class RealRandomSearch : SamplingOptimizer<double>
    {
        public RealRandomSearch(IEvaluation<double> evaluation, AStopCondition stopCondition, int? seed = null)
            : base(evaluation, stopCondition, new RealRandomGenerator(evaluation.pcConstraint, seed))
        {
        }
    }
}
