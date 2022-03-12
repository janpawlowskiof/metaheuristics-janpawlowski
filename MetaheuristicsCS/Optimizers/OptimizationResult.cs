using System.Collections.Generic;

namespace Optimizers
{
    public class OptimizationResult<Element>
    {
        public double BestValue { get; }
        public List<Element> BestSolution { get; }
        public long BestIteration { get; }
        public long BestFFE { get; }
        public double BestTime { get; }

        public OptimizationResult(double bestValue, List<Element> bestSolution, long bestIteration, long bestFFE, double bestTime)
        {
            BestValue = bestValue;
            BestSolution = new List<Element>(bestSolution);
            BestIteration = bestIteration;
            BestFFE = bestFFE;
            BestTime = bestTime;
        }
    }
}
