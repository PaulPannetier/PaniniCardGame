#ifndef DECK_HPP
#define DECK_HPP

#include <vector>
#include "Card.hpp"

class Deck : Object
{
private:
	std::vector<Card> cards;//0=> bas du deck, count() => haut du deck

public:
	Deck() = default;

	void Start();
	int count() const { return cards.size(); }
	void Shuffle();
	bool DrawCard(Card& card);
	void AddCard(Card card);
	bool isEmpty() { return count() <= 0; }
	std::string ToString() const override;
};

#endif