#pragma once

#include "Constraint.h"

#include <Constraint.h>

namespace ConstraintsCLI
{
	public ref class CRealConstraint : public IConstraint<double>
	{
	public:
		CRealConstraint(Constraints::IConstraint<double> &cNativeRealConstraint);

		virtual double tGetLowerBound(int iDimension) { return c_native_real_constraint.tGetLowerBound(iDimension); }

		virtual double tGetUpperBound(int iDimension) { return c_native_real_constraint.tGetUpperBound(iDimension); }

		virtual bool bIsFeasible(int iDimension, double tValue) { return c_native_real_constraint.bIsFeasible(iDimension, tValue); }

	private:
		Constraints::IConstraint<double> &c_native_real_constraint;
	};//public ref class CRealConstraint : public IConstraint<double>
}//namespace ConstraintsCLI