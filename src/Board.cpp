/**
 * Board implementation
 */

#include <SFML/Graphics.hpp>
#include "Board.h"


void Board::Draw(sf::RenderTarget& target, int x, int y, bool hidden)
{
	// Grid is cols by rows
	for(int r=0; r<rows; r++)
	{
		for(int c=0; c<cols; c++)
		{
			int dx = cell_size * c;
			int dy = cell_size * r;
			dx += x;
			dy += y;

			open_cell.setPosition(dx, dy);
			full_cell.setPosition(dx, dy);
			miss_cell.setPosition(dx, dy);
			hit_cell.setPosition(dx, dy);

			int cell = cols*r+c;

			switch(grid[cell]) {
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
	grid[cell] = type;
}

Board::CellType Board::getCell(int col, int row)
{
	if(col > cols || row > rows || col < 0 || row < 0)
		return CellType::OPEN;

	int cell = cols*row + col;
	return grid[cell];
}

bool Board::Attack(int col, int row)
{
	switch (getCell(col, row))
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
		if(c==CellType::FULL)
			return false;

	return true;
}
