
#include "Player.hpp"
#include "Board.hpp"
#include "InputManager.hpp"
#include <vector>

using namespace std; 
using namespace sf;

void Player::Start()
{
	isMyTurn = false;
	deck.Start();
	hand.Start();
	hand.player = this;
	mana = 1;
	isABoardCardSelected = false;
}

void Player::Update(RenderWindow& window)
{
	//On selection une carte sur le plateau de jeu
	if (isMyTurn)
	{
		if (InputManager::Instance().GetKeyDown(Mouse::Button::Left))
		{
			CardPlaceInfo info;
			if (Board::Instance().GetCardPlaceInfo(InputManager::Instance().MousePosition(), info))
			{
				if (!isABoardCardSelected)
				{
					if (info.card->isInitialized && info.card->isPlayerOneCard == isPlayerOne)
					{
						isABoardCardSelected = true;
						cardBoardSelected = CardPlaceInfo(info);
						cardBoardSelected.card->isSelected = true;
						cout << cardBoardSelected.card->name() << endl;
					}
				}
				else
				{
					if (info.card->isPlayerOneCard == isPlayerOne)
					{
						cardBoardSelected = CardPlaceInfo(info);
						cardBoardSelected.card->isSelected = true;
						cout << cardBoardSelected.card->name() << endl;
					}
					else
					{
						if (cardBoardSelected.card->CanAttack(cardBoardSelected, info))
						{
							//trade entre les deux!
							Board::Instance().MakeDuel(cardBoardSelected, info);
						}
					}
				}
			}
		}
	}

	//on actualise la main
	hand.Update(window);

	//on place la carte selectionner sur le plateau
	if (isMyTurn)
	{
		if (!hand.IsSelected() && hand.isACardSelected && InputManager::Instance().GetKeyDown(Mouse::Button::Left))
		{
			CardPlaceInfo info;
			if (Board::Instance().GetCardPlaceInfo(InputManager::Instance().MousePosition(), info))
			{
				if (false)
				{
					cout << info.card->ToString() << endl;
					cout << info.indexPlace << endl;
					cout << info.line << endl;
					cout << to_string(info.playerOnePlace) << endl << endl;
				}

				if (info.playerOnePlace == isPlayerOne)
				{
					//on place la carte sur le plateau
					Card card;
					hand.GetSelectedCard(card);
					if (Board::Instance().CanPlaceCard(card, isPlayerOne, info.line, info.indexPlace))
					{
						Board::Instance().PlaceCard(card, isPlayerOne, info.line, info.indexPlace);
						hand.RemoveCard(card);
					}
				}
			}
		}
	}
}

void Player::Draw(RenderWindow& window)
{
	hand.Draw(window);
}

void Player::FillDeck(vector<CardsManager::CardNum>& cards)
{
	for (int i = 0; i < cards.size(); i++)
	{
		Card card = CardsManager::Instance().GetCard(cards[i]);
		card.isPlayerOneCard = this->isPlayerOne;
		this->deck.AddCard(card);
	}
	deck.Shuffle();
}

void Player::FirstDraw(int nbCards)
{
	Card drawCard;
	for (int i = 0; i < nbCards; i++)
	{
		if (this->deck.DrawCard(drawCard))
		{
			this->hand.AddCard(drawCard);
		}
	}
}

void Player::BeginTurn()
{

}

void Player::EndTurn()
{

}