#pragma once

#include <ctime>

namespace TimeUtils
{
	double dCalculateSeconds(clock_t tFrom, clock_t tTo = clock());
}//namespace TimeUtils