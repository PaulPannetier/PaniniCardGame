#include "Ball.hpp"
#include "AssetsManager.hpp"

using namespace std;
using namespace sf;

Ball::Ball()
{
	card = nullptr;
}

Ball& Ball::Instance()
{
	static Ball instance;
	return instance;
}

void Ball::Start()
{
	sprite.setTexture(AssetsManager::Instance().GetTexture("Ball"));
	sprite.setColor(Color::White);
	sprite.setOrigin(sprite.getTextureRect().width * 0.5f, sprite.getTextureRect().height * 0.5f);
	sprite.setPosition(100, 100);
	sprite.setScale(ballSize.x / sprite.getTexture()->getSize().x, ballSize.y / sprite.getTexture()->getSize().y);
}

void Ball::CalculateTransform()
{
	if (card == nullptr)
		return;
	float coeff = card->isPlayerOneCard ? 1.0f : -1.0f;
	Rectangle hitbox = card->GetHitbox();
	sprite.setPosition(card->GetHitbox().center + Vector2f(coeff * card->GetHitbox().size.x * 0.5f, 0));
}

void Ball::SetAttachCard(Card& card)
{
	if (this->card != nullptr)
	{
		this->card->haveTheBall = false;
	}
	this->card = &card;
	card.haveTheBall = true;
}

void Ball::DeSetAttachCard()
{
	this->card = nullptr;
}

void Ball::Update(RenderWindow& window)
{
	CalculateTransform();
}

void Ball::Draw(RenderWindow& window)
{
	window.draw(sprite);
}