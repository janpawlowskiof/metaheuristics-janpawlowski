#pragma once

#include <vector>

using namespace std;

namespace Optimizers
{
	template <typename TElement>
	class COptimizationResult
	{
	public:
		COptimizationResult(double dBestValue, vector<TElement> vBestSolution, long long iBestIteration, long long iBestFFE, double dBestTime)
			: d_best_value(dBestValue), v_best_solution(vBestSolution), i_best_iteration(iBestIteration), i_best_ffe(iBestFFE), d_best_time(dBestTime)
		{

		}//COptimizationResult(double dBestValue, vector<TElement> vBestSolution, long long iBestIteration, long long iBestFFE, double dBestTime)

		double dGetBestValue() { return d_best_value; }
		vector<TElement> &vGetBestSolution() { return v_best_solution; }

		long long iGetBestIteration() { return i_best_iteration; }
		long long iGetBestFFE() { return i_best_ffe; }
		double dGetBestTime() { return d_best_time; }

	private:
		double d_best_value;
		vector<TElement> v_best_solution;

		long long i_best_iteration;
		long long i_best_ffe;
		double d_best_time;
	};//class COptimizationResult
}//namespace Optimizers
