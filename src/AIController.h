/**
 * AI Controller class.
 */

#pragma once
#include <ctime>
#include <optional>
#include <vector>
#include "Board.h"


class AIController
{
	Board& target;
	int cols, rows, delay;

	enum class Mode {
		RAND,
		SEARCH,
		TRACE
	};

	std::optional<Board::Cell> cold_hit = std::nullopt;
	std::optional<Board::Cell> last_hit = std::nullopt;
	Board::Cell rel_move = {0,0};
	std::vector<Board::Cell> try_cells;
	bool streak = false;
	Mode mode = Mode::RAND;

	struct timespec timestamp;
	bool myturn = false;
	bool CheckDelayTimer();

	bool CheckCellValid(const Board::Cell& cell) const;
	std::vector<Board::Cell> GetAdjacentCells(const Board::Cell& cell);
	Board::Cell RandomValidCell() const;
	Board::Cell NextCellInTrace() const;
	Board::Cell CalculateCell();

public:
	AIController() = delete;
	AIController(Board& target, int delay);

	bool Strike();
	bool isMyTurn() const;
	void ActivateTurn();
};
