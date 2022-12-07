#include <SFML/Graphics.hpp>

#include "Collider2D.hpp"

using namespace std;
using namespace sf;

string Collider2D::ToString() const
{
	return "Collider2D";
}

void Rectangle::Draw(sf::RenderWindow& window, const Vector2f& center, const Vector2f& size, const sf::Color& color)
{
	sf::RectangleShape rec = sf::RectangleShape();
	rec.setFillColor(color);
	//acess to mainwindow
}

bool Rectangle::Contain(const Vector2f& point) const
{
	return point.x >= center.x - size.x * 0.5 && point.x <= center.x + size.x * 0.5 &&
		point.y >= center.y - size.x * 0.5 && point.y <= center.y + size.y * 0.5;
}

string Rectangle::ToString() const
{
	ostringstream os;
	os << "{ center : (" << center.x << ", " << center.y  << "), size : (" << size.x << ", " << size.y << ") }";
	return os.str();
}



void Circle::Draw(sf::RenderWindow& window, const Vector2f& center, float radius, sf::Color color)
{
	CircleShape c = CircleShape(radius, 60);
	c.setFillColor(color);
	c.setPosition(center - Vector2f(radius, radius));
	window.draw(c);
}

bool Circle::Contain(const Vector2f& point) const
{
	return Useful::SqrDistance(center, point) <= radius * radius;
}

string Circle::ToString() const
{
	ostringstream os;
	os << "{ center : (" << center.x << ", " << center.y << "), radius : " << radius << " }";
	return os.str();
}