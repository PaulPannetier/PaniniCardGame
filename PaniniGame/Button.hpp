#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Collider2D.hpp"
#include "Useful.hpp"

class Button : Object
{
protected:
	bool isHover, oldIsMousePressed;

public:
	Rectangle rectangle;

	Button();
	Button(const Rectangle& rectangle, void (*OnClick)(Button& button));

	void (*OnClick)(Button& button);//une fonction de type void prennant en entré un bouton
	virtual void Update(sf::RenderWindow& window);
	virtual void Draw(sf::RenderWindow& window);

	std::string ToString() const override;
};

#endif