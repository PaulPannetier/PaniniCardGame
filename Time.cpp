
#include "Time.hpp"
#include <iostream>

using namespace std;
using namespace sf;

float TimeManager::DeltaTime(float dt, bool getOnly)
{
	static float deltaTime;
	if (getOnly)
	{
		return deltaTime;
	}
	deltaTime = dt;
	return deltaTime;
}

float TimeManager::DeltaTime()
{
	return DeltaTime(0, true);
}

void TimeManager::Update(RenderWindow& window)
{
	static Clock deltaClock;
	float dt = deltaClock.restart().asSeconds();
	DeltaTime(dt, false);
}