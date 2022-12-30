
#include "Time.hpp"
#include "InputManager.hpp"

using namespace std;
using namespace sf;

InputManager::InputManager()
{

}

InputManager& InputManager::Instance()
{
	static InputManager instance;
	return instance;
}

bool InputManager::GetKey(Mouse::Button button)
{
	return Mouse::isButtonPressed(button);
}

bool InputManager::GetKey(Keyboard::Key key)
{
	return Keyboard::isKeyPressed(key);
}

bool InputManager::GetKeyDown(Mouse::Button button)
{
	return !oldIsPressesMouse[(int)button] && newIsPressesMouse[(int)button];
}

bool InputManager::GetKeyDown(Keyboard::Key key)
{
	return !oldIsPressesKeyboard[(int)key] && newIsPressesKeyboard[(int)key];
}

Vector2f InputManager::MousePosition()
{
	return newMousePosition;
}

Vector2f InputManager::MouseVelocity()
{
	return mouseVelosity;
}

void InputManager::Start(RenderWindow& window)
{
	for (int i = 0; i < (int)Mouse::Button::ButtonCount; i++)
	{
		this->oldIsPressesMouse[i] = false;
		this->newIsPressesMouse[i] = false;
	}

	for (int i = 0; i < (int)Keyboard::Key::KeyCount; i++)
	{
		this->newIsPressesKeyboard[i] = false;
	}

	Vector2u tmp = window.getSize();
	Mouse::setPosition(Vector2i(tmp.x * 0.5, tmp.y * 0.5), window);
	oldMousePosition = Vector2f(0, 0);
	newMousePosition = Vector2f(0, 0);
	mouseVelosity = Vector2f(0, 0);
}

void InputManager::Update(RenderWindow& window)
{
	for (int i = 0; i < (int)Mouse::Button::ButtonCount; i++)
	{
		oldIsPressesMouse[i] = newIsPressesMouse[i];
	}

	for (int i = 0; i < (int)Keyboard::Key::KeyCount; i++)
	{
		oldIsPressesKeyboard[i] = newIsPressesKeyboard[i];
	}

	for (int i = 0; i < (int)Mouse::Button::ButtonCount; i++)
	{
		newIsPressesMouse[i] = Mouse::isButtonPressed((Mouse::Button)i);
	}

	for (int i = 0; i < (int)Mouse::Button::ButtonCount; i++)
	{
		newIsPressesKeyboard[i] = Keyboard::isKeyPressed((Keyboard::Key)i);
	}

	oldMousePosition = newMousePosition;
	Vector2i tmp = Mouse::getPosition(window);
	newMousePosition = Vector2f(tmp.x, tmp.y);
	mouseVelosity = (newMousePosition - oldMousePosition) / TimeManager::DeltaTime();
}