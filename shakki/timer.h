#pragma once
#include <chrono>

class Timer
{
public:
	Timer();
	~Timer();
	void Stop();

	std::chrono::time_point< std::chrono::steady_clock> _StartTimePoint;
	std::chrono::time_point< std::chrono::steady_clock> _EndTimePoint;
	std::chrono::duration<float> _Duration;
	float _Seconds;
	float _MilliSeconds;

private:

	
};

