#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <SFML/Graphics.hpp>
#include "AssetsManager.hpp"
#include "Board.hpp"

class GameManager
{
private:

	GameManager();
	Board board;
	sf::Vector2f _windowSize;

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