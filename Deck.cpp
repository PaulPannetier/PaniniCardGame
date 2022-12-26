
#include "Deck.hpp"

using namespace std;

void Deck::Start()
{

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

bool Deck::Draw(Card card)
{
    if (this->isEmpty())
    {
        return false;
    }

    card = Card(cards[0]);
    cards.erase(cards.begin());

    return true;
}

void Deck::AddCard(Card card)
{
    cards.push_back(card);
}

string Deck::ToString() const
{
    ostringstream os;
    //os << "[Deck], count : " << count();
    return os.str();
}