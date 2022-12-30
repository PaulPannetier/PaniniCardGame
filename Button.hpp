#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Useful.hpp"
#include "Collider2D.hpp"

class Button : Object
{
private:
	bool isHover;

public:

	Rectangle hitbox;
	void (*OnClick)(const Button& button);

	Button();
	Button(const Rectangle& hitbox, void (*OnClick)(const Button& button));

	void Update(sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);

	std::string ToString() const override;
};

#endif