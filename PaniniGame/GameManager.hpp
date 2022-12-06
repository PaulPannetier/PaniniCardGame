#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <SFML/Graphics.hpp>

class GameManager
{
public:
	static GameManager instance;

	sf::RenderWindow mainWindow;

};

#endif