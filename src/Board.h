/**
 * The battlefield grid of 90 spaces
 */

#pragma once

#include <vector>
#include <optional>
#include "IDrawable.h"

namespace sf {
	class Shape;
	class Text;
	class RenderTarget;
}


class Board : public IDrawable
{
public:
	enum CellType {
		OPEN,
		FULL,
		MISS,
		HIT
	};

	struct Cell {
		int col, row;
	};

private:
	int cols, rows;
	int x, y;
	int cell_size;
	bool hidden = false;
	std::vector<CellType> grid;

	sf::Shape& open_cell;
	sf::Shape& full_cell;
	sf::Shape& miss_cell;
	sf::Shape& hit_cell;
	sf::Text* display = nullptr;

	Board() = delete;

public:
	Board(int cellsize, int cols, int rows, int x, int y,
		sf::Shape& open,
		sf::Shape& full,
		sf::Shape& miss,
		sf::Shape& hit) : cell_size{cellsize}, cols{cols}, rows{rows}, x{x}, y{y}, open_cell{open}, full_cell{full}, miss_cell{miss}, hit_cell{hit}
	{
		int size = rows*cols;
		grid.reserve(size);
		std::fill_n(std::back_inserter(grid), size, CellType::OPEN);
	}
	~Board() {
		grid.clear();
	}

	bool SetCell(int col, int row, CellType);
	std::optional<CellType> GetCell(int col, int row);
	std::optional<Cell> GetCellFromString(std::string input);

	bool Attack(int col, int row);
	bool Attack(Cell);
	bool CheckDefeated();

	void SetDisplayResource(sf::Text* TextResource);
	void SetHidden(bool);

	void Draw(sf::RenderTarget& target) const override;

	void RandomFill(unsigned int qt);
	void Clear();

};
