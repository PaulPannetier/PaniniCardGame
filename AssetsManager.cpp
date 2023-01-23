
#include<iostream>
#include "AssetsManager.hpp"

using namespace std;
using namespace sf;

AssetsManager::AssetsManager()
{
	
}

AssetsManager& AssetsManager::Instance()
{
	static AssetsManager instance;
	return instance;
}

void AssetsManager::Start()
{
	LoadAssets();
}

void AssetsManager::LoadAssets()
{
	//Textures
	map<string, string>::const_iterator iter;
	for (iter = imagesPath.begin(); iter != imagesPath.end(); iter++)
	{
		string name = iter->first;
		string imgPath = iter->second;
		shared_ptr<Texture> texture = make_shared<Texture>();
		if (texture->loadFromFile(imgPath))
		{
			this->textures[name] = move(texture);
			cout << "Image : " << name << " at : " << imgPath << " loaded!" << endl;
		}
		else
		{
			cout << "Can't load the image : " << name << " at : " << imgPath << endl;
		}
	}

	//Fonts
	for (iter = fontsPath.begin(); iter != fontsPath.end(); iter++)
	{
		string name = iter->first;
		string fontPath = iter->second;
		shared_ptr<Font> font = make_shared<Font>();
		if (font->loadFromFile(fontPath))
		{
			this->fonts[name] = move(font);
			cout << "Font : " << name << " at : " << fontPath << " loaded!" << endl;
		}
		else
		{
			cout << "Can't load the font : " << name << " at : " << fontPath << endl;
		}
	}
}

Texture& AssetsManager::GetTexture(string name) const
{
	return *(textures.at(name).get());
}

Font& AssetsManager::GetFont(string name) const
{
	return *(fonts.at(name).get());
}