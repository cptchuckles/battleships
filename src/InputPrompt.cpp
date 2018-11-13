/**
 * Input Prompt implementation
 */

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "InputPrompt.h"
#include "KeyInput.h"


void InputPrompt::Update()
{
	// sf::Keyboard::Key enum stores A-Z,0-9 as (int)0-35
	// Create an ASCII representation of it here:
	static std::string keylist = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

	for(int k=0; k<=35; k++)
	{
		auto key = (sf::Keyboard::Key)k;
		if(KeyInput::Get().KeyPressed(key)) buffer += keylist[k];
	}

	if(KeyInput::Get().KeyPressed(sf::Keyboard::Key::Backspace))
		if(buffer.length() > 0) buffer.erase(buffer.length()-1);
}


std::string InputPrompt::GetContent()
{
	return buffer;
}


void InputPrompt::ClearInput()
{
	buffer.clear();
}


void InputPrompt::SetPos(int newx, int newy)
{
	x = newx;
	y = newy;
}


void InputPrompt::SetCaption(std::string newCap)
{
	caption = newCap;
}


void InputPrompt::Draw(sf::RenderTarget& target) const
{
	display.setPosition((float)x, (float)y);
	display.setString(caption + buffer);
	target.draw(display);
}
