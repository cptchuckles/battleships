/**
 * Input Prompt object
 * handles taking input from player
 */

#include <string>
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
		bool valid;
	};

private:
	sf::Text* display = nullptr;
	std::string caption;
	KeyboardBuffer kbuf;

	bool enabled = true;


public:

	InputPrompt(std::string caption, sf::Text* TextResource, int x=0, int y=0) : caption{caption}, display{TextResource}
	{
		SetPos(x, y);
	}

	void Update();
	bool Submitted();
	void Enable() { enabled = true; }
	void Disable() { enabled = false; }
	Cell GetCellFromInput();
	std::string GetContent() { return kbuf.Get(); }
	void ClearInput();

	void SetCaption(std::string newCap) { caption = newCap; }
	void SetPos(int x, int y);
	void Draw(sf::RenderTarget& target);
};
