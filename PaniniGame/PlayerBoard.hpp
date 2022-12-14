#ifndef PLAYER_BOARD_HPP
#define PLAYER_BOARD_HPP

#include <vector>
#include "Deck.hpp"

#define NB_MAX_GOAL_KEEPER 1
#define NB_MAX_DEFENDER 5
#define NB_MAX_STRIKER 4

class PlayerBoard
{
private :

	const sf::Vector2f goalKeeperUpPos1 = sf::Vector2f(800, 100);

	const sf::Vector2f defenderUpPos1= sf::Vector2f(400, 250);
	const sf::Vector2f defenderUpPos2 = sf::Vector2f(600, 250);
	const sf::Vector2f defenderUpPos3 = sf::Vector2f(800, 250);
	const sf::Vector2f defenderUpPos4 = sf::Vector2f(1000, 250);
	const sf::Vector2f defenderUpPos5 = sf::Vector2f(1200, 250);

	const sf::Vector2f strikerUpPos1 = sf::Vector2f(500, 400);
	const sf::Vector2f strikerUpPos2 = sf::Vector2f(700, 400);
	const sf::Vector2f strikerUpPos3 = sf::Vector2f(900, 400);
	const sf::Vector2f strikerUpPos4 = sf::Vector2f(1100, 400);

	const sf::Vector2f goalKeeperDownPos1 = sf::Vector2f(800, 800);

	const sf::Vector2f defenderDownPos1 = sf::Vector2f(400, 650);
	const sf::Vector2f defenderDownPos2 = sf::Vector2f(600, 650);
	const sf::Vector2f defenderDownPos3 = sf::Vector2f(800, 650);
	const sf::Vector2f defenderDownPos4 = sf::Vector2f(1000, 650);
	const sf::Vector2f defenderDownPos5 = sf::Vector2f(1200, 650);

	const sf::Vector2f strikerDownPos1 = sf::Vector2f(500, 500);
	const sf::Vector2f strikerDownPos2 = sf::Vector2f(700, 500);
	const sf::Vector2f strikerDownPos3 = sf::Vector2f(900, 500);
	const sf::Vector2f strikerDownPos4 = sf::Vector2f(1100, 500);

	//Deck deck;
	//Card goalKeepers[NB_MAX_GOAL_KEEPER];
	//Card defencers[NB_MAX_DEFENDER];
	//Card strikers[NB_MAX_STRIKER];
	int _playerID;

public:
	//Getter
	int playerID() { return _playerID; }

	PlayerBoard();
	PlayerBoard(int playerID);

	void Draw();//dessine le board
	//bool CanPlaceCardInBoard(const Card& card, int placeIndex) const;
	//bool PlaceCardInBoard(Card card, int placeIndex);

	PlayerBoard& operator =(PlayerBoard value)
	{
		this->_playerID = value._playerID;
		return value;
	}
};

#endif
