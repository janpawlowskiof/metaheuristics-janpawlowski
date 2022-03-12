#pragma once

#include "SamplingOptimizer.h"
#include "RealGenerators.h"

using namespace Generators;

namespace Optimizers
{
	class CRealRandomSearch : public CSamplingOptimizer<double>
	{
	public:
		CRealRandomSearch(IEvaluation<double> &cEvaluation, IStopCondition &cStopCondition, mt19937 &cRandomEngine);

	private:
		CRealRandomGenerator c_random_generation;
	};//class CRealRandomSearch : public CSamplingOptimizer<double>
}//namespace Optimizers