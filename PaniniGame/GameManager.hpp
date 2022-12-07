#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <SFML/Graphics.hpp>

class GameManager
{
public:

	GameManager() { }
	void Start() const;
	void GameLoop(sf::RenderWindow& window) const;
	void Update(sf::RenderWindow& window) const;
	void Draw(sf::RenderWindow& window) const;
	void HandleEvent(sf::RenderWindow& window) const;
	void Close(sf::RenderWindow& window) const;
};

#endif