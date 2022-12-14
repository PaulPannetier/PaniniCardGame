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

    Rectangle rec = Rectangle(Vector2f(300, 100), Vector2f(250, 100));
    Vector2i tmp = Mouse::getPosition(window);
    Vector2f mousPos = Vector2f(tmp.x, tmp.y);

    bool contain = rec.Contain(mousPos);
    Color c = contain ? Color::Red : Color::Green;
    Rectangle::Draw(window, rec, c);
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