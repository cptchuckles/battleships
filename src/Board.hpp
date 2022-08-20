/**
 * The battlefield grid of 90 spaces
 */

#pragma once

#include <vector>
#include <optional>
#include <string>
#include "IDrawable.hpp"

namespace sf {
	class Shape;
	class Text;
	class RenderTarget;
}


class Board : public IDrawable
{
public:
	enum CellType {
		OPEN = 1,
		FULL = 2,
		MISS = 4,
		HIT  = 8
	};

	struct Cell {
		int col, row;
		bool operator==(Cell const& in) { return (col==in.col && row==in.row); }
		bool operator!=(Cell const& in) { return !operator==(in); }
		friend Cell operator+(const Cell& a, const Cell& b) { return std::move(Cell{a.col+b.col, a.row+b.row}); }
		friend Cell operator-(const Cell& a, const Cell& b) { return std::move(Cell{a.col-b.col, a.row-b.row}); }
	};

private:
	int cols, rows;
	int x, y;
	int cell_size;
	bool hidden = false;
	bool draw = true;
	std::vector<CellType> grid;

	sf::Shape& open_cell;
	sf::Shape& full_cell;
	sf::Shape& miss_cell;
	sf::Shape& hit_cell;
	sf::Text* display = nullptr;

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
	std::optional<CellType> GetCellType(int col, int row) const;
	std::optional<CellType> GetCellType(Cell cell) const;
	std::optional<Cell> GetCellFromString(std::string input) const;
	Cell GetDimensions() const;

	bool Attack(int col, int row);
	bool Attack(Cell);
	bool CheckDefeated() const;

	void SetDisplayResource(sf::Text* TextResource);
	void SetHidden(bool);
	void SetDraw(bool);

	void Draw(sf::RenderTarget& target) const override;

	void Clear();

};
