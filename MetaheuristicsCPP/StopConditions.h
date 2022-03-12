#pragma once

#include "StopCondition.h"
#include "TimeUtils.h"

#include <cfloat>
#include <ctime>

namespace StopConditions
{
	class CIterationsStopCondition : public CStopCondition
	{
	public:
		CIterationsStopCondition(double dMaxValue, long long iMaxIterationNumber, double dEpsilon = DBL_EPSILON);

	protected:
		virtual bool b_stop(long long iIterationNumber, long long iFFE, clock_t tStartTime);

	private:
		long long i_max_iteration_number;
	};//class CIterationsStopCondition : public CStopCondition


	class CFFEStopCondition : public CStopCondition
	{
	public:
		CFFEStopCondition(double dMaxValue, long long iMaxFFE, double dEpsilon = DBL_EPSILON);

	protected:
		virtual bool b_stop(long long iIterationNumber, long long iFFE, clock_t tStartTime);

	private:
		long long i_max_ffe;
	};//class CFFEStopCondition : public CStopCondition


	class CRunningTimeStopCondition : public CStopCondition
	{
	public:
		CRunningTimeStopCondition(double dMaxValue, double dMaxRunningTime, double dEpsilon = DBL_EPSILON);

	protected:
		virtual bool b_stop(long long iIterationNumber, long long iFFE, clock_t tStartTime);

	private:
		double d_max_running_time;
	};//class CRunningTimeStopCondition : public CStopCondition
}//namespace StopConditions