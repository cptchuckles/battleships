/**
 * Input Prompt object
 * handles taking input from player
 */

#include <string>
#include <memory>
#include "KeyboardBuffer.h"

class Board;

namespace sf
{
	class Text;
	class RenderTarget;
};



class InputPrompt
{
	std::unique_ptr<sf::Text> display;
	std::string caption;
	KeyboardBuffer kbuf;

	bool enabled = true;

	struct Cell {
		int col, row;
		bool valid;
	};

	Cell parseCell(std::string input);

public:

	InputPrompt(std::string caption, std::unique_ptr<sf::Text> TextResource, int x=0, int y=0) : caption{caption}, display{std::move(TextResource)}
	{
		SetPos(x, y);
	}

	bool Update();
	void Enable() { enabled = true; }
	void Disable() { enabled = false; }
	void TryCellFromInput(Board& opponent);
	void ClearInput();

	void SetCaption(std::string newCap) { caption = newCap; }
	void SetPos(int x, int y);
	void Draw(sf::RenderTarget& target);
};
