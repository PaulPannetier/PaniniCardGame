#ifndef HAND_HPP
#define HAND_HPP

#include <SFML/Graphics.hpp>
#include "Card.hpp"
#include "Collider2D.hpp"

class Player;

#define MAX_HAND_SIZE 5
#define NB_BEGIN_CARDS 3

class Hand
{
private:
	const Rectangle recNotSelected = Rectangle(sf::Vector2f(800, 800), sf::Vector2f(400, 200));
	const Rectangle recNotHerTurn = Rectangle(sf::Vector2f(800, 100), sf::Vector2f(400, 200));
	const Rectangle recSelected = Rectangle(sf::Vector2f(800, 450), sf::Vector2f(600, 400));

	Card cards[MAX_HAND_SIZE];
	bool isACardSelected, isSelected;
	int indexCardSelected, indexLastCard;

public :

	Player* player;

	Hand();

	void Start();
	void Update(sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
	bool IsFull() const;
	bool AddCard(const Card& card);
	bool RemoveCard(const Card& card);
};

#endif