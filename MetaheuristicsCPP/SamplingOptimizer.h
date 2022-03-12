#pragma once

#include "Generator.h"
#include "Optimizer.h"

#include <vector>

using namespace Generators;

using namespace std;

namespace Optimizers
{
	template <typename TElement>
	class CSamplingOptimizer : public COptimizer<TElement>
	{
	public:
		CSamplingOptimizer(IEvaluation<TElement> &cEvaluation, IStopCondition &cStopCondition, IGenerator<TElement> &cGeneration)
			: COptimizer<TElement>(cEvaluation, cStopCondition), c_generation(cGeneration)
		{

		}//CSamplingOptimizer(IEvaluation<TElement> &cEvaluation, IStopCondition &cStopCondition, IGeneration<TElement> &cGeneration)

	protected:
		virtual void v_initialize(clock_t tStartTime) { }

		virtual bool b_run_iteration(long long iIterationNumber, clock_t tStartTime)
		{
			vector<TElement> *pv_solution = c_generation.pvCreate(this->c_evaluation.iGetSize());
			double d_value = this->c_evaluation.dEvaluate(*pv_solution);

			bool b_best_updated = this->b_check_new_best(*pv_solution, d_value);

			delete pv_solution;

			return b_best_updated;
		}//virtual bool b_run_iteration(long long iIterationNumber, clock_t tStartTime)

	private:
		IGenerator<TElement> &c_generation;
	};//class CSamplingOptimizer : public COptimizer<TElement>
}//namespace Optimizers
