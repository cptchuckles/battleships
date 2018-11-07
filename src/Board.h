/**
 * The battlefield grid of 90 spaces
 */

#pragma once

#include <vector>
#include <optional>

namespace sf
{
	class RenderTarget;
	class Shape;
	class Text;
}


class Board
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
	std::vector<CellType> grid;

	sf::Shape& open_cell;
	sf::Shape& full_cell;
	sf::Shape& miss_cell;
	sf::Shape& hit_cell;
	sf::Text* display = nullptr;

	Board() = delete;

public:
	void setCell(int col, int row, CellType);
	int cell_size;


	Board(int cellsize, int cols, int rows,
		sf::Shape& open,
		sf::Shape& full,
		sf::Shape& miss,
		sf::Shape& hit) : cell_size{cellsize}, rows{rows}, cols{cols}, open_cell{open}, full_cell{full}, miss_cell{miss}, hit_cell{hit}
	{
		int size = rows*cols;
		grid.reserve(size);
		std::fill_n(std::back_inserter(grid), size, CellType::OPEN);
	}
	~Board() {
		grid.clear();
	}

	std::optional<CellType> getCell(int col, int row);
	std::optional<Cell> GetCellFromString(std::string input);

	bool Attack(int col, int row);
	bool Attack(Cell);
	bool CheckDefeated();
	void RandomFill(unsigned int qt);
	void Draw(sf::RenderTarget& target, int x, int y, bool hidden=false);

	void SetDisplayResource(sf::Text* TextResource) { display = TextResource; }

	void Clear() {
		for(int i=0; i<grid.capacity(); i++)
			grid[i] = CellType::OPEN;
	}

};
