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
	const Rectangle recNotSelected = Rectangle(sf::Vector2f(800, 925), sf::Vector2f(900, 350));
	const Rectangle recNotHerTurn = Rectangle(sf::Vector2f(800, -50), sf::Vector2f(900, 350));
	const Rectangle recSelected = Rectangle(sf::Vector2f(800, 450), sf::Vector2f(1500, 600));

	const sf::Vector2f cardSizeWhenSelected = sf::Vector2f(220, 450);
	const sf::Vector2f cardSizeWhenNotSelected = sf::Vector2f(110, 300);
	const sf::Vector2f cardSizeWhenNotHerTurn = sf::Vector2f(110, 300);

	Card cards[MAX_HAND_SIZE];
	bool isSelected;// si la main est sélectionner
	int indexLastCard;// index de la dernière carte

	void CalculateCardsTransform(int nbCards, const Rectangle& rec, const sf::Vector2f& cardSize);
	void DeselectSelectedCard();

public :
	bool isACardSelected;//si une carte est selectionner 
	int indexCardSelected;//l'index de la carte sélectionner 

	Player* player;

	Hand();

	//Getter
	bool IsSelected();
	bool GetSelectedCard(Card& card);

	void Start();
	void Update(sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
	bool IsFull() const;
	void DeselectAllCard();
	bool AddCard(const Card& card);
	bool RemoveCard(const Card& card);
	bool RemoveCard(int cardId);
	int GetNbCards() const;
	void Clear();
};

#endif