#include <SFML/Graphics.hpp>

#include "GameManager.hpp"

using namespace std;
using namespace sf;

int main()
{
    GameManager gameManager = GameManager::Instance();

    RenderWindow window(VideoMode(1600, 900), "Panini GameCard");

    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    gameManager.Start(window);

    gameManager.GameLoop(window);

    return 0;
}