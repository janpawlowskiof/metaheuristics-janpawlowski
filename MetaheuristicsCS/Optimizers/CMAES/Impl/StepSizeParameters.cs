using MathNet.Numerics.LinearAlgebra;
using System;

namespace Optimizers.CMAESImpl
{
    class StepSizeParameters
    {
        private readonly double initSigma;

        public Vector<double> PSigma { get; private set; }
        public Vector<double> PC { get; private set; }
        public int HSigma { get; private set; }
        public double Sigma { get; private set; }

        public StepSizeParameters(int problemSize, double initSigma)
        {
            this.initSigma = initSigma;

            PSigma = Vector<double>.Build.Dense(problemSize);
            PC = Vector<double>.Build.Dense(problemSize);

            Reset();
        }

        public void Reset()
        {
            PSigma.Clear();
            PC.Clear();

            HSigma = 0;
            Sigma = initSigma;
        }

        public void UpdateEvolutionPaths(Matrix<double> eigenvectors, Matrix<double> invertedSqrtEigenvalues, 
                                         AdaptationParameters adaptationParameters, SelectionParameters selectionParameters, 
                                         long FFE, Vector<double> means, Vector<double> previousMeans)
        {
            int problemSize = PSigma.Count;

            Matrix<double> invertedSqrtCovarianceMatrix = eigenvectors * invertedSqrtEigenvalues * eigenvectors.Transpose();
            Vector<double> meanDifferenceDivBySigma = (means - previousMeans) / Sigma;

            PSigma *= 1 - adaptationParameters.CSigma;
            PSigma += invertedSqrtCovarianceMatrix * PathUpdateCoefficient(adaptationParameters.CSigma, selectionParameters.MuEff, meanDifferenceDivBySigma);

            HSigma = Convert.ToInt32(PSigma.DotProduct(PSigma) / (1.0 - Math.Pow(1.0 - adaptationParameters.CSigma, 
                                                                                 2.0 * FFE / selectionParameters.Lambda)) / problemSize
                                     < 2.0 + 4.0 / (problemSize + 1.0));

            PC *= 1.0 - adaptationParameters.CC;
            PC += HSigma * PathUpdateCoefficient(adaptationParameters.CC, selectionParameters.MuEff, meanDifferenceDivBySigma);
        }

        public void AdaptStepSize(AdaptationParameters adaptationParameters)
        {
            Sigma *= Math.Exp(adaptationParameters.CSigma / adaptationParameters.Damping * (PSigma.L2Norm() / adaptationParameters.ChiN - 1.0));
        }

        private Vector<double> PathUpdateCoefficient(double specificValue, double muEff, Vector<double> meanDifferenceDivBySigma)
        {
            return Math.Sqrt(specificValue * (2.0 - specificValue) * muEff) * meanDifferenceDivBySigma;
        }
    }
}
