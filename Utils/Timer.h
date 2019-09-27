#pragma once

#include <iostream>
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;

//
static std::chrono::time_point<std::chrono::steady_clock> timePrev;
static std::chrono::time_point<std::chrono::steady_clock> timeCurr;

// Prep the timer
inline void TimerStart()
{
	timePrev = Clock::now();
	timeCurr = Clock::now();
}

//
inline double TimerGet()
{
	double dt; // delta time

	// Get delta time
	timeCurr = Clock::now();
	dt = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(timeCurr - timePrev).count() * 0.000000001;
	timePrev = timeCurr;

	return dt;
}
