using System;
using System.Collections.Generic;

using EvaluationsCLI;
using Generators;
using Mutations;
using StopConditions;
using Utility;

namespace Optimizers.Simple
{
    sealed class RealEvolutionStrategy11
    {
        public OptimizationResult<double> Result { get; private set; }

        private IEvaluation<double> evaluation;
        private AStopCondition stopCondition;

        private readonly ARealMutationES11Adaptation mutationAdaptation;
        private readonly RealRandomGenerator randomGeneration;

        private long iterationNumber;
        private DateTime startTime;

        public RealEvolutionStrategy11(IEvaluation<double> evaluation, AStopCondition stopCondition, ARealMutationES11Adaptation mutationAdaptation, int? seed = null)
        {
            Result = null;
            this.evaluation = evaluation;
            this.stopCondition = stopCondition;
            this.mutationAdaptation = mutationAdaptation;
            randomGeneration = new RealRandomGenerator(evaluation.pcConstraint, seed);
        }

        public void Initialize()
        {
            Result = null;
            iterationNumber = 0;
            startTime = DateTime.UtcNow;

            Initialize(startTime);
        }

        public bool RunIteration()
        {
            return RunIteration(iterationNumber++, startTime);
        }

        public bool ShouldStop()
        {
            return stopCondition.Stop((Result != null) ? Result.BestValue : double.NegativeInfinity, iterationNumber, evaluation.iFFE, startTime);
        }

        public void Run()
        {
            Initialize();

            while (!ShouldStop())
            {
                RunIteration();
            }
        }

        private bool CheckNewBest(List<double> solution, double value, bool onlyImprovements = true)
        {
            if (Result == null || value > Result.BestValue || value == Result.BestValue && !onlyImprovements)
            {
                Result = new OptimizationResult<double>(value, solution, iterationNumber, evaluation.iFFE, TimeUtils.DurationInSeconds(startTime));

                return true;
            }

            return false;
        }

        private void Initialize(DateTime startTime)
        {
            List<double> initialSolution = randomGeneration.Create(evaluation.iSize);

            CheckNewBest(initialSolution, evaluation.dEvaluate(initialSolution));
        }

        private bool RunIteration(long itertionNumber, DateTime startTime)
        {
            List<double> candidateSolution = new List<double>(Result.BestSolution);

            mutationAdaptation.Mutation.Mutate(candidateSolution);
            double candidateValue = evaluation.dEvaluate(candidateSolution);

            mutationAdaptation.Adapt(Result.BestValue, Result.BestSolution, candidateValue, candidateSolution);

            return CheckNewBest(candidateSolution, candidateValue);
        }
    }
}
