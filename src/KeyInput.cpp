/**
 * Keyboard Input implementation
 */

#include "KeyInput.h"

KeyInput& KeyInput::Get()
{
	static KeyInput instance;

	return instance;
}


void KeyInput::Update()
{
	for(auto key : keys)
	{
		bool down = sf::Keyboard::isKeyPressed(key.first);

		keys.at(key.first).pressed = false;
		if(down && !key.second.isdown)
			keys.at(key.first).pressed = true;

		keys.at(key.first).isdown = down;
	}
}


bool KeyInput::KeyPressed(sf::Keyboard::Key key)
{
	bool result = false;
	try {
		result = keys.at(key).pressed;
	} catch(...) {
		keys.emplace(key, Keystroke{false,false});
		return false;
	}

	keys.at(key).pressed = false; // Eat input
	return result;
}


bool KeyInput::Return()
{
	return KeyPressed(sf::Keyboard::Key::Return);
}
