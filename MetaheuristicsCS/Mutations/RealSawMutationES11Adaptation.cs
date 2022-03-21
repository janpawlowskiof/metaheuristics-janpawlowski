using System;
using System.Collections.Generic;
using System.Linq;
using System.Management.Instrumentation;
using ConstraintsCLI;

namespace Mutations
{
    class RealSawMutationES11Adaptation : ARealMutationES11Adaptation
    {
        private double minPower;
        private int cycleLength;
        private int nCycles = 0;
        private List<double> sigmaScales;


        public RealSawMutationES11Adaptation(int cycleLength, double minPower, RealGaussianMutation mutation)
            : base(mutation)
        {
            this.minPower = minPower;
            this.cycleLength = cycleLength;
            sigmaScales = Enumerable.Repeat(1.0, mutation.NumSigmas()).ToList();
        }
        
        public RealSawMutationES11Adaptation(int cycleLength, double minPower, RealGaussianMutation mutation, IConstraint<double> constraint)
            : base(mutation)
        {
            this.minPower = minPower;
            this.cycleLength = cycleLength;

            sigmaScales = Enumerable.Repeat(1.0, mutation.NumSigmas()).ToList();
            
            for (int i = 0; i < mutation.NumSigmas(); i++)
            {
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
            double newSigma = Math.Pow(10, -minPower + minPower * (1.0 - nCycles % cycleLength / (double)cycleLength));

            for (var sigmaIndex = 0; sigmaIndex < numGenes; sigmaIndex++)
            {
                Mutation.Sigmas(sigmaIndex, newSigma * sigmaScales[sigmaIndex]);
            }
        }
    }
}