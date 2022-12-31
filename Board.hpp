#ifndef BOARD_HPP
#define BOARD_HPP

#include "Card.hpp"
#include "Button.hpp"
#include "Player.hpp"

#define NB_MAX_GOAL_KEEPER 1
#define NB_MAX_DEFENDER 5
#define NB_MAX_STRIKER 4

struct CardPlaceInfo
{
	bool playerOnePlace;
	CardType line;
	int indexPlace;
	Card card;

	CardPlaceInfo()
	{

	}

	CardPlaceInfo(bool playerOnePlace, CardType line, int indexPlace, Card card)
	{
		this->playerOnePlace = playerOnePlace;
		this->line = line;
		this->indexPlace = indexPlace;
		this->card = card;
	}
};

class Board
{
private:

	sf::Sprite background;
	Button endTurnButton;
	Player player1, player2;

	Board();

	void CalculateCardsTransform();
	void FillDeck();

public:

	const sf::Vector2f cardSize = sf::Vector2f(75, 100);
	const sf::Vector2f goalKeeperOnePos[1] = { sf::Vector2f(120, 450) };

	const sf::Vector2f defenderOnePos[5] =
	{
		sf::Vector2f(400, 150),
		sf::Vector2f(400, 300),
		sf::Vector2f(400, 450),
		sf::Vector2f(400, 600),
		sf::Vector2f(400, 750)
	};

	const sf::Vector2f strikerOnePos[4] =
	{
		sf::Vector2f(650, 225),
		sf::Vector2f(650, 375),
		sf::Vector2f(650, 525),
		sf::Vector2f(650, 675)
	};

	const sf::Vector2f goalKeeperTwoPos[1] = { sf::Vector2f(1480, 450) };

	const sf::Vector2f defenderTwoPos[5] =
	{
		sf::Vector2f(1200, 150),
		sf::Vector2f(1200, 300),
		sf::Vector2f(1200, 450),
		sf::Vector2f(1200, 600),
		sf::Vector2f(1200, 750)
	};

	const sf::Vector2f strikerTwoPos[4] =
	{
		sf::Vector2f(950, 225),
		sf::Vector2f(950, 375),
		sf::Vector2f(950, 525),
		sf::Vector2f(950, 675)
	};

	Card goalKeepersOne[NB_MAX_GOAL_KEEPER];
	Card defencersOne[NB_MAX_DEFENDER];
	Card strikersOne[NB_MAX_STRIKER];
	Card goalKeepersTwo[NB_MAX_GOAL_KEEPER];
	Card defencersTwo[NB_MAX_DEFENDER];
	Card strikersTwo[NB_MAX_STRIKER];

	static Board& Instance();

	void Start();

	bool CanPlaceCard(const Card& card, bool playerOneBoard, CardType line, int indexPlace);
	void PlaceCard(const Card& card, bool playerOneBoard, CardType line, int indexPlace);
	bool GetCardPlaceInfo(sf::Vector2f position, CardPlaceInfo& info);
	void OnClickEndTurnButtonAction(const Button& button);

	void Update(sf::RenderWindow& windows);
	void Draw(sf::RenderWindow& windows);
};

#endif