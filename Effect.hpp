#ifndef EFFECT_HPP
#define EFFECT_HPP

#include "Useful.hpp"

class Card;

class Effect : Object
{
public:
	Effect();
	Effect(Effect& effet);

	Card* card;

	virtual Effect* Clone() = 0;
	virtual void OnBeginTurn(bool isPlayerOneTurn) = 0;
	std::string ToString() const override;
};

#endif