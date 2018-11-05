#include "timer.h"

namespace engine {
	double Timer::GetCurrentForMilliseconds(){
		LARGE_INTEGER largeInteger;
		QueryPerformanceCounter(&largeInteger);
		double count = double(largeInteger.QuadPart);

		return count;
	}

	double Timer::GetCurrentForSecondes(){
		return GetCurrentForMilliseconds() / 1000.0;
	}
}