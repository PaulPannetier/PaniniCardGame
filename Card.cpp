
#include "Card.hpp"
#include "Collider2D.hpp"
#include "AssetsManager.hpp"
#include "GameManager.hpp"

using namespace std;
using namespace sf;

Card::Card()
{
	isInitialised = isOnBoard = false;
}

Card::Card(string name, string description, int attack, int defence, CardType cardType, string textureName)
{
	this->name(name); this->description(description); this->attack(attack); this->defence(defence);
	this->cardType(cardType);
	isInitialised = isOnBoard = false;

	Texture& texture = AssetsManager::Instance().GetTexture(textureName);
	this->sprite.setTexture(texture);
	this->sprite.setOrigin(texture.getSize().x * 0.5, texture.getSize().y * 0.5);
	Vector2f cardSize = Board::Instance().cardSize;
	Vector2f scale = Vector2f(cardSize.x / texture.getSize().x, cardSize.y / texture.getSize().y);
	this->sprite.setScale(scale);
}

Card::Card(const Card& card)
{
	this->name(card._name); this->description(card._description); this->attack(card._attack); this->defence(card._defence);
	this->cardType(card._cardType);
	this->isInitialised = card.isInitialised;
	isOnBoard = card.isOnBoard;
	this->sprite = Sprite(card.sprite);
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

void Card::Draw(RenderWindow& window, const Vector2f& position, const Vector2f& size)
{
	sprite.setPosition(position);
	window.draw(sprite);
}

string Card::ToString() const
{
	ostringstream os;
	os << "[Card], name : " << this->_name;
	return os.str();
}