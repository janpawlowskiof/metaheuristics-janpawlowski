using System;
using System.Collections.Generic;
using System.Linq;
using EvaluationsCLI;
using Metaheur;
using Optimizers;
using StopConditions;

static void Lab1BinaryRandomSearch(IEvaluation<bool> evaluation, int? seed, int maxIterationNumber)
{
    IterationsStopCondition stopCondition = new IterationsStopCondition(evaluation.dMaxValue, maxIterationNumber);
    BinaryRandomSearch randomSearch = new BinaryRandomSearch(evaluation, stopCondition, seed);

    randomSearch.Run();

    ReportOptimizationResult(randomSearch.Result);
}

static void Lab1OneMax(int? seed)
{
    Lab1BinaryRandomSearch(new CBinaryOneMaxEvaluation(5), seed, 500);
}

static void Lab1StandardDeceptiveConcatenation(int? seed)
{
    Lab1BinaryRandomSearch(new CBinaryStandardDeceptiveConcatenationEvaluation(5, 1), seed, 500);
}

static void Lab1BimodalDeceptiveConcatenation(int? seed)
{
    Lab1BinaryRandomSearch(new CBinaryBimodalDeceptiveConcatenationEvaluation(10, 1), seed, 500);
}

static void Lab1IsingSpinGlass(int? seed)
{
    Lab1BinaryRandomSearch(new CBinaryIsingSpinGlassEvaluation(25), seed, 500);
}

static void Lab1NkLandscapes(int? seed)
{
    Lab1BinaryRandomSearch(new CBinaryNKLandscapesEvaluation(10), seed, 500);
}

void TestOneMax()
{
    Console.WriteLine("Testing one max problem");
    Lab1BinaryRandomSearch(new CBinaryOneMaxEvaluation(5), seed, 500);
    Lab1BinaryRandomSearch(new CBinaryOneMaxEvaluation(10), seed, 500);
    Lab1BinaryRandomSearch(new CBinaryOneMaxEvaluation(51), seed, 500);
}


TestOneMax();
