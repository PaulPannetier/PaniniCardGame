#ifndef COLLIDER2D_HPP
#define COLLIDER2D_HPP

#include <SFML/Graphics.hpp>
#include "Useful.hpp"

class Collider2D : Object
{
public:
	sf::Vector2f center;

	virtual bool Contain(const sf::Vector2f& point) const = 0;
	std::string ToString() const;
};

class Rectangle : public Collider2D
{
public:
	sf::Vector2f size;

	static void Draw(sf::RenderWindow& window, const sf::Vector2f &center, const sf::Vector2f &size, const sf::Color &color);
	bool Contain(const sf::Vector2f& point) const override;
	std::string ToString() const override;
};

class Circle : public Collider2D
{
public:
	float radius;

	static void Draw(sf::RenderWindow& window, const sf::Vector2f& center, float radius, sf::Color color);
	bool Contain(const sf::Vector2f& point) const override;
	std::string ToString() const override;
};

#endif