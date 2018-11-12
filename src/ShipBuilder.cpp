/**
 * Ship Builder implementation.
 */

#include <SFML/Graphics.hpp>
#include <ctime>
#include <random>
#include "ShipBuilder.h"


bool ShipBuilder::KeyPressed(sf::Keyboard::Key key)
{
	bool down = sf::Keyboard::isKeyPressed(key);

	bool result = down && !keys.at(key);

	keys.at(key) = down;

	return result;
}


bool ShipBuilder::Submitted()
{
	return KeyPressed(sf::Keyboard::Key::Return);
}


ShipBuilder::Ship* ShipBuilder::GetShip()
{
	return ship;
}


bool ShipBuilder::ConstructShip(unsigned int length)
{
	if(ship) return false;
	if(length == 0 || (length > rows && length > cols)) return false;

	ship = new Ship {0,0, length, (length > cols)};

	return true;
}


bool ShipBuilder::CheckSpaceFree(Ship& s)
{
	int c = s.col;
	int r = s.row;
	for(int i=0; i<s.length; i++)
	{
		if(board.GetCell(c,r).value() == Board::CellType::FULL) return false;
		c += !s.vertical;
		r += s.vertical;
	}

	return true;
}


void ShipBuilder::Update()
{
	if(!ship) return;

	// Movement deltas
	int dc = KeyPressed(sf::Keyboard::Key::Right) - KeyPressed(sf::Keyboard::Key::Left);
	int dr = KeyPressed(sf::Keyboard::Key::Down) - KeyPressed(sf::Keyboard::Key::Up);

	if(KeyPressed(sf::Keyboard::Key::Space))
		FlipShip();

	dc += ship->col;
	dr += ship->row;

	// Shrink bounds based on ship orientation
	//int goodcols = ship->vertical ? cols-1 : (cols - ship->length);
	//int goodrows = ship->vertical ? (rows - ship->length) : rows-1;
	//if(dc < 0 || dc > goodcols) dc = ship->col;
	//if(dr < 0 || dr > goodrows) dr = ship->row;

	ship->col = dc;
	ship->row = dr;

	ConfineShipToBoard();
}


void ShipBuilder::ConfineShipToBoard()
{
	if(!ship) return;

	int goodcols = ship->vertical ? cols-1 : (cols - ship->length);
	int goodrows = ship->vertical ? (rows - ship->length) : rows-1;

	if(ship->col > goodcols) ship->col = goodcols;
	if(ship->col < 0) ship->col = 0;
	if(ship->row > goodrows) ship->row = goodrows;
	if(ship->row < 0) ship->row = 0;
}


void ShipBuilder::FlipShip()
{
	if(!ship) return;

	ship->vertical = !ship->vertical;

	ConfineShipToBoard();
	//int goodcols = ship->vertical ? cols-1 : (cols - ship->length);
	//int goodrows = ship->vertical ? (rows - ship->length) : rows-1;
	//if(ship->col > goodcols) ship->col = goodcols;
	//if(ship->row > goodrows) ship->row = goodrows;
}


bool ShipBuilder::FinalizeShip()
{
	if(!ship) return false;
	if(!CheckSpaceFree(*ship)) return false;

	int c = ship->col;
	int r = ship->row;
	for(int i=0; i<ship->length; i++)
	{
		board.SetCell(c,r, Board::CellType::FULL);
		c += !ship->vertical;
		r += ship->vertical;

		ConfineShipToBoard();
	}

	delete ship;
	ship = nullptr;

	return true;
}


void ShipBuilder::DrawBoard(sf::RenderTarget& target)
{
	Board temp = board;
	temp.SetDraw(true);

	if(ship)
	{
		int c = ship->col;
		int r = ship->row;
		for(int i=0; i < ship->length; i++)
		{
			if(temp.GetCell(c,r).value() == Board::CellType::FULL)
				temp.SetCell(c,r, Board::CellType::HIT);
			else
				temp.SetCell(c,r, Board::CellType::MISS);

			c += !ship->vertical;
			r += ship->vertical;
		}
	} // if ship

	temp.Draw(target);
}


bool ShipBuilder::RandomShip(unsigned int length)
{
	if(! ConstructShip(length)) return false;

	// Get system time resource
	struct timespec tm;
	clock_gettime(CLOCK_REALTIME, &tm);

	// Create random num generator functors with clock nanoseconds as seed
	std::minstd_rand0 e{tm.tv_nsec};
	std::uniform_int_distribution<int> ud_c{0, cols-1};
	std::uniform_int_distribution<int> ud_r{0, rows-1};
	std::uniform_int_distribution<int> ud_v{0, 1};

	ship->col = ud_c(e);
	ship->row = ud_r(e);
	ship->vertical = ud_v(e);
	ConfineShipToBoard();

	while(!CheckSpaceFree(*ship)) {
		ship->col = ud_c(e);
		ship->row = ud_r(e);
		ship->vertical = ud_v(e);
		ConfineShipToBoard();
	}

	FinalizeShip();

	return true;
}
