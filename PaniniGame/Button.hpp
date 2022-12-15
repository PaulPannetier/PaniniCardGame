#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Collider2D.hpp"
#include "Useful.hpp"

class Button : Object
{
protected:
	bool isHover;

public:
	Collider2D* collider;

	Button();
	Button(void (*OnClick)(Button button), Collider2D* collider);

	void (*OnClick)(Button button);//une fonction de type void prennant en entré un bouton
	virtual void Update(sf::RenderWindow& window);
	virtual void Draw(sf::RenderWindow& window);

	std::string ToString() const override;

	~Button()
	{
		//delete collider;
	}
};

class RectangleButton : Button
{
public:

	RectangleButton();
	RectangleButton(Rectangle rec, void (*OnClick)(Button button));

	void Update(sf::RenderWindow& window) override;
	void Draw(sf::RenderWindow& window) override;

	std::string ToString() const override;
};

class CircleButton : Button
{
public:
	CircleButton();
	CircleButton(Circle rec, void (*OnClick)(Button button));

	void Update(sf::RenderWindow& window) override;
	void Draw(sf::RenderWindow& window) override;

	std::string ToString() const override;
};

#endif