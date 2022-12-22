#include<iostream>

#include "GameManager.hpp"
#include "Collider2D.hpp"
#include "CardManager.hpp"
#include "Test.hpp"

using namespace std;
using namespace sf;

bool testCollider2D = false;

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
    this->_windowSize = Vector2f(window.getSize().x, window.getSize().y);
    AssetsManager::Instance().Start();//on charge les assets
    CardsManager::Instance().Start();//Crétion de toutes les cartes du jeu
    Board::Instance().Start();//Création du plateau dde jeu

    //on place des cartes au pif mdr
    Card card;
    card = CardsManager::Instance().GetCard(CardsManager::CardNum::Lorris);
    Board::Instance().PlaceCard(card, false, CardType::goalkeeper, 0);
    card = CardsManager::Instance().GetCard(CardsManager::CardNum::Giroud);
    Board::Instance().PlaceCard(card, false, CardType::defender, 3);
    card = CardsManager::Instance().GetCard(CardsManager::CardNum::Pavard);
    Board::Instance().PlaceCard(card, true, CardType::striker, 0);
}

void GameManager::Update(RenderWindow& window)
{
    HandleEvent(window);
    Board::Instance().Update(window);
}

void GameManager::Draw(RenderWindow& window)
{
    if (testCollider2D)
    {
        TestCollider2D(window);
    }

    Board::Instance().Draw(window);
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