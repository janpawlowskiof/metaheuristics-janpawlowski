using System;

namespace Optimizers.CMAESImpl
{
    class AdaptationParameters
    {
        public double CC { get; }
        public double CSigma { get; }
        public double C1 { get; }
        public double CMu { get; }
        public double Damping { get; }
        public double ChiN { get; }

        public AdaptationParameters(int problemSize, SelectionParameters selectionParameters)
        {
            double muEff = selectionParameters.MuEff;

            CC = (4.0 + muEff / problemSize) / (problemSize + 4.0 + 2.0 * muEff / problemSize);
            CSigma = (muEff + 2.0) / (problemSize + muEff + 5.0);
            C1 = 2.0 / (Math.Pow(problemSize + 1.3, 2) + muEff);
            CMu = Math.Min(1 - C1, 2.0 * (muEff - 2.0 + 1.0 / muEff) / (Math.Pow(problemSize + 2.0, 2) + muEff));
            Damping = 1.0 + 2.0 * Math.Max(0.0, Math.Sqrt((muEff - 1.0) / (problemSize + 1.0)) - 1.0) + CSigma;
            ChiN = Math.Sqrt(problemSize) * (1.0 - 1.0 / (4.0 * problemSize) + 1.0 / (21.0 * Math.Pow(problemSize, 2)));
        }
    }
}
