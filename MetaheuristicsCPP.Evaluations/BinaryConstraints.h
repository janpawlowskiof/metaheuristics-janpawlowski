#pragma once

#include "Constraint.h"

namespace Constraints
{
	class CBinaryNoConstraint : public IConstraint<bool>
	{
	public:
		virtual bool tGetLowerBound(int iDimension) { return false; }
		virtual bool tGetUpperBound(int iDimension) { return true; }

		virtual bool bIsFeasible(int iDimension, bool tValue) { return true; }
	};//class CBinaryNoConstraint : public IConstraint<bool>
}//namespace Constraints