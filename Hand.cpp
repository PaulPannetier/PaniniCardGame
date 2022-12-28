
#include "Hand.hpp"
#include "Player.hpp"

using namespace std;
using namespace sf;

Hand::Hand()
{

}

void Hand::Start()
{
	isACardSelected = isSelected = false;
	indexCardSelected = -1;
	indexLastCard = -1;
	player = nullptr;
}

void Hand::Update(sf::RenderWindow& window)
{

}

void Hand::Draw(sf::RenderWindow& window)
{
	if (player->isMyTurn)
	{
		if (isSelected)
		{
			Rectangle::DrawWire(window, recSelected, Color::Blue);
		}
		else
		{
			Rectangle::DrawWire(window, recNotSelected, Color::Blue);
		}
	}
	else
	{
		Rectangle::DrawWire(window, recNotHerTurn, Color::Blue);
	}
}

bool Hand::IsFull() const
{
	return indexLastCard >= MAX_HAND_SIZE - 1;
}

bool Hand::AddCard(const Card& card)
{
	if (IsFull())
		return false;

	indexLastCard++;
	this->cards[indexLastCard] = Card(card);
	return true;
}
bool Hand::RemoveCard(const Card& card)
{
	if (indexLastCard < 0)
		return false;
	for (int i = 0; i < MAX_HAND_SIZE; i++)
	{
		if (cards[i].isInitialized && !cards[i].isOnBoard)
		{
			if (cards[i].id == card.id)
			{
				for (int j = i; j < MAX_HAND_SIZE - 1; j++)
				{
					cards[j] = Card(cards[j + 1]);
				}
				cards[MAX_HAND_SIZE - 1].isInitialized = false;
				return true;
			}
		}
	}
	return false;
}