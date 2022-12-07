#include<iostream>

#include "GameManager.hpp"
#include "Collider2D.hpp"

using namespace std;
using namespace sf;

void GameManager::Start() const
{

}

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

void GameManager::Update(RenderWindow& window) const
{
    HandleEvent(window);
}

void GameManager::Draw(RenderWindow& window) const
{

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