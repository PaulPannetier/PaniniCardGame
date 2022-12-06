#ifndef COLLIDER2D_HPP
#define COLLIDER2D_HPP

#include <SFML/Graphics.hpp>
#include "Useful.hpp"

class Collider2D : Object
{
public:
	Vector2 center;

	virtual bool Contain(const Vector2& point) const;
	std::string ToString() const;
};

class Rectangle : public Collider2D
{
public:
	Vector2 size;

	static void Draw(const Vector2 &center, const Vector2 &size, const sf::Color &color);
	bool Contain(const Vector2& point) const override;
	std::string ToString() const override;
};

class Circle : public Collider2D
{
public:
	float radius;

	static void Draw(const Vector2& center, float radius, sf::Color color);
	bool Contain(const Vector2& point) const override;
	std::string ToString() const override;
};

#endif