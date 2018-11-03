/**
 * The battlefield grid of 90 spaces
 */

#include <vector>

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
		for(int i=0; i<size; i++)
			grid.push_back(CellType::OPEN);
	}
	~Board() {
		grid.clear();
	}

	CellType getCell(int col, int row);

	bool Attack(int col, int row);
	bool CheckDefeated();
	void RandomFill(int qt);
	void Draw(sf::RenderTarget& target, int x, int y, bool hidden=false);

	void SetDisplayResource(sf::Text* TextResource) { display = TextResource; }

	void Clear() {
		for(int i=0; i<grid.capacity()-1; i++)
			grid[i] = CellType::OPEN;
	}

};
