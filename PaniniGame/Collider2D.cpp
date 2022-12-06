#include <SFML/Graphics.hpp>
#include "Collider2D.hpp"

using namespace std;

string Collider2D::ToString() const
{
	return "Collider2D";
}

void Rectangle::Draw(const Vector2& center, const Vector2& size, const sf::Color& color)
{
	sf::RectangleShape rec = sf::RectangleShape();
	rec.setFillColor(color);
	//acess to mainwindow
}

bool Rectangle::Contain(const Vector2& point) const
{
	return point.x >= center.x - size.x * 0.5 && point.x <= center.x + size.x * 0.5 &&
		point.y >= center.y - size.x * 0.5 && point.y <= center.y + size.y * 0.5;
}

string Rectangle::ToString() const
{
	ostringstream os;
	os << "{ center : " << this->center.ToString() << ", size : " << this->size.ToString() << " }";
	return os.str();
}



void Circle::Draw(const Vector2& center, float radius, sf::Color color)
{
	sf::CircleShape c = sf::CircleShape();
	c.setFillColor(color);
	//acess to mainwindow
}

bool Circle::Contain(const Vector2& point) const
{
	return center.SqrDistance(point) <= radius * radius;
}

string Circle::ToString() const
{
	ostringstream os;
	os << "{ center : " << this->center.ToString() << ", radius : " << this->radius << " }";
	return os.str();
}