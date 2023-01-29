#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include "Deck.hpp"
#include "Hand.hpp"
#include "CardManager.hpp"
#include "CardPlaceInfo.hpp"

class Player : Object
{
private :

	const sf::Vector2f scoreTextPosPlayerOne = sf::Vector2f(50, 50);
	const sf::Vector2f scoreTextPosPlayerTwo = sf::Vector2f(1550, 50);
	const sf::Vector2f manaTextPos = sf::Vector2f(120, 860);

	Deck deck;//le deck du joueur
	Hand hand;//la main du joueur
	int mana;//les point permettant de jouer des carte
	int nbGoals;//le nombre de but marqué par ce joueur
	sf::Text scoreText, manaText;

	//pour update
	bool isABoardCardSelected;
	CardPlaceInfo cardBoardSelected;

public :

	bool isPlayerOne;
	bool isMyTurn;//true si c'est le tour de ce joueur, false sinon

	Player() = default;

	void DeSelectAllCards();
	void Clear();

	void Start();
	void ReStart();
	void Update(sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);

	void FillDeck(std::vector<CardsManager::CardNum>& cards);
	void FirstDraw(int nbCards);
	void DrawCard();
	void OnBeginTurn(bool isPlayerOneTurn);
	void OnEndTurn(bool isPlayerOneEndTurn);
	void OnMakeGoal(Card& card);
	std::string ToString() const override;
};

#endif
