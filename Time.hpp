#ifndef TIME_HPP
#define TIME_HPP

#include <SFML/Graphics.hpp>

class TimeManager
{
private:

	static float DeltaTime(float dt, bool get);

public:

	static float DeltaTime();
	static void Update(sf::RenderWindow& window);

};

#endif