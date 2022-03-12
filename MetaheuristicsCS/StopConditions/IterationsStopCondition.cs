using System;

namespace StopConditions
{
    public class IterationsStopCondition : AStopCondition
    {
        private readonly long maxIterationNumber;

        public IterationsStopCondition(double maxValue, long maxIterationNumber, double epsilon = double.Epsilon)
            : base(maxValue, epsilon)
        {
            this.maxIterationNumber = maxIterationNumber;
        }

        protected override bool Stop(long iterationNumber, long FFE, DateTime startTime)
        {
            return iterationNumber >= maxIterationNumber;
        }
    }
}
