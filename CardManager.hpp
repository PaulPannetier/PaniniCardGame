#ifndef CARDS_MANAGER_HPP
#define CARDS_MANAGER_HPP

#include "Card.hpp"

class CardsManager
{
	typedef enum
	{
		Pavard,
		Giroud,
		Lorris
	}CardNum;

	Card gameCards[3] =
	{
		Card("Pavard", "Second poteau Pavard!", 5, 3, CardType::striker, "Pavard"),
		Card("Giroud", "ENcore raté", 3, 3, CardType::defender, "Giroud"),
		Card("Lorris", "Ramener la coupe à la maison", 5, 3, CardType::goalkeeper, "Lioris")
	};
};

#endif