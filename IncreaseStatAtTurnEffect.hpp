#ifndef INCREASE_STAT_AT_TURN
#define INCREASE_STAT_AT_TURN

#include "Effect.hpp"

class IncreaseStatAtTurn : public Effect
{
public:
	IncreaseStatAtTurn();
	IncreaseStatAtTurn(IncreaseStatAtTurn& effect);
	IncreaseStatAtTurn(Effect& effect);

	int attackAmount, defenceAmount;
	IncreaseStatAtTurn(int attackAmount, int defenceAmount);

	Effect* Clone() override;
	void OnBeginTurn(bool isPlayerOneTurn) override;

	std::string ToString() const override;
};

#endif