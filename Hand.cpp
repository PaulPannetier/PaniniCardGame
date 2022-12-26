
#include "Hand.hpp"

using namespace std;
using namespace sf;

Hand::Hand()
{

}

void Hand::Start()
{
	isACardSelected = isSelected = false;
	indexCardSelected = -1;
	player = nullptr;
}

void Hand::Update(sf::RenderWindow& window)
{

}

void Hand::Draw(sf::RenderWindow& window)
{
	if (true)//player->isMyTurn)
	{
		if (isSelected)
		{
			Rectangle::DrawWire(window, recSelected, Color::Blue);
		}
		else
		{
			Rectangle::DrawWire(window, recNotSelected, Color::Blue);
		}
	}
	else
	{
		Rectangle::DrawWire(window, recNotHerTurn, Color::Blue);
	}
}