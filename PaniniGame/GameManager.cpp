#include<iostream>

#include "GameManager.hpp"
#include "Collider2D.hpp"
#include "Button.hpp"
#include "Test.hpp"

using namespace std;
using namespace sf;

bool testCollider2D = false;

void OnClick(Button b)
{
    cout << b.ToString() << ": are pressed" << endl;
}

RectangleButton rb = RectangleButton(Rectangle(Vector2f(200, 200), Vector2f(300, 150)), OnClick);
CircleButton cb = CircleButton(Circle(Vector2f(600, 300), 75), OnClick);

GameManager::GameManager()
{

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
    AssetsManager::instance();
    this->_windowSize = Vector2f(window.getSize().x, window.getSize().y);
}

void GameManager::Update(RenderWindow& window)
{
    HandleEvent(window);
    //rb.Update(window);
    //cb.Update(window);
}

void GameManager::Draw(RenderWindow& window)
{
    if (testCollider2D)
    {
        TestCollider2D(window);
    }

    this->board.Draw(window);
    rb.Draw(window);
    cb.Draw(window);
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