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
		DoIfDown(k, [&]{ buffer += keylist[k]; });

	DoIfDown(59, [&] {
		if(buffer.length() > 0) buffer.erase(buffer.length()-1);
	});
}

template<typename F>
void KeyboardBuffer::DoIfDown(int key, F f)
{
	bool down = sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key);

	if (! keysDown[key])
		if(down) f();

	keysDown[key] = down;
}
