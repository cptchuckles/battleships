/**
 * AI Controller implementation
 */

#include "AIController.h"
#include "Utility.h"
#include "Board.h"


AIController::AIController(Board& target, int delay) : target{target}, delay{delay}
{
	auto dim = target.GetColsRows();

	cols = dim.first;
	rows = dim.second;

	clock_gettime(CLOCK_REALTIME, &timestamp);
}


bool AIController::Strike()
{
	if(!CheckDelayTimer()) return false;

	auto c = CalculateCell();

	if(target.Attack(c))
	{
		last_hit = std::optional(c);

		switch(mode)
		{
		case Mode::RAND :
			cold_hit = std::optional(c);
			try_cells = GetAdjacentCells(c);
			mode = Mode::SEARCH;
			break;
		case Mode::SEARCH :
			rel_move = last_hit.value() - cold_hit.value();
			mode = Mode::TRACE;
		}
	} else {
		if(mode==Mode::TRACE) mode = Mode::SEARCH;
	}

	myturn = false;

	return true;
}


Board::Cell AIController::CalculateCell()
{
	Board::Cell c;

	switch(mode)
	{
	case Mode::RAND :
		c = RandomValidCell();
		break;

	case Mode::SEARCH :
		if(try_cells.size() > 0) {
			int i = util::Rand(0, try_cells.size()-1);
			c = try_cells.at(i);
			try_cells.erase(try_cells.begin()+i);
		} else {
			mode = Mode::RAND;
			c = RandomValidCell();
		}
		break;

	case Mode::TRACE :
		auto oc = NextCellInTrace();
		if(oc) c = oc.value();
		else {
			mode = Mode::SEARCH;
			c = CalculateCell();
		}
	}

	return c;
}


Board::Cell AIController::RandomValidCell() const
{
	Board::Cell try_cell;
	do
	{
		try_cell.col = util::Rand(0, cols-1);
		try_cell.row = util::Rand(0, rows-1);
	}
	while( !CheckCellValid(try_cell) );

	return try_cell;
}


std::optional<Board::Cell> AIController::NextCellInTrace() const
{
	if(!last_hit) return { RandomValidCell() };

	auto cell = last_hit.value() + rel_move;

	if(! CheckCellValid(cell)) return std::nullopt;

	return {cell};
}


std::vector<Board::Cell> AIController::GetAdjacentCells(const Board::Cell& cell)
{
	std::vector<Board::Cell> cells;
	auto check = cell;

	check.col--;
	if(CheckCellValid(check)) cells.push_back(check);
	check.col+=2;
	if(CheckCellValid(check)) cells.push_back(check);
	check.col--;
	check.row--;
	if(CheckCellValid(check)) cells.push_back(check);
	check.row+=2;
	if(CheckCellValid(check)) cells.push_back(check);

	return cells;
}


bool AIController::CheckCellValid(const Board::Cell& cell) const
{
	auto optcell = target.GetCell(cell.col, cell.row);

	if(!optcell) return false;

	auto cellv = optcell.value();

	return ( cellv != Board::CellType::MISS
		&& cellv != Board::CellType::HIT );
}


bool AIController::isMyTurn() const
{
	return myturn;
}


void AIController::ActivateTurn()
{
	clock_gettime(CLOCK_REALTIME, &timestamp);
	myturn = true;
}


bool AIController::CheckDelayTimer()
{
	struct timespec tm;
	clock_gettime(CLOCK_REALTIME, &tm);

	return ((tm.tv_sec - timestamp.tv_sec) >= delay);
}
