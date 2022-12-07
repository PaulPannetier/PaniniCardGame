#include <SFML/Graphics.hpp>

#include "GameManager.hpp"

using namespace std;
using namespace sf;

GameManager gameManager = GameManager();

int main()
{
    RenderWindow window(VideoMode(1600, 900), "SFML!");
    window.setVerticalSyncEnabled(true);

    gameManager.Start();

    gameManager.GameLoop(window);

    return 0;
}