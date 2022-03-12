#pragma once

#include "Generator.h"

#include <random>

namespace Generators
{
	class CBinaryRandomGenerator : public CGenerator<bool>
	{
	public:
		CBinaryRandomGenerator(IConstraint<bool> &cConstraint, mt19937 &cRandomEngine);

		virtual void vFill(vector<bool> &vSolution);

	private:
		mt19937 &c_random_engine;
	};//class CBinaryRandomGenerator : public CGenerator<bool>
}//namespace Generators