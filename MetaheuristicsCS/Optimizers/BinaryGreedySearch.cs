using System;
using System.Collections.Generic;
using System.Linq;
using ConstraintsCLI;
using EvaluationsCLI;
using Optimizers;
using StopConditions;

namespace Generators
{
    public class BinaryGreedySearch : AOptimizer<bool>
    {
        private List<int> optimizationOrder;

        public BinaryGreedySearch(IEvaluation<bool> evaluation, AStopCondition stopCondition) : base(evaluation, stopCondition)
        {
            optimizationOrder = new List<int>(evaluation.iSize);
            for (var i = 0; i < optimizationOrder.Capacity; i++)
            {
                optimizationOrder.Add(i);
            }
        }

        void ShuffleOptimizationOrder()
        {
            var random = new Random();
            optimizationOrder = optimizationOrder.OrderBy(x => random.Next()).ToList();
        }

        bool OptimizeGene(int geneIndex)
        {
            var inversedGenotype = new List<bool>(Result.BestSolution);
            inversedGenotype[geneIndex] = !inversedGenotype[geneIndex]; 

            var improvement = CheckNewBest(inversedGenotype, evaluation.dEvaluate(inversedGenotype));
            return improvement;
        }

        protected override void Initialize(DateTime startTime)
        {
            var initialSolution = new List<bool>(evaluation.iSize);
            var random = new Random();
            for (int i = 0; i < optimizationOrder.Capacity; i++)
            {
                initialSolution.Add(random.NextDouble() < 0.5);
            }

            CheckNewBest(initialSolution, evaluation.dEvaluate(initialSolution));
        }

        protected override bool RunIteration(long itertionNumber, DateTime startTime)
        {
            ShuffleOptimizationOrder();
            var optimizationFound = false;
            foreach (var geneIndex in optimizationOrder)
            {
                optimizationFound = OptimizeGene(geneIndex) | optimizationFound;
            }

            return optimizationFound;
        }
    }
}