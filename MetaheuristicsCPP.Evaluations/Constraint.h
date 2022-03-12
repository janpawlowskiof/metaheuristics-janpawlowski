#pragma once

namespace Constraints
{
	template <typename TElement>
	class IConstraint
	{
	public:
		virtual ~IConstraint() = default;

		virtual TElement tGetLowerBound(int iDimension) = 0;
		virtual TElement tGetUpperBound(int iDimension) = 0;

		virtual bool bIsFeasible(int iDimension, TElement tValue) = 0;
	};//class IContraint
}//namespace Constraints
