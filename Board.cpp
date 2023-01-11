
#include "Board.hpp"
#include "Collider2D.hpp"
#include "AssetsManager.hpp"
#include "GameManager.hpp"

using namespace std;
using namespace sf;

void Board::OnClickEndTurnButtonAction(const Button& button)
{
	Player& player = player1.isMyTurn ? player1 : player2;
	Player& otherPlayer = player1.isMyTurn ? player2 : player1;
	player.isMyTurn = false;
	player.EndTurn();
	otherPlayer.isMyTurn = true;
	otherPlayer.BeginTurn();
}

void OnClickEndTurnButton(const Button& button)
{
	Board::Instance().OnClickEndTurnButtonAction(button);
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
	endTurnButton = Button(Rectangle(Vector2f(1500, 800), Vector2f(50, 50)), OnClickEndTurnButton);
	Texture& bgText = AssetsManager::Instance().GetTexture("BoardBackground");
	background.setTexture(bgText);
	Vector2f windowSize = GameManager::Instance().GetWindowSize();//marche pas
	Vector2f textureSize = Vector2f(bgText.getSize());
	Vector2f scale = Vector2f(1600 / textureSize.x, 900 / textureSize.y);

	//start the players
	background.setScale(scale);
	player1.isPlayerOne = true;
	player1.Start();
	player2.isPlayerOne = false;
	player2.Start();
	FillDeck();
	player1.FirstDraw(NB_BEGIN_CARDS);
	player2.FirstDraw(NB_BEGIN_CARDS);
	player1.isMyTurn = true;
	player1.BeginTurn();
}

void Board::FillDeck()
{
	vector<CardsManager::CardNum> deckPlayer1 =
	{
		CardsManager::CardNum::Lorris,
		CardsManager::CardNum::Lorris,
		CardsManager::CardNum::Lorris,
		CardsManager::CardNum::Giroud,
		CardsManager::CardNum::Giroud,
		CardsManager::CardNum::Giroud,
		CardsManager::CardNum::Pavard,
		CardsManager::CardNum::Pavard,
		CardsManager::CardNum::Pavard
	};
	player1.FillDeck(deckPlayer1);

	vector<CardsManager::CardNum> deckPlayer2 =
	{
		CardsManager::CardNum::Lorris,
		CardsManager::CardNum::Lorris,
		CardsManager::CardNum::Lorris,
		CardsManager::CardNum::Giroud,
		CardsManager::CardNum::Giroud,
		CardsManager::CardNum::Giroud,
		CardsManager::CardNum::Pavard,
		CardsManager::CardNum::Pavard,
		CardsManager::CardNum::Pavard
	};
	player2.FillDeck(deckPlayer2);
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
			if (goalKeepersOne[indexPlace].isOnBoard)
				return false;
			return true;
		}
		if (goalKeepersTwo[indexPlace].isOnBoard)
			return false;
		return true;
	case CardType::defender:
		if (indexPlace >= NB_MAX_DEFENDER)
			return false;
		if (playerOneBoard)
		{
			if (defencersOne[indexPlace].isOnBoard)
				return false;
			return true;
		}
		if (defencersTwo[indexPlace].isOnBoard)
			return false;
		return true;
	case CardType::striker:
		if (indexPlace >= NB_MAX_STRIKER)
			return false;
		if (playerOneBoard)
		{
			if (strikersOne[indexPlace].isOnBoard)
				return false;
			return true;
		}
		if (strikersTwo[indexPlace].isOnBoard)
			return false;
		return true;
	case CardType::spell:
		return true;
	default:
		return false;
	}
}

bool Board::GetCardPlaceInfo(Vector2f position, CardPlaceInfo& info)
{
	Rectangle hitbox;
	//gardien joueur 1
	for (int i = 0; i < NB_MAX_GOAL_KEEPER; i++)
	{
		hitbox = Rectangle(goalKeeperOnePos[i], cardSize);
		if (hitbox.Contain(position))
		{
			info.indexPlace = i;
			info.card = Card(this->goalKeepersOne[i]);
			info.line = CardType::goalkeeper;
			info.playerOnePlace = true;
			info.hitbox = hitbox;
			return true;
		}
	}

	//defenceurs joueur 1
	for (int i = 0; i < NB_MAX_DEFENDER; i++)
	{
		hitbox = Rectangle(defenderOnePos[i], cardSize);
		if (hitbox.Contain(position))
		{
			info.indexPlace = i;
			info.card = Card(this->defencersOne[i]);
			info.line = CardType::defender;
			info.playerOnePlace = true;
			info.hitbox = hitbox;
			return true;
		}
	}

	//attaquant joueur 1
	for (int i = 0; i < NB_MAX_STRIKER; i++)
	{
		hitbox = Rectangle(strikerOnePos[i], cardSize);
		if (hitbox.Contain(position))
		{
			info.indexPlace = i;
			info.card = Card(this->strikersOne[i]);
			info.line = CardType::striker;
			info.playerOnePlace = true;
			info.hitbox = hitbox;
			return true;
		}
	}

	//gardien joueur 2
	for (int i = 0; i < NB_MAX_GOAL_KEEPER; i++)
	{
		hitbox = Rectangle(goalKeeperTwoPos[i], cardSize);
		if (hitbox.Contain(position))
		{
			info.indexPlace = i;
			info.card = Card(this->goalKeepersTwo[i]);
			info.line = CardType::goalkeeper;
			info.playerOnePlace = false;
			info.hitbox = hitbox;
			return true;
		}
	}

	//defenceurs joueur 2
	for (int i = 0; i < NB_MAX_DEFENDER; i++)
	{
		hitbox = Rectangle(defenderTwoPos[i], cardSize);
		if (hitbox.Contain(position))
		{
			info.indexPlace = i;
			info.card = Card(this->defencersTwo[i]);
			info.line = CardType::defender;
			info.playerOnePlace = false;
			info.hitbox = hitbox;
			return true;
		}
	}

	//attaquant joueur 2
	for (int i = 0; i < NB_MAX_STRIKER; i++)
	{
		hitbox = Rectangle(strikerTwoPos[i], cardSize);
		if (hitbox.Contain(position))
		{
			info.indexPlace = i;
			info.card = Card(this->strikersTwo[i]);
			info.line = CardType::striker;
			info.playerOnePlace = false;
			info.hitbox = hitbox;
			return true;
		}
	}

	return false;
}

void Board::PlaceCard(Card& boardCard, const Card& newCard, int index, int globalIndex = 0)
{
	boardCard = Card(newCard);
	boardCard.isOnBoard = true;
	boardCard.isSelected = false;
	boardCards[globalIndex] = &boardCard;
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
			PlaceCard(goalKeepersOne[indexPlace], card, indexPlace, indexPlace);
		}
		else
		{
			PlaceCard(goalKeepersTwo[indexPlace], card, indexPlace, ((NB_MAX_DEFENDER + NB_MAX_STRIKER) * 2) + NB_MAX_GOAL_KEEPER - 1 + indexPlace);
		}
		break;
	case CardType::defender:
		if (playerOneBoard)
		{
			PlaceCard(defencersOne[indexPlace], card, indexPlace, NB_MAX_GOAL_KEEPER + indexPlace);
		}
		else
		{
			PlaceCard(defencersTwo[indexPlace], card, indexPlace, NB_MAX_GOAL_KEEPER + NB_MAX_DEFENDER + 2 * NB_MAX_STRIKER + indexPlace);
		}
		break;
	case CardType::striker:
		if (playerOneBoard)
		{
			PlaceCard(strikersOne[indexPlace], card, indexPlace, NB_MAX_GOAL_KEEPER + NB_MAX_DEFENDER + indexPlace);
		}
		else
		{
			PlaceCard(strikersTwo[indexPlace], card, indexPlace, NB_MAX_GOAL_KEEPER + NB_MAX_DEFENDER + NB_MAX_STRIKER + indexPlace);
		}
		break;
	default:
		break;
	}
}

void Board::CalculateCardsTransform()
{
	//goals joueur 1
	for (int i = 0; i < NB_MAX_GOAL_KEEPER; i++)
	{
		goalKeepersOne[i].SetPosition(goalKeeperOnePos[i]);
		goalKeepersOne[i].SetSize(cardSize);
	}

	//defenceurs joueur 1
	for (int i = 0; i < NB_MAX_DEFENDER; i++)
	{
		defencersOne[i].SetPosition(defenderOnePos[i]);
		defencersOne[i].SetSize(cardSize);
	}

	//attaquant joueur 1
	for (int i = 0; i < NB_MAX_STRIKER; i++)
	{
		strikersOne[i].SetPosition(strikerOnePos[i]);
		strikersOne[i].SetSize(cardSize);
	}

	//gardien joueur 2
	for (int i = 0; i < NB_MAX_GOAL_KEEPER; i++)
	{
		goalKeepersTwo[i].SetPosition(goalKeeperTwoPos[i]);
		goalKeepersTwo[i].SetSize(cardSize);
	}

	//defenceurs joueur 2
	for (int i = 0; i < NB_MAX_DEFENDER; i++)
	{
		defencersTwo[i].SetPosition(defenderTwoPos[i]);
		defencersTwo[i].SetSize(cardSize);
	}

	//attaquant joueur 2
	for (int i = 0; i < NB_MAX_STRIKER; i++)
	{
		strikersTwo[i].SetPosition(strikerTwoPos[i]);
		strikersTwo[i].SetSize(cardSize);
	}
}

void Board::GetPlayerCard(bool playerOneCards, vector<CardPlaceInfo>& res)
{
	res.clear();

	//goals joueur 1
	for (int i = 0; i < NB_MAX_GOAL_KEEPER; i++)
	{
		if (goalKeepersOne[i].isInitialized && goalKeepersOne[i].isPlayerOneCard == playerOneCards)
		{
			CardPlaceInfo cpi = CardPlaceInfo(playerOneCards, goalKeepersOne[i].cardType(), i, Card(goalKeepersOne[i]), Rectangle(goalKeeperOnePos[i], cardSize));
			res.push_back(cpi);
		}
	}

	//defenceurs joueur 1
	for (int i = 0; i < NB_MAX_DEFENDER; i++)
	{
		if (defencersOne[i].isInitialized && defencersOne[i].isPlayerOneCard == playerOneCards)
		{
			CardPlaceInfo cpi = CardPlaceInfo(playerOneCards, defencersOne[i].cardType(), i, Card(defencersOne[i]), Rectangle(defenderOnePos[i], cardSize));
			res.push_back(cpi);
		}
	}

	//attaquant joueur 1
	for (int i = 0; i < NB_MAX_STRIKER; i++)
	{
		if (strikersOne[i].isInitialized && strikersOne[i].isPlayerOneCard == playerOneCards)
		{
			CardPlaceInfo cpi = CardPlaceInfo(playerOneCards, strikersOne[i].cardType(), i, Card(strikersOne[i]), Rectangle(strikerOnePos[i], cardSize));
			res.push_back(cpi);
		}
	}

	//gardien joueur 2
	for (int i = 0; i < NB_MAX_GOAL_KEEPER; i++)
	{
		if (goalKeepersTwo[i].isInitialized && goalKeepersTwo[i].isPlayerOneCard == playerOneCards)
		{
			CardPlaceInfo cpi = CardPlaceInfo(playerOneCards, goalKeepersTwo[i].cardType(), i, Card(strikersOne[i]), Rectangle(goalKeeperTwoPos[i], cardSize));
			res.push_back(cpi);
		}
	}

	//defenceurs joueur 2
	for (int i = 0; i < NB_MAX_DEFENDER; i++)
	{
		if (defencersTwo[i].isInitialized && strikersOne[i].isPlayerOneCard == playerOneCards)
		{
			CardPlaceInfo cpi = CardPlaceInfo(playerOneCards, defencersTwo[i].cardType(), i, Card(defencersTwo[i]), Rectangle(defenderTwoPos[i], cardSize));
			res.push_back(cpi);
		}
	}

	//attaquant joueur 2
	for (int i = 0; i < NB_MAX_STRIKER; i++)
	{
		if (strikersTwo[i].isInitialized && strikersTwo[i].isPlayerOneCard == playerOneCards)
		{
			CardPlaceInfo cpi = CardPlaceInfo(playerOneCards, strikersTwo[i].cardType(), i, Card(strikersOne[i]), Rectangle(strikerTwoPos[i], cardSize));
			res.push_back(cpi);
		}
	}
}

void Board::MakeDuel(const CardPlaceInfo& striker, const CardPlaceInfo& defender)
{

}

void Board::Update(RenderWindow& window)
{
	player1.Update(window);
	player2.Update(window);
	CalculateCardsTransform();
	endTurnButton.Update(window);
}

//Affiche le plateau de jeu
void Board::Draw(RenderWindow& window)
{
	//afficher le background
	window.draw(background);

	player1.Draw(window);
	player2.Draw(window);

	int i;
	//Le joueur du haut
	//le goal
	for (i = 0; i < NB_MAX_GOAL_KEEPER; i++)
	{
		if (this->goalKeepersOne[i].isOnBoard)
		{
			this->goalKeepersOne[i].Draw(window);
		}
		else
		{
			Rectangle::DrawWire(window, this->goalKeeperOnePos[i], this->cardSize, Color::Red, 3.0f);
		}
	}
	//defenseurs
	for (i = 0; i < NB_MAX_DEFENDER; i++)
	{
		if (this->defencersOne[i].isOnBoard)
		{
			this->defencersOne[i].Draw(window);
		}
		else
		{
			Rectangle::DrawWire(window, this->defenderOnePos[i], this->cardSize, Color::Blue, 3.0f);
		}
	}
	//attaquants
	for (i = 0; i < NB_MAX_STRIKER; i++)
	{
		if (this->strikersOne[i].isOnBoard)
		{
			this->strikersOne[i].Draw(window);
		}
		else
		{
			Rectangle::DrawWire(window, this->strikerOnePos[i], this->cardSize, Color::Green, 3.0f);
		}
	}

	//Le joueur du bas
	//le goal
	for (i = 0; i < NB_MAX_GOAL_KEEPER; i++)
	{
		if (this->goalKeepersTwo[i].isOnBoard)
		{
			this->goalKeepersTwo[i].Draw(window);
		}
		else
		{
			Rectangle::DrawWire(window, this->goalKeeperTwoPos[i], this->cardSize, Color::Red, 3.0f);
		}
	}
	//defenseurs
	for (i = 0; i < NB_MAX_DEFENDER; i++)
	{
		if (this->defencersTwo[i].isOnBoard)
		{
			this->defencersTwo[i].Draw(window);
		}
		else
		{
			Rectangle::DrawWire(window, this->defenderTwoPos[i], this->cardSize, Color::Blue, 3.0f);
		}
	}
	//attaquants
	for (i = 0; i < NB_MAX_STRIKER; i++)
	{
		if (this->strikersTwo[i].isOnBoard)
		{
			this->strikersTwo[i].Draw(window);
		}
		else
		{
			Rectangle::DrawWire(window, this->strikerTwoPos[i], this->cardSize, Color::Green, 3.0f);
		}
	}

	//les boutons
	endTurnButton.Draw(window);
}