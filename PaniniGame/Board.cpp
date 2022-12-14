
#include "Board.hpp"
#include "Collider2D.hpp"

using namespace std;
using namespace sf;

Board::Board()
{
	/*
	background.setColor(Color::White);
	background.setPosition(Vector2f(0, 0));
	background.setScale(1, 1);
	*/
}

bool Board::CanPlaceCard(const Card& card, bool playerOneBoard, CardType line, int indexPlace)
{
	if (!card.CanPlaceInBoard(playerOneBoard, line, indexPlace) || indexPlace < 0)
	{
		return false;
	}
	switch (line)
	{
		case CardType::goalkeeper:
			if (indexPlace >= NB_MAX_GOAL_KEEPER)
				return false;
			if (playerOneBoard)
			{
				if (goalKeepersUp[indexPlace].isInitialised)
					return false;
				return true;
			}
			if (goalKeepersDown[indexPlace].isInitialised)
				return false;
			return true;
		case CardType::defender:
			if (indexPlace >= NB_MAX_DEFENDER)
				return false;
			if (playerOneBoard)
			{
				if (defencersUp[indexPlace].isInitialised)
					return false;
				return true;
			}
			if (defencersDown[indexPlace].isInitialised)
				return false;
			return true;
		case CardType::striker:
			if (indexPlace >= NB_MAX_STRIKER)
				return false;
			if (playerOneBoard)
			{
				if (strikersUp[indexPlace].isInitialised)
					return false;
				return true;
			}
			if (strikersDown[indexPlace].isInitialised)
				return false;
			return true;
		case CardType::spell:
			return true;
		default:
			return false;
	}
}

void Board::PlaceCard(const Card& card, bool playerOneBoard, CardType line, int indexPlace)
{
	if (!CanPlaceCard(card, playerOneBoard, line, indexPlace))
		return;
	switch (line)
	{
	case CardType::goalkeeper:
		if (playerOneBoard)
		{
			goalKeepersUp[indexPlace] = Card(card);
		}
		else
		{
			goalKeepersDown[indexPlace] = Card(card);
		}
	case CardType::defender:
		if (playerOneBoard)
		{
			defencersUp[indexPlace] = Card(card);
		}
		else
		{
			defencersDown[indexPlace] = Card(card);
		}
	case CardType::striker:
		if (playerOneBoard)
		{
			strikersUp[indexPlace] = Card(card);
		}
		else
		{
			strikersDown[indexPlace] = Card(card);
		}
	default:
		return;
	}
}

//Affiche le plateau de jeu
void Board::Draw(RenderWindow& window)
{
	//afficher le background



	int i;
	//Le joueur du haut
	//le goal
	for (i = 0; i < NB_MAX_GOAL_KEEPER; i++)
	{
		if (this->goalKeepersUp[i].isInitialised)
		{
			this->goalKeepersUp[i].Draw(window, this->goalKeeperUpPos[i], this->cardSize);
		}
		else
		{
			Rectangle::DrawWire(window, this->goalKeeperUpPos[i], this->cardSize, Color::Red, 3.0f);
		}
	}
	//defenseurs
	for (i = 0; i < NB_MAX_DEFENDER; i++)
	{
		if (this->defencersUp[i].isInitialised)
		{
			this->goalKeepersUp[i].Draw(window, this->defenderUpPos[i], this->cardSize);
		}
		else
		{
			Rectangle::DrawWire(window, this->defenderUpPos[i], this->cardSize, Color::Blue, 3.0f);
		}
	}
	//attaquants
	for (i = 0; i < NB_MAX_STRIKER; i++)
	{
		if (this->strikersUp[i].isInitialised)
		{
			this->goalKeepersUp[i].Draw(window, this->strikerUpPos[i], this->cardSize);
		}
		else
		{
			Rectangle::DrawWire(window, this->strikerUpPos[i], this->cardSize, Color::Green, 3.0f);
		}
	}

	//Le joueur du bas
	//le goal
	for (i = 0; i < NB_MAX_GOAL_KEEPER; i++)
	{
		if (this->goalKeepersDown[i].isInitialised)
		{
			this->goalKeepersDown[i].Draw(window, this->goalKeeperDownPos[i], this->cardSize);
		}
		else
		{
			Rectangle::DrawWire(window, this->goalKeeperDownPos[i], this->cardSize, Color::Red, 3.0f);
		}
	}
	//defenseurs
	for (i = 0; i < NB_MAX_DEFENDER; i++)
	{
		if (this->defencersDown[i].isInitialised)
		{
			this->goalKeepersDown[i].Draw(window, this->defenderDownPos[i], this->cardSize);
		}
		else
		{
			Rectangle::DrawWire(window, this->defenderDownPos[i], this->cardSize, Color::Blue, 3.0f);
		}
	}
	//attaquants
	for (i = 0; i < NB_MAX_STRIKER; i++)
	{
		if (this->strikersUp[i].isInitialised)
		{
			this->goalKeepersDown[i].Draw(window, this->strikerDownPos[i], this->cardSize);
		}
		else
		{
			Rectangle::DrawWire(window, this->strikerDownPos[i], this->cardSize, Color::Green, 3.0f);
		}
	}
}