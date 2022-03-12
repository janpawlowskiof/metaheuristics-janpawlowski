using System;

using Utility;

namespace StopConditions
{
    class RunningTimeStopCondition : AStopCondition
    {
        private readonly double maxRunningTime;

        public RunningTimeStopCondition(double maxValue, double maxRunningTime, double epsilon = double.Epsilon)
            : base(maxValue, epsilon)
        {
            this.maxRunningTime = maxRunningTime;
        }

        protected override bool Stop(long iterationNumber, long FFE, DateTime startTime)
        {
            return TimeUtils.DurationInSeconds(startTime) >= maxRunningTime;
        }
    }
}
