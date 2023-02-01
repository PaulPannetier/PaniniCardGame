#ifndef TEST_HPP
#define TEST_HPP

#include "Collider2D.hpp"

void TestCollider2D()
{
	Circle circle = Circle(sf::Vector2f(50.0f, 50.0f), 50.0f);
	Circle circle2 = Circle(circle);

	circle2.center = sf::Vector2f(10.0f, 10.0f);
	float mag = Useful::Magnitude(circle2.center - sf::Vector2f(10.0f, 10.0f));
	if (mag > 0.0001f)
	{
		std::cout << "Error : " << mag << " greter than " << 0.0001f << " ,error in TestCollider2D" << std::endl;
	}
	circle2.radius = 8.457f;
	if (((8.457f - circle2.radius) > 0.0001f))
	{
		std::cout << "Error : " << (8.457f - circle2.radius) << " greter than " << 0.0001f << " ,error in TestCollider2D" << std::endl;
	}

	Rectangle rec = Rectangle(sf::Vector2f(100.0, 250.0), sf::Vector2f(100, 150));
	Rectangle rec2 = Rectangle(rec);

	rec2.center = sf::Vector2f(10, 10);
	mag = Useful::Magnitude(rec2.center - sf::Vector2f(10, 10));
	if (mag > 0.0001f)
	{
		std::cout << "Error : " << mag << " greter than " << 0.0001f << " ,error in TestCollider2D" << std::endl;
	}

	rec2.size = sf::Vector2f(120, 12);
	mag = Useful::Magnitude(rec2.size - sf::Vector2f(120, 12));
	if (mag > 0.0001f)
	{
		std::cout << "Error : " << mag << " greter than " << 0.0001f << " ,error in TestCollider2D" << std::endl;
	}
}

void TestDeck()
{
	Deck deck;
	deck.AddCard(Card("Toto", "Description", 2, 3, 4, CardType::goalkeeper, "", true));
	deck.AddCard(Card("Titi", "Description2", 5, 6, 7, CardType::defender, "", false));

	if (deck.count() != 2)
	{
		std::cout << "Error : " << deck.count() << " different than " << 2 << " ,error in TestDeck" << std::endl;
	}

	Card card;
	if (!deck.DrawCard(card))
	{
		std::cout << "Error : " << "can't draw card," << " ,error in TestDeck" << std::endl;
	}

	if (card.attack() != 2)
	{
		std::cout << "Error : " << card.attack() << " different than " << 2 << " ,error in TestDeck" << std::endl;
	}

	if (card.defence() != 3)
	{
		std::cout << "Error : " << card.defence() << " different than " << 3 << " ,error in TestDeck" << std::endl;
	}

	if (card.cost() != 4)
	{
		std::cout << "Error : " << card.cost() << " different than " << 4 << " ,error in TestDeck" << std::endl;
	}

	if (card.cardType() != CardType::goalkeeper)
	{
		std::cout << "Error : " << card.cardType() << " different than " << CardType::goalkeeper << " ,error in TestDeck" << std::endl;
	}

	if (card.description() != "Description")
	{
		std::cout << "Error : " << card.cardType() << " different than " << "Description" << " ,error in TestDeck" << std::endl;
	}

	if (!card.isPlayerOneCard)
	{
		std::cout << "Error : " << card.isPlayerOneCard << " different than " << "true" << " ,error in TestDeck" << std::endl;
	}

	if (deck.isEmpty())
	{
		std::cout << "Error : " << deck.isEmpty() << " different than " << "false" << " ,error in TestDeck" << std::endl;
	}

	deck.AddCard(Card("Tata", "Description3", 5, 6, 7, CardType::defender, "", false));
	deck.AddCard(Card("Tutu", "Description4", 5, 6, 7, CardType::defender, "", false));
	deck.AddCard(Card("Toutou", "Description5", 5, 6, 7, CardType::defender, "", false));

	deck.Shuffle();// ex�cut� en pas � pas pour v�rifi� le contenue du deck

	for (int i = 0; i < 4; i++)
	{
		deck.DrawCard(card);
	}

	if (!deck.isEmpty())
	{
		std::cout << "Error : " << deck.isEmpty() << " different than " << "true" << " ,error in TestDeck" << std::endl;
	}

	if (deck.DrawCard(card))
	{
		std::cout << "Error : can't be able to draw another card" << " ,error in TestDeck" << std::endl;
	}
}

void DoTest()
{
	TestCollider2D();
	TestDeck();

	std::cout << "Test complete!" << std::endl;
}


#endif
