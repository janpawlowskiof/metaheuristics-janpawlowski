#pragma once

#include "BinaryGenerators.h"
#include "SamplingOptimizer.h"

using namespace Generators;

namespace Optimizers
{
	class CBinaryRandomSearch : public CSamplingOptimizer<bool>
	{
	public:
		CBinaryRandomSearch(IEvaluation<bool> &cEvaluation, IStopCondition &cStopCondition, mt19937 &cRandomEngine);

	private:
		CBinaryRandomGenerator c_random_generation;
	};//class CBinaryRandomSearch : public CSamplingOptimizer<bool>
}//namespace Optimizers