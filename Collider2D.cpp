#include <SFML/Graphics.hpp>

#include "Collider2D.hpp"

using namespace std;
using namespace sf;

Collider2D::Collider2D()
{

}

Collider2D::Collider2D(Vector2f center)
{
	this->center = Vector2f(center);
}

string Collider2D::ToString() const
{
	return "Collider2D";
}

Rectangle::Rectangle() : Collider2D()
{

}

Rectangle::Rectangle(const Vector2f& center, const Vector2f& size) : Collider2D(center)
{
	//this->center = Vector2f(center);
	this->size = Vector2f(size);
}

Rectangle::Rectangle(const Rectangle& rec) : Collider2D(rec.center)
{
	this->center = Vector2f(rec.center);
	this->size = Vector2f(rec.size);
}

void Rectangle::Draw(RenderWindow& window, const Vector2f& center, const Vector2f& size, const Color& color)
{
	RectangleShape rec = RectangleShape(size);
	rec.setFillColor(color);
	rec.setPosition(center - (size * 0.5f));
	window.draw(rec);
}

void Rectangle::Draw(RenderWindow& window, const Rectangle& rec, const Color& color)
{
	Rectangle::Draw(window, rec.center, rec.size, color);
}

void Rectangle::DrawWire(RenderWindow& window, const Vector2f& center, const Vector2f& size, const Color& color, float thinckness)
{
	Rectangle::Draw(window, Vector2f(center.x, center.y - size.y * 0.5f), Vector2f(size.x + thinckness, thinckness), color);
	Rectangle::Draw(window, Vector2f(center.x, center.y + size.y * 0.5f), Vector2f(size.x + thinckness, thinckness), color);
	Rectangle::Draw(window, Vector2f(center.x - size.x * 0.5f, center.y), Vector2f(thinckness, size.y + thinckness), color);
	Rectangle::Draw(window, Vector2f(center.x + size.x * 0.5f, center.y), Vector2f(thinckness, size.y + thinckness), color);
}

void Rectangle::DrawWire(RenderWindow& window, const Rectangle& rec, const Color& color, float thinckness)
{
	Rectangle::DrawWire(window, rec.center, rec.size, color, thinckness);
}

bool Rectangle::Contain(const Vector2f& point) const
{
	return point.x >= center.x - size.x * 0.5 && point.x <= center.x + size.x * 0.5 &&
		point.y >= center.y - size.y * 0.5 && point.y <= center.y + size.y * 0.5;
}

string Rectangle::ToString() const
{
	ostringstream os;
	os << "{ center : (" << center.x << ", " << center.y << "), size : (" << size.x << ", " << size.y << ") }";
	return os.str();
}

Circle::Circle() : Collider2D()
{

}

Circle::Circle(const Circle& circle) : Collider2D(circle.center)
{
	//this->center = Vector2f(circle.center);
	this->radius = circle.radius;
}

Circle::Circle(const Vector2f& center, float radius) : Collider2D(center)
{
	//this->center = Vector2f(center);
	this->radius = radius;
}

void Circle::Draw(RenderWindow& window, const Vector2f& center, float radius, const Color& color)
{
	CircleShape c = CircleShape(radius, 60);
	c.setFillColor(color);
	c.setPosition(center - Vector2f(radius, radius));
	window.draw(c);
}

void Circle::Draw(RenderWindow& window, const Circle& circle, const Color& color)
{
	Circle::Draw(window, circle.center, circle.radius, color);
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