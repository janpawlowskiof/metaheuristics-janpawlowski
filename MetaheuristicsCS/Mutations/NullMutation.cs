using System.Collections.Generic;

namespace Mutations
{
    class NullMutation<Element> : IMutation<Element>
    {
        public double Probability{ get{ return 1; } set{ } }

        public virtual bool Mutate(List<Element> solution)
        {
            return false;
        }
    }
}
