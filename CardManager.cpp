 #include "CardManager.hpp"
#include "IncreaseStatAtTurnEffect.hpp"

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
		Card("Pavard", "Second poteau\n Pavard!", 5, 4, 4, CardType::striker, "Pavard"),
		Card("Giroud", "", 2, 2, 2, CardType::defender, "Giroud"),
		Card("Lorris", "Ramener la coupe\n � la maison", 1, 5, 3, CardType::goalkeeper, "Lioris"),
		Card("Ronaldo", "Gagne +1 d'attaque\n au d�but de chaque\n tour", 1, 5, 5, CardType::striker, "Ronaldo", false, new IncreaseStatAtTurn(1,0))
	};
}

Card CardsManager::GetCard(const CardNum& cardNum)
{
	return Card(this->gameCards[(int)cardNum]);
}
