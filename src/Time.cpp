#include "Time.h"

#include <chrono>
#include <thread>


#define clock std::chrono::steady_clock

float Time::deltaTime = 0;
float Time::elapsedTime = 0;

void Time::Update()
{
	using namespace std::chrono;
	static clock::time_point last = clock::now();

	clock::time_point now = clock::now();
	deltaTime = duration_cast<microseconds>(now - last).count() / 1000000.0f;
	last = now;

	elapsedTime += deltaTime;
}

void Time::ThreadSleep(int milliseconds)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
