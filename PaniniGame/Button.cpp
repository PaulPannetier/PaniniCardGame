
#include "Button.hpp"

using namespace std;
using namespace sf;

Button::Button()
{
	this->OnClick = NULL;
	isHover = oldIsMousePressed = false;
}

Button::Button(const Rectangle& rectangle, void (*OnClick)(Button& button))
{
	this->OnClick = OnClick;
	isHover = oldIsMousePressed = false;
	this->rectangle = Rectangle(rectangle);
}

void Button::Update(RenderWindow& window)
{
	Vector2i tmp = Mouse::getPosition(window);
	Vector2f mousePos = Vector2f(tmp.x, tmp.y);
	this->isHover = rectangle.Contain(mousePos);
	bool isMousePressed = Mouse::isButtonPressed(Mouse::Button::Left);
	if (isHover && !oldIsMousePressed && isMousePressed)
	{
		OnClick(*this);
	}
	oldIsMousePressed = isMousePressed;
}

void Button::Draw(RenderWindow& window)
{
	Color color = isHover ? Color::Red : Color::Green;
	Rectangle::Draw(window, rectangle, color);
}

string Button::ToString() const
{
	return "Button";
}

