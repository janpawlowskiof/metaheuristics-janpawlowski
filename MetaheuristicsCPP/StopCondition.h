#pragma once

#include <cfloat>
#include <cmath>
#include <ctime>

namespace StopConditions
{
	class IStopCondition
	{
	public:
		virtual ~IStopCondition() = default;

		virtual bool bStop(double dBestValue, long long iIterationNumber, long long iFFE, clock_t tStartTime) = 0;
	};//class IStopCondition


	class CStopCondition : public IStopCondition
	{
	public:
		CStopCondition(double dMaxValue, double dEpsilon = DBL_EPSILON);

		virtual bool bStop(double dBestValue, long long iIterationNumber, long long iFFE, clock_t tStartTime) final;

	protected:
		virtual bool b_stop(long long iIterationNumber, long long iFFE, clock_t tStartTime) = 0;

	private:
		double d_max_value;
		double d_epsilon;
	};//class CStopCondition : public IStopCondition
}//namespace StopConditions