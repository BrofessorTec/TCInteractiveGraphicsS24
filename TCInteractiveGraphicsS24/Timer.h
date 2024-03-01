#pragma once
#include "BaseObject.h"
#include <ctime>
#include <ratio>
#include <chrono>

class Timer :
    public BaseObject
{
protected:
	std::chrono::high_resolution_clock::time_point startTime, endTime;

public:
	Timer();
	void StartTiming();
	double GetElapsedTimeInSeconds();
};

