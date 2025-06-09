#pragma once
#include <chrono>

class Time
{
	using clock = std::chrono::steady_clock;

public:
	static void Update();
	static float GetDeltaTime() { return deltaTime; }

private:
	static float deltaTime;
};

