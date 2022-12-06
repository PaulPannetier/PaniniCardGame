#ifndef CARD_HPP
#define CARD_HPP

#include <string>

class Card
{
private:
	std::string _name;
	std::string _description;
	int _attack, _defence;

public:
	//Getter:
	std::string name();
	std::string description();
	int attack();
};

#endif

