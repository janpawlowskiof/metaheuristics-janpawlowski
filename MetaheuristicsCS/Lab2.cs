using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using EvaluationsCLI;
using MetaheuristicsCS.Exporting;
using Mutations;
using Newtonsoft.Json.Linq;
using Optimizers;
using StopConditions;

namespace MetaheuristicsCS
{
    public class Lab2
    {
        private const int MaxIterations = 30_000;

        private static OptimizationResult<double> Lab2ES11(IEvaluation<double> evaluation, double sigma)
        {
            var stopCondition = new IterationsStopCondition(evaluation.dMaxValue, MaxIterations);

            List<double> sigmas = Enumerable.Repeat(sigma, evaluation.iSize).ToList();
            RealGaussianMutation mutation = new RealGaussianMutation(sigmas, evaluation);
            RealNullRealMutationES11Adaptation mutationAdaptation = new RealNullRealMutationES11Adaptation(mutation);
            RealEvolutionStrategy11 es11 = new RealEvolutionStrategy11(evaluation, stopCondition, mutationAdaptation);


            es11.Run();
            return es11.Result;
        }

        private static OptimizationResult<double> Lab2ESOneFifthRule(IEvaluation<double> evaluation, double startSigma)
        {
            var archiveSize = 25;
            var modifier = 0.82;
            var stopCondition = new IterationsStopCondition(evaluation.dMaxValue, MaxIterations);

            List<double> sigmas = Enumerable.Repeat(startSigma, evaluation.iSize).ToList();
            RealGaussianMutation gaussianMutation = new RealGaussianMutation(sigmas, evaluation);
            var mutation = new RealOneFifthRuleMutationES11Adaptation(archiveSize, modifier, gaussianMutation);
            RealEvolutionStrategy11 es11 = new RealEvolutionStrategy11(evaluation, stopCondition, mutation);


            es11.Run();
            return es11.Result;
        }

        private static OptimizationResult<double> Lab2Cycle(IEvaluation<double> evaluation, int cycleLength, double minSigma, double maxSigma)
        {
            var stopCondition = new IterationsStopCondition(evaluation.dMaxValue, MaxIterations);

            List<double> sigmas = Enumerable.Repeat(0.1, evaluation.iSize).ToList();
            RealGaussianMutation gaussianMutation = new RealGaussianMutation(sigmas, evaluation);
            var mutation = new RealCycleMutationES11Adaptation(cycleLength, minSigma, maxSigma, gaussianMutation);
            RealEvolutionStrategy11 es11 = new RealEvolutionStrategy11(evaluation, stopCondition, mutation);

            es11.Run();
            return es11.Result;
        }

        private static OptimizationResult<double> Lab2SawScaled(IEvaluation<double> evaluation, int cycleLength, double minPower)
        {
            var stopCondition = new IterationsStopCondition(evaluation.dMaxValue, MaxIterations);

            List<double> sigmas = Enumerable.Repeat(0.1, evaluation.iSize).ToList();
            RealGaussianMutation gaussianMutation = new RealGaussianMutation(sigmas, evaluation);
            var mutation = new RealSawMutationES11Adaptation(cycleLength, minPower, gaussianMutation, evaluation.pcConstraint);
            RealEvolutionStrategy11 es11 = new RealEvolutionStrategy11(evaluation, stopCondition, mutation);

            es11.Run();
            return es11.Result;
        }
        
        private static OptimizationResult<double> Lab2CycleScaled(IEvaluation<double> evaluation, int cycleLength, double minSigma, double maxSigma)
        {
            var stopCondition = new IterationsStopCondition(evaluation.dMaxValue, MaxIterations);

            List<double> sigmas = Enumerable.Repeat(0.1, evaluation.iSize).ToList();
            RealGaussianMutation gaussianMutation = new RealGaussianMutation(sigmas, evaluation);
            var mutation = new RealCycleMutationES11Adaptation(cycleLength, minSigma, maxSigma, gaussianMutation, evaluation.pcConstraint);
            RealEvolutionStrategy11 es11 = new RealEvolutionStrategy11(evaluation, stopCondition, mutation);

            es11.Run();
            return es11.Result;
        }
        private static void RunExperimentsForProblem(List<Experiment> experiments, Func<IEvaluation<double>> evaluationFactory, string problemName, string description)
        {
            var numRepeats = 10;

            {
                var experiment = new Experiment(problemName, "Random: 0.1", description);
                experiment.RunExperimentNTimes(resultFactory: () => Lab2ES11(evaluationFactory(), sigma:0.1), n: numRepeats);
                experiments.Add(experiment);
            }
            
            {
                var experiment = new Experiment(problemName, "Random: 1.0", description);
                experiment.RunExperimentNTimes(resultFactory: () => Lab2ES11(evaluationFactory(), sigma:1.0), n: numRepeats);
                experiments.Add(experiment);
            }
            
            {
                var experiment = new Experiment(problemName, "OneFifth: 0.1", description);
                experiment.RunExperimentNTimes(resultFactory: () => Lab2ESOneFifthRule(evaluationFactory(), startSigma: 0.1), numRepeats);
                experiments.Add(experiment);
            }
            
            {
                var experiment = new Experiment(problemName, "OneFifth: 1.0", description);
                experiment.RunExperimentNTimes(resultFactory: () => Lab2ESOneFifthRule(evaluationFactory(), startSigma: 1.0), numRepeats);
                experiments.Add(experiment);
            }
            
            // {
            //     var experiment = new Experiment(problemName, "Half Cycle 1 (0.01 - 10)", description);
            //     experiment.RunExperimentNTimes(resultFactory: () => Lab2Cycle(evaluationFactory(), MaxIterations * 2, minSigma: 0.01, maxSigma: 10.0), numRepeats);
            //     experiments.Add(experiment);
            // }
            
            {
                var experiment = new Experiment(problemName, "Half Cycle 3 (0.01 - 10)", description);
                experiment.RunExperimentNTimes(resultFactory: () => Lab2Cycle(evaluationFactory(), MaxIterations * 2 / 3, minSigma: 0.01, maxSigma: 10.0), numRepeats);
                experiments.Add(experiment);
            }
            
            // {
            //     var experiment = new Experiment(problemName, "Half Scaled Cycle 1 (0.001% - 0.5%)", description);
            //     experiment.RunExperimentNTimes(resultFactory: () => Lab2CycleScaled(evaluationFactory(), MaxIterations * 2, minSigma: 0.001, maxSigma: 1.0), numRepeats);
            //     experiments.Add(experiment);
            // }

            {
                var experiment = new Experiment(problemName, "Half Scaled Cycle 3 (0.001 - 1.0)", description);
                experiment.RunExperimentNTimes(resultFactory: () => Lab2CycleScaled(evaluationFactory(), MaxIterations * 2 / 3, minSigma: 0.001, maxSigma: 1.0), numRepeats);
                experiments.Add(experiment);
            }

            {
                var experiment = new Experiment(problemName, "Scaled Saw(x1) (10e-5)", description);
                experiment.RunExperimentNTimes(resultFactory: () => Lab2SawScaled(evaluationFactory(), MaxIterations, minPower:5), numRepeats);
                experiments.Add(experiment);
            }
            
            {
                var experiment = new Experiment(problemName, "Scaled Saw(x3) (10e-5)", description);
                experiment.RunExperimentNTimes(resultFactory: () => Lab2SawScaled(evaluationFactory(), MaxIterations / 3, minPower:5), numRepeats);
                experiments.Add(experiment);
            }
        }

        private static void Lab2Sphere(List<Experiment> experiments)
        {
            foreach (var genes in new[] {2, 5, 10, 15})
            {
                RunExperimentsForProblem(experiments, () => new CRealSphereEvaluation(genes), "Sphere", genes.ToString());
            }
        }


        private static void Lab2Sphere10(List<Experiment> experiments)
        {
            foreach (var genes in new[] {2, 5, 10, 15})
            {
                RunExperimentsForProblem(experiments, () => new CRealSphere10Evaluation(genes), "Sphere10", genes.ToString());
            }
        }


        private static void Lab2Ellipsoid(List<Experiment> experiments)
        {
            foreach (var genes in new[] {2, 5, 10, 20, 30})
            {
                RunExperimentsForProblem(experiments, () => new CRealEllipsoidEvaluation(genes), "Ellipsoid", genes.ToString());
            }
        }

        private static void Lab2Step2Sphere(List<Experiment> experiments)
        {
            foreach (var genes in new[] {2, 5, 10, 15, 20})
            {
                RunExperimentsForProblem(experiments, () => new CRealStep2SphereEvaluation(genes), "Step-2 Sphere", genes.ToString());
            }
        }

        public static void Run()
        {
            var experiments = new List<Experiment>();

            Lab2Sphere(experiments);
            Lab2Sphere10(experiments);
            Lab2Ellipsoid(experiments);
            Lab2Step2Sphere(experiments);

            var json = JObject.FromObject(new {Experiments = experiments});
            string path = @"C:\Users\blond\Desktop\MetaResultsList2.txt";
            File.WriteAllText(path, json.ToString());
        }
    }
}