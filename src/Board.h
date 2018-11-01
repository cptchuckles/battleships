/**
 * The battlefield grid of 90 spaces
 */

#include <vector>
#include <memory>

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

	std::unique_ptr<sf::Shape> open_cell = nullptr;
	std::unique_ptr<sf::Shape> full_cell = nullptr;
	std::unique_ptr<sf::Shape> hit_cell = nullptr;

	Board() {}

public:
	int cell_size;


	Board(int cellsize, int cols, int rows,
		std::unique_ptr<sf::Shape> open,
		std::unique_ptr<sf::Shape> full,
		std::unique_ptr<sf::Shape> hit) : cell_size{cellsize}, rows{rows}, cols{cols}
	{
		int size = rows*cols;
		grid.reserve(size);
		for(int i=0; i<size; i++)
			grid[i] = CellType::OPEN;

		open_cell = std::move(open);
		full_cell = std::move(full);
		hit_cell = std::move(hit);
	}
	~Board() {
		grid.clear();
	}

	void setCell(int x, int y, CellType=CellType::OPEN);
	CellType getCell(int x, int y);

	void Draw(sf::RenderTarget& target, int x, int y);
};
