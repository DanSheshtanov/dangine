#pragma once

class Time
{
public:
	static void Update();
	static float GetDeltaTime() { return deltaTime; }
	static void ThreadSleep(int milliseconds);

private:
	static float deltaTime;
};

