#ifndef BOARD_HPP
#define BOARD_HPP

#include "Card.hpp"
#include "Button.hpp"

#define NB_MAX_GOAL_KEEPER 1
#define NB_MAX_DEFENDER 5
#define NB_MAX_STRIKER 4

class Board
{
private:

	sf::Sprite background;
	Button endTurnButton;

	Board();

public:

	const sf::Vector2f cardSize = sf::Vector2f(75, 100);
	const sf::Vector2f goalKeeperUpPos[1] = { sf::Vector2f(120, 450) };

	const sf::Vector2f defenderUpPos[5] =
	{
		sf::Vector2f(400, 150),
		sf::Vector2f(400, 300),
		sf::Vector2f(400, 450),
		sf::Vector2f(400, 600),
		sf::Vector2f(400, 750)
	};

	const sf::Vector2f strikerUpPos[4] =
	{
		sf::Vector2f(650, 225),
		sf::Vector2f(650, 375),
		sf::Vector2f(650, 525),
		sf::Vector2f(650, 675)
	};

	const sf::Vector2f goalKeeperDownPos[1] = { sf::Vector2f(1480, 450) };

	const sf::Vector2f defenderDownPos[5] =
	{
		sf::Vector2f(1200, 150),
		sf::Vector2f(1200, 300),
		sf::Vector2f(1200, 450),
		sf::Vector2f(1200, 600),
		sf::Vector2f(1200, 750)
	};

	const sf::Vector2f strikerDownPos[4] =
	{
		sf::Vector2f(950, 225),
		sf::Vector2f(950, 375),
		sf::Vector2f(950, 525),
		sf::Vector2f(950, 675)
	};

	Card goalKeepersUp[NB_MAX_GOAL_KEEPER];
	Card defencersUp[NB_MAX_DEFENDER];
	Card strikersUp[NB_MAX_STRIKER];
	Card goalKeepersDown[NB_MAX_GOAL_KEEPER];
	Card defencersDown[NB_MAX_DEFENDER];
	Card strikersDown[NB_MAX_STRIKER];

	static Board& Instance();

	void Start();

	bool CanPlaceCard(const Card& card, bool playerOneBoard, CardType line, int indexPlace);
	void PlaceCard(const Card& card, bool playerOneBoard, CardType line, int indexPlace);

	void Update(sf::RenderWindow& windows);
	void Draw(sf::RenderWindow& windows);
};

#endif