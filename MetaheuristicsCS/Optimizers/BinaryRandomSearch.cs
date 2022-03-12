using EvaluationsCLI;
using Generators;
using StopConditions;

namespace Optimizers
{
    class BinaryRandomSearch : SamplingOptimizer<bool>
    {
        public BinaryRandomSearch(IEvaluation<bool> evaluation, AStopCondition stopCondition, int? seed = null)
            : base(evaluation, stopCondition, new BinaryRandomGenerator(evaluation.pcConstraint, seed))
        {
        }
    }
}
