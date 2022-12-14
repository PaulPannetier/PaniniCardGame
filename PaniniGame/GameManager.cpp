#include<iostream>

#include "GameManager.hpp"
#include "Collider2D.hpp"
#include "Test.hpp"

using namespace std;
using namespace sf;

bool testCollider2D = false;

void GameManager::GameLoop(RenderWindow& window) const
{
    while (window.isOpen())
    {
        Update(window);

        window.clear(Color::Black);
        Draw(window);
        window.display();
    }
}

void GameManager::Start() const
{
    //Board b = Board();
}

void GameManager::Update(RenderWindow& window) const
{
    HandleEvent(window);
}

void GameManager::Draw(RenderWindow& window) const
{
    if (testCollider2D)
    {
        TestCollider2D(window);
    }
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