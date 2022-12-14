#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Useful.hpp"

class Button : Object
{
private:


public:

	void (*OnClick)(Button button);
	std::string ToString() const override;
};

class RectangleButton : Button
{
	std::string ToString() const override;
};

class CircleButton : Button
{

	std::string ToString() const override;
};

#endif