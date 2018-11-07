/**
 * Input Prompt implementation
 */

#include <SFML/Graphics.hpp>
#include "InputPrompt.h"
#include "Board.h"

void InputPrompt::Update()
{
	kbuf.Update();
}

bool InputPrompt::Submitted()
{
	return kbuf.UserSubmitted();
}

std::string InputPrompt::GetContent()
{
	return kbuf.Get();
}

void InputPrompt::ClearInput()
{
	kbuf.Clear();
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

void InputPrompt::Draw(sf::RenderTarget& target)
{
	if(display == nullptr) return;

	display->setPosition((float)x, (float)y);
	display->setString(caption + kbuf.Get());
	target.draw(*display);
}
