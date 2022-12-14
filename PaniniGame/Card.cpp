
#include "Card.hpp"
#include "Collider2D.hpp"

using namespace std;
using namespace sf;

Card::Card()
{
	isInitialised = false;
}

Card::Card(string name, string description, int attack, int defence, CardType cardType, Image* image)
{
	this->name(name); this->description(description); this->attack(attack); this->defence(defence);
	this->cardType(cardType);
	this->sticker = image;
	isInitialised = true;
}

Card::Card(const Card& card)
{
	this->name(card._name); this->description(card._description); this->attack(card._attack); this->defence(card._defence);
	this->cardType(card._cardType);
	this->isInitialised = card.isInitialised;
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

void Card::Draw(RenderWindow& window, const Vector2f& position, const Vector2f& size) const
{
	Color color = this->_cardType == CardType::goalkeeper ? Color::Red : (_cardType == CardType::defender ? Color::Cyan : Color::Green);
	Rectangle::Draw(window, position, size, color);
}

string Card::ToString() const
{
	ostringstream os;
	os << "[Card], name : " << this->_name;
	return os.str();
}