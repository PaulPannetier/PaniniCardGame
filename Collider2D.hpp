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
	static void Draw(sf::RenderWindow& window, const sf::Vector2f& center, const sf::Vector2f& size, const sf::Color& color);
	static void Draw(sf::RenderWindow& window, const Rectangle& rec, const sf::Color& color);
	static void DrawWire(sf::RenderWindow& window, const Rectangle& rec, const sf::Color& color, float thinckness = 3.0f);
	static void DrawWire(sf::RenderWindow& window, const sf::Vector2f& center, const sf::Vector2f& size, const sf::Color& color, float thinckness = 3.0f);

	sf::Vector2f size;

	Rectangle();
	Rectangle(const sf::Vector2f& center, const sf::Vector2f& size);
	Rectangle(const Rectangle& rec);

	bool Contain(const sf::Vector2f& point) const override;
	std::string ToString() const override;

	friend Rectangle operator*(Rectangle rec, float f)
	{
		return Rectangle(rec.center, rec.size * f);
	}

	friend Rectangle operator*(float f, Rectangle rec)
	{
		return rec * f;
	}
};

class Circle : public Collider2D
{
public:
	static void Draw(sf::RenderWindow& window, const sf::Vector2f& center, float radius, const sf::Color& color);
	static void Draw(sf::RenderWindow& window, const Circle& circle, const sf::Color& color);

	float radius;

	Circle();
	Circle(const sf::Vector2f& center, float radius);
	Circle(const Circle& circle);

	bool Contain(const sf::Vector2f& point) const override;
	std::string ToString() const override;

	friend Circle operator*(Circle c, float f)
	{
		return Circle(c.center, c.radius * f);
	}

	friend Circle operator*(float f, Circle c)
	{
		return c * f;
	}
};

#endif