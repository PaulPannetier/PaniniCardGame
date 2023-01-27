#include "RonaldoCard.hpp"

using namespace std;
using namespace sf;

RonaldoCard::RonaldoCard() : Card()
{

}

RonaldoCard::RonaldoCard(std::string name, std::string description, int attack, int defence, int cost, CardType cardType, std::string textureName, bool isPlayerOneCard)
	: Card(name, description, attack, defence, cost, cardType, textureName, isPlayerOneCard)
{

}

RonaldoCard::RonaldoCard(const RonaldoCard& card) : Card(card)
{

}


void RonaldoCard::OnBeginTurn(bool isPlayerOneTurn)
{
	Card::OnBeginTurn(isPlayerOneCard);

	if (this->isPlayerOneCard == isPlayerOneTurn)
	{
		this->attackBonus++;
	}
}