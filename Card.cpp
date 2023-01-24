#include "Card.hpp"
#include "Board.hpp"
#include "AssetsManager.hpp"
#include "GameManager.hpp"
#include "EventManager.hpp"
#include "InputManager.hpp"

using namespace std;
using namespace sf;

Card::Card()
{
	isInitialized = false;
	isSleeping = true;
}

Card::Card(string name, string description, int attack, int defence, int cost, CardType cardType, string textureName, bool isPLayerOneCard)
{
	this->name(name); this->description(description); this->attack(attack); this->defence(defence);
	this->cardType(cardType); this->cost(cost);
	isOnBoard = false;

	Texture& texture = AssetsManager::Instance().GetTexture(textureName);
	this->sprite.setTexture(texture);
	this->sprite.setOrigin(texture.getSize().x * 0.5, texture.getSize().y * 0.5);
	Vector2f cardSize = Board::Instance().cardSize;
	Vector2f scale = Vector2f(cardSize.x / texture.getSize().x, cardSize.y / texture.getSize().y);
	this->sprite.setScale(scale);
	this->id = GetUniqueId();
	this->isInitialized = true;
	this->isSelected = false;
	this->isPlayerOneCard = isPlayerOneCard;
	this->haveTheBall = false;
	this->isSleeping = true;
	this->attackBonus = this->defenceBonus = this->costBonus = 0;
}

Card::Card(const Card& card)
{
	this->name(card._name); this->description(card._description); this->attack(card._attack); this->defence(card._defence);
	this->cardType(card._cardType); this->cost(card._cost);
	isOnBoard = card.isOnBoard;
	this->sprite = Sprite(card.sprite);
	this->id = card.id;
	this->isInitialized = card.isInitialized;
	this->isSelected = card.isSelected;
	this->isPlayerOneCard = card.isPlayerOneCard;
	this->haveTheBall = card.haveTheBall;
	this->cardPlaceInfo = CardPlaceInfo(card.cardPlaceInfo);
	this->isSleeping = card.isSleeping;
	this->attackBonus = card.attackBonus;
	this->defenceBonus = card.defenceBonus;
	this->attackText = card.attackText;
	this->defenceText = card.defenceText;
	this->costText = card.costText;
	this->costBonus = card.costBonus;
}

int Card::GetUniqueId()
{
	static int id = -1;
	id++;
	return id;
}

Font& Card::GetCardFont()
{
	return AssetsManager::Instance().GetFont("poppins");
}

void Card::CalculateCardBoardTransform()
{
	SetPosition(this->cardPlaceInfo.hitbox.center);
	SetSize(this->cardPlaceInfo.hitbox.size);
}

Vector2f Card::GetPosition()
{
	return sprite.getPosition();
}

void Card::SetPosition(const Vector2f& position)
{
	this->sprite.setPosition(position);
}

float Card::GetRotation()
{
	return sprite.getRotation();
}

void Card::SetRotation(float angle)
{
	this->sprite.setRotation(angle);
}

Vector2f Card::GetSize()
{
	if (!isInitialized)
		return cardPlaceInfo.hitbox.size;
	Vector2f scale = sprite.getScale();
	Vector2f fullSize = Vector2f(sprite.getTextureRect().width, sprite.getTextureRect().height);
	return Vector2f(scale.x * fullSize.x, scale.y * fullSize.y);
}

void Card::SetSize(const Vector2f& size)
{
	if (!isInitialized)
		return;
	Vector2f textureSize = Vector2f(this->sprite.getTexture()->getSize().x, this->sprite.getTexture()->getSize().y);
	Vector2f scale = Vector2f(size.x / textureSize.x, size.y / textureSize.y);
	this->sprite.setScale(scale);
}

Rectangle Card::GetHitbox()
{
	return Rectangle(GetPosition(), GetSize());
}

void Card::InverseScale(bool x, bool y)
{
	if (sprite.getScale().x >= 0.0f)
	{
		if (x)
			sprite.setScale(Vector2f(-sprite.getScale().x, sprite.getScale().y));
	}
	else
	{
		if (!x)
			sprite.setScale(Vector2f(-sprite.getScale().x, sprite.getScale().y));
	}
	if (sprite.getScale().y >= 0.0f)
	{
		if (y)
			sprite.setScale(Vector2f(sprite.getScale().x, -sprite.getScale().y));
	}
	else
	{
		if (!y)
			sprite.setScale(Vector2f(sprite.getScale().x, -sprite.getScale().y));
	}
}

bool Card::CanPlaceInBoard(bool playerOneBoard, CardType line, int index) const
{
	if (this->_cardType != line)
	{
		return false;
	}
	return true;
}

bool Card::CanAttack(const CardPlaceInfo& thisCardInfo, const CardPlaceInfo& defencerInfo)
{
	return true;
}

bool Card::CanDefend(const CardPlaceInfo& thisCardInfo, const CardPlaceInfo& strikerInfo)
{
	return true;
}

void Card::GetCardsCanAttack(vector<CardPlaceInfo>& cardsCanAttackInfo)
{
	Board::Instance().GetAdjacentCardsPlacesInfo(cardPlaceInfo, cardsCanAttackInfo);
	for (int i = cardsCanAttackInfo.size() - 1; i >= 0; i--)
	{
		if (!cardsCanAttackInfo[i].card->isInitialized || cardsCanAttackInfo[i].card->isPlayerOneCard == cardPlaceInfo.card->isPlayerOneCard)
		{
			cardsCanAttackInfo.erase(cardsCanAttackInfo.begin() + i);
		}
	}
}

void Card::GetPlaceToMove(vector<CardPlaceInfo>& placeCanMove)
{
	Board::Instance().GetAdjacentCardsPlacesInfo(cardPlaceInfo, placeCanMove);
	for (int i = placeCanMove.size() - 1; i >= 0; i--)
	{
		if (placeCanMove[i].card->isInitialized)
		{
			placeCanMove.erase(placeCanMove.begin() + i);
		}
	}
}

void Card::OnPlaceOnBoard()
{
	isSleeping = true;
	isSelected = false;
}

void Card::OnBeginTurn(bool playerOneTurn)
{
	if (isInitialized)
	{
		isSleeping = false;
	}
}

void Card::OnEndTurn(bool playerOneEndTurn)
{
	isSelected = false;
}

void Card::OnMove()
{
	isSleeping = true;
	isSelected = false;
}

void Card::OnMakeDuel(const CardPlaceInfo& striker, const CardPlaceInfo& defender)
{

}

void Card::Update(RenderWindow& window)
{
	if (!isInitialized)
		return;
	if (isOnBoard)
	{
		CalculateCardBoardTransform();
		if (isSelected)
		{
			if (!isSleeping)
			{
				GetPlaceToMove(placeToMove);

				if (InputManager::Instance().GetKeyDown(Mouse::Button::Left))
				{
					for (int i = 0; i < placeToMove.size(); i++)
					{
						if (placeToMove[i].hitbox.Contains(InputManager::Instance().MousePosition()))
						{
							Board::Instance().SwitchCards(cardPlaceInfo, placeToMove[i]);
							OnMove();
						}
					}
				}

				if (haveTheBall)
				{
					GetCardsCanAttack(cardsCanAttack);
					if (InputManager::Instance().GetKeyDown(Mouse::Button::Left))
					{
						for (int i = 0; i < cardsCanAttack.size(); i++)
						{
							CardPlaceInfo* tmpCard = &cardsCanAttack[i];
							if (tmpCard->hitbox.Contains(InputManager::Instance().MousePosition()))
							{
								Board::Instance().MakeDuel(this->cardPlaceInfo, *tmpCard);
							}
						}
					}
				}
			}
		}
	}
}

void Card::Draw(RenderWindow& window)
{
	if (!isInitialized)
		return;

	window.draw(sprite);
	Color color = isSelected ? Color::Yellow : Color::Blue;
	Rectangle::DrawWire(window, GetHitbox(), color);

	if (isSelected)
	{
		for (int i = 0; i < placeToMove.size(); i++)
		{
			Rectangle::Draw(window, placeToMove[i].hitbox * 0.8, Color::Green);
		}
	}

	if (isSelected)
	{
		for (int i = 0; i < cardsCanAttack.size(); i++)
		{
			Rectangle::Draw(window, cardsCanAttack[i].hitbox * 0.8, Color::Red);
		}
	}

	//Draw the text
	//attackText
	attackText.setString(to_string(_attack + attackBonus));
	color = attackBonus > 0 ? Color::Green : (attackBonus < 0 ? Color::Red : Color::White);
	attackText.setFillColor(color);
	attackText.setOutlineColor(color);
	attackText.setOrigin(Vector2f(attackText.getLocalBounds().width * 0.5f, attackText.getLocalBounds().height * 0.5f));
	attackText.setPosition(GetPosition() + (GetHitbox().size * 0.5f) - Vector2f(attackText.getLocalBounds().left, attackText.getLocalBounds().top));
	//Rectangle::DrawWire(window, Rectangle(attackText.getPosition() + Vector2f(attackText.getLocalBounds().left, attackText.getLocalBounds().top), Vector2f(attackText.getLocalBounds().width, attackText.getLocalBounds().height)), Color::Yellow);
	attackText.setFont(GetCardFont());
	attackText.setCharacterSize(50);
	window.draw(attackText);

	defenceText.setString(to_string(_defence + defenceBonus));
	color = defenceBonus > 0 ? Color::Green : (defenceBonus < 0 ? Color::Red : Color::White);
	defenceText.setFillColor(color);
	defenceText.setOutlineColor(color);
	defenceText.setOrigin(Vector2f(defenceText.getLocalBounds().width * 0.5f, defenceText.getLocalBounds().height * 0.5f));
	defenceText.setPosition(GetPosition() + Vector2f(-GetHitbox().size.x * 0.5, GetHitbox().size.y * 0.5) - Vector2f(defenceText.getLocalBounds().left, defenceText.getLocalBounds().top));
	//Rectangle::DrawWire(window, Rectangle(defenceText.getPosition() + Vector2f(defenceText.getLocalBounds().left, defenceText.getLocalBounds().top), Vector2f(defenceText.getLocalBounds().width, defenceText.getLocalBounds().height)), Color::Yellow);
	defenceText.setFont(GetCardFont());
	defenceText.setCharacterSize(50);
	window.draw(defenceText);

	costText.setString(to_string(_cost + costBonus));
	color = costBonus > 0 ? Color::Green : (costBonus < 0 ? Color::Red : Color::Blue);
	costText.setFillColor(color);
	costText.setOutlineColor(color);
	costText.setOrigin(Vector2f(costText.getLocalBounds().width * 0.5f, costText.getLocalBounds().height * 0.5f));
	costText.setPosition(GetPosition() - (GetHitbox().size * 0.5f) - Vector2f(costText.getLocalBounds().left, costText.getLocalBounds().top));
	costText.setFont(GetCardFont());
	costText.setCharacterSize(65);
	window.draw(costText);
}

string Card::ToString() const
{
	ostringstream os;
	os << "[Card], name : " << this->_name;
	return os.str();
}