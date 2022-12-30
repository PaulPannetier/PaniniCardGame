#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Useful.hpp"
#include "Collider2D.hpp"

class Button : Object
{
private:
	bool isHover;

public:

	Rectangle hitbox;//la hitbox clicable du bouton
	void (*OnClick)(const Button& button);//la fonction appelé lorsqu'on click sur le bouton

	Button();
	Button(const Rectangle& hitbox, void (*OnClick)(const Button& button));

	void Update(sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);

	std::string ToString() const override;
};

#endif