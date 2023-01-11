#ifndef CARD_PLACE_INFO_HPP
#define CARD_PLACE_INFO_HPP

#include "Card.hpp"

struct CardPlaceInfo
{
	bool playerOnePlace;
	CardType line;
	int indexPlace;
	Card card;
	Rectangle hitbox;

	CardPlaceInfo()
	{

	}

	CardPlaceInfo(bool playerOnePlace, CardType line, int indexPlace, Card card, Rectangle hitbox)
	{
		this->playerOnePlace = playerOnePlace;
		this->line = line;
		this->indexPlace = indexPlace;
		this->card = card;
	}

	CardPlaceInfo(const CardPlaceInfo& cardPlaceInfo)
	{
		this->playerOnePlace = cardPlaceInfo.playerOnePlace;
		this->line = cardPlaceInfo.line;
		this->indexPlace = cardPlaceInfo.indexPlace;
		this->card = Card(cardPlaceInfo.card);
		this->hitbox = Rectangle(cardPlaceInfo.hitbox);
	}
};

#endif