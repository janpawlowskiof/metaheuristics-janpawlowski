#pragma once

#include "Constraint.h"

#include <Constraint.h>

namespace ConstraintsCLI
{
	public ref class CBinaryConstraint : public IConstraint<bool>
	{
	public:
		CBinaryConstraint(Constraints::IConstraint<bool> &cNativeBinaryConstraint);

		virtual bool tGetLowerBound(int iDimension) { return c_native_binary_constraint.tGetLowerBound(iDimension); }

		virtual bool tGetUpperBound(int iDimension) { return c_native_binary_constraint.tGetUpperBound(iDimension); }

		virtual bool bIsFeasible(int iDimension, bool tValue) { return c_native_binary_constraint.bIsFeasible(iDimension, tValue); }

	private:
		Constraints::IConstraint<bool> &c_native_binary_constraint;
	};//public ref class CBinaryConstraint : IConstraint<bool>
}//namespace ConstraintsCLI