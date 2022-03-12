using System;
using System.Collections.Generic;

namespace Mutations
{
    class RealOneFifthRuleMutationES11Adaptation : ARealMutationES11Adaptation
    {
        private const double OneFifth = 0.2;

        private readonly int archiveSize;
        private readonly double modifier;

        private int successCounter;

        private readonly Queue<bool> successes;

        public RealOneFifthRuleMutationES11Adaptation(int archiveSize, double modifier, RealGaussianMutation mutation)
            : base(mutation)
        {
            this.archiveSize = archiveSize;
            this.modifier = modifier;

            successCounter = 0;
            successes = new Queue<bool>();
        }

        public override void Adapt(double beforeMutationValue, List<double> beforeMutationSolution, 
                                   double afterMutationValue, List<double> afterMutationSolution)
        {
            if(successes.Count == archiveSize)
            {
                successCounter -= Convert.ToInt32(successes.Dequeue());
            }

            bool isSuccess = afterMutationValue > beforeMutationValue;

            successes.Enqueue(isSuccess);
            successCounter += Convert.ToInt32(isSuccess);

            if (successes.Count == archiveSize)
            {
                double ratio = successCounter / (double)archiveSize;

                if (ratio > OneFifth)
                {
                    Mutation.MultiplySigmas(1.0 / modifier);
                }
                else if (ratio < OneFifth)
                {
                    Mutation.MultiplySigmas(modifier);
                }
            }
        }
    }
}
