/**
 * Ship Builder implementation.
 */

#include <SFML/Graphics.hpp>
#include <algorithm>
#include "ShipBuilder.h"
#include "KeyInput.h"
#include "Utility.h"


ShipBuilder::Ship* ShipBuilder::GetShip() const
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


bool ShipBuilder::CheckSpaceFree(Ship& s) const
{
  int c = s.col;
  int r = s.row;
  for(int i=0; i<s.length; i++)
  {
    if(board.GetCellType(c,r).value() == Board::CellType::FULL) return false;
    c += !s.vertical;
    r += s.vertical;
  }

  return true;
}


void ShipBuilder::Update(sf::RenderTarget& target)
{
  if(!ship) return;

  auto& kb = KeyInput::Get();

  // Movement deltas
  int dc = kb.KeyPressed(sf::Keyboard::Key::Right) - kb.KeyPressed(sf::Keyboard::Key::Left);
  int dr = kb.KeyPressed(sf::Keyboard::Key::Down) - kb.KeyPressed(sf::Keyboard::Key::Up);

  if(kb.KeyPressed(sf::Keyboard::Key::Space))
    FlipShip();

  ship->col += dc;
  ship->row += dr;

  ConfineShipToBoard();
  DrawBoard(target);
}


void ShipBuilder::ConfineShipToBoard()
{
  if(!ship) return;

  int goodcols = ship->vertical ? cols-1 : (cols - ship->length);
  int goodrows = ship->vertical ? (rows - ship->length) : rows-1;

  ship->col = std::clamp(ship->col, 0, goodcols);
  ship->row = std::clamp(ship->row, 0, goodrows);
}


void ShipBuilder::FlipShip()
{
  if(!ship) return;

  ship->vertical = !ship->vertical;

  ConfineShipToBoard();
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
      if(temp.GetCellType(c,r).value() == Board::CellType::FULL)
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

  do {
    ship->col = util::Rand(0, cols-1);
    ship->row = util::Rand(0, rows-1);
    ship->vertical = util::Rand(0, 1);
    ConfineShipToBoard();
  }
  while(!CheckSpaceFree(*ship));

  FinalizeShip();

  return true;
}
