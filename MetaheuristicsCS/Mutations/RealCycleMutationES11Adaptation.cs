using System;
using System.Collections.Generic;
using System.Linq;
using System.Management.Instrumentation;
using ConstraintsCLI;

namespace Mutations
{
    class RealCycleMutationES11Adaptation : ARealMutationES11Adaptation
    {
        private double minSigma;
        private double maxSigma;
        private int cycleLength;
        private int nCycles = 0;
        private List<double> sigmaScales;


        public RealCycleMutationES11Adaptation(int cycleLength, double minSigma, double maxSigma, RealGaussianMutation mutation)
            : base(mutation)
        {
            this.minSigma = minSigma;
            this.maxSigma = maxSigma;
            this.cycleLength = cycleLength;
            sigmaScales = Enumerable.Repeat(1.0, mutation.NumSigmas()).ToList();
        }
        
        public RealCycleMutationES11Adaptation(int cycleLength, double minSigma, double maxSigma, RealGaussianMutation mutation, IConstraint<double> constraint)
            : base(mutation)
        {
            this.minSigma = minSigma;
            this.maxSigma = maxSigma;
            this.cycleLength = cycleLength;

            sigmaScales = Enumerable.Repeat(1.0, mutation.NumSigmas()).ToList();
            // double minRange = double.PositiveInfinity;
            // for (int i = 0; i < mutation.NumSigmas(); i++)
            // {
            //     minRange = Math.Min(minRange, constraint.tGetUpperBound(i) - constraint.tGetLowerBound(i));
            // }
            
            for (int i = 0; i < mutation.NumSigmas(); i++)
            {
                // sigmaScales[i] = (constraint.tGetUpperBound(i) - constraint.tGetLowerBound(i)) / minRange;
                sigmaScales[i] = (constraint.tGetUpperBound(i) - constraint.tGetLowerBound(i));
            }
        }

        public override void Adapt(
            double beforeMutationValue,
            List<double> beforeMutationSolution,
            double afterMutationValue,
            List<double> afterMutationSolution
        )
        {
            nCycles++;
            
            int numGenes = beforeMutationSolution.Count;
            double newSigma = (Math.Cos(2 * Math.PI * nCycles / cycleLength) + 1) / 2 * (maxSigma - minSigma) + minSigma;

            for (var sigmaIndex = 0; sigmaIndex < numGenes; sigmaIndex++)
            {
                Mutation.Sigmas(sigmaIndex, newSigma * sigmaScales[sigmaIndex]);
            }
        }
    }
}