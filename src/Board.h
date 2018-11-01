/**
 * The battlefield grid of 90 spaces
 */

#include <vector>

namespace sf
{
	class RenderTarget;
	class Shape;
}


class Board
{
public:
	enum class CellType {
		OPEN,
		FULL,
		HIT
	};

private:
	std::vector<CellType> grid;
	int rows, cols;

	sf::Shape& open_cell;
	sf::Shape& full_cell;
	sf::Shape& hit_cell;

	Board() = delete;

public:
	int cell_size;


	Board(int cellsize, int cols, int rows,
		sf::Shape& open,
		sf::Shape& full,
		sf::Shape& hit) : cell_size{cellsize}, rows{rows}, cols{cols}, open_cell{open}, full_cell{full}, hit_cell{hit}
	{
		int size = rows*cols;
		grid.reserve(size);
		for(int i=0; i<size; i++)
			grid[i] = CellType::OPEN;
	}
	~Board() {
		grid.clear();
	}

	void setCell(int col, int row, CellType=CellType::OPEN);
	CellType getCell(int col, int row);

	void Draw(sf::RenderTarget& target, int x, int y);
};
