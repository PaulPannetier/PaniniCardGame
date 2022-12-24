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
		{ "BoardBackground", "Assets/bg.jpg" },
		{ "Pavard", "Assets/Cards/Pavard.jpg" },
		{ "Giroud", "Assets/Cards/Giroud.png" },
		{ "Lioris", "Assets/Cards/Lioris.jpg" },
	};

	std::map<std::string, std::shared_ptr<sf::Texture>> textures;

	AssetsManager();

	void LoadAssets();

public:

	static AssetsManager& Instance();

	void Start();
	sf::Texture &GetTexture(std::string name) const;
};

#endif