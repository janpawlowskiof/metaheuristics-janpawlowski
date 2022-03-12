using System;

namespace Utility
{
    class TimeUtils
    {
        public static double DurationInSeconds(DateTime from)
        {
            return DurationInSeconds(from, DateTime.UtcNow);
        }

        public static double DurationInSeconds(DateTime from, DateTime to)
        {
            return (to - from).TotalSeconds;
        }
    }
}
