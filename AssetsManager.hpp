#ifndef ASSETS_MANAGER_HPP
#define ASSETS_MANAGER_HPP

#include<map>
#include<memory>
#include<string>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>

class AssetsManager
{
private:

	const std::map<std::string, std::string> imagesPath =
	{
		{ "Card", "Assets/card.png" },
		{ "Mana", "Assets/mana.png" },
		{ "Defence", "Assets/defence.png" },
		{ "Attack", "Assets/attack.png" },
		{ "BoardBackground", "Assets/bg.jpg" },
		{ "Pavard", "Assets/Cards/Pavard.jpg" },
		{ "Giroud", "Assets/Cards/Giroud.png" },
		{ "Ronaldo", "Assets/Cards/ronaldo.jpg" },
		{ "Lioris", "Assets/Cards/Lioris.jpg" },
		{ "Ball", "Assets/ball.png" },
		{ "Deck", "Assets/deck.png" },
	};

	std::map<std::string, std::shared_ptr<sf::Texture>> textures;

	const std::map<std::string, std::string> fontsPath =
	{
		{ "poppins", "Assets/poppins.ttf" },
	};

	std::map<std::string, std::shared_ptr<sf::Font>> fonts;

	AssetsManager();

	void LoadAssets();

public:

	static AssetsManager& Instance();

	void Start();
	sf::Texture& GetTexture(std::string name) const;
	sf::Font& GetFont(std::string name) const;
};

#endif