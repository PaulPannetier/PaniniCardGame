#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>
#include "Card.hpp"

class Ball
{
private:
	sf::Sprite sprite;
	Ball();

	const sf::Vector2f ballSize = sf::Vector2f(50, 50);

public:
	Card* card;

	static Ball& Instance();
	void Start();

	void CalculateTransform();
	void SetAttachCard(Card& card);

	void Update(sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);

};

#endif
