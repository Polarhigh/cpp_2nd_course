#ifndef _TIME_UTILS_H_
#define _TIME_UTILS_H_

#include <iostream>
#include <functional>
#include <chrono>

// замеряет время исполнения ф-ии execFunc
void GetExecutionTime(const std::function<void()>& execFunc, long long& outMs, long long& outNs)
{
	using namespace std::chrono;

	auto startTime = high_resolution_clock::now();
	execFunc();
	auto endTime = high_resolution_clock::now() - startTime;

	outMs = duration_cast<milliseconds>(endTime).count();
	outNs = duration_cast<nanoseconds>(endTime).count();
}

// форматированный вывод времени исполнения
void PrintExecutionTime(const std::string& frontText, long long ms, long long ns)
{
	std::cout << frontText.c_str();
	if (ms > 0ll)
		std::cout << ms << " ms";
	else
		std::cout << ns << " ns";
	std::cout << std::endl;
}

#endif // _TIME_UTILS_H_