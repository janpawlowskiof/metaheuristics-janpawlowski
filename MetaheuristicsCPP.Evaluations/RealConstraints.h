#pragma once

#include "Constraint.h"

#include <vector>

using namespace std;

namespace Constraints
{
	class CRealBoundingBoxConstraint : public IConstraint<double>
	{
	public:
		CRealBoundingBoxConstraint(double dLowerBound, double dUpperBound, int iSize);
		CRealBoundingBoxConstraint(vector<double> &vLowerBounds, vector<double> &vUpperBounds);

		virtual double tGetLowerBound(int iDimension) { return v_lower_bounds[(size_t)iDimension]; }
		virtual double tGetUpperBound(int iDimension) { return v_upper_bounds[(size_t)iDimension]; }

		virtual bool bIsFeasible(int iDimension, double tValue) { return tGetLowerBound(iDimension) <= tValue && tValue <= tGetUpperBound(iDimension); }

	private:
		vector<double> v_lower_bounds;
		vector<double> v_upper_bounds;
	};//class CRealBoundingBoxConstraint : public IConstraint<double>
}//namespace Constraints