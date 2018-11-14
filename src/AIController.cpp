/**
 * AI Controller implementation
 */

#include "AIController.h"
#include "Utility.h"
#include "Board.h"


AIController::AIController(Board& target) : target{target}
{
	auto dim = target.GetColsRows();

	cols = dim.first;
	rows = dim.second;
}


void AIController::Strike()
{
	int col, row;
	Board::CellType cell;

	do
	{
		col = util::Rand(0, cols-1);
		row = util::Rand(0, rows-1);
		cell = target.GetCell(col,row).value();
	}
	while( cell == Board::CellType::MISS
		|| cell == Board::CellType::HIT );

	target.Attack(col, row);
}
