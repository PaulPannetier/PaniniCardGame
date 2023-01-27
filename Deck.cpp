#include "Player.hpp"
#include "Deck.hpp"
#include "Useful.hpp"
#include "AssetsManager.hpp"
#include "InputManager.hpp"

using namespace std;
using namespace sf;

void Deck::Start()
{
    Texture& texture = AssetsManager::Instance().GetTexture("Deck");
    this->sprite.setTexture(texture);
    this->sprite.setScale(deckHitboxPlayerOne.size.x / texture.getSize().x, deckHitboxPlayerOne.size.y / texture.getSize().y);
    this->sprite.setOrigin(texture.getSize().x * 0.5f, texture.getSize().y * 0.5f);

    infoText.setFont(AssetsManager::Instance().GetFont("poppins"));
    infoText.setFillColor(Color::Blue);
    infoText.setCharacterSize(25);
}

void Deck::Shuffle()
{
    for (int i = 0; i < count(); i++)
    {
        int randIndex1 = Random::RandExclude(0, count());
        int randIndex2 = Random::RandExclude(0, count());
        Card tmp = cards[randIndex1];
        cards[randIndex1] = cards[randIndex2];
        cards[randIndex2] = tmp;
    }
}

bool Deck::DrawCard(Card& drawCard)
{
    if (this->isEmpty())
    {
        return false;
    }

    drawCard = Card(cards[0]);
    cards.erase(cards.begin());
    return true;
}

void Deck::AddCard(Card card)
{
    cards.push_back(card);
}

void Deck::Clear()
{
    for (int i = cards.size() - 1; i >= 0; i--)
    {
        cards.pop_back();
    }
}

void Deck::Update(RenderWindow& window)
{
    this->sprite.setPosition(this->player->isPlayerOne ? deckHitboxPlayerOne.center : deckHitboxPlayerTwo.center);
    if (this->player->isPlayerOne)
    {
        this->sprite.setScale(-Useful::Abs(sprite.getScale().x), sprite.getScale().y);
    }

    Rectangle rec = player->isPlayerOne ? deckHitboxPlayerOne : deckHitboxPlayerTwo;
    if (rec.Contains(InputManager::Instance().MousePosition()))
    {
        infoText.setString(to_string(this->count()) + " cartes");
        infoText.setOrigin(infoText.getLocalBounds().width * 0.5f, player->isPlayerOne ? -infoText.getLocalBounds().height : 0);
        infoText.setPosition(rec.center + Vector2f(0, (player->isPlayerOne ? -2.0f : 1) * rec.size.y * 0.5f));
    }
    else
    {
        infoText.setString("");
    }
}

void Deck::Draw(RenderWindow& window)
{
    window.draw(sprite);
    window.draw(infoText);
}

string Deck::ToString() const
{
    ostringstream os;
    return os.str();
}