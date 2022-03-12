#include "RealGenerators.h"

using namespace Generators;


CRealRandomGenerator::CRealRandomGenerator(IConstraint<double> &cConstraint, mt19937 &cRandomEngine)
	: CGenerator<double>(cConstraint), c_random_engine(cRandomEngine)
{

}//CRealRandomGenerator::CRealRandomGenerator(IConstraint<double> &cConstraint, mt19937 &cRandomEngine)

void CRealRandomGenerator::vFill(vector<double> &vSolution)
{
	for (size_t i = 0; i < vSolution.size(); i++)
	{
		uniform_real_distribution<double> c_distr(c_constraint.tGetLowerBound((int)i), c_constraint.tGetUpperBound((int)i));
		vSolution[i] = c_distr(c_random_engine);
	}//for (size_t i = 0; i < vSolution.size(); i++)
}//void CRealRandomGenerator::vFill(vector<double> &vSolution)