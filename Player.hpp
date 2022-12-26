#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Deck.hpp"
#include "Hand.hpp"

class Player
{
private :
	Deck deck;
	Hand hand;

public :

	bool isMyTurn;

	Player() = default;

	void Start();
	void Update(sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
};

#endif
