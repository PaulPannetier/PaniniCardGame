#ifndef PLAYER_BOARD_HPP
#define PLAYER_BOARD_HPP

#include <vector>
#include "Deck.hpp"

class PlayerBoard
{
private :
	const int nbMaxGoalKeepers = 1;
	const int nbMaxDefencers = 5;
	const int nbMaxStrikers = 4;

	Deck deck;
	std::vector<Card> goalKeepers;
	std::vector<Card> defencers;
	std::vector<Card> strikers;
	int _playerID;

public:
	//Getter
	int playerID() { return _playerID; }

	PlayerBoard();
	PlayerBoard(int playerID);

	void Draw();//dessine le board

	PlayerBoard& operator =(PlayerBoard value)
	{
		this->_playerID = value._playerID;
		return value;
	}
};

#endif
