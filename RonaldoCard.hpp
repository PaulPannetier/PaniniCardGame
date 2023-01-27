#ifndef RONALDO_CARD_HPP
#define RONALDO_CARD_HPP

#include "Card.hpp"

class RonaldoCard : public Card
{
public:
	RonaldoCard();
	RonaldoCard(std::string name, std::string description, int attack, int defence, int cost, CardType cardType, std::string textureName, bool isPlayerOneCard = false);
	RonaldoCard(const RonaldoCard& card);

	void OnBeginTurn(bool playerOneTurn) override;
};

#endif
