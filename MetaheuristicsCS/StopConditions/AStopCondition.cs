using System;

namespace StopConditions
{
    public abstract class AStopCondition
    {
        private readonly double maxValue;
        private readonly double epsilon;

        public AStopCondition(double maxValue, double epsilon = double.Epsilon)
        {
            this.maxValue = maxValue;
            this.epsilon = epsilon;
        }

        public bool Stop(double bestValue, long iterationNumber, long FFE, DateTime startTime)
        {
            return (Math.Abs(bestValue - maxValue) <= epsilon) ? true : Stop(iterationNumber, FFE, startTime);
        }

        protected abstract bool Stop(long iterationNumber, long FFE, DateTime startTime);
    }
}
