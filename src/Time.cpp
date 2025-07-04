#include <thread>
#include <chrono>

#include "Time.h"

#define clock std::chrono::steady_clock

float Time::deltaTime = 0;

void Time::Update()
{
	using namespace std;
	static clock::time_point last = clock::now();

	clock::time_point now = clock::now();
	deltaTime = chrono::duration_cast<chrono::microseconds>(now - last).count() / 1000000.0f;
	last = now;
}

void Time::ThreadSleep(int milliseconds)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
