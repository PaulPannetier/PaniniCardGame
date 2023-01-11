
#include "Card.hpp"
#include "Board.hpp"
#include "AssetsManager.hpp"
#include "GameManager.hpp"
#include "CardPlaceInfo.hpp"

using namespace std;
using namespace sf;

Card::Card()
{
	isInitialized = false;
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
}

int Card::GetUniqueId()
{
	static int id = -1;
	id++;
	return id;
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
		return Vector2f(0, 0);
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

void Card::Draw(RenderWindow& window)
{
	if (!isInitialized)
		return;
	window.draw(sprite);
	Color color = isSelected ? Color::Yellow : Color::Blue;
	Rectangle::DrawWire(window, GetHitbox(), color);
}

string Card::ToString() const
{
	ostringstream os;
	os << "[Card], name : " << this->_name;
	return os.str();
}