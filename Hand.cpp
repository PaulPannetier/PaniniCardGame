
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

void Hand::Update(RenderWindow& window)
{

}

void Hand::Draw(RenderWindow& window)
{
	if (player->isMyTurn)
	{
		if (isSelected)
		{
			Rectangle::DrawWire(window, recSelected, Color::Blue);

			int nbCards = GetNbCards();
			Vector2f space = Vector2f(recSelected.size.x - ((float)nbCards * cardSizeWhenSelected.x), recSelected.size.y - cardSizeWhenSelected.y);
			int nbGapX = nbCards + 1;
			Vector2f gap = Vector2f(space.x / nbGapX, space.y * 0.5f);
			float y = recSelected.center.y;
			float x;
			for (int i = 0; i < nbCards; i++)
			{
				x = gap.x * (i + 1);
				cards[i].SetPosition(Vector2f(x, y));
				cards[i].SetSize(cardSizeWhenSelected);
				cards[i].Draw(window);
			}
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

int Hand::GetNbCards() const
{
	return indexLastCard + 1;
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
				indexLastCard--;
				return true;
			}
		}
	}
	return false;
}