#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include "Useful.hpp"

typedef enum { goalkeeper, defender, striker, spell } CardType;

class Card : Object
{
private:
	std::string _name;
	std::string _description;
	int _attack, _defence;
	CardType _cardType;
	sf::Sprite sprite;

	int GetUniqueId();

public:
	int id;
	bool isOnBoard;
	bool isInitialized;

	Card();
	Card(std::string name, std::string description, int attack, int defence, CardType cardType, std::string textureName);
	Card(const Card& card);

	//Getter:
	std::string name() { return _name; }
	std::string description() { return _description; }
	int attack() { return _attack; } int defence() { return _defence; }
	CardType cardType() { return _cardType; }

	//Setter
	void name(std::string value) { _name = value; }
	void description(std::string value) { _description = value; }
	void attack(int value) { _attack = value; } void defence(int value) { _defence = value; }
	void cardType(CardType value) { _cardType = value; }
	void SetPosition(const sf::Vector2f& position);
	void SetRotation(float angle);
	void SetSize(const sf::Vector2f& size);
	void InverseScale(bool x, bool y);
	sf::Vector2f GetSize();

	bool CanPlaceInBoard(bool playerOneBoard, CardType line, int index) const;
	void OnPlay();

	void Draw(sf::RenderWindow& window);
	std::string ToString() const override;
};

#endif

