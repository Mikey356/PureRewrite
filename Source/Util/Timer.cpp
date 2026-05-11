#include "Timer.h"
#include <iostream>

Timer::Timer(const std::string& name)
{
	m_name = name;
	m_startTime = std::chrono::steady_clock::now();
}

Timer::~Timer()
{
	m_endTime = std::chrono::steady_clock::now();

	std::chrono::duration<double, std::milli> duration = m_endTime - m_startTime;
	std::cout << m_name << " " << duration.count();
}