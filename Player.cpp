#include "AssetsManager.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "InputManager.hpp"
#include <vector>
#include "EventManager.hpp"

using namespace std; 
using namespace sf;

void Player::Start()
{
	ReStart();
	nbGoals = 0;
	scoreText.setFont(AssetsManager::Instance().GetFont("poppins"));
	scoreText.setCharacterSize(50);
	scoreText.setFillColor(Color::White);
	this->deck.player = this;
}

void Player::ReStart()
{
	isMyTurn = false;
	deck.Start();
	hand.Start();
	hand.player = this;
	mana = 1;
	isABoardCardSelected = false;
}

void Player::DeSelectAllCards()
{
	if (isABoardCardSelected)
	{
		isABoardCardSelected = false;
		cardBoardSelected.card->isSelected = false;
	}
}

void Player::Update(RenderWindow& window)
{
	//On selection une carte sur le plateau de jeu
	if (isMyTurn)
	{
		if (InputManager::Instance().GetKeyDown(Mouse::Button::Left) && !hand.IsSelected())
		{
			CardPlaceInfo info;
			if (Board::Instance().GetCardPlaceInfo(InputManager::Instance().MousePosition(), info))
			{
				if (info.card->isInitialized && info.card->isOnBoard && info.card->isPlayerOneCard == isPlayerOne)
				{
					if (!isABoardCardSelected)
					{
						if (info.card->isInitialized && info.card->isPlayerOneCard == isPlayerOne)
						{
							hand.DeselectAllCard();
							isABoardCardSelected = true;
							cardBoardSelected = CardPlaceInfo(info);
							cardBoardSelected.card->isSelected = true;
							cout << cardBoardSelected.card->name() << " is selected" << endl;
						}
					}
					else
					{
						if (info.card->isPlayerOneCard == isPlayerOne)
						{
							hand.DeselectAllCard();
							cardBoardSelected.card->isSelected = false;
							cout << cardBoardSelected.card->name() << " is deselected" << endl;
							cardBoardSelected = CardPlaceInfo(info);
							cardBoardSelected.card->isSelected = true;
							cout << cardBoardSelected.card->name() << " is selected" << endl;
						}
						else
						{
							if (cardBoardSelected.card->CanAttack(cardBoardSelected, info))
							{
								Board::Instance().MakeDuel(cardBoardSelected, info);
							}
							else
							{
								isABoardCardSelected = false;
								cardBoardSelected.card->isSelected = false;
								cout << cardBoardSelected.card->name() << " is deselected" << endl;
							}
						}
					}
				}
			}
			else
			{
				DeSelectAllCards();
			}
		}
	}

	//on actualise la main
	hand.Update(window);

	//On actualise le deck
	deck.Update(window);

	//on place la carte selectionner de la main sur le plateau
	if (isMyTurn)
	{
		if (!hand.IsSelected() && hand.isACardSelected && !isABoardCardSelected && InputManager::Instance().GetKeyDown(Mouse::Button::Left))
		{
			CardPlaceInfo info;
			if (Board::Instance().GetCardPlaceInfo(InputManager::Instance().MousePosition(), info))
			{
				if (info.playerOnePlace == isPlayerOne)
				{
					//on place la carte sur le plateau
					Card card;
					hand.GetSelectedCard(card);
					if (Board::Instance().CanPlaceCard(card, isPlayerOne, info.line, info.indexPlace))
					{
						Board::Instance().PlaceCard(card, isPlayerOne, info.line, info.indexPlace);
						hand.RemoveCard(card);
						hand.DeselectAllCard();
					}
				}
			}
		}
	}

	//On regarde si on a marque un but
	if (isMyTurn)
	{
		CardPlaceInfo info;
		Board::Instance().GetCardPlaceInfo(!isPlayerOne, CardType::goalkeeper, 0, info);
		if (info.card->isInitialized && info.card->isOnBoard && info.card->haveTheBall && info.card->isPlayerOneCard == isPlayerOne)
		{
			EventManager::Instance().OnMakeGoal(*info.card, *this);
		}
	}

	//le text de score
	scoreText.setString(to_string(this->nbGoals));
	
	scoreText.setPosition(isPlayerOne ? (scoreTextPosPlayerOne) : (scoreTextPosPlayerTwo - Vector2f(scoreText.getLocalBounds().width, 0)));
}

void Player::Draw(RenderWindow& window)
{
	hand.Draw(window);
	deck.Draw(window);
	window.draw(scoreText);
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

void Player::DrawCard()
{
	Card drawCard;
	if (this->deck.DrawCard(drawCard))
	{
		this->hand.AddCard(drawCard);
	}
}

void Player::Clear()
{
	this->deck.Clear();
	this->hand.Clear();
	this->mana = 0;
}

void Player::OnBeginTurn(bool isPlayerOneTurn)
{
	if (isPlayerOne == isPlayerOneTurn)
	{
		hand.DeselectAllCard();
		DrawCard();
	}
}

void Player::OnEndTurn(bool isPlayerOneEndTurn)
{
	if (isPlayerOne == isPlayerOneEndTurn)
	{
		hand.DeselectAllCard();
	}
}

void Player::OnMakeGoal(Card& card)
{
	this->nbGoals++;
}