#pragma once

#include <chrono>


class Timer
{
	std::chrono::steady_clock::time_point start, end;

public:
	Timer();
	~Timer();
};