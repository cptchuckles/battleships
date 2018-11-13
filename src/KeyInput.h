/**
 * Keyboard Input handler singleton.
 * Will record all keypresses and eat them upon check.
 */

#pragma once

#include <map>
#include <SFML/Window/Keyboard.hpp>


class KeyInput
{
public:
	struct Keystroke {
		bool pressed=false;
		bool isdown=false;
	};

private:
	std::map<sf::Keyboard::Key, Keystroke> keys;

	KeyInput() {};
public:
	KeyInput(KeyInput const&)		= delete;
	KeyInput(KeyInput const&&)		= delete;
	void operator=(KeyInput const&)	= delete;

	static KeyInput& Get();

	void Update();
	bool KeyPressed(sf::Keyboard::Key key);
	bool Return(); // Special case for brevity
};
