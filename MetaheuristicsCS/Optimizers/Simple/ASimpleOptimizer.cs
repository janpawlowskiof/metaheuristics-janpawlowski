using System;
using System.Collections.Generic;

using EvaluationsCLI;
using Generators;
using StopConditions;
using Utility;

namespace Optimizers.Simple
{
    // A template of a simple optimizer.
    // Copy-paste and modify.
    // "Element" parameter has to be changed into the type of values (problem defined)
    // and removed after the name of the class (with the "<>" brackets).
    // Moreover, Initialize and RunIteration methods have to be implemented for a specific
    // otimization method.
    sealed class ASimpleOptimizer<Element>
    {
        public OptimizationResult<Element> Result { get; private set; }

        private IEvaluation<Element> evaluation;
        private AStopCondition stopCondition;

        private readonly AGenerator<Element> generator;

        private long iterationNumber;
        private DateTime startTime;

        public ASimpleOptimizer(IEvaluation<Element> evaluation, AStopCondition stopCondition, AGenerator<Element> generator)
        {
            Result = null;
            this.evaluation = evaluation;
            this.stopCondition = stopCondition;
            this.generator = generator;
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

        private bool CheckNewBest(List<Element> solution, double value, bool onlyImprovements = true)
        {
            if (Result == null || value > Result.BestValue || value == Result.BestValue && !onlyImprovements)
            {
                Result = new OptimizationResult<Element>(value, solution, iterationNumber, evaluation.iFFE, TimeUtils.DurationInSeconds(startTime));

                return true;
            }

            return false;
        }

        private void Initialize(DateTime startTime)
        {
            throw new NotImplementedException();
        }

        private bool RunIteration(long itertionNumber, DateTime startTime)
        {
            throw new NotImplementedException();
        }
    }
}
