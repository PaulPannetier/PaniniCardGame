#include <SFML/Graphics.hpp>

#include "GameManager.hpp"

using namespace std;
using namespace sf;

int main()
{
    Sprite sprite;

    GameManager gameManager = GameManager::Instance();

    RenderWindow window(VideoMode(1600, 900), "SFML!");

    window.setVerticalSyncEnabled(true);

    gameManager.Start(window);

    gameManager.GameLoop(window);

    return 0;
}