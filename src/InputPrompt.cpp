/**
 * Input Prompt implementation
 */

#include <SFML/Graphics.hpp>
#include "InputPrompt.h"
#include "Board.h"

bool InputPrompt::Update()
{
	if(!enabled) return false;

	kbuf.Update();

	return kbuf.UserSubmitted();
}

void InputPrompt::ClearInput()
{
	kbuf.Clear();
}

InputPrompt::Cell InputPrompt::GetCellFromInput()
{
	Cell cell = { 0,0, false };

	// Valid formats are [A-I].[0-9].
	auto input = kbuf.Get();
	if(input.length() > 2) return cell;

	try {
		cell.row = std::stoi(std::string{input[1]});
	} catch(...) {
		return cell;
	}

	cell.col = std::string{"ABCDEFGHI"}.find(input[0]);

	if(cell.col != std::string::npos) cell.valid = true;

	return cell;
}

void InputPrompt::SetPos(int x, int y)
{
	display->setPosition(x, y);
}

void InputPrompt::Draw(sf::RenderTarget& target)
{
	display->setString(caption + kbuf.Get());
	target.draw(*display);
}
