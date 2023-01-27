#include "Effect.hpp"

using namespace std;
using namespace sf;

Effect::Effect()
{
	this->card = nullptr;
}

Effect::Effect(Effect& effect)
{
	this->card = effect.card;
}

string Effect::ToString() const
{
	return "Effect";
}