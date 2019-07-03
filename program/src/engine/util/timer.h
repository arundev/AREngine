#ifndef ENGINE_UTIL_TIMER_H
#define ENGINE_UTIL_TIMER_H

#if win32
#include "time.h"
#endif

#include "engine_pch.h"
#include "singleton.h"

namespace engine {
	class Timer : public Singleton<Timer> {
	public:
		static double GetCurrentForSecondes();
		static double GetCurrentForMilliseconds();
	protected:
	private:
	};
}

#endif