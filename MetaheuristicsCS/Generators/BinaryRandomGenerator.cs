using System.Collections.Generic;

using ConstraintsCLI;
using Utility;

namespace Generators
{
    public class BinaryRandomGenerator : AGenerator<bool>
    {
        private readonly BoolRandom rng;

        public BinaryRandomGenerator(IConstraint<bool> constraint, int? seed = null)
            : base(constraint)
        {
            rng = new BoolRandom(seed);
        }

        public override List<bool> Fill(List<bool> solution)
        {
            bool lowerBound;

            for(int i = 0; i < solution.Capacity; ++i)
            {
                lowerBound = constraint.tGetLowerBound(i);

                solution.Add((lowerBound == constraint.tGetUpperBound(i)) ? lowerBound : rng.Next());
            }

            return solution;
        }
    }
}
