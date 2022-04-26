using System;
using System.Collections.Generic;
using EvaluationsCLI;
using Generators;
using MathNet.Numerics.LinearAlgebra;
using MathNet.Numerics.LinearAlgebra.Factorization;
using Optimizers.CMAESImpl;
using StopConditions;
using Utility;

namespace Optimizers
{
    public class CMAES : AOptimizer<double>
    {
        protected readonly NormalRealRandom normalRNG;
        private readonly RealRandomGenerator realGenerator;

        protected Vector<double> previousMeans;
        protected Vector<double> means;
        protected readonly Matrix<double> covarianceMatrix;

        private readonly AdaptationParameters adaptationParameters;
        protected readonly SelectionParameters selectionParameters;
        protected readonly StepSizeParameters stepSizeParameters;

        protected readonly List<Individual> sampledPopulation;

        public CMAES(IEvaluation<double> evaluation, AStopCondition stopCondition, double initSigma, int? seed = null)
            : base(evaluation, stopCondition)
        {
            normalRNG = new NormalRealRandom(seed);
            realGenerator = new RealRandomGenerator(evaluation.pcConstraint, seed);

            int N = evaluation.iSize;

            previousMeans = Vector<double>.Build.Dense(N);
            means = Vector<double>.Build.Dense(N);
            covarianceMatrix = Matrix<double>.Build.Dense(N, N);

            selectionParameters = new SelectionParameters(N);
            stepSizeParameters = new StepSizeParameters(N, initSigma);
            adaptationParameters = new AdaptationParameters(N, selectionParameters);

            sampledPopulation = new List<Individual>(selectionParameters.Lambda);
        }

        protected override void Initialize(DateTime startTime)
        {
            sampledPopulation.Clear();
            sampledPopulation.Capacity = selectionParameters.Lambda;

            InitMeans();

            covarianceMatrix.Clear();
            covarianceMatrix.SetDiagonal(Vector<double>.Build.Dense(evaluation.iSize, 1.0));
        }

        protected override bool RunIteration(long itertionNumber, DateTime startTime)
        {
            try
            {
                sampledPopulation.Clear();

                Evd<double> covarianceMatrixDecomposition = covarianceMatrix.Evd();

                Matrix<double> eigenvectors = covarianceMatrixDecomposition.EigenVectors;
                Matrix<double> sqrtEigenvalues = covarianceMatrixDecomposition.D.PointwiseSqrt();
                Matrix<double> invertedSqrtEigenvalues = Matrix<double>.Build.DenseOfMatrix(sqrtEigenvalues);
                invertedSqrtEigenvalues.SetDiagonal(invertedSqrtEigenvalues.Diagonal().DivideByThis(1.0));

                FillPopulation(eigenvectors, sqrtEigenvalues);
                SortPopulation();

                AdaptMeans();
                stepSizeParameters.UpdateEvolutionPaths(eigenvectors,
                    invertedSqrtEigenvalues,
                    adaptationParameters,
                    selectionParameters,
                    evaluation.iFFE,
                    means,
                    previousMeans);
                AdaptCovarianceMatrix();
                stepSizeParameters.AdaptStepSize(adaptationParameters);

                return CheckNewBest(sampledPopulation[0]);
            }
            catch
            {
                return false;
            }
        }

        protected void InitMeans()
        {
            means.SetValues(realGenerator.Fill(new List<double>(evaluation.iSize)).ToArray());
            previousMeans.SetValues(realGenerator.Fill(new List<double>(evaluation.iSize)).ToArray());
        }

        private void FillPopulation(Matrix<double> eigenvectors, Matrix<double> sqrtEigenvalues)
        {
            Matrix<double> samplingTransform = SamplingTransform(eigenvectors, sqrtEigenvalues);

            Individual individual;

            for (int i = 0; i < selectionParameters.Lambda; ++i)
            {
                individual = new Individual(evaluation, MultivariateNormalDistributionSample(samplingTransform));
                individual.RepairGenotype();
                individual.Evaluate();

                sampledPopulation.Add(individual);
            }
        }

        private void SortPopulation()
        {
            sampledPopulation.Sort((x, y) => { return (x.Fitness == y.Fitness) ? 0 : (x.Fitness < y.Fitness) ? 1 : -1; });
        }

        protected virtual void AdaptMeans()
        {
            previousMeans.SetSubVector(0, means.Count, means);

            double weightedMean;

            for (int i = 0; i < evaluation.iSize; ++i)
            {
                weightedMean = 0.0;

                for (int j = 0; j < selectionParameters.Mu; ++j)
                {
                    weightedMean += sampledPopulation[j].Genotype[i] * selectionParameters.Weights[j];
                }

                means[i] = weightedMean;
            }
        }

        private void AdaptCovarianceMatrix()
        {
            Matrix<double> rankMuUpdateMatrix = Matrix<double>.Build.Dense(covarianceMatrix.RowCount, covarianceMatrix.ColumnCount);

            for (int i = 0; i < selectionParameters.Mu; ++i)
            {
                Vector<double> vx = Vector<double>.Build.DenseOfEnumerable(sampledPopulation[i].Genotype);
                Vector<double> vy = (vx - previousMeans) / stepSizeParameters.Sigma;

                rankMuUpdateMatrix += selectionParameters.Weights[i] * vy.OuterProduct(vy);
            }

            covarianceMatrix.SetSubMatrix(0,
                0,
                (1.0 - adaptationParameters.C1 - adaptationParameters.CMu) * covarianceMatrix
                + adaptationParameters.C1 * (stepSizeParameters.PC.OuterProduct(stepSizeParameters.PC)
                                             + (1 - stepSizeParameters.HSigma) * adaptationParameters.CC
                                                                               * (2.0 - adaptationParameters.CC) * covarianceMatrix)
                + adaptationParameters.CMu * rankMuUpdateMatrix);
        }

        private Matrix<double> SamplingTransform(Matrix<double> eigenvectors, Matrix<double> sqrtEigenvalues)
        {
            return eigenvectors * sqrtEigenvalues;
        }

        protected virtual Vector<double> MultivariateNormalDistributionSample(Matrix<double> samplingTransform)
        {
            Vector<double> independentN01Sample = Vector<double>.Build.Dense(evaluation.iSize, i => normalRNG.Next());

            return means + stepSizeParameters.Sigma * samplingTransform * independentN01Sample;
        }

        public bool CheckNewBest(Individual individual)
        {
            return CheckNewBest(individual.Genotype, individual.Fitness);
        }
    }
}