
#include<iostream>
#include "AssetsManager.hpp"

using namespace std; 
using namespace sf;

AssetsManager::AssetsManager()
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
		Image image;
		cout << imgPath << endl;
		if (image.loadFromFile(imgPath))
		{
			this->assets.insert({ name, image });
		}
	}
}

bool AssetsManager::GetAsset(string assetName, Image* res)
{
	if (this->assets.find(assetName) == this->assets.end())
	{
		return false;
	}
	res = &this->assets[assetName];
	return true;
}