#ifndef TEST_HPP
#define TEST_HPP

#include "Collider2D.hpp"

void TestCollider2D(sf::RenderWindow& window)
{
	Circle circle = Circle(sf::Vector2f(50.0f, 50.0f), 50.0f);
	Circle circle2 = Circle(circle);

	std::cout << "Draw a green circle in the top left corner" << std::endl;
	Circle::Draw(window, circle2, sf::Color::Green);

	circle2.center = sf::Vector2f(10.0f, 10.0f);
	float mag = Useful::Magnitude(circle2.center - sf::Vector2f(10.0f, 10.0f));
	std::cout << (mag < 0.0001f) << std::endl;
	circle2.radius = 8.457f;
	std::cout << ((8.457f - circle2.radius) < 0.0001f) << std::endl;

	Rectangle rec = Rectangle(sf::Vector2f(100.0, 250.0), sf::Vector2f(100, 150));
	Rectangle rec2 = Rectangle(rec);
	std::cout << "Draw a red rectangle at 100, 250 pixel" << std::endl;
	Rectangle::Draw(window, rec, sf::Color::Red);

	rec2.center = sf::Vector2f(10, 10);
	std::cout << (Useful::Magnitude(rec2.center - sf::Vector2f(10, 10)) < 0.0001f) << std::endl;

	rec2.size = sf::Vector2f(120, 12);
	std::cout << (Useful::Magnitude(rec2.size - sf::Vector2f(120, 12)) < 0.0001f) << std::endl;
}


#endif