/**
 * Ship Builder class.
 * Not the "builder" design pattern.
 * It handles laying ships of variable length onto a board.
 */

#pragma once

#include <SFML/Window/Keyboard.hpp>
#include "Board.h"

namespace sf {
	class RenderTarget;
}


class ShipBuilder
{
public:
	struct Ship {
		int col,row, length;
		bool vertical;
	};

private:
	Board& board;
	int cols, rows;
	Ship* ship = nullptr;

	void FlipShip();
	void ConfineShipToBoard();
	bool CheckSpaceFree(Ship&) const;
	void DrawBoard(sf::RenderTarget& target);

public:
	ShipBuilder(Board& board) : board{board}
	{
		board.SetDraw(false);

		auto size = board.GetDimensions();
		cols = size.col;
		rows = size.row;
	}
	~ShipBuilder()
	{
		if(ship) {
			if(!FinalizeShip()) {
				delete ship;
				ship = nullptr;
			}
		}

		board.SetDraw(true);
	}


	void Update(sf::RenderTarget& target);

	bool ConstructShip(unsigned int length);
	bool RandomShip(unsigned int length);
	bool FinalizeShip();

	Ship* GetShip() const;
};
