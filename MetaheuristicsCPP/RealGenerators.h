#pragma once

#include "Generator.h"

#include <random>

namespace Generators
{
	class CRealRandomGenerator : public CGenerator<double>
	{
	public:
		CRealRandomGenerator(IConstraint<double> &cConstraint, mt19937 &cRandomEngine);

		virtual void vFill(vector<double> &vSolution);

	private:
		mt19937 &c_random_engine;
	};//class CRealRandomGenerator : public CGenerator<double>
}//namespace Generators