#include "RealConstraints.h"

using namespace ConstraintsCLI;

CRealConstraint::CRealConstraint(Constraints::IConstraint<double> &cNativeRealConstraint)
	: c_native_real_constraint(cNativeRealConstraint)
{

}//CRealConstraint::CRealConstraint(Constraints::IConstraint<double> &cNativeRealConstraint)