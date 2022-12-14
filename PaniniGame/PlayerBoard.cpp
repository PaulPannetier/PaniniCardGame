
#include "PlayerBoard.hpp"

using namespace std;

PlayerBoard::PlayerBoard()
{
	this->_playerID = 0;
}

PlayerBoard::PlayerBoard(int playerID)
{
	this->_playerID = playerID;
}

/*
bool PlayerBoard::CanPlaceCardInBoard(const Card& card, int placeIndex) const
{
	return true;
}
*/
/*
bool PlayerBoard::PlaceCardInBoard(Card card, int placeIndex)
{
	return true;
}
*/

void PlayerBoard::Draw()
{
	if (playerID() == 0)//en bas du plateau
	{
		//draw goal keeper

	}
}