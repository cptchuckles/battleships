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

std::optional<InputPrompt::Cell> InputPrompt::GetCellFromInput()
{
	Cell cell = { 0,0 };

	// Valid formats are [A-I].[0-9].
	auto input = kbuf.Get();
	if(input.length() > 2) return std::nullopt;

	try {
		cell.row = std::stoi(std::string{input[1]});
	} catch(...) {
		return std::nullopt;
	}

	cell.col = std::string{"ABCDEFGHI"}.find(input[0]);

	if(cell.col == std::string::npos) return std::nullopt;

	return {cell};
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
