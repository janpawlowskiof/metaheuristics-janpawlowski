using System.Collections.Generic;

using ConstraintsCLI;

namespace Generators
{
    public abstract class AGenerator<Element>
    {
        protected IConstraint<Element> constraint;

        public AGenerator(IConstraint<Element> constraint)
        {
            this.constraint = constraint;
        }

        public List<Element> Create(int size)
        {
            return Fill(new List<Element>(size));
        }

        public abstract List<Element> Fill(List<Element> solution);
    }
}
