
#include "Card.hpp"

using namespace std;

Card::Card(string name, string description, int attack, int defence)
{
	this->name(name); this->description(description); this->attack(attack); this->defence(defence);
}

string Card::ToString() const
{
	ostringstream os;
	os << "[Card], name : " << this->_name;
	return os.str();
}