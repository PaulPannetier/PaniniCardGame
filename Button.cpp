
#include "Button.hpp"
#include "InputManager.hpp"

using namespace std;
using namespace sf;

Button::Button()
{
	this->isHover = false;
}

Button::Button(const Rectangle& hitbox, void (*OnClick)(const Button& button))
{
	this->isHover = false;
	this->hitbox = Rectangle(hitbox);
	this->OnClick = OnClick;
}

void Button::Update(RenderWindow& window)
{
	isHover = this->hitbox.Contains(InputManager::Instance().MousePosition());
	if (isHover && InputManager::Instance().GetKeyDown(Mouse::Button::Left))
	{
		OnClick(*this);
	}
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

