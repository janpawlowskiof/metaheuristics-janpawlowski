using EvaluationsCLI;
using Optimizers;
using Optimizers.Simple;
using StopConditions;

static void ReportOptimizationResult<Element>(OptimizationResult<Element> optimizationResult)
{
    Console.WriteLine("value: {0}", optimizationResult.BestValue);
    Console.WriteLine("\twhen (time): {0}s", optimizationResult.BestTime);
    Console.WriteLine("\twhen (iteration): {0}", optimizationResult.BestIteration);
    Console.WriteLine("\twhen (FFE): {0}", optimizationResult.BestFFE);
}

static void Lab1BinaryRandomSearch(IEvaluation<bool> evaluation, int? seed, int maxIterationNumber)
{
    IterationsStopCondition stopCondition = new IterationsStopCondition(evaluation.dMaxValue, maxIterationNumber);
    BinaryRandomSearch randomSearch = new BinaryRandomSearch(evaluation, stopCondition, seed);

    randomSearch.Run();

    ReportOptimizationResult(randomSearch.Result);
}


Console.WriteLine("Hello, World!");