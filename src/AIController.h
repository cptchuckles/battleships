/**
 * AI Controller class.
 */

#pragma once

class Board;


class AIController
{
	Board& target;
	int cols, rows;

public:
	AIController() = delete;
	AIController(Board& target);

	void Strike();
};
