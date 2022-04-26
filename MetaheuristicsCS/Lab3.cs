using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using EvaluationsCLI;
using MetaheuristicsCS.Exporting;
using Mutations;
using Newtonsoft.Json.Linq;
using Optimizers;
using StopConditions;

namespace MetaheuristicsCS
{
    public class Lab3
    {
        private const int MaxIterations = 3_000;

        private const double InitialSigma = 1.0;

        // private static List<Thread> threads = new List<Thread>();
        private static List<Experiment> experiments = new List<Experiment>();

        private static void RunExperimentsForProblem(Func<IEvaluation<double>> evaluationFactory, string problemName, string description)
        {
            var numRepeats = 25;

            {
                var experiment = new Experiment(problemName, "CMAES", description);
                experiment.RunExperimentNTimes(resultFactory: () => Lab3CMAES(evaluationFactory()), n: numRepeats);
                experiments.Add(experiment);
            }

            {
                var experiment = new Experiment(problemName, "Restarting CMAES", description);
                experiment.RunExperimentNTimes(resultFactory: () => Lab3RestartingCMAES(evaluationFactory()), n: numRepeats);
                experiments.Add(experiment);
            }

            // {
            //     var experiment = new Experiment(problemName, "Jumping R_CMAES 10.0", description);
            //     experiment.RunExperimentNTimes(resultFactory: () => Lab3R_JumpingCMAES(evaluationFactory(), 10.0), n: numRepeats);
            //     experiments.Add(experiment);
            // }

            {
                var experiment = new Experiment(problemName, "R_CMAES 10.0", description);
                experiment.RunExperimentNTimes(resultFactory: () => Lab3R_CMAES(evaluationFactory(), 10.0), n: numRepeats);
                experiments.Add(experiment);
            }

            {
                var experiment = new Experiment(problemName, "Jumping CMAES", description);
                experiment.RunExperimentNTimes(resultFactory: () => Lab3JumpingCMAES(evaluationFactory()), n: numRepeats);
                experiments.Add(experiment);
            }

            // {
            //     var experiment = new Experiment(problemName, "Very Greedy CMAES", description);
            //     experiment.RunExperimentNTimes(resultFactory: () => Lab3VeryGreedyCMAES(evaluationFactory()), n: numRepeats);
            //     experiments.Add(experiment);
            // }
        }

        private static OptimizationResult<double> Lab3CMAES(IEvaluation<double> evaluation)
        {
            var stopCondition = new IterationsStopCondition(evaluation.dMaxValue, MaxIterations);
            CMAES cmaes = new CMAES(evaluation, stopCondition, InitialSigma);
            cmaes.Run();
            return cmaes.Result;
        }

        private static OptimizationResult<double> Lab3RestartingCMAES(IEvaluation<double> evaluation)
        {
            var stopCondition = new IterationsStopCondition(evaluation.dMaxValue, MaxIterations);
            CMAES cmaes = new RestartingCMAES(evaluation, stopCondition, InitialSigma, numIterationsWithoutImprovementThreshold: 500);
            cmaes.Run();
            return cmaes.Result;
        }

        private static OptimizationResult<double> Lab3R_CMAES(IEvaluation<double> evaluation, double stepSize)
        {
            var stopCondition = new IterationsStopCondition(evaluation.dMaxValue, MaxIterations);
            CMAES cmaes = new R_CMAES(evaluation, stopCondition, InitialSigma, stepSize);
            cmaes.Run();
            return cmaes.Result;
        }

        private static OptimizationResult<double> Lab3R_JumpingCMAES(IEvaluation<double> evaluation, double stepSize)
        {
            var stopCondition = new IterationsStopCondition(evaluation.dMaxValue, MaxIterations);
            CMAES cmaes = new R_JumpingCMAES(evaluation, stopCondition, InitialSigma, stepSize);
            cmaes.Run();
            return cmaes.Result;
        }

        private static OptimizationResult<double> Lab3JumpingCMAES(IEvaluation<double> evaluation)
        {
            var stopCondition = new IterationsStopCondition(evaluation.dMaxValue, MaxIterations);
            CMAES cmaes = new JumpingCMAES(evaluation, stopCondition, InitialSigma, numIterationsWithoutImprovementThreshold: 200, sigmaMultiplier: 1.001);
            cmaes.Run();
            return cmaes.Result;
        }

        private static OptimizationResult<double> Lab3VeryGreedyCMAES(IEvaluation<double> evaluation)
        {
            var stopCondition = new IterationsStopCondition(evaluation.dMaxValue, MaxIterations);
            CMAES cmaes = new VeryGreedyCMAES(evaluation, stopCondition, InitialSigma);
            cmaes.Run();
            return cmaes.Result;
        }

        private static void Lab3SphereCMAES()
        {
            foreach (var genes in new[] {2, 5, 10, 20})
            {
                RunExperimentsForProblem(() => new CRealSphereEvaluation(genes), "Sphere", genes.ToString());
            }
        }

        private static void Lab3Sphere10CMAES()
        {
            foreach (var genes in new[] {2, 5, 10, 20})
            {
                RunExperimentsForProblem(() => new CRealSphere10Evaluation(genes), "Sphere10", genes.ToString());
            }
        }

        private static void Lab3EllipsoidCMAES()
        {
            foreach (var genes in new[] {2, 5, 10, 20})
            {
                RunExperimentsForProblem(() => new CRealEllipsoidEvaluation(genes), "Ellipsoid", genes.ToString());
            }
        }

        private static void Lab3Step2SphereCMAES()
        {
            foreach (var genes in new[] {2, 5, 10, 20})
            {
                RunExperimentsForProblem(() => new CRealStep2SphereEvaluation(genes), "Step-2 Sphere", genes.ToString());
            }
        }

        private static void Lab3RastriginCMAES()
        {
            foreach (var genes in new[] {2, 5, 10, 20, 30, 40})
            {
                RunExperimentsForProblem(() => new CRealRastriginEvaluation(genes), "Rastrigin", genes.ToString());
            }
        }

        private static void Lab3AckleyCMAES()
        {
            foreach (var genes in new[] {2, 5, 10, 20, 30, 40})
            {
                RunExperimentsForProblem(() => new CRealAckleyEvaluation(genes), "Ackley", genes.ToString());
            }
        }

        public static void Run()
        {
            Lab3SphereCMAES();
            Lab3Sphere10CMAES();
            Lab3EllipsoidCMAES();
            Lab3Step2SphereCMAES();
            Lab3RastriginCMAES();
            Lab3AckleyCMAES();

            Console.WriteLine("FINAL NUM EXPERIMENTS " + experiments.Count);
            var json = JObject.FromObject(new {Experiments = experiments});
            string path = @"C:\Users\blond\Desktop\MetaResultsList3.txt";
            File.WriteAllText(path, json.ToString());
        }
    }
}