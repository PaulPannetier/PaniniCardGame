
#include "Card.hpp"
#include "PlayerBoard.hpp"

using namespace std;

Card::Card()
{

}

Card::Card(string name, string description, int attack, int defence, CardType cardType)
{
	this->name(name); this->description(description); this->attack(attack); this->defence(defence);
	this->cardType(cardType);
}

Card::Card(const Card& card)
{
	this->name(card._name); this->description(card._description); this->attack(card._attack); this->defence(card._defence);
	this->cardType(card._cardType);
}

bool Card::CanPlaceInBoard(PlayerBoard playerBoard, int indexPlace)
{
	return true;
}

string Card::ToString() const
{
	ostringstream os;
	os << "[Card], name : " << this->_name;
	return os.str();
}