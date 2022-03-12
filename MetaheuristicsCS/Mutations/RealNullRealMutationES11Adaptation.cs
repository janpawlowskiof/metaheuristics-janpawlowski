using System.Collections.Generic;

namespace Mutations
{
    class RealNullRealMutationES11Adaptation : ARealMutationES11Adaptation
    {
        public RealNullRealMutationES11Adaptation(RealGaussianMutation mutation)
            : base(mutation)
        {
        }

        public override void Adapt(double beforeMutationValue, List<double> beforeMutationSolution, 
                                   double afterMutationValue, List<double> afterMutationSolution)
        {
        }
    }
}
