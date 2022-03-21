using System;
using System.Collections.Generic;
using System.IO;
using EvaluationsCLI;
using Generators;
using MetaheuristicsCS.Exporting;
using Newtonsoft.Json.Linq;
using Optimizers;
using StopConditions;

namespace MetaheuristicsCS
{
    public class Lab1
    {
        private const int MaxFFE = 12_000;
        
        private static OptimizationResult<bool> Lab1BinaryRandomSearch(
            IEvaluation<bool> evaluation
        )
        {
            // var stopCondition = new IterationsStopCondition(evaluation.dMaxValue, maxIterationNumber);
            var stopCondition = new FFEStopCondition(evaluation.dMaxValue, MaxFFE);
            
            var randomSearch = new BinaryRandomSearch(evaluation, stopCondition);
            randomSearch.Run();
            return randomSearch.Result;
        }

        private static OptimizationResult<bool> Lab1BinaryGreedySearch(
            IEvaluation<bool> evaluation
        )
        {
            var stopCondition = new FFEStopCondition(evaluation.dMaxValue, MaxFFE);
            var search = new BinaryGreedySearch(evaluation, stopCondition);
            search.Run();
            return search.Result;
        }

        private static OptimizationResult<bool> Lab1BinaryGreedyRS1(
            IEvaluation<bool> evaluation
        )
        {
            var stopCondition = new FFEStopCondition(evaluation.dMaxValue, MaxFFE);
            var search = new BinaryGreedyRSSearch(evaluation, stopCondition, 1);
            search.Run();
            return search.Result;
        }
        
        private static OptimizationResult<bool> Lab1BinaryGreedyRS5(
            IEvaluation<bool> evaluation
        )
        {
            var stopCondition = new FFEStopCondition(evaluation.dMaxValue, MaxFFE);
            var search = new BinaryGreedyRSSearch(evaluation, stopCondition, 5);
            search.Run();
            return search.Result;
        }
        
        private static OptimizationResult<bool> Lab1BinaryGreedyRSAuto(
            IEvaluation<bool> evaluation
        )
        {
            var stopCondition = new FFEStopCondition(evaluation.dMaxValue, MaxFFE);
            var search = new BinaryGreedyRSAutoSearch(evaluation, stopCondition);
            search.Run();
            return search.Result;
        }

        private static void RunExperimentsForProblem(List<Experiment> experiments, Func<IEvaluation<bool>> evaluationFactory, string problemName, string description)
        {
            var numRepeats = 100;
            {
                var experiment = new Experiment(problemName, "Greedy", description);
                experiment.RunExperimentNTimes(resultFactory: () => Lab1BinaryGreedySearch(evaluationFactory()), n: numRepeats);
                experiments.Add(experiment);
            }

            {
                var experiment = new Experiment(problemName, "RS", description);
                experiment.RunExperimentNTimes(resultFactory: () => Lab1BinaryRandomSearch(evaluationFactory()), n: numRepeats);
                experiments.Add(experiment);
            }
            
            {
                var experiment = new Experiment(problemName, "GreedyRS1", description);
                experiment.RunExperimentNTimes(resultFactory: () => Lab1BinaryGreedyRS1(evaluationFactory()), n: numRepeats);
                experiments.Add(experiment);
            }
            
            {
                var experiment = new Experiment(problemName, "GreedyRS5", description);
                experiment.RunExperimentNTimes(resultFactory: () => Lab1BinaryGreedyRS5(evaluationFactory()), n: numRepeats);
                experiments.Add(experiment);
            }
            
            {
                var experiment = new Experiment(problemName, "GreedyRSAuto", description);
                experiment.RunExperimentNTimes(resultFactory: () => Lab1BinaryGreedyRSAuto(evaluationFactory()), n: numRepeats);
                experiments.Add(experiment);
            }
        }
        
        private static void Lab1OneMax(List<Experiment> experiments)
        {
            foreach (var genes in new[] {5, 15, 30})
            {
                RunExperimentsForProblem(experiments, () => new CBinaryOneMaxEvaluation(genes), "OneMax", genes.ToString());
            }
        }

        private static void Lab1StandardDeceptiveConcatenation(List<Experiment> experiments)
        {
            var blockSize = 5;
            foreach (var blocks in new[] {1, 2, 6, 10})
            {
                RunExperimentsForProblem(experiments, () => new CBinaryStandardDeceptiveConcatenationEvaluation(blockSize, blocks), "Order5 Standard Deceptive Concatenation", (blockSize * blocks).ToString());
            }
        }

        private static void Lab1BimodalDeceptiveConcatenation(List<Experiment> experiments)
        {
            var blockSize = 10;
            foreach (var blocks in new[] {1, 2, 3, 5})
            {
                RunExperimentsForProblem(experiments, () => new CBinaryBimodalDeceptiveConcatenationEvaluation(blockSize, blocks), "Bimodal5 Standard Deceptive Concatenation", (blockSize * blocks).ToString());
            }
        }

        private static void Lab1IsingSpinGlass(List<Experiment> experiments)
        {
            foreach (var genes in new[] {25, 49, 100, 484})
            {
                RunExperimentsForProblem(experiments, () => new CBinaryIsingSpinGlassEvaluation(genes), "Ising Spin Glass", genes.ToString());
            }
        }

        private static void Lab1NkLandscapes(List<Experiment> experiments)
        {
            foreach (var genes in new[] {10, 50, 100, 200})
            {
                RunExperimentsForProblem(experiments, () => new CBinaryNKLandscapesEvaluation(genes), "NK Fitness Landscapes", genes.ToString());
            }
        }

        public static void Run()
        {
            var experiments = new List<Experiment>();

            Lab1OneMax(experiments);
            Lab1StandardDeceptiveConcatenation(experiments);
            Lab1BimodalDeceptiveConcatenation(experiments);
            Lab1IsingSpinGlass(experiments);
            Lab1NkLandscapes(experiments);

            var json = JObject.FromObject(new {Experiments = experiments});
            string path = @"C:\Users\blond\Desktop\MetaResults.txt";
            File.WriteAllText(path, json.ToString());
        }
    }
}