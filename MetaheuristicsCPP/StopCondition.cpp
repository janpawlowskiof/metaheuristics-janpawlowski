#include "StopConditions.h"

using namespace StopConditions;

CStopCondition::CStopCondition(double dMaxValue, double dEpsilon)
	: d_max_value(dMaxValue), d_epsilon(dEpsilon)
{

}//CStopCondition::CStopCondition(double dMaxValue, double dEpsilon)

bool CStopCondition::bStop(double dBestValue, long long iIterationNumber, long long iFFE, clock_t tStartTime)
{
	if (abs(dBestValue - d_max_value) <= d_epsilon)
		return true;

	return b_stop(iIterationNumber, iFFE, tStartTime);
}//bool CStopCondition::bStop(double dBestValue, long long iIterations, long long iFFE, clock_t tStartTime)