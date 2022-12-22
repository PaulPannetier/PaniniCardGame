#ifndef CARDS_MANAGER_HPP
#define CARDS_MANAGER_HPP

#include <vector>
#include "Card.hpp"

class CardsManager
{
private:

	std::vector<Card> gameCards;

	CardsManager();

	void CreateCards();

public:

	typedef enum
	{
		Pavard,
		Giroud,
		Lorris
	}CardNum;

	static CardsManager& Instance();

	void Start();

	Card GetCard(const CardNum& cardNum);
};

#endif