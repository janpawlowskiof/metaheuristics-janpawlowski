using System;

namespace Utility
{
    public class ASeedableRandom
    {
        protected readonly Random rng;

        public ASeedableRandom(int? seed = null)
        {
            rng = seed.HasValue ? new Random(seed.Value) : new Random();
        }
    }
}
