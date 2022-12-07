#include<iostream>

#include "Input.hpp"

using namespace std;
using namespace sf;

void Input::Update(RenderWindow& window)
{
	Vector2i mousePos = Mouse::getPosition() - window.getPosition();
	//Input::mousePosition = mousePos;
	//cout << "x : " << mousePos.x << " y : " << mousePos.y << endl;
}