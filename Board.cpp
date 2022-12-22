
#include "Board.hpp"
#include "Collider2D.hpp"
#include "AssetsManager.hpp"
#include "GameManager.hpp"

using namespace std;
using namespace sf;

void OnClickEndTurnButton(const Button& button)
{
	cout << "End Turn" << endl;
}

Board::Board()
{

}

Board& Board::Instance()
{
	static Board instance;
	return instance;
}

void Board::Start()
{
	endTurnButton = Button(Rectangle(Vector2f(1300, 450), Vector2f(50, 50)), OnClickEndTurnButton);
	Texture& bgText = AssetsManager::Instance().GetTexture("BoardBackground");
	background.setTexture(bgText);
	Vector2f windowSize = GameManager::Instance().GetWindowSize();//marche pas
	Vector2f textureSize = Vector2f(bgText.getSize());
	Vector2f scale = Vector2f(1600 / textureSize.x, 900 / textureSize.y);
	background.setScale(scale);
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
			if (goalKeepersUp[indexPlace].isOnBoard)
				return false;
			return true;
		}
		if (goalKeepersDown[indexPlace].isOnBoard)
			return false;
		return true;
	case CardType::defender:
		if (indexPlace >= NB_MAX_DEFENDER)
			return false;
		if (playerOneBoard)
		{
			if (defencersUp[indexPlace].isOnBoard)
				return false;
			return true;
		}
		if (defencersDown[indexPlace].isOnBoard)
			return false;
		return true;
	case CardType::striker:
		if (indexPlace >= NB_MAX_STRIKER)
			return false;
		if (playerOneBoard)
		{
			if (strikersUp[indexPlace].isOnBoard)
				return false;
			return true;
		}
		if (strikersDown[indexPlace].isOnBoard)
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
			goalKeepersUp[indexPlace].isOnBoard = true;
		}
		else
		{
			goalKeepersDown[indexPlace] = Card(card);
			goalKeepersDown[indexPlace].isOnBoard = true;
		}
		break;
	case CardType::defender:
		if (playerOneBoard)
		{
			defencersUp[indexPlace] = Card(card);
			defencersUp[indexPlace].isOnBoard = true;
		}
		else
		{
			defencersDown[indexPlace] = Card(card);
			defencersDown[indexPlace].isOnBoard = true;
		}
		break;
	case CardType::striker:
		if (playerOneBoard)
		{
			strikersUp[indexPlace] = Card(card);
			strikersUp[indexPlace].isOnBoard = true;
		}
		else
		{
			strikersDown[indexPlace] = Card(card);
			strikersDown[indexPlace].isOnBoard = true;
		}
		break;
	default:
		break;
	}
}

void Board::Update(RenderWindow& window)
{
	endTurnButton.Update(window);
}

//Affiche le plateau de jeu
void Board::Draw(RenderWindow& window)
{
	//afficher le background
	window.draw(background);

	//les boutons
	endTurnButton.Draw(window);

	int i;
	//Le joueur du haut
	//le goal
	for (i = 0; i < NB_MAX_GOAL_KEEPER; i++)
	{
		if (this->goalKeepersUp[i].isOnBoard)
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
		if (this->defencersUp[i].isOnBoard)
		{
			this->defencersUp[i].Draw(window, this->defenderUpPos[i], this->cardSize);
		}
		else
		{
			Rectangle::DrawWire(window, this->defenderUpPos[i], this->cardSize, Color::Blue, 3.0f);
		}
	}
	//attaquants
	for (i = 0; i < NB_MAX_STRIKER; i++)
	{
		if (this->strikersUp[i].isOnBoard)
		{
			this->strikersUp[i].Draw(window, this->strikerUpPos[i], this->cardSize);
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
		if (this->goalKeepersDown[i].isOnBoard)
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
		if (this->defencersDown[i].isOnBoard)
		{
			this->defencersDown[i].Draw(window, this->defenderDownPos[i], this->cardSize);
		}
		else
		{
			Rectangle::DrawWire(window, this->defenderDownPos[i], this->cardSize, Color::Blue, 3.0f);
		}
	}
	//attaquants
	for (i = 0; i < NB_MAX_STRIKER; i++)
	{
		if (this->strikersDown[i].isOnBoard)
		{
			this->strikersDown[i].Draw(window, this->strikerDownPos[i], this->cardSize);
		}
		else
		{
			Rectangle::DrawWire(window, this->strikerDownPos[i], this->cardSize, Color::Green, 3.0f);
		}
	}
}