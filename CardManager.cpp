
#include "CardManager.hpp"

CardsManager::CardsManager()
{

}

CardsManager& CardsManager::Instance()
{
	static CardsManager instance;
	return instance;
}

void CardsManager::Start()
{
	CreateCards();
}

void CardsManager::CreateCards()
{
	this->gameCards = 
	{
		Card("Pavard", "Second poteau Pavard!", 5, 3, 3, CardType::striker, "Pavard"),
		Card("Giroud", "Encore raté", 3, 3, 2, CardType::defender, "Giroud"),
		Card("Lorris", "Ramener la coupe à la maison", 5, 3, 2, CardType::goalkeeper, "Lioris")
	};
}

Card CardsManager::GetCard(const CardNum& cardNum)
{
	return Card(this->gameCards[(int)cardNum]);
}
