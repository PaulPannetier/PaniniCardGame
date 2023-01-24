#include "EventManager.hpp"
#include "Board.hpp"

EventManager::EventManager()
{

}

EventManager& EventManager::Instance()
{
	static EventManager instance;
	return instance;
}

void EventManager::Start()
{

}

void EventManager::OnCardsSwitched(const CardPlaceInfo& newCard1, const CardPlaceInfo& newCard2)
{
	newCard1.card->OnMove();
	newCard2.card->OnMove();
}

void EventManager::OnBeginTurn(bool playerOneTurn)
{
	Board::Instance().OnBeginTurn(playerOneTurn);
}

void EventManager::OnEndTurn(bool playerOneEndTurn)
{
	Board::Instance().OnEndTurn(playerOneEndTurn);
}

void EventManager::OnMakeDuel(const CardPlaceInfo& striker, const CardPlaceInfo& defender)
{

}

