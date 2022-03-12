using System;
using System.Collections.Generic;
using System.Linq;
using ConstraintsCLI;
using EvaluationsCLI;
using Optimizers;
using StopConditions;

namespace Generators
{
    public class BinaryGreedyRSAutoSearch : AOptimizer<bool>
    {
        private int greedyRepeats;

        public BinaryGreedyRSAutoSearch(IEvaluation<bool> evaluation, AStopCondition stopCondition) : base(evaluation, stopCondition)
        {
        }

        protected override void Initialize(DateTime startTime)
        {
        }

        protected override bool RunIteration(long itertionNumber, DateTime startTime)
        {
            var rs = new BinaryRandomSearch(evaluation, stopCondition);
            rs.Initialize();
            bool rsImprovement = rs.RunIteration();

            
            var greedy = new BinaryGreedySearch(evaluation, stopCondition);
            greedy.Initialize();
            greedy.Result = rs.Result;
            
            var greedyImprovement = false;
            while (greedy.RunIteration())
            {
                greedyImprovement = true;
            }

            CheckNewBest(greedy.Result.BestSolution, greedy.Result.BestValue);
            return rsImprovement | greedyImprovement;
        }
    }
}