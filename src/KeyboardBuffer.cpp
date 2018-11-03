/**
 * Keyboard input buffer implementation
 */

#include <SFML/Window/Keyboard.hpp>
#include "KeyboardBuffer.h"

void KeyboardBuffer::Update()
{
	// sf::Keyboard::Key enum stores A-Z,0-9 as (int)0-35
	// Create an ASCII representation of it here:
	static std::string keylist = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

	for(int k=0; k<=35; k++)
		if(KeycodePressed(k)) buffer += keylist[k];

	if(KeycodePressed(59)) // backspace key
		if(buffer.length() > 0) buffer.erase(buffer.length()-1);

	submit = KeycodePressed(58); // return key
}


bool KeyboardBuffer::KeycodePressed(int key)
{
	bool down = sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key);

	bool result = (down && ! keysDown[key]);

	keysDown[key] = down;

	return result;
}
