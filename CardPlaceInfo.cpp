#include "Card.hpp"
#include "CardPlaceInfo.hpp"

CardPlaceInfo::CardPlaceInfo()
{
	card = nullptr;
}

CardPlaceInfo::CardPlaceInfo(bool playerOnePlace, CardType line, int indexPlace, Card card, Rectangle hitbox)
{
	this->playerOnePlace = playerOnePlace;
	this->line = line;
	this->indexPlace = indexPlace;
	this->card = &card;
}

CardPlaceInfo::CardPlaceInfo(const CardPlaceInfo& cardPlaceInfo)
{
	this->playerOnePlace = cardPlaceInfo.playerOnePlace;
	this->line = cardPlaceInfo.line;
	this->indexPlace = cardPlaceInfo.indexPlace;
	this->card = cardPlaceInfo.card;
	this->hitbox = Rectangle(cardPlaceInfo.hitbox);
}