#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Deck.hpp"
#include "Hand.hpp"
#include <vector>
#include "CardManager.hpp"

class Player
{
private :
	Deck deck;//le deck du joueur
	Hand hand;//la main du joueur
	int mana;//les point permettant de jouer des carte

public :

	bool isPlayerOne;
	bool isMyTurn;//true si c'est le tour de ce joueur, false sinon

	Player() = default;

	void Start();
	void Update(sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);

	void FillDeck(std::vector<CardsManager::CardNum>& cards);
	void FirstDraw(int nbCards);
	void BeginTurn();
	void EndTurn();
};

#endif
