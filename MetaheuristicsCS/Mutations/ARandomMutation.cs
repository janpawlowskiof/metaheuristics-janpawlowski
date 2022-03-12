using System.Collections.Generic;

using EvaluationsCLI;

namespace Mutations
{
    abstract class ARandomMutation<Element> : IMutation<Element>
    {
        protected readonly IEvaluationProfile<Element> evaluationProfile;

        public double Probability { get; set; }

        public ARandomMutation(double probability, IEvaluationProfile<Element> evaluationProfile)
        {
            this.evaluationProfile = evaluationProfile;
            Probability = probability;
        }

        public abstract bool Mutate(List<Element> solution);
    }
}
