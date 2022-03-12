using System.Collections.Generic;

using EvaluationsCLI;
using Utility;

namespace Mutations
{
    class BinaryBitFlipMutation : ARandomMutation<bool>
    {
        private readonly BoolRandom rng;

        public BinaryBitFlipMutation(double probability, IEvaluationProfile<bool> evaluationProfile, int? seed = null)
            : base(probability, evaluationProfile)
        {
            rng = new BoolRandom(seed);
        }

        public override bool Mutate(List<bool> solution)
        {
            bool successfulMutation = false;

            for (int i = 0; i < solution.Count; ++i)
            {
                if (rng.Next(Probability)
                    && evaluationProfile.pcConstraint.bIsFeasible(i, !solution[i]))
                {
                    solution[i] = !solution[i];
                    successfulMutation = true;
                }
            }

            return successfulMutation;
        }
    }
}
