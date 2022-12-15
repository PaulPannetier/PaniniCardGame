
#include "Button.hpp"

using namespace std;
using namespace sf;

Button::Button()
{
	this->OnClick = NULL;
	isHover = false;
	this->collider = NULL;
}

Button::Button(void (*OnClick)(Button button), Collider2D* collider)
{
	this->OnClick = OnClick;
	isHover = false;
	this->collider = collider;
}

void Button::Update(RenderWindow& window)
{
	Vector2i tmp = Mouse::getPosition(window);
	Vector2f mousePos = Vector2f(tmp.x, tmp.y);
	this->isHover = collider->Contain(mousePos);
}

void Button::Draw(RenderWindow& window)
{

}

string Button::ToString() const
{
	return "Button";
}

RectangleButton::RectangleButton() : Button()
{

}

RectangleButton::RectangleButton(Rectangle rec, void (*OnClick)(Button button)) : Button(OnClick, &rec)
{

}

void RectangleButton::Update(RenderWindow& window)
{
	Button::Update(window);
}

void RectangleButton::Draw(RenderWindow& window)
{
	Rectangle* rec = (Rectangle*)(&collider);//marche pas
	Color c = isHover ? Color::Red : Color::Green;
	Rectangle::Draw(window, *rec, c);
}

string RectangleButton::ToString() const
{
	return "RectangleButton";
}

CircleButton::CircleButton() : Button()
{

}

CircleButton::CircleButton(Circle circle, void (*OnClick)(Button button)) : Button(OnClick, &circle)
{

}

void CircleButton::Update(RenderWindow& window)
{
	Button::Update(window);
}

void CircleButton::Draw(RenderWindow& window)
{
	Circle* circle = (Circle*)(&collider);
	Color c = isHover ? Color::Red : Color::Green;
	Circle::Draw(window, *circle, c);
}

string CircleButton::ToString() const
{
	return "CirceButton";
}



