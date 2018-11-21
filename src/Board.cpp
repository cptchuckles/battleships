/**
 * Board implementation
 */

#include <SFML/Graphics.hpp>
#include "Utility.h"
#include "Board.h"


void Board::SetDisplayResource(sf::Text* TextResource)
{
	display = TextResource;
}


void Board::SetHidden(bool hide)
{
	hidden = hide;
}


void Board::SetDraw(bool d)
{
	draw = d;
}


void Board::Clear()
{
	std::fill(grid.begin(), grid.end(), CellType::OPEN);
}


void Board::Draw(sf::RenderTarget& target) const
{
	if(!draw) return;

	bool hasDisplay = (display != nullptr);

	// Grid is cols by rows
	for(int r=0; r<rows; r++)
	{
		int dy = cell_size * r;
		dy += y;

		if(hasDisplay){
			display->setString(std::to_string(r));
			display->setPosition(x-cell_size, dy);
			target.draw(*display);
		}

		for(int c=0; c<cols; c++)
		{
			int dx = cell_size * c;
			dx += x;

			if(hasDisplay){
				display->setString((char)((int)'A'+c));
				display->setPosition(dx, y-cell_size);
				target.draw(*display);
			}

			open_cell.setPosition(dx, dy);
			full_cell.setPosition(dx, dy);
			miss_cell.setPosition(dx, dy);
			hit_cell.setPosition(dx, dy);

			int cell = cols*r+c;

			switch(grid.at(cell)) {
			case CellType::OPEN:
				target.draw(open_cell);
				break;
			case CellType::FULL:
				hidden ? target.draw(open_cell) : target.draw(full_cell);
				break;
			case CellType::MISS:
				target.draw(miss_cell);
				break;
			case CellType::HIT:
				target.draw(hit_cell);
			};
		} // for c
	} // for r
}


bool Board::SetCell(int col, int row, CellType type)
{
	if(col > cols-1 || row > rows-1 || col < 0 || row < 0)
		return false;

	int cell = cols*row + col;
	grid.at(cell) = type;

	return true;
}


std::optional<Board::CellType> Board::GetCell(int col, int row) const
{
	if(col > cols-1 || row > rows-1 || col < 0 || row < 0)
		return std::nullopt;

	int cell = cols*row + col;
	return { grid.at(cell) };
}


std::optional<Board::Cell> Board::GetCellFromString(std::string input) const
{
	Cell cell = { 0,0 };

	if(input.length() > 2) return std::nullopt;

	try {
		cell.row = std::stoi(std::string{input[1]});
	} catch(...) {
		return std::nullopt;
	}

	std::string validchars;
	for(int i=0; i<cols; i++)
		validchars.push_back('A'+i);

	cell.col = validchars.find(input[0]);

	if(cell.col == std::string::npos)
		return std::nullopt;

	return {cell};
}


Board::Cell Board::GetDimensions() const
{
	return {cols, rows};
}


bool Board::Attack(Cell cell)
{
	return Attack(cell.col, cell.row);
}

bool Board::Attack(int col, int row)
{
	auto cell = GetCell(col, row);
	if(!cell) return false;

	switch (cell.value())
	{
	case CellType::FULL :
		SetCell(col, row, CellType::HIT);
		return true;
	case CellType::HIT :
		return false;
	default :
		SetCell(col, row, CellType::MISS);
	}

	return false;
}


bool Board::CheckDefeated() const
{
	for(auto c : grid)
		if(c == CellType::FULL)
			return false;

	return true;
}


void Board::RandomFill(unsigned int qt)
{
	// qt > grid.size() will infinitely loop.
	if(qt > grid.size()) return;

	for(int i=0; i<qt; i++) {
		int c = util::Rand(0, grid.size()-1);
		while(grid.at(c) == CellType::FULL)
			c = util::Rand(0, grid.size()-1);

		grid.at(c) = CellType::FULL;
	}
}
