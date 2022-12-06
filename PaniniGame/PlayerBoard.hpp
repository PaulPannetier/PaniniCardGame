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

public:
	void Draw();//dessine le board
};

#endif
