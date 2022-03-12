using MathNet.Numerics.LinearAlgebra;
using System;

namespace Optimizers.CMAESImpl
{
    class SelectionParameters
    {
        public int Lambda { get; }
        public Vector<double> Weights { get; }
        public int Mu { get; }
        public double MuEff { get; }

        public SelectionParameters(int problemSize)
        {
            Lambda = 4 + (int)Math.Floor(3.0 * Math.Log(problemSize));
            Mu = Lambda / 2;

            Weights = Vector<double>.Build.Dense(Mu);

            for (int i = 0; i < Weights.Count; ++i)
            {
                Weights[i] = Math.Log(Lambda / 2.0 + 0.5) - Math.Log(i + 1);
            }

            Weights /= Weights.Sum();

            MuEff = 1.0 / Weights.DotProduct(Weights);
        }
    }
}
