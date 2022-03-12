#include "TimeUtils.h"

double TimeUtils::dCalculateSeconds(clock_t tFrom, clock_t tTo)
{
	return (double)(tTo - tFrom) / CLOCKS_PER_SEC;
}//double TimeUtils::dCalculateSeconds(clock_t tFrom, clock_t tTo)