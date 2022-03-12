using System;

namespace Utility
{
    class BoolRandom : ASeedableRandom
    {
        public BoolRandom(int? seed = null)
            : base(seed)
        {

        }

        public bool Next(double probability = 0.5)
        {
            return rng.NextDouble() < probability;
        }
    }
}
