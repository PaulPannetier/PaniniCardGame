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
	const Rectangle recNotSelected = Rectangle(sf::Vector2f(800, 925), sf::Vector2f(700, 350));
	const Rectangle recNotHerTurn = Rectangle(sf::Vector2f(800, -50), sf::Vector2f(700, 350));
	const Rectangle recSelected = Rectangle(sf::Vector2f(800, 450), sf::Vector2f(900, 600));

	const sf::Vector2f cardSizeWhenSelected = sf::Vector2f(150, 400);
	const sf::Vector2f cardSizeWhenNotSelected = sf::Vector2f(80, 300);
	const sf::Vector2f cardSizeWhenNotHerTurn = sf::Vector2f(80, 300);

	Card cards[MAX_HAND_SIZE];
	bool isACardSelected, isSelected;
	int indexCardSelected, indexLastCard;

	void CalculateCardsTransform(int nbCards, const Rectangle& rec, const sf::Vector2f& cardSize);


public :

	Player* player;

	Hand();

	void Start();
	void Update(sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
	bool IsFull() const;
	bool AddCard(const Card& card);
	bool RemoveCard(const Card& card);
	int GetNbCards() const;
};

#endif