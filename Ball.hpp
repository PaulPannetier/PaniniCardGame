#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>
#include "Card.hpp"

class Ball
{
private:
	sf::Sprite sprite;
	Ball();

public:
	Card* card;


	static Ball& Instance();
	void Start();

};

#endif
