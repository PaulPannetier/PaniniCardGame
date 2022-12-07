
#include "Card.hpp"

using namespace std;

Card::Card(string name, string description, int attack, int defence)
{
	this->name(name); this->description(description); this->attack(attack); this->defence(defence);
}

Card::Card(const Card& card)
{
	this->name(card._name); this->description(card._description); this->attack(card._attack); this->defence(card._defence);
}

string Card::ToString() const
{
	ostringstream os;
	os << "[Card], name : " << this->_name;
	return os.str();
}