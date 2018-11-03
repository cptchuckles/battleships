/**
 * Input Prompt implementation
 */

#include <SFML/Graphics.hpp>
#include "InputPrompt.h"
#include "Board.h"

bool InputPrompt::Update()
{
	kbuf.Update();

	return kbuf.UserSubmitted();
}

void InputPrompt::ClearInput()
{
	kbuf.Clear();
}

void InputPrompt::TryCellFromInput(Board& board)
{
	auto cell = parseCell(kbuf.Get());
	if(!cell.valid) return;

	board.Attack(cell.col, cell.row);
}

InputPrompt::Cell InputPrompt::parseCell(std::string input)
{
	Cell cell = { 0,0, false };

	// Valid formats are [A-I].[0-9].
	if(input.length() > 2) return cell;

	cell.row = std::stoi(std::string{input[1]});
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
