#include "IncreaseStatAtTurnEffect.hpp"
#include "Card.hpp"

using namespace std;
using namespace sf;

IncreaseStatAtTurn::IncreaseStatAtTurn() : Effect()
{
	this->attackAmount = this->defenceAmount = 0;
}

IncreaseStatAtTurn::IncreaseStatAtTurn(IncreaseStatAtTurn& effect) : Effect(effect)
{
	this->attackAmount = effect.attackAmount;
	this->defenceAmount = effect.defenceAmount;
}

Effect* IncreaseStatAtTurn::Clone()
{
	return new IncreaseStatAtTurn(*this);
}

IncreaseStatAtTurn::IncreaseStatAtTurn(int attackAmount, int defenceAmount) : Effect()
{
	this->attackAmount = attackAmount;
	this->defenceAmount = defenceAmount;
}

void IncreaseStatAtTurn::OnBeginTurn(bool isPlayerOneBeginTurn)
{
	if (this->card->isPlayerOneCard == isPlayerOneBeginTurn)
	{
		card->attackBonus += this->attackAmount;
		card->defenceBonus += this->defenceAmount;
	}
}

string IncreaseStatAtTurn::ToString() const
{
	return "IncreaseStatAtTurn : (" + to_string(attackAmount) + ", " + to_string(defenceAmount) + ")";
}