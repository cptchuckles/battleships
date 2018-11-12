/**
 * Ship Builder class.
 * Not the "builder" design pattern.
 * It handles laying ships of variable length onto a board.
 */

#include <map>
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

	std::map<sf::Keyboard::Key, bool> keys;

	bool KeyPressed(sf::Keyboard::Key key);

public:
	ShipBuilder(Board& board) : board{board}
	{
		board.SetDraw(false);

		keys[sf::Keyboard::Key::Left] = false;
		keys[sf::Keyboard::Key::Right] = false;
		keys[sf::Keyboard::Key::Up] = false;
		keys[sf::Keyboard::Key::Down] = false;
		keys[sf::Keyboard::Key::Return] = false;
		keys[sf::Keyboard::Key::Space] = false;

		auto size = board.GetColsRows();
		cols = size.first;
		rows = size.second;
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

	void Update();
	void DrawBoard(sf::RenderTarget& target);
	void FlipShip();
	void ConfineShipToBoard();
	Ship* GetShip();
	bool CheckSpaceFree(Ship&);
	bool Submitted();
	bool ConstructShip(unsigned int length);
	bool FinalizeShip();
	bool RandomShip(unsigned int length);
};
