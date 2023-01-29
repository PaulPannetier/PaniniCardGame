#ifndef DECK_HPP
#define DECK_HPP

#include <vector>
#include "Card.hpp"

class Player;

class Deck : Object
{
private:
	const Rectangle deckHitboxPlayerOne = Rectangle(sf::Vector2f(60, 350), sf::Vector2f(50, 100));
	const Rectangle deckHitboxPlayerTwo = Rectangle(sf::Vector2f(1550, 550), sf::Vector2f(50, 100));

	std::vector<Card> cards;//0=> haut du deck, count() => bas du deck
	sf::Sprite sprite;
	sf::Text infoText;

public:

	Player* player;

	Deck() = default;

	void Start();
	int count() const { return cards.size(); }
	void Shuffle();
	bool DrawCard(Card& card);
	void AddCard(Card card);
	bool isEmpty() { return count() <= 0; }
	void Clear();

	void Update(sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);

	std::string ToString() const override;
};

#endif