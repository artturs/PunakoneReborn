#include "timer.h"
#include <iostream>
#include <chrono>
#include <cmath>

#pragma optimize("", off)


Timer::Timer()
{
	_StartTimePoint = std::chrono::high_resolution_clock::now();
}

Timer::~Timer()
{

}

void Timer::Stop()
{
	_EndTimePoint = std::chrono::high_resolution_clock::now();

	_Duration = _EndTimePoint - _StartTimePoint;

	_Seconds = floor(_Duration.count());

	_MilliSeconds = (_Duration.count() * 1000.0f) - (_Seconds * 1000.0f);

	std::wcout << "\n Timer took: " << _Seconds << "s " << _MilliSeconds << "ms. \n";

}

#pragma optimize("", on)
