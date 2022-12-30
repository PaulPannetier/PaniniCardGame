#include <iostream>
#include <vector>
#include "GameManager.hpp"
#include "Collider2D.hpp"
#include "CardManager.hpp"
#include "Board.hpp"
#include "Test.hpp"
#include "InputManager.hpp"
#include "Time.hpp"

using namespace std;
using namespace sf;

bool testCollider2D = false;
void FillDeck(Player& player1, Player& player2);

GameManager::GameManager()
{

}

GameManager& GameManager::Instance()
{
    static GameManager gameManager;
    return gameManager;
}

void GameManager::GameLoop(RenderWindow& window)
{
    while (window.isOpen())
    {
        Update(window);

        window.clear(Color::Black);
        Draw(window);
        window.display();
    }
}

void GameManager::Start(RenderWindow& window)
{
    Random::SetRandomSeed();
    this->_windowSize = Vector2f(window.getSize().x, window.getSize().y);
    InputManager::Instance().Start(window);
    AssetsManager::Instance().Start();//on charge les assets
    CardsManager::Instance().Start();//Création de toutes les cartes du jeu
    Board::Instance().Start();//Création du plateau dde jeu
    player1.Start();
    player2.Start();
    FillDeck(player1, player2);
    player1.FirstDraw(NB_BEGIN_CARDS);
    player2.FirstDraw(NB_BEGIN_CARDS);
    player1.isMyTurn = true;


    //on place des cartes au pif mdr
    /*
    Card card;
    card = CardsManager::Instance().GetCard(CardsManager::CardNum::Lorris);
    Board::Instance().PlaceCard(card, false, CardType::goalkeeper, 0);
    card = CardsManager::Instance().GetCard(CardsManager::CardNum::Giroud);
    Board::Instance().PlaceCard(card, false, CardType::defender, 3);
    card = CardsManager::Instance().GetCard(CardsManager::CardNum::Pavard);
    Board::Instance().PlaceCard(card, true, CardType::striker, 0);
    */
}

void FillDeck(Player& player1, Player& player2)
{
    vector<CardsManager::CardNum> deckPlayer1 =
    {
        CardsManager::CardNum::Lorris,
        CardsManager::CardNum::Lorris,
        CardsManager::CardNum::Lorris,
        CardsManager::CardNum::Giroud,
        CardsManager::CardNum::Giroud,
        CardsManager::CardNum::Giroud,
        CardsManager::CardNum::Pavard,
        CardsManager::CardNum::Pavard,
        CardsManager::CardNum::Pavard
    };
    player1.FillDeck(deckPlayer1);

    vector<CardsManager::CardNum> deckPlayer2 =
    {
        CardsManager::CardNum::Lorris,
        CardsManager::CardNum::Lorris,
        CardsManager::CardNum::Lorris,
        CardsManager::CardNum::Giroud,
        CardsManager::CardNum::Giroud,
        CardsManager::CardNum::Giroud,
        CardsManager::CardNum::Pavard,
        CardsManager::CardNum::Pavard,
        CardsManager::CardNum::Pavard
    };
    player2.FillDeck(deckPlayer2);
}

void GameManager::Update(RenderWindow& window)
{
    HandleEvent(window);
    TimeManager::Update(window);
    InputManager::Instance().Update(window);
    player1.Update(window);
    player2.Update(window);
    Board::Instance().Update(window);
}

void GameManager::Draw(RenderWindow& window)
{
    if (testCollider2D)
    {
        TestCollider2D(window);
    }

    Board::Instance().Draw(window);
    player1.Draw(window);
    player2.Draw(window);
}

void GameManager::HandleEvent(RenderWindow& window) const
{
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            Close(window);
        }
    }
}

void GameManager::Close(RenderWindow& window) const
{
    window.close();
}