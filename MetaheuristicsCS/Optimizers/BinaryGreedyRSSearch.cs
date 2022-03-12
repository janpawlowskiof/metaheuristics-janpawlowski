using System;
using System.Collections.Generic;
using System.Linq;
using ConstraintsCLI;
using EvaluationsCLI;
using Optimizers;
using StopConditions;

namespace Generators
{
    public class BinaryGreedyRSSearch : AOptimizer<bool>
    {
        private int greedyRepeats;

        public BinaryGreedyRSSearch(IEvaluation<bool> evaluation, AStopCondition stopCondition, int greedyRepeats) : base(evaluation, stopCondition)
        {
            this.greedyRepeats = greedyRepeats;
        }

        protected override void Initialize(DateTime startTime)
        {
        }

        protected override bool RunIteration(long itertionNumber, DateTime startTime)
        {
            var rs = new BinaryRandomSearch(evaluation, stopCondition);
            rs.Initialize();
            bool improvement = rs.RunIteration();
            
            var greedy = new BinaryGreedySearch(evaluation, stopCondition);
            greedy.Initialize();
            greedy.Result = rs.Result;

            for (var i = 0; i < greedyRepeats; i++)
            {
                improvement = greedy.RunIteration() | improvement;
            }

            CheckNewBest(greedy.Result.BestSolution, greedy.Result.BestValue);
            return improvement;
        }
    }
}