using System;

namespace Utility
{
    class NormalRealRandom : ASeedableRandom
    {
        private double? value;

        public NormalRealRandom(int? seed = null)
            : base(seed)
        {
            value = null;
        }

        public double Next(double miu = 0.0, double sigma = 1.0)
        {
            if(value.HasValue)
            {
                double val = value.Value;
                value = null;

                return val;
            }
            else
            {
                return BoxMuller(miu, sigma);
            }
        }

        private double BoxMuller(double miu, double sigma)
        {
            double u1 = 1.0 - rng.NextDouble();
            double u2 = 1.0 - rng.NextDouble();

            double sigmaR = sigma * Math.Sqrt(-2.0 * Math.Log(u1));
            double theta = 2.0 * Math.PI * u2;

            value = sigmaR * Math.Sin(theta) + miu;

            return sigmaR * Math.Cos(theta) + miu;
        }
    }
}
