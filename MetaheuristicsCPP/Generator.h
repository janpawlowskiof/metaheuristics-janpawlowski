#pragma once

#include <Constraint.h>
#include <vector>

using namespace Constraints;

using namespace std;

namespace Generators
{
	template <typename TElement>
	class IGenerator
	{
	public:
		virtual ~IGenerator() = default;

		virtual vector<TElement> *pvCreate(int iSize) = 0;
		virtual void vFill(vector<TElement> &vSolution) = 0;
	};//class IGenerator


	template <typename TElement>
	class CGenerator : public IGenerator<TElement>
	{
	public:
		CGenerator(IConstraint<TElement> &cConstraint) : c_constraint(cConstraint) { }

		virtual vector<TElement> *pvCreate(int iSize)
		{
			vector<TElement> *pv_solution = new vector<TElement>((size_t)iSize);

			this->vFill(*pv_solution);
			
			return pv_solution;
		}//virtual vector<TElement> *pvCreate(int iSize)

	protected:
		IConstraint<TElement> &c_constraint;
	};//class CGenerator : public IGenerator<TElement>
}//namespace Generators