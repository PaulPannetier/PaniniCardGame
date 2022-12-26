#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <SFML/Graphics.hpp>
#include "AssetsManager.hpp"
#include "Player.hpp"

class GameManager
{
private:

	GameManager();
	sf::Vector2f _windowSize;
	Player player1, player2;

public:

	static GameManager& Instance();

	sf::Vector2f GetWindowSize() {
		return _windowSize;
	}

	void Start(sf::RenderWindow& window);
	void GameLoop(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
	void HandleEvent(sf::RenderWindow& window) const;
	void Close(sf::RenderWindow& window) const;
};

#endif