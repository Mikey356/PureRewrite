#pragma once
#include <chrono>
#include <string>
struct Timer
{
	Timer(const std::string& name);
	~Timer();

	std::chrono::time_point<std::chrono::steady_clock> m_startTime;
	std::chrono::time_point<std::chrono::steady_clock> m_endTime;
	std::string m_name;
};