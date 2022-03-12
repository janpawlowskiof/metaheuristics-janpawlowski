#include "RealConstraints.h"

using namespace Constraints;


CRealBoundingBoxConstraint::CRealBoundingBoxConstraint(double dLowerBound, double dUpperBound, int iSize)
	: v_lower_bounds((size_t)iSize, dLowerBound), v_upper_bounds((size_t)iSize, dUpperBound)
{

}//CRealBoundingBoxConstraint::CRealBoundingBoxConstraint(double dLowerBound, double dUpperBound, int iSize)

CRealBoundingBoxConstraint::CRealBoundingBoxConstraint(vector<double> &vLowerBounds, vector<double> &vUpperBounds)
	: v_lower_bounds(vLowerBounds), v_upper_bounds(vUpperBounds)
{

}//CRealBoundingBoxConstraint::CRealBoundingBoxConstraint(vector<double> &vLowerBounds, vector<double> &vUpperBounds)