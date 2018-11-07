/**
 * Board implementation
 */

#include <SFML/Graphics.hpp>
#include <random>
#include <ctime>
#include "Board.h"


void Board::Draw(sf::RenderTarget& target, int x, int y, bool hidden)
{
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
		}
	}
}


void Board::setCell(int col, int row, CellType type)
{
	if(col > cols || row > rows || col < 0 || row < 0)
		return;

	int cell = cols*row + col;
	grid.at(cell) = type;
}

std::optional<Board::CellType> Board::getCell(int col, int row)
{
	if(col > cols || row > rows || col < 0 || row < 0)
		return std::nullopt;

	int cell = cols*row + col;
	return { grid.at(cell) };
}

std::optional<Board::Cell> Board::GetCellFromString(std::string input)
{
	Cell cell = { 0,0 };

	// Valid formats are [A-I].[0-9].
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

	if(cell.col == std::string::npos) return std::nullopt;

	return {cell};
}

bool Board::Attack(Cell cell)
{
	return Attack(cell.col, cell.row);
}

bool Board::Attack(int col, int row)
{
	auto cell = getCell(col, row);
	if(!cell) return false;

	switch (cell.value())
	{
	case CellType::FULL :
		setCell(col, row, CellType::HIT);
		return true;
	case CellType::HIT :
		return false;
	default :
		setCell(col, row, CellType::MISS);
	}

	return false;
}

bool Board::CheckDefeated()
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

	// Get system time resource
	struct timespec tm;
	clock_gettime(CLOCK_REALTIME, &tm);

	// Create random num generator functor with clock nanoseconds as seed
	std::minstd_rand0 e{tm.tv_nsec};
	std::uniform_int_distribution<int> ud{0, grid.size()-1};

	for(int i=0; i<qt; i++) {
		int c = ud(e);
		while(grid.at(c) == CellType::FULL) c = ud(e);

		grid.at(c) = CellType::FULL;
	}
}
