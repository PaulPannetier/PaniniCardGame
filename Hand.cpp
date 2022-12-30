
#include "Hand.hpp"
#include "Player.hpp"
#include "InputManager.hpp"

using namespace std;
using namespace sf;

Hand::Hand()
{

}

bool Hand::IsSelected()
{
	return isSelected;
}

bool Hand::GetSelectedCard(Card& card)
{
	if (isACardSelected)
	{
		card = Card(cards[indexCardSelected]);
		return true;
	}
	return false;
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
	//calculate cards transform
	if (player->isMyTurn)
	{
		if (isSelected)
		{
			CalculateCardsTransform(GetNbCards(), recSelected, cardSizeWhenSelected);
		}
		else
		{
			CalculateCardsTransform(GetNbCards(), recNotSelected, cardSizeWhenNotSelected);
		}
	}
	else
	{
		CalculateCardsTransform(GetNbCards(), recNotHerTurn, cardSizeWhenNotHerTurn);
	}

	//select or not the hand
	if (player->isMyTurn)
	{
		if (isSelected)
		{
			if (!recSelected.Contain(InputManager::Instance().MousePosition()) && InputManager::Instance().GetKeyDown(Mouse::Button::Left))
			{
				isSelected = false;
				//on déselectionne la carte sélectionner
				DeselectSelectedCard();
			}
		}
		else
		{
			if (recNotSelected.Contain(InputManager::Instance().MousePosition()) && InputManager::Instance().GetKeyDown(Mouse::Button::Left))
			{
				isSelected = true;
;			}
		}
	}

	//select the card
	if (player->isMyTurn)
	{
		if (isSelected)
		{
			if (InputManager::Instance().GetKeyDown(Mouse::Button::Left))
			{
				int nbCard = GetNbCards();
				for (int i = 0; i < nbCard; i++)
				{
					Rectangle hitbox = cards[i].GetHitbox();
					if (hitbox.Contain(InputManager::Instance().MousePosition()))
					{
						//on déseclectionne la carte précédemment sélectionner
						DeselectSelectedCard();
						
						//on sélectionne la nouvelle
						cards[i].isSelected = true;
						isSelected = false;
						isACardSelected = true;
						indexCardSelected = i;
						break;
					}
				}
			}
		}
	}
}

void Hand::DeselectSelectedCard()
{
	if (isACardSelected)
	{
		cards[indexCardSelected].isSelected = false;
		isACardSelected = false;
	}
}

void Hand::CalculateCardsTransform(int nbCards, const Rectangle& rec, const Vector2f& cardSize)
{
	int nbGapX = nbCards + 1;
	Vector2f space = Vector2f(rec.size.x - ((float)nbCards * cardSize.x), rec.size.y - cardSize.y);
	Vector2f gap = Vector2f(space.x / nbGapX, space.y * 0.5f);
	float y = rec.center.y;
	float offset = rec.center.x - rec.size.x * 0.5f + cardSize.x * 0.5f;
	float x;
	for (int i = 0; i < nbCards; i++)
	{
		x = offset + gap.x * (i + 1) + i * cardSize.x;
		cards[i].SetPosition(Vector2f(x, y));
		cards[i].SetSize(cardSize);
		cards[i].InverseScale(false, !player->isMyTurn);
	}
}

void Hand::Draw(RenderWindow& window)
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

	int nbCards = GetNbCards();
	for (int i = 0; i < nbCards; i++)
	{
		cards[i].Draw(window);
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

bool Hand::RemoveCard(int cardId)
{
	if (indexLastCard < 0)
		return false;
	for (int i = 0; i < MAX_HAND_SIZE; i++)
	{
		if (cards[i].isInitialized && !cards[i].isOnBoard)
		{
			if (cards[i].id == cardId)
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

bool Hand::RemoveCard(const Card& card)
{
	return RemoveCard(card.id);
}