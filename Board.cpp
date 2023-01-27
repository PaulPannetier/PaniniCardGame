#include "EventManager.hpp"
#include "Board.hpp"
#include "Collider2D.hpp"
#include "AssetsManager.hpp"
#include "GameManager.hpp"
#include "Ball.hpp"

using namespace std;
using namespace sf;

void Board::OnClickEndTurnButtonAction(const Button& button)
{
	Player& player = player1.isMyTurn ? player1 : player2;
	Player& otherPlayer = player1.isMyTurn ? player2 : player1;
	player.isMyTurn = false;
	EventManager::Instance().OnEndTurn(player.isPlayerOne);
	otherPlayer.isMyTurn = true;
	EventManager::Instance().OnBeginTurn(otherPlayer.isPlayerOne);
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

#include "RonaldoCard.hpp"

void Board::Start()
{
	endTurnButton = Button(Rectangle(Vector2f(1500, 800), Vector2f(50, 50)), OnClickEndTurnButton);
	Texture& bgText = AssetsManager::Instance().GetTexture("BoardBackground");
	background.setTexture(bgText);
	Vector2f windowSize = GameManager::Instance().GetWindowSize();//marche pas
	Vector2f textureSize = Vector2f(bgText.getSize());
	Vector2f scale = Vector2f(1600 / textureSize.x, 900 / textureSize.y);

	Clear();

	//start the ball
	Ball::Instance().Start();
	//on met la balle au centre du terrain
	Card* cardWidthTheBall = Random::Rand() >= 0.5f ? &strikersOne[Random::Rand(1,2)] : &strikersTwo[Random::Rand(1, 2)];
	Ball::Instance().SetAttachCard(*cardWidthTheBall);

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

	EventManager::Instance().OnBeginTurn(true);
}

void Board::ReStart()
{
	Clear();
	player1.Clear();
	player2.Clear();

	Card* cardWidthTheBall = Random::Rand() >= 0.5f ? &strikersOne[Random::Rand(1, 2)] : &strikersTwo[Random::Rand(1, 2)];
	Ball::Instance().SetAttachCard(*cardWidthTheBall);

	player1.isPlayerOne = true;
	player1.ReStart();
	player2.isPlayerOne = false;
	player2.ReStart();
	FillDeck();
	player1.FirstDraw(NB_BEGIN_CARDS);
	player2.FirstDraw(NB_BEGIN_CARDS);
	player1.isMyTurn = true;
	EventManager::Instance().OnBeginTurn(true);
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
		CardsManager::CardNum::Pavard,
		CardsManager::CardNum::Ronaldo,
		CardsManager::CardNum::Ronaldo,
		CardsManager::CardNum::Ronaldo
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
		CardsManager::CardNum::Pavard,
		CardsManager::CardNum::Ronaldo,
		CardsManager::CardNum::Ronaldo,
		CardsManager::CardNum::Ronaldo

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
			if (goalKeepersOne[indexPlace].isInitialized)
				return false;
			return true;
		}
		if (goalKeepersTwo[indexPlace].isInitialized)
			return false;
		return true;
	case CardType::defender:
		if (indexPlace >= NB_MAX_DEFENDER)
			return false;
		if (playerOneBoard)
		{
			if (defencersOne[indexPlace].isInitialized)
				return false;
			return true;
		}
		if (defencersTwo[indexPlace].isInitialized)
			return false;
		return true;
	case CardType::striker:
		if (indexPlace >= NB_MAX_STRIKER)
			return false;
		if (playerOneBoard)
		{
			if (strikersOne[indexPlace].isInitialized)
				return false;
			return true;
		}
		if (strikersTwo[indexPlace].isInitialized)
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
		if (hitbox.Contains(position))
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
		if (hitbox.Contains(position))
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
		if (hitbox.Contains(position))
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
		if (hitbox.Contains(position))
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
		if (hitbox.Contains(position))
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
		if (hitbox.Contains(position))
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
	bool boardCardHaveTheBall = boardCard.haveTheBall;
	boardCard = newCard;
	boardCard.isOnBoard = true;
	boardCard.isSelected = false;
	boardCard.cardPlaceInfo = CardPlaceInfo(placeInfo);
	boardCard.cardPlaceInfo.card = &boardCard;
	boardCard.OnPlaceOnBoard();
	boardCards[globalIndex] = &boardCard;
	if (boardCardHaveTheBall)
	{
		Ball::Instance().SetAttachCard(boardCard);
	}
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

void Board::SwitchCards(const CardPlaceInfo& card1, const CardPlaceInfo& card2)
{
	CardPlaceInfo tmp = CardPlaceInfo(card1);
	Card tmpCard = Card(*tmp.card);

	CardPlaceInfo tmp2 = CardPlaceInfo(card2);
	Card tmpCard2 = Card(*tmp2.card);

	//replace card1 by card2
	switch (card1.line)
	{
	case CardType::goalkeeper:
		if (card1.playerOnePlace)
		{
			goalKeepersOne[tmp.indexPlace] = Card(*card2.card);
			goalKeepersOne[tmp.indexPlace].cardPlaceInfo = CardPlaceInfo(tmp.playerOnePlace, CardType::goalkeeper, tmp.indexPlace, &goalKeepersOne[tmp.indexPlace], tmp.hitbox);
		}
		else
		{
			goalKeepersTwo[tmp.indexPlace] = Card(*card2.card);
			goalKeepersTwo[tmp.indexPlace].cardPlaceInfo = CardPlaceInfo(tmp.playerOnePlace, CardType::goalkeeper, tmp.indexPlace, &goalKeepersTwo[tmp.indexPlace], tmp.hitbox);
		}
		break;
	case CardType::defender:
		if (card1.playerOnePlace)
		{
			defencersOne[tmp.indexPlace] = Card(*card2.card);
			defencersOne[tmp.indexPlace].cardPlaceInfo = CardPlaceInfo(tmp.playerOnePlace, CardType::defender, tmp.indexPlace, &defencersOne[tmp.indexPlace], tmp.hitbox);
		}
		else
		{
			defencersTwo[tmp.indexPlace] = Card(*card2.card);
			defencersTwo[tmp.indexPlace].cardPlaceInfo = CardPlaceInfo(tmp.playerOnePlace, CardType::defender, tmp.indexPlace, &defencersTwo[tmp.indexPlace], tmp.hitbox);
		}
		break;
	case CardType::striker:
		if (card1.playerOnePlace)
		{
			strikersOne[tmp.indexPlace] = Card(*card2.card);
			strikersOne[tmp.indexPlace].cardPlaceInfo = CardPlaceInfo(tmp.playerOnePlace, CardType::striker, tmp.indexPlace, &strikersOne[tmp.indexPlace], tmp.hitbox);
		}
		else
		{
			strikersTwo[tmp.indexPlace] = Card(*card2.card);
			strikersTwo[tmp.indexPlace].cardPlaceInfo = CardPlaceInfo(tmp.playerOnePlace, CardType::striker, tmp.indexPlace, &strikersTwo[tmp.indexPlace], tmp.hitbox);
		}
		break;
	case CardType::spell:
		return;
	default:
		return;
	}

	//replace card2 by the copy of card1
	switch (card2.line)
	{
	case CardType::goalkeeper:
		if (card2.playerOnePlace)
		{
			goalKeepersOne[tmp2.indexPlace] = Card(tmpCard);
			goalKeepersOne[tmp2.indexPlace].cardPlaceInfo = CardPlaceInfo(tmp2.playerOnePlace, CardType::goalkeeper, tmp2.indexPlace, &goalKeepersOne[tmp2.indexPlace], tmp2.hitbox);
		}
		else
		{
			goalKeepersTwo[tmp2.indexPlace] = Card(tmpCard);
			goalKeepersTwo[tmp2.indexPlace].cardPlaceInfo = CardPlaceInfo(tmp2.playerOnePlace, CardType::goalkeeper, tmp2.indexPlace, &goalKeepersTwo[tmp2.indexPlace], tmp2.hitbox);
		}
		break;
	case CardType::defender:
		if (card2.playerOnePlace)
		{
			defencersOne[tmp2.indexPlace] = Card(tmpCard);
			defencersOne[tmp2.indexPlace].cardPlaceInfo = CardPlaceInfo(tmp2.playerOnePlace, CardType::defender, tmp2.indexPlace, &defencersOne[tmp2.indexPlace], tmp2.hitbox);
		}
		else
		{
			defencersTwo[tmp2.indexPlace] = Card(tmpCard);
			defencersTwo[tmp2.indexPlace].cardPlaceInfo = CardPlaceInfo(tmp2.playerOnePlace, CardType::defender, tmp2.indexPlace, &defencersTwo[tmp2.indexPlace], tmp2.hitbox);
		}
		break;
	case CardType::striker:
		if (card2.playerOnePlace)
		{
			strikersOne[tmp2.indexPlace] = Card(tmpCard);
			strikersOne[tmp2.indexPlace].cardPlaceInfo = CardPlaceInfo(tmp2.playerOnePlace, CardType::striker, tmp2.indexPlace, &strikersOne[tmp2.indexPlace], tmp2.hitbox);
		}
		else
		{
			strikersTwo[tmp2.indexPlace] = Card(tmpCard);
			strikersTwo[tmp2.indexPlace].cardPlaceInfo = CardPlaceInfo(tmp2.playerOnePlace, CardType::striker, tmp2.indexPlace, &strikersTwo[tmp2.indexPlace], tmp2.hitbox);
		}
		break;
	case CardType::spell:
		return;
	default:
		return;
	}

	EventManager::Instance().OnCardsSwitched(card1, card2);
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

void Board::ClearPlace(const CardPlaceInfo& place)
{
	CardPlaceInfo tmp = CardPlaceInfo(place);
	switch (tmp.line)
	{
	case CardType::goalkeeper:
		if (tmp.playerOnePlace)
		{
			goalKeepersOne[tmp.indexPlace] = Card();
			goalKeepersOne[tmp.indexPlace].isOnBoard = goalKeepersOne[tmp.indexPlace].isPlayerOneCard = true;
			goalKeepersOne[tmp.indexPlace].cardPlaceInfo = CardPlaceInfo(true, CardType::goalkeeper, tmp.indexPlace, &goalKeepersOne[tmp.indexPlace], Rectangle(goalKeeperOnePos[tmp.indexPlace], cardSize));
			goalKeepersOne[tmp.indexPlace].CalculateCardBoardTransform();
		}
		else
		{
			goalKeepersTwo[tmp.indexPlace] = Card();
			goalKeepersTwo[tmp.indexPlace].isOnBoard = true;
			goalKeepersTwo[tmp.indexPlace].isPlayerOneCard = false;
			goalKeepersTwo[tmp.indexPlace].cardPlaceInfo = CardPlaceInfo(false, CardType::goalkeeper, tmp.indexPlace, &goalKeepersTwo[tmp.indexPlace], Rectangle(goalKeeperTwoPos[tmp.indexPlace], cardSize));
			goalKeepersTwo[tmp.indexPlace].CalculateCardBoardTransform();
		}
		break;
	case CardType::defender:
		if (tmp.playerOnePlace)
		{
			defencersOne[tmp.indexPlace] = Card();
			defencersOne[tmp.indexPlace].isOnBoard = defencersOne[tmp.indexPlace].isPlayerOneCard = true;
			defencersOne[tmp.indexPlace].cardPlaceInfo = CardPlaceInfo(true, CardType::defender, tmp.indexPlace, &defencersOne[tmp.indexPlace], Rectangle(defenderTwoPos[tmp.indexPlace], cardSize));
			defencersOne[tmp.indexPlace].CalculateCardBoardTransform();
		}
		else
		{
			defencersTwo[tmp.indexPlace] = Card();
			defencersTwo[tmp.indexPlace].isOnBoard = true;
			defencersTwo[tmp.indexPlace].isPlayerOneCard = false;
			defencersTwo[tmp.indexPlace].cardPlaceInfo = CardPlaceInfo(false, CardType::defender, tmp.indexPlace, &defencersTwo[tmp.indexPlace], Rectangle(defenderTwoPos[tmp.indexPlace], cardSize));
			defencersTwo[tmp.indexPlace].CalculateCardBoardTransform();
		}
		break;
	case CardType::striker:
		if (tmp.playerOnePlace)
		{
			strikersOne[tmp.indexPlace] = Card();
			strikersOne[tmp.indexPlace].isOnBoard = strikersOne[tmp.indexPlace].isPlayerOneCard = true;
			strikersOne[tmp.indexPlace].cardPlaceInfo = CardPlaceInfo(true, CardType::striker, tmp.indexPlace, &strikersOne[tmp.indexPlace], Rectangle(strikerOnePos[tmp.indexPlace], cardSize));
			strikersOne[tmp.indexPlace].CalculateCardBoardTransform();
		}
		else
		{
			strikersTwo[tmp.indexPlace] = Card();
			strikersTwo[tmp.indexPlace].isOnBoard = true;
			strikersTwo[tmp.indexPlace].isPlayerOneCard = false;
			strikersTwo[tmp.indexPlace].cardPlaceInfo = CardPlaceInfo(false, CardType::striker, tmp.indexPlace, &strikersTwo[tmp.indexPlace], Rectangle(strikerTwoPos[tmp.indexPlace], cardSize));
			strikersTwo[tmp.indexPlace].CalculateCardBoardTransform();
		}
		break;
	case CardType::spell:
		return;
	default:
		return;
	}
}

void Board::MakeDuel(const CardPlaceInfo& striker, const CardPlaceInfo& defender)
{
	cout << "Duel betwenn : " << striker.card->name() << " and " << defender.card->name() << endl;
	EventManager::Instance().OnMakeDuel(striker, defender);
	int attack = striker.card->attack() + striker.card->attackBonus;
	int defence = defender.card->defence() + defender.card->defenceBonus;
	bool oneOfThemHaveTheball = striker.card->haveTheBall || defender.card->haveTheBall;
	if (oneOfThemHaveTheball)
	{
		Ball::Instance().DeSetAttachCard();
		striker.card->haveTheBall = defender.card->haveTheBall = false;
	}

	if (attack > defence)
	{
		CardPlaceInfo tmp = CardPlaceInfo(striker);
		SwitchCards(striker, defender);
		ClearPlace(tmp);
		if (oneOfThemHaveTheball)
		{
			Ball::Instance().SetAttachCard(*defender.card);
		}
	}
	else
	{
		ClearPlace(striker);
		if (oneOfThemHaveTheball)
		{
			Ball::Instance().SetAttachCard(*defender.card);
		}
	}
}

void Board::Clear()
{
	int i;
	for (i = 0; i < NB_MAX_GOAL_KEEPER; i++)
	{
		ClearPlace(CardPlaceInfo(true, CardType::goalkeeper, i, nullptr, Rectangle()));
		boardCards[i] = &goalKeepersOne[i];
		ClearPlace(CardPlaceInfo(false, CardType::goalkeeper, i, nullptr, Rectangle()));
		boardCards[NB_MAX_GOAL_KEEPER + NB_MAX_DEFENDER + NB_MAX_STRIKER + i] = &goalKeepersTwo[i];
	}
	//defenceurs joueur 1
	for (i = 0; i < NB_MAX_DEFENDER; i++)
	{
		ClearPlace(CardPlaceInfo(true, CardType::defender, i, nullptr, Rectangle()));
		boardCards[NB_MAX_GOAL_KEEPER + i] = &defencersOne[i];
		ClearPlace(CardPlaceInfo(false, CardType::defender, i, nullptr, Rectangle()));
		boardCards[(NB_MAX_GOAL_KEEPER * 2) + NB_MAX_DEFENDER + NB_MAX_STRIKER + i] = &defencersTwo[i];
	}
	//attaquant joueur 1
	for (i = 0; i < NB_MAX_STRIKER; i++)
	{
		ClearPlace(CardPlaceInfo(true, CardType::striker, i, nullptr, Rectangle()));
		boardCards[NB_MAX_GOAL_KEEPER + NB_MAX_DEFENDER + i] = &strikersOne[i];
		ClearPlace(CardPlaceInfo(false, CardType::striker, i, nullptr, Rectangle()));
		boardCards[((NB_MAX_GOAL_KEEPER + NB_MAX_DEFENDER) * 2) + NB_MAX_STRIKER + i] = &strikersTwo[i];
	}
}

void Board::OnMakeDuel(const CardPlaceInfo& striker, const CardPlaceInfo& defender)
{
	for (int i = 0; i < NB_MAX_CARD_IN_BOARD; i++)
	{
		this->boardCards[i]->OnMakeDuel(striker, defender);
	}
}

void Board::OnBeginTurn(bool isPlayerOneTurn)
{
	for (int i = 0; i < NB_MAX_CARD_IN_BOARD; i++)
	{
		boardCards[i]->OnBeginTurn(isPlayerOneTurn);
	}
	player1.OnBeginTurn(isPlayerOneTurn);
	player2.OnBeginTurn(isPlayerOneTurn);
}

void Board::OnEndTurn(bool isPlayerOneEndTurn)
{
	for (int i = 0; i < NB_MAX_CARD_IN_BOARD; i++)
	{
		boardCards[i]->OnEndTurn(isPlayerOneEndTurn);
	}
	player1.OnEndTurn(isPlayerOneEndTurn);
	player2.OnEndTurn(isPlayerOneEndTurn);
}

void Board::OnMakeGoal(Card& card, Player& player)
{
	ReStart();
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

	Ball::Instance().Update(window);

	endTurnButton.Update(window);
}

//Affiche le plateau de jeu
void Board::Draw(RenderWindow& window)
{
	//afficher le background
	window.draw(background);

	int i;
	//Le joueur du haut
	//le goal
	for (i = 0; i < NB_MAX_GOAL_KEEPER; i++)
	{
		if (this->goalKeepersOne[i].isInitialized && this->goalKeepersOne[i].isOnBoard)
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
		if (this->defencersOne[i].isInitialized && this->defencersOne[i].isOnBoard)
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
		if (this->strikersOne[i].isInitialized && this->strikersOne[i].isOnBoard)
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
		if (this->goalKeepersTwo[i].isInitialized && this->goalKeepersTwo[i].isOnBoard)
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
		if (this->defencersTwo[i].isInitialized && this->defencersTwo[i].isOnBoard)
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
		if (this->strikersTwo[i].isInitialized && this->strikersTwo[i].isOnBoard)
		{
			this->strikersTwo[i].Draw(window);
		}
		else
		{
			Rectangle::DrawWire(window, this->strikerTwoPos[i], this->cardSize, Color::Green, 3.0f);
		}
	}

	//la balle
	Ball::Instance().Draw(window);

	//les boutons
	endTurnButton.Draw(window);

	//les joueurs
	player1.Draw(window);
	player2.Draw(window);
}