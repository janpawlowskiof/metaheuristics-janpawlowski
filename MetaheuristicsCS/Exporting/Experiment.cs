using System;
using System.Collections.Generic;
using Newtonsoft.Json.Linq;
using Optimizers;

namespace MetaheuristicsCS.Exporting
{
    public class Experiment
    {
        public Experiment(string problemName, string optimizerName, string description)
        {
            ProblemName = problemName;
            OptimizerName = optimizerName;
            Description = description;
        }

        public Experiment RunExperimentNTimes<Element>(Func<OptimizationResult<Element>> resultFactory, int n = 100)
        {
            for (var i = 0; i < n; i++)
            {
                var result = OptimizationResultForExport.FromOptimizationResult(resultFactory());
                Results.Add(result);
            }

            Print();

            return this;
        }

        public void Print()
        {
            double bestTime = 0;
            double bestIteration = 0;
            double bestFFE = 0;
            double bestValue = 0;
            foreach (var result in Results)
            {
                bestTime += result.BestTime;
                bestIteration += result.BestIteration;
                bestFFE += result.BestFFE;
                bestValue += result.BestValue;
            }

            Console.WriteLine(OptimizerName + ProblemName + Description);
            Console.WriteLine("\twhen (time): {0}s", bestTime / Results.Count);
            Console.WriteLine("\twhen (iteration): {0}", bestIteration / Results.Count);
            Console.WriteLine("\twhen (FFE): {0}", bestFFE / Results.Count);
            Console.WriteLine("\twhen (value): {0}", bestValue / Results.Count);
        }

        public string ProblemName;
        public string OptimizerName;
        public string Description;
        public List<OptimizationResultForExport> Results = new List<OptimizationResultForExport>();
    }
}