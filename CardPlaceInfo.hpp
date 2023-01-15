#ifndef CARD_PLACE_INFO_HPP
#define CARD_PLACE_INFO_HPP

class Card;

struct CardPlaceInfo
{
	bool playerOnePlace;
	CardType line;
	int indexPlace;
	Card* card;
	Rectangle hitbox;

	CardPlaceInfo();

	CardPlaceInfo(bool playerOnePlace, CardType line, int indexPlace, Card card, Rectangle hitbox);

	CardPlaceInfo(const CardPlaceInfo& cardPlaceInfo);
};

#endif