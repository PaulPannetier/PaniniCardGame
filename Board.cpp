
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

	//init board Cards

	//goals joueur 1
	int i;
	for (i = 0; i < NB_MAX_GOAL_KEEPER; i++)
	{
		boardCards[i] = &goalKeepersOne[i];
	}
	//defenceurs joueur 1
	for (i = 0; i < NB_MAX_DEFENDER; i++)
	{
		boardCards[NB_MAX_GOAL_KEEPER + i] = &defencersOne[i];
	}
	//attaquant joueur 1
	for (i = 0; i < NB_MAX_STRIKER; i++)
	{
		boardCards[NB_MAX_GOAL_KEEPER + NB_MAX_DEFENDER + i] = &strikersOne[i];
	}
	//gardien joueur 2
	for (i = 0; i < NB_MAX_GOAL_KEEPER; i++)
	{
		boardCards[NB_MAX_GOAL_KEEPER + NB_MAX_DEFENDER + NB_MAX_STRIKER + i] = &goalKeepersTwo[i];
	}
	//defenceurs joueur 2
	for (i = 0; i < NB_MAX_DEFENDER; i++)
	{
		boardCards[(NB_MAX_GOAL_KEEPER * 2) + NB_MAX_DEFENDER + NB_MAX_STRIKER + i] = &defencersTwo[i];
	}
	//attaquant joueur 2
	for (i = 0; i < NB_MAX_STRIKER; i++)
	{
		boardCards[((NB_MAX_GOAL_KEEPER + NB_MAX_DEFENDER) * 2) + NB_MAX_STRIKER + i] = &strikersTwo[i];
	}

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

bool Board::GetCardPlaceInfo(bool playerOne, CardType line, int indexPlace, CardPlaceInfo& info)
{
	switch (line)
	{
	case CardType::goalkeeper:
		if (indexPlace < 0 || indexPlace >= NB_MAX_GOAL_KEEPER)
			return false;

		info.card = playerOne ? &goalKeepersOne[indexPlace] : &goalKeepersTwo[indexPlace];
		if (!info.card->isInitialized || !info.card->isOnBoard)
			return false;
		info.line = line;
		info.hitbox = info.card->GetHitbox();
		info.indexPlace = indexPlace;
		info.playerOnePlace = playerOne;
		return true;
	case CardType::defender:
		if (indexPlace < 0 || indexPlace >= NB_MAX_DEFENDER)
			return false;

		info.card = playerOne ? &defencersOne[indexPlace] : &defencersTwo[indexPlace];
		if (!info.card->isInitialized || !info.card->isOnBoard)
			return false;
		info.line = line;
		info.hitbox = info.card->GetHitbox();
		info.indexPlace = indexPlace;
		info.playerOnePlace = playerOne;
		return true;
	case CardType::striker:
		if (indexPlace < 0 || indexPlace >= NB_MAX_STRIKER)
			return false;

		info.card = playerOne ? &strikersOne[indexPlace] : &strikersTwo[indexPlace];
		if (!info.card->isInitialized || !info.card->isOnBoard)
			return false;
		info.line = line;
		info.hitbox = info.card->GetHitbox();
		info.indexPlace = indexPlace;
		info.playerOnePlace = playerOne;
		return true;
	case CardType::spell:
		return true;
	default:
		return false;
	}
}

void Board::GetAdjacentCardsPlacesInfo(const CardPlaceInfo& current, std::vector<CardPlaceInfo>& adjacents)
{
	adjacents.clear();
	switch (current.line)
	{
	case CardType::goalkeeper:
		if (current.indexPlace < 0 || current.indexPlace >= NB_MAX_GOAL_KEEPER)
			return;

		if (current.playerOnePlace)
		{
			for (int i = 0; i < NB_MAX_DEFENDER; i++)
			{
				CardPlaceInfo cpi = CardPlaceInfo(current.playerOnePlace, CardType::defender, i, &defencersOne[i], Rectangle(defenderOnePos[i], cardSize));
				adjacents.push_back(cpi);
			}
		}
		else
		{
			for (int i = 0; i < NB_MAX_DEFENDER; i++)
			{
				CardPlaceInfo cpi = CardPlaceInfo(current.playerOnePlace, CardType::defender, i, &defencersTwo[i], Rectangle(defenderTwoPos[i], cardSize));
				adjacents.push_back(cpi);
			}
		}
		return;

	case CardType::defender:
	
		if (current.indexPlace < 0 || current.indexPlace >= NB_MAX_DEFENDER)
			return;

		if (current.playerOnePlace)
		{
			adjacents.push_back(CardPlaceInfo(current.playerOnePlace, CardType::goalkeeper, 0, &goalKeepersOne[0], Rectangle(goalKeeperOnePos[0], cardSize)));
			if (current.indexPlace == 0)
			{
				adjacents.push_back(CardPlaceInfo(current.playerOnePlace, CardType::defender, 1, &defencersOne[1], Rectangle(defenderOnePos[1], cardSize)));
				adjacents.push_back(CardPlaceInfo(current.playerOnePlace, CardType::striker, 0, &strikersOne[0], Rectangle(strikerOnePos[0], cardSize)));
				return;
			}
			if (current.indexPlace == NB_MAX_DEFENDER - 1)
			{
				adjacents.push_back(CardPlaceInfo(current.playerOnePlace, CardType::defender, current.indexPlace - 1, &defencersOne[current.indexPlace - 1], Rectangle(defenderOnePos[current.indexPlace - 1], cardSize)));
				adjacents.push_back(CardPlaceInfo(current.playerOnePlace, CardType::striker, NB_MAX_STRIKER - 1, &strikersOne[NB_MAX_STRIKER - 1], Rectangle(strikerOnePos[NB_MAX_STRIKER - 1], cardSize)));
				return;
			}

			adjacents.push_back(CardPlaceInfo(current.playerOnePlace, CardType::defender, current.indexPlace - 1, &defencersOne[current.indexPlace - 1], Rectangle(defenderOnePos[current.indexPlace - 1], cardSize)));
			adjacents.push_back(CardPlaceInfo(current.playerOnePlace, CardType::defender, current.indexPlace + 1, &defencersOne[current.indexPlace + 1], Rectangle(defenderOnePos[current.indexPlace + 1], cardSize)));
			adjacents.push_back(CardPlaceInfo(current.playerOnePlace, CardType::striker, current.indexPlace - 1, &strikersOne[current.indexPlace - 1], Rectangle(strikerOnePos[current.indexPlace - 1], cardSize)));
			adjacents.push_back(CardPlaceInfo(current.playerOnePlace, CardType::striker, current.indexPlace, &strikersOne[current.indexPlace], Rectangle(strikerOnePos[current.indexPlace], cardSize)));
		}
		else
		{
			adjacents.push_back(CardPlaceInfo(current.playerOnePlace, CardType::goalkeeper, 0, &goalKeepersTwo[0], Rectangle(goalKeeperTwoPos[0], cardSize)));
			if (current.indexPlace == 0)
			{
				adjacents.push_back(CardPlaceInfo(current.playerOnePlace, CardType::defender, 1, &defencersTwo[1], Rectangle(defenderTwoPos[1], cardSize)));
				adjacents.push_back(CardPlaceInfo(current.playerOnePlace, CardType::striker, 0, &strikersTwo[0], Rectangle(strikerTwoPos[0], cardSize)));
				return;
			}
			if (current.indexPlace == NB_MAX_DEFENDER - 1)
			{
				adjacents.push_back(CardPlaceInfo(current.playerOnePlace, CardType::defender, current.indexPlace - 1, &defencersTwo[current.indexPlace - 1], Rectangle(defenderTwoPos[current.indexPlace - 1], cardSize)));
				adjacents.push_back(CardPlaceInfo(current.playerOnePlace, CardType::striker, NB_MAX_STRIKER - 1, &strikersTwo[NB_MAX_STRIKER - 1], Rectangle(strikerTwoPos[NB_MAX_STRIKER - 1], cardSize)));
				return;
			}

			adjacents.push_back(CardPlaceInfo(current.playerOnePlace, CardType::defender, current.indexPlace - 1, &defencersTwo[current.indexPlace - 1], Rectangle(defenderTwoPos[current.indexPlace - 1], cardSize)));
			adjacents.push_back(CardPlaceInfo(current.playerOnePlace, CardType::defender, current.indexPlace + 1, &defencersTwo[current.indexPlace + 1], Rectangle(defenderTwoPos[current.indexPlace + 1], cardSize)));
			adjacents.push_back(CardPlaceInfo(current.playerOnePlace, CardType::striker, current.indexPlace - 1, &strikersTwo[current.indexPlace - 1], Rectangle(strikerTwoPos[current.indexPlace - 1], cardSize)));
			adjacents.push_back(CardPlaceInfo(current.playerOnePlace, CardType::striker, current.indexPlace, &strikersTwo[current.indexPlace], Rectangle(strikerTwoPos[current.indexPlace], cardSize)));
		}
		return;
	case CardType::striker:
		if (current.indexPlace < 0 || current.indexPlace >= NB_MAX_STRIKER)
			return;

		if (current.playerOnePlace)
		{
			//défensseurs
			adjacents.push_back(CardPlaceInfo(current.playerOnePlace, CardType::defender, current.indexPlace, &defencersOne[current.indexPlace], Rectangle(defenderOnePos[current.indexPlace], cardSize)));
			adjacents.push_back(CardPlaceInfo(current.playerOnePlace, CardType::defender, current.indexPlace + 1, &defencersOne[current.indexPlace + 1], Rectangle(defenderOnePos[current.indexPlace + 1], cardSize)));

			//attaquant allié
			if (current.indexPlace != 0)
			{
				adjacents.push_back(CardPlaceInfo(current.playerOnePlace, CardType::striker, current.indexPlace - 1, &strikersOne[current.indexPlace - 1], Rectangle(strikerOnePos[current.indexPlace - 1], cardSize)));
			}
			if (current.indexPlace != NB_MAX_STRIKER - 1)
			{
				adjacents.push_back(CardPlaceInfo(current.playerOnePlace, CardType::striker, current.indexPlace + 1, &strikersOne[current.indexPlace + 1], Rectangle(strikerOnePos[current.indexPlace + 1], cardSize)));
			}

			//attaquant d'en face
			adjacents.push_back(CardPlaceInfo(!current.playerOnePlace, CardType::striker, current.indexPlace, &strikersTwo[current.indexPlace], Rectangle(strikerTwoPos[current.indexPlace], cardSize)));
			if (current.indexPlace != 0)
			{
				adjacents.push_back(CardPlaceInfo(!current.playerOnePlace, CardType::striker, current.indexPlace - 1, &strikersTwo[current.indexPlace - 1], Rectangle(strikerTwoPos[current.indexPlace - 1], cardSize)));
			}
			if (current.indexPlace != NB_MAX_STRIKER - 1)
			{
				adjacents.push_back(CardPlaceInfo(!current.playerOnePlace, CardType::striker, current.indexPlace + 1, &strikersTwo[current.indexPlace + 1], Rectangle(strikerTwoPos[current.indexPlace + 1], cardSize)));
			}
		}
		else
		{
			//défensseurs
			adjacents.push_back(CardPlaceInfo(current.playerOnePlace, CardType::defender, current.indexPlace, &defencersTwo[current.indexPlace], Rectangle(defenderTwoPos[current.indexPlace], cardSize)));
			adjacents.push_back(CardPlaceInfo(current.playerOnePlace, CardType::defender, current.indexPlace + 1, &defencersTwo[current.indexPlace + 1], Rectangle(defenderTwoPos[current.indexPlace + 1], cardSize)));

			//attaquant allié
			if (current.indexPlace != 0)
			{
				adjacents.push_back(CardPlaceInfo(current.playerOnePlace, CardType::striker, current.indexPlace - 1, &strikersTwo[current.indexPlace - 1], Rectangle(strikerTwoPos[current.indexPlace - 1], cardSize)));
			}
			if (current.indexPlace != NB_MAX_STRIKER - 1)
			{
				adjacents.push_back(CardPlaceInfo(current.playerOnePlace, CardType::striker, current.indexPlace + 1, &strikersTwo[current.indexPlace + 1], Rectangle(strikerTwoPos[current.indexPlace + 1], cardSize)));
			}

			//attaquant d'en face
			adjacents.push_back(CardPlaceInfo(!current.playerOnePlace, CardType::striker, current.indexPlace, &strikersOne[current.indexPlace], Rectangle(strikerOnePos[current.indexPlace], cardSize)));
			if (current.indexPlace != 0)
			{
				adjacents.push_back(CardPlaceInfo(!current.playerOnePlace, CardType::striker, current.indexPlace - 1, &strikersOne[current.indexPlace - 1], Rectangle(strikerOnePos[current.indexPlace - 1], cardSize)));
			}
			if (current.indexPlace != NB_MAX_STRIKER - 1)
			{
				adjacents.push_back(CardPlaceInfo(!current.playerOnePlace, CardType::striker, current.indexPlace + 1, &strikersOne[current.indexPlace + 1], Rectangle(strikerOnePos[current.indexPlace + 1], cardSize)));
			}
		}
		return;
	case CardType::spell:
		return;
	default:
		return;
	}
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
			info.card = &this->goalKeepersOne[i];
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
			info.card = &this->defencersOne[i];
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
			info.card = &this->strikersOne[i];
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
			info.card = &this->goalKeepersTwo[i];
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
			info.card = &this->defencersTwo[i];
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
			info.card = &this->strikersTwo[i];
			info.line = CardType::striker;
			info.playerOnePlace = false;
			info.hitbox = hitbox;
			return true;
		}
	}

	return false;
}

void Board::PlaceCard(Card& boardCard, const Card& newCard, CardPlaceInfo& placeInfo, int globalIndex = 0)
{
	boardCard = newCard;
	boardCard.isOnBoard = true;
	boardCard.isSelected = false;
	boardCard.cardPlaceInfo = CardPlaceInfo(placeInfo);
	boardCards[globalIndex] = &boardCard;
}

void Board::PlaceCard(Card& card, bool playerOneBoard, CardType line, int indexPlace)
{
	if (!CanPlaceCard(card, playerOneBoard, line, indexPlace))
		return;
	
	switch (line)
	{
	case CardType::goalkeeper:
		if (playerOneBoard)
		{
			CardPlaceInfo cpi = CardPlaceInfo(playerOneBoard, line, indexPlace, &card, Rectangle(goalKeeperOnePos[indexPlace], cardSize));
			PlaceCard(goalKeepersOne[indexPlace], card, cpi, indexPlace);
		}
		else
		{
			CardPlaceInfo cpi = CardPlaceInfo(playerOneBoard, line, indexPlace, &card, Rectangle(goalKeeperTwoPos[indexPlace], cardSize));
			PlaceCard(goalKeepersTwo[indexPlace], card, cpi, ((NB_MAX_DEFENDER + NB_MAX_STRIKER) * 2) + NB_MAX_GOAL_KEEPER - 1 + indexPlace);
		}
		break;
	case CardType::defender:
		if (playerOneBoard)
		{
			CardPlaceInfo cpi = CardPlaceInfo(playerOneBoard, line, indexPlace, &card, Rectangle(defenderOnePos[indexPlace], cardSize));
			PlaceCard(defencersOne[indexPlace], card, cpi, NB_MAX_GOAL_KEEPER + indexPlace);
		}
		else
		{
			CardPlaceInfo cpi = CardPlaceInfo(playerOneBoard, line, indexPlace, &card, Rectangle(defenderTwoPos[indexPlace], cardSize));
			PlaceCard(defencersTwo[indexPlace], card, cpi, NB_MAX_GOAL_KEEPER + NB_MAX_DEFENDER + 2 * NB_MAX_STRIKER + indexPlace);
		}
		break;
	case CardType::striker:
		if (playerOneBoard)
		{
			CardPlaceInfo cpi = CardPlaceInfo(playerOneBoard, line, indexPlace, &card, Rectangle(strikerOnePos[indexPlace], cardSize));
			PlaceCard(strikersOne[indexPlace], card, cpi, NB_MAX_GOAL_KEEPER + NB_MAX_DEFENDER + indexPlace);
		}
		else
		{
			CardPlaceInfo cpi = CardPlaceInfo(playerOneBoard, line, indexPlace, &card, Rectangle(strikerTwoPos[indexPlace], cardSize));
			PlaceCard(strikersTwo[indexPlace], card, cpi, NB_MAX_GOAL_KEEPER + NB_MAX_DEFENDER + NB_MAX_STRIKER + indexPlace);
		}
		break;
	default:
		break;
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
			CardPlaceInfo cpi = CardPlaceInfo(playerOneCards, goalKeepersOne[i].cardType(), i, &goalKeepersOne[i], Rectangle(goalKeeperOnePos[i], cardSize));
			res.push_back(cpi);
		}
	}

	//defenceurs joueur 1
	for (int i = 0; i < NB_MAX_DEFENDER; i++)
	{
		if (defencersOne[i].isInitialized && defencersOne[i].isPlayerOneCard == playerOneCards)
		{
			CardPlaceInfo cpi = CardPlaceInfo(playerOneCards, defencersOne[i].cardType(), i, &defencersOne[i], Rectangle(defenderOnePos[i], cardSize));
			res.push_back(cpi);
		}
	}

	//attaquant joueur 1
	for (int i = 0; i < NB_MAX_STRIKER; i++)
	{
		if (strikersOne[i].isInitialized && strikersOne[i].isPlayerOneCard == playerOneCards)
		{
			CardPlaceInfo cpi = CardPlaceInfo(playerOneCards, strikersOne[i].cardType(), i, &strikersOne[i], Rectangle(strikerOnePos[i], cardSize));
			res.push_back(cpi);
		}
	}

	//gardien joueur 2
	for (int i = 0; i < NB_MAX_GOAL_KEEPER; i++)
	{
		if (goalKeepersTwo[i].isInitialized && goalKeepersTwo[i].isPlayerOneCard == playerOneCards)
		{
			CardPlaceInfo cpi = CardPlaceInfo(playerOneCards, goalKeepersTwo[i].cardType(), i, &strikersOne[i], Rectangle(goalKeeperTwoPos[i], cardSize));
			res.push_back(cpi);
		}
	}

	//defenceurs joueur 2
	for (int i = 0; i < NB_MAX_DEFENDER; i++)
	{
		if (defencersTwo[i].isInitialized && strikersOne[i].isPlayerOneCard == playerOneCards)
		{
			CardPlaceInfo cpi = CardPlaceInfo(playerOneCards, defencersTwo[i].cardType(), i, &defencersTwo[i], Rectangle(defenderTwoPos[i], cardSize));
			res.push_back(cpi);
		}
	}

	//attaquant joueur 2
	for (int i = 0; i < NB_MAX_STRIKER; i++)
	{
		if (strikersTwo[i].isInitialized && strikersTwo[i].isPlayerOneCard == playerOneCards)
		{
			CardPlaceInfo cpi = CardPlaceInfo(playerOneCards, strikersTwo[i].cardType(), i, &strikersOne[i], Rectangle(strikerTwoPos[i], cardSize));
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

	//Update des cartes
	for (int i = 0; i < NB_MAX_CARD_IN_BOARD; i++)
	{
		boardCards[i]->Update(window);
	}

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