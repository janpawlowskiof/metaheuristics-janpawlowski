#pragma once

#include "Optimizer.h"
#include "RealGenerators.h"
#include "RealMutationES11Adaptation.h"

#include <random>

using namespace Generators;
using namespace Mutations;

using namespace std;

namespace Optimizers
{
	class CRealEvolutionStrategy11 : public COptimizer<double>
	{
	public:
		CRealEvolutionStrategy11(IEvaluation<double> &cEvaluation, IStopCondition &cStopCondition, IRealMutationES11Adaptation &cMutationAdaptation, mt19937 &cRandomEngine);

	protected:
		virtual void v_initialize(clock_t tStartTime);
		virtual bool b_run_iteration(long long iIterationNumber, clock_t tStartTime);

	private:
		IRealMutationES11Adaptation &c_mutation_adaptation;
		mt19937 &c_random_engine;
	};//class CRealEvolutionStrategy11 : public COptimizer<double>
}//namespace Optimizers