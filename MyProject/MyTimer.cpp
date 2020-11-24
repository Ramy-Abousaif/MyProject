#include "MyTimer.h"

using namespace std::chrono;

MyTimer::MyTimer() noexcept
{
	last = steady_clock::now();
}

//checks time elapsed since the last time mark was called
float MyTimer::Mark() noexcept
{
	const auto old = last;
	last = steady_clock::now();
	const duration<float> frameTime = last - old;
	return frameTime.count();
}

//same function as mark without resetting mark
float MyTimer::Peek() const noexcept
{
	return duration<float>(steady_clock::now() - last).count();
}
