
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
}

Texture& AssetsManager::GetTexture(string name) const
{
	return *(textures.at(name).get());
}