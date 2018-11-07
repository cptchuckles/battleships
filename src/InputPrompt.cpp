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

void InputPrompt::ClearInput()
{
	kbuf.Clear();
}

void InputPrompt::SetPos(int newx, int newy)
{
	x = newx;
	y = newy;
}

void InputPrompt::Draw(sf::RenderTarget& target)
{
	display->setString(caption + kbuf.Get());
	display->setPosition((float)x, (float)y);
	target.draw(*display);
}
