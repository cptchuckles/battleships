/**
 * Input Prompt object
 * handles taking input from player
 */

#include <string>
#include <optional>
#include "KeyboardBuffer.h"

class Board;

namespace sf
{
	class Text;
	class RenderTarget;
};



class InputPrompt
{
public:
	struct Cell {
		int col, row;
	};

private:
	sf::Text* display = nullptr;
	std::string caption;
	KeyboardBuffer kbuf;

	int x, y;


public:

	InputPrompt(std::string caption, sf::Text* TextResource, int x=0, int y=0) : caption{caption}, display{TextResource}, x{x}, y{y}
	{}

	void Update();
	bool Submitted();
	std::optional<Cell> GetCellFromInput();
	std::string GetContent() { return kbuf.Get(); }
	void ClearInput();
	void SetPos(int newx, int newy);

	void SetCaption(std::string newCap) { caption = newCap; }
	void Draw(sf::RenderTarget& target);
};
