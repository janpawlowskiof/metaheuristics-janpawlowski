using Optimizers;

namespace MetaheuristicsCS.Exporting
{
    public struct OptimizationResultForExport
    {
        public double BestValue;
        public long BestIteration;
        public long BestFFE;
        public double BestTime;

        public static OptimizationResultForExport FromOptimizationResult<T>(OptimizationResult<T> result)
        {
            var returnValue = new OptimizationResultForExport();
            returnValue.BestIteration = result.BestIteration;
            returnValue.BestValue = result.BestValue;
            returnValue.BestFFE = result.BestFFE;
            returnValue.BestTime = result.BestTime;
            return returnValue;
        }
    }
}