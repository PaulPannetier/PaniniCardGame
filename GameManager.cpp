#include <iostream>
#include <vector>
#include "GameManager.hpp"
#include "Collider2D.hpp"
#include "CardManager.hpp"
#include "Board.hpp"
#include "Test.hpp"
#include "InputManager.hpp"
#include "Time.hpp"
#include "EventManager.hpp"

using namespace std;
using namespace sf;

void FillDeck(Player& player1, Player& player2);

GameManager::GameManager()
{

}

GameManager& GameManager::Instance()
{
    static GameManager gameManager;
    return gameManager;
}

Vector2f GameManager::GetWindowSize()
{
    return this->_windowSize;
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
    EventManager::Instance().Start();
    CardsManager::Instance().Start();//Cr�ation de toutes les cartes du jeu
    Board::Instance().Start();//Cr�ation du plateau dde jeu
}

void GameManager::Update(RenderWindow& window)
{
    HandleEvent(window);
    TimeManager::Update(window);
    InputManager::Instance().Update(window);
    Board::Instance().Update(window);
}

void GameManager::Draw(RenderWindow& window)
{
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