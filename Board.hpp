#ifndef BOARD_HPP
#define BOARD_HPP

#include "Deck.hpp"
#include "Button.hpp"

#define NB_MAX_GOAL_KEEPER 1
#define NB_MAX_DEFENDER 5
#define NB_MAX_STRIKER 4

class Board
{
private:

	const sf::Vector2f cardSize = sf::Vector2f(50, 100);
	const sf::Vector2f goalKeeperUpPos[1] = { sf::Vector2f(800, 100) };

	const sf::Vector2f defenderUpPos[5] =
	{
		sf::Vector2f(400, 250),
		sf::Vector2f(600, 250),
		sf::Vector2f(800, 250),
		sf::Vector2f(1000, 250),
		sf::Vector2f(1200, 250)
	};

	const sf::Vector2f strikerUpPos[4] =
	{
		sf::Vector2f(500, 400),
		sf::Vector2f(700, 400),
		sf::Vector2f(900, 400),
		sf::Vector2f(1100, 400)
	};

	const sf::Vector2f goalKeeperDownPos[1] = { sf::Vector2f(800, 800) };

	const sf::Vector2f defenderDownPos[5] =
	{
		sf::Vector2f(400, 650),
		sf::Vector2f(600, 650),
		sf::Vector2f(800, 650),
		sf::Vector2f(1000, 650),
		sf::Vector2f(1200, 650)
	};

	const sf::Vector2f strikerDownPos[4] =
	{
		sf::Vector2f(500, 500),
		sf::Vector2f(700, 500),
		sf::Vector2f(900, 500),
		sf::Vector2f(1100, 500)
	};

	Deck deckPlayer1, deckPlayer2;
	Card goalKeepersUp[NB_MAX_GOAL_KEEPER];
	Card defencersUp[NB_MAX_DEFENDER];
	Card strikersUp[NB_MAX_STRIKER];
	Card goalKeepersDown[NB_MAX_GOAL_KEEPER];
	Card defencersDown[NB_MAX_DEFENDER];
	Card strikersDown[NB_MAX_STRIKER];

	sf::Sprite background;
	Button endTurnButton;

public:

	Board();

	bool CanPlaceCard(const Card& card, bool playerOneBoard, CardType line, int indexPlace);
	void PlaceCard(const Card& card, bool playerOneBoard, CardType line, int indexPlace);

	void Start();
	void Update(sf::RenderWindow& windows);
	void Draw(sf::RenderWindow& windows);
};

#endif