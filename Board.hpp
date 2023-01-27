#ifndef BOARD_HPP
#define BOARD_HPP

#include "Card.hpp"
#include "Button.hpp"
#include "Player.hpp"
#include "CardPlaceInfo.hpp"

#define NB_MAX_GOAL_KEEPER 1
#define NB_MAX_DEFENDER 5
#define NB_MAX_STRIKER 4
#define NB_MAX_CARD_IN_BOARD (NB_MAX_GOAL_KEEPER + NB_MAX_DEFENDER + NB_MAX_STRIKER) * 2

class Board
{
private:

	sf::Sprite background;
	Button endTurnButton;

	Board();

	void FillDeck();
	void PlaceCard(Card& boardCard, const Card& card, CardPlaceInfo& placeInfo, int globalIndex);
	void ReStart();
	void Clear();

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

	Player player1, player2;
	int turnNunber;
	Card goalKeepersOne[NB_MAX_GOAL_KEEPER];
	Card defencersOne[NB_MAX_DEFENDER];
	Card strikersOne[NB_MAX_STRIKER];
	Card goalKeepersTwo[NB_MAX_GOAL_KEEPER];
	Card defencersTwo[NB_MAX_DEFENDER];
	Card strikersTwo[NB_MAX_STRIKER];
	Card* boardCards[NB_MAX_CARD_IN_BOARD];

	static Board& Instance();

	void Start();

	bool CanPlaceCard(const Card& card, bool playerOneBoard, CardType line, int indexPlace);
	void PlaceCard(Card& card, bool playerOneBoard, CardType line, int indexPlace);
	void SwitchCards(const CardPlaceInfo& card1, const CardPlaceInfo& card2);

	bool GetCardPlaceInfo(sf::Vector2f position, CardPlaceInfo& info);
	bool GetCardPlaceInfo(bool playerOne, CardType line, int indexPlace, CardPlaceInfo& info);
	void GetAdjacentCardsPlacesInfo(const CardPlaceInfo& current, std::vector<CardPlaceInfo>& adjacents);
	void OnClickEndTurnButtonAction(const Button& button);
	void ClearPlace(const CardPlaceInfo& place);

	void GetPlayerCard(bool playerOneCards, std::vector<CardPlaceInfo>& res);

	void MakeDuel(const CardPlaceInfo& striker, const CardPlaceInfo& defender);

	void OnBeginTurn(bool isPlayerOneTurn);
	void OnEndTurn(bool isPlayerOneEndTurn);
	void OnMakeDuel(const CardPlaceInfo& striker, const CardPlaceInfo& defender);
	void OnMakeGoal(Card& card, Player& player);

	void Update(sf::RenderWindow& windows);
	void Draw(sf::RenderWindow& windows);
};

#endif