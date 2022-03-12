#pragma once

#include "OptimizationResult.h"
#include "StopCondition.h"
#include "TimeUtils.h"

#include <ctime>
#include <Evaluation.h>
#include <random>
#include <vector>

using namespace StopConditions;

using namespace Evaluations;
using namespace std;

namespace Optimizers
{
	template <typename TElement>
	class IOptimizer
	{
	public:
		virtual ~IOptimizer() = default;

		virtual void vInitialize() = 0;
		virtual bool bRunIteration() = 0;
		virtual bool bShouldStop() = 0;

		virtual void vRun() = 0;

		virtual COptimizationResult<TElement> *pcGetResult() = 0;
	};//class IOptimizer


	template <typename TElement>
	class COptimizer : public IOptimizer<TElement>
	{
	public:
		COptimizer(IEvaluation<TElement> &cEvaluation, IStopCondition &cStopCondition)
			: c_evaluation(cEvaluation), c_stop_condition(cStopCondition)
		{
			pc_result = nullptr;
		}//COptimizer(IEvaluation<TElement> &cEvaluation, IStopCondition &cStopCondition)

		COptimizer(const COptimizer<TElement> &cOther) = delete;
		COptimizer(COptimizer<TElement> &&cOther) = delete;

		virtual ~COptimizer()
		{
			delete pc_result;
		}//virtual ~COptimizer()

		virtual void vInitialize() final
		{
			delete pc_result;
			pc_result = nullptr;

			i_iteration_number = 0;
			t_start_time = clock();

			v_initialize(t_start_time);
		}//virtual void vInitialize() final

		virtual bool bRunIteration() final
		{
			bool b_best_updated = b_run_iteration(i_iteration_number, t_start_time);
			i_iteration_number++;

			return b_best_updated;
		}//virtual void vRunIteration() final

		virtual bool bShouldStop() final
		{
			double d_best_value = pc_result != nullptr ? pc_result->dGetBestValue() : -DBL_MAX;

			return c_stop_condition.bStop(d_best_value, i_iteration_number, c_evaluation.iGetFFE(), t_start_time);
		}//virtual bool bShouldStop() final

		virtual void vRun()
		{
			vInitialize();

			while (!bShouldStop())
			{
				bRunIteration();
			}//while (!bShouldStop())
		}//virtual void vRun()

		virtual COptimizationResult<TElement> *pcGetResult() { return pc_result; }

		COptimizer<TElement>& operator=(const COptimizer<TElement> &cOther) = delete;
		COptimizer<TElement>& operator=(COptimizer<TElement> &&cOther) = delete;

	protected:
		virtual void v_initialize(clock_t tStartTime) = 0;
		virtual bool b_run_iteration(long long iIterationNumber, clock_t tStartTime) = 0;
		
		bool b_check_new_best(vector<TElement> &vSolution, double dValue, bool bOnlyImprovements = true)
		{
			bool b_best_updated = false;

			if (pc_result == nullptr || dValue > pc_result->dGetBestValue() || dValue == pc_result->dGetBestValue() && !bOnlyImprovements)
			{
				delete pc_result;
				pc_result = new COptimizationResult<TElement>(dValue, vSolution, i_iteration_number, c_evaluation.iGetFFE(), TimeUtils::dCalculateSeconds(t_start_time));

				b_best_updated = true;
			}//if (pc_result == nullptr || dValue > pc_result->dGetBestValue() || dValue == pc_result->dGetBestValue() && !bOnlyImprovements)

			return b_best_updated;
		}//void v_check_new_best(vector<TElement> &vSolution, double dValue)

		IEvaluation<TElement> &c_evaluation;
		IStopCondition &c_stop_condition;

		COptimizationResult<TElement> *pc_result;

	private:
		long long i_iteration_number;
		clock_t t_start_time;
	};//class COptimizer : public IOptimizer<TElement>
}//namespace Optimizers

