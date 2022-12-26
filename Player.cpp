
#include "Player.hpp"

using namespace std; 
using namespace sf;

void Player::Start()
{
	isMyTurn = false;
	deck.Start();
	hand.Start();
	hand.player = this;
}

void Player::Update(sf::RenderWindow& window)
{
	if (isMyTurn)
	{
		//hand.Update(window);
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	if (isMyTurn)
	{
		//hand.Draw(window);
	}
}