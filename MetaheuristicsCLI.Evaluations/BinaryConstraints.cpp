#include "BinaryConstraints.h"

using namespace ConstraintsCLI;

CBinaryConstraint::CBinaryConstraint(Constraints::IConstraint<bool> &cNativeBinaryConstraint)
	: c_native_binary_constraint(cNativeBinaryConstraint)
{

}//CBinaryConstraint::CBinaryConstraint(Constraints::IConstraint<bool> &cNativeBinaryConstraint)