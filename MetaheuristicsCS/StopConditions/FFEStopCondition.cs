using System;

namespace StopConditions
{
    class FFEStopCondition : AStopCondition
    {
        private readonly long maxFFE;

        public FFEStopCondition(double maxValue, long maxFFE, double epsilon = double.Epsilon)
            : base(maxValue, epsilon)
        {
            this.maxFFE = maxFFE;
        }

        protected override bool Stop(long iterationNumber, long FFE, DateTime startTime)
        {
            return FFE >= maxFFE;
        }
    }
}
