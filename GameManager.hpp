#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <SFML/Graphics.hpp>
#include "AssetsManager.hpp"

class GameManager
{
private:

	GameManager();
	sf::Vector2f _windowSize;

	void HandleEvent(sf::RenderWindow& window) const;

public:

	static GameManager& Instance();

	sf::Vector2f GetWindowSize();

	void Start(sf::RenderWindow& window);
	void GameLoop(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
	void Close(sf::RenderWindow& window) const;
};

#endif