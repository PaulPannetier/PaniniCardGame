#ifndef ASSETS_MANAGER_HPP
#define ASSETS_MANAGER_HPP

#include<map>
#include<vector>
#include<string>
#include <SFML/Graphics.hpp>

class AssetsManager
{
private:

	const std::map<std::string, std::string> imagesPath =
	{
		{ "background", "a.jpg" },
	};

	AssetsManager();

	std::map<std::string, sf::Image> images;

	void LoadAssets();

public:

	static AssetsManager instance()
	{
		static AssetsManager asset; 
		return asset;
	}

	std::map<std::string, sf::Image> assets;

	bool GetAsset(std::string assetName, sf::Image* res);
};

#endif