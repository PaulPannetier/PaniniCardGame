
#include "Card.hpp"
#include "Board.hpp"
#include "Collider2D.hpp"
#include "AssetsManager.hpp"
#include "GameManager.hpp"

using namespace std;
using namespace sf;

Card::Card()
{
	isOnBoard = false;
	isInitialized = false;
}

Card::Card(string name, string description, int attack, int defence, CardType cardType, string textureName)
{
	this->name(name); this->description(description); this->attack(attack); this->defence(defence);
	this->cardType(cardType);
	isOnBoard = false;

	Texture& texture = AssetsManager::Instance().GetTexture(textureName);
	this->sprite.setTexture(texture);
	this->sprite.setOrigin(texture.getSize().x * 0.5, texture.getSize().y * 0.5);
	Vector2f cardSize = Board::Instance().cardSize;
	Vector2f scale = Vector2f(cardSize.x / texture.getSize().x, cardSize.y / texture.getSize().y);
	this->sprite.setScale(scale);
	this->id = GetUniqueId();
	this->isInitialized = true;
}

Card::Card(const Card& card)
{
	this->name(card._name); this->description(card._description); this->attack(card._attack); this->defence(card._defence);
	this->cardType(card._cardType);
	isOnBoard = card.isOnBoard;
	this->sprite = Sprite(card.sprite);
	this->id = card.id;
	this->isInitialized = card.isInitialized;
}

int Card::GetUniqueId()
{
	static int id = -1;
	id++;
	return id;
}

void Card::SetPosition(const Vector2f& position)
{
	this->sprite.setPosition(position);
}

void Card::SetRotation(float angle)
{
	this->sprite.setRotation(angle);
}

void Card::SetSize(const Vector2f& size)
{
	Vector2f textureSize = Vector2f(this->sprite.getTexture()->getSize().x, this->sprite.getTexture()->getSize().y);
	Vector2f scale = Vector2f(size.x / textureSize.x, size.y / textureSize.y);
	this->sprite.setScale(scale);
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

Vector2f Card::GetSize()
{
	Vector2f textureSize = Vector2f(this->sprite.getTexture()->getSize().x, this->sprite.getTexture()->getSize().y);
	Vector2f scale = sprite.getScale();
	return Vector2f(scale.x * textureSize.x, scale.y * textureSize.y);
}

bool Card::CanPlaceInBoard(bool playerOneBoard, CardType line, int index) const
{
	if (this->_cardType != line)
	{
		return false;
	}
	return true;
}

void Card::OnPlay()
{

}

void Card::Draw(RenderWindow& window)
{
	if (!isInitialized)
		return;
	window.draw(sprite);
	Rectangle::DrawWire(window, Rectangle(sprite.getPosition(), GetSize()), Color::Blue);
}

string Card::ToString() const
{
	ostringstream os;
	os << "[Card], name : " << this->_name;
	return os.str();
}