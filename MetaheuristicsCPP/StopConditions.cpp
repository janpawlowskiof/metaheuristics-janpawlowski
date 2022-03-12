#include "StopConditions.h"

using namespace StopConditions;


CIterationsStopCondition::CIterationsStopCondition(double dMaxValue, long long iMaxIterationNumber, double dEpsilon)
	: CStopCondition(dMaxValue, dEpsilon), i_max_iteration_number(iMaxIterationNumber)
{

}//CIterationsStopCondition::CIterationsStopCondition(double dMaxValue, long long iMaxIterationNumber, double dEpsilon)

bool CIterationsStopCondition::b_stop(long long iIterationNumber, long long iFFE, clock_t tStartTime)
{
	return iIterationNumber >= i_max_iteration_number;
}//bool CIterationsStopCondition::b_stop(long long iIterationNumber, long long iFFE, clock_t tStartTime)


CFFEStopCondition::CFFEStopCondition(double dMaxValue, long long iMaxFFE, double dEpsilon)
	: CStopCondition(dMaxValue, dEpsilon), i_max_ffe(iMaxFFE)
{

}//CFFEStopCondition::CFFEStopCondition(double dMaxValue, long long iMaxFFE, double dEpsilon)

bool CFFEStopCondition::b_stop(long long iIterationNumber, long long iFFE, clock_t tStartTime)
{
	return iFFE >= i_max_ffe;
}//bool CFFEStopCondition::b_stop(long long iIterationNumber, long long iFFE, clock_t tStartTime)


CRunningTimeStopCondition::CRunningTimeStopCondition(double dMaxValue, double dMaxRunningTime, double dEpsilon)
	: CStopCondition(dMaxValue, dEpsilon), d_max_running_time(dMaxRunningTime)
{

}//CRunningTimeStopCondition::CRunningTimeStopCondition(double dMaxValue, double dMaxRunningTime, double dEpsilon)

bool CRunningTimeStopCondition::b_stop(long long iIterationNumber, long long iFFE, clock_t tStartTime)
{
	return TimeUtils::dCalculateSeconds(tStartTime) >= d_max_running_time;
}//bool CRunningTimeStopCondition::b_stop(long long iIterationNumber, long long iFFE, clock_t tStartTime)