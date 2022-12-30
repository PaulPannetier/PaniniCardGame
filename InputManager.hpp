#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <SFML/Graphics.hpp>

class InputManager
{
private:
	bool oldIsPressesMouse[sf::Mouse::Button::ButtonCount];
	bool oldIsPressesKeyboard[sf::Keyboard::Key::KeyCount];
	bool newIsPressesMouse[sf::Mouse::Button::ButtonCount];
	bool newIsPressesKeyboard[sf::Keyboard::Key::KeyCount];
	sf::Vector2f oldMousePosition, newMousePosition, mouseVelosity;

	InputManager();

public:

	static InputManager& Instance();

	bool GetKey(sf::Mouse::Button button);
	bool GetKey(sf::Keyboard::Key key);
	bool GetKeyDown(sf::Mouse::Button button);
	bool GetKeyDown(sf::Keyboard::Key key);

	sf::Vector2f MousePosition();
	sf::Vector2f MouseVelocity();

	void Start(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window);

};

#endif
