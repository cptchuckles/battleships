/**
 * Keyboard input buffer class
 * Because all SFML offers is a way to check if a key is held down.
 */

#pragma once

#include <string>
#include <map>


class KeyboardBuffer
{
	std::string buffer;
	std::map<int, bool> keysDown;

	bool submit = false;

	bool KeycodePressed(int);
public:
	KeyboardBuffer() {
		// sf::Keyboard::Key encodes A..Z,0..9 as 0..35
		for(int k=0; k<=35; k++) keysDown[k] = false;

		// 58 is return, 59 is backspace
		keysDown[58] = false;
		keysDown[59] = false;
	}

	void Update();
	void Clear() { buffer.clear(); }

	bool UserSubmitted() const { return submit; }

	std::string Get() const { return buffer; }
};
