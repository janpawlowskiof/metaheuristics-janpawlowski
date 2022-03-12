using System;
using System.Collections.Generic;

using EvaluationsCLI;
using StopConditions;
using Utility;

namespace Optimizers
{
    public abstract class AOptimizer<Element>
    {
        public OptimizationResult<Element> Result { get; set; }

        protected IEvaluation<Element> evaluation;
        protected AStopCondition stopCondition;

        private long iterationNumber;
        private DateTime startTime;

        public AOptimizer(IEvaluation<Element> evaluation, AStopCondition stopCondition)
        {
            Result = null;
            this.evaluation = evaluation;
            this.stopCondition = stopCondition;
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

        protected abstract void Initialize(DateTime startTime);
        protected abstract bool RunIteration(long itertionNumber, DateTime startTime);

        protected bool CheckNewBest(List<Element> solution, double value, bool onlyImprovements = true)
        {
            if (Result == null || value > Result.BestValue || value == Result.BestValue && !onlyImprovements)
            {
                Result = new OptimizationResult<Element>(value, solution, iterationNumber, evaluation.iFFE, TimeUtils.DurationInSeconds(startTime));

                return true;
            }

            return false;
        }
    }
}
