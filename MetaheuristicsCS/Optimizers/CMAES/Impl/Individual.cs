using MathNet.Numerics.LinearAlgebra;
using System.Collections.Generic;

using ConstraintsCLI;
using EvaluationsCLI;

namespace Optimizers.CMAESImpl
{
    class Individual
    {
        private readonly IEvaluation<double> evaluation;

        public double Fitness { get; private set; }
        public List<double> Genotype { get; private set; }

        public Individual(IEvaluation<double> evaluation, Vector<double> sample)
        {
            this.evaluation = evaluation;
            Genotype = new List<double>(sample.Enumerate());
        }

        public void RepairGenotype()
        {
            IConstraint<double> constraint = evaluation.pcConstraint;

            double lowerBound;
            double upperBound;

            for (int i = 0; i < Genotype.Count; ++i)
            {
                lowerBound = constraint.tGetLowerBound(i);
                upperBound = constraint.tGetUpperBound(i);

                if (Genotype[i] < lowerBound)
                {
                    Genotype[i] = lowerBound;
                }
                else if (Genotype[i] > upperBound)
                {
                    Genotype[i] = upperBound;
                }
            }
        }

        public void Evaluate()
        {
            Fitness = evaluation.dEvaluate(Genotype);
        }
    }
}
