/**
 * Board implementation
 */

#include <SFML/Graphics.hpp>
#include "Board.h"


void Board::Draw(sf::RenderTarget& target, int x, int y)
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
			hit_cell.setPosition(dx, dy);

			int cell = cols*r+c;

			switch(grid[cell]) {
			case CellType::OPEN:
				target.draw(open_cell);
				break;
			case CellType::FULL:
				target.draw(full_cell);
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
