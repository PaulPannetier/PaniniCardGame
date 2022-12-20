
#include "Button.hpp"

using namespace std;
using namespace sf;

Button::Button()
{
	this->isHover = oldOnMouseClick = false;
}

Button::Button(const Rectangle& hitbox, void (*OnClick)(const Button& button))
{
	this->isHover = oldOnMouseClick = false;
	this->hitbox = Rectangle(hitbox);
	this->OnClick = OnClick;
}

void Button::Update(RenderWindow& window)
{
	Vector2i tmp = Mouse::getPosition(window);
	Vector2f mousePosition = Vector2f(tmp.x, tmp.y);
	isHover = this->hitbox.Contain(mousePosition);
	bool onMouseClick = Mouse::isButtonPressed(Mouse::Button::Left);
	if (isHover && !oldOnMouseClick && onMouseClick)
	{
		OnClick(*this);
	}
	oldOnMouseClick = onMouseClick;
}

void Button::Draw(RenderWindow& window)
{
	Color color = isHover ? Color::Red : Color::Green;
	Rectangle::Draw(window, this->hitbox, color);
}

string Button::ToString() const
{
	return "Button";
}

