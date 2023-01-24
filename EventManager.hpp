#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include "CardPlaceInfo.hpp"
#include "Action.hpp"

class EventManager
{
private:

	EventManager();

public:

	static EventManager& Instance();
	void Start();

	void OnCardsSwitched(const CardPlaceInfo& newCard1, const CardPlaceInfo& newCard2);

	void OnBeginTurn(bool playerOneTurn);

	void OnEndTurn(bool playerOneEndTurn);

	void OnMakeDuel(const CardPlaceInfo& striker, const CardPlaceInfo& defender);
};

#endif