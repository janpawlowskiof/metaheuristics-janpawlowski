using System.Collections.Generic;

namespace Mutations
{
    abstract class ARealMutationES11Adaptation
    {
        public RealGaussianMutation Mutation { get; }

        public ARealMutationES11Adaptation(RealGaussianMutation mutation)
        {
            Mutation = mutation;
        }

        public abstract void Adapt(double beforeMutationValue, List<double> beforeMutationSolution, 
                                   double afterMutationValue, List<double> afterMutationSolution);
    }
}
