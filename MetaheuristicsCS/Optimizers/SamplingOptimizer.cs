using System;
using System.Collections.Generic;

using Generators;
using EvaluationsCLI;
using StopConditions;

namespace Optimizers
{
    class SamplingOptimizer<Element> : AOptimizer<Element>
    {
        private readonly AGenerator<Element> generator;

        public SamplingOptimizer(IEvaluation<Element> evaluation, AStopCondition stopCondition, AGenerator<Element> generator)
            : base(evaluation, stopCondition)
        {
            this.generator = generator;
        }

        protected override void Initialize(DateTime startTime)
        {
        }

        protected override bool RunIteration(long itertionNumber, DateTime startTime)
        {
            List<Element> solution = generator.Create(evaluation.iSize);

            return CheckNewBest(solution, evaluation.dEvaluate(solution));
        }
    }
}
