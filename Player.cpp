
#include "Player.hpp"
#include <vector>

using namespace std; 
using namespace sf;

void Player::Start()
{
	isMyTurn = false;
	deck.Start();
	hand.Start();
	hand.player = this;
}

void Player::Update(RenderWindow& window)
{
	if (isMyTurn)
	{
		hand.Update(window);
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
		this->deck.AddCard(CardsManager::Instance().GetCard(cards[i]));
	}
	deck.Shuffle();
}

void Player::FirstDraw(int nbCards)
{
	Card drawCard;
	for (int i = 0; i < nbCards; i++)
	{
		if (this->deck.Draw(drawCard))
		{
			this->hand.AddCard(drawCard);
		}
	}
}