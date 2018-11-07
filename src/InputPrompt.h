/**
 * Input Prompt object
 * handles taking input from player
 */

#pragma once

#include <string>
#include <optional>
#include "KeyboardBuffer.h"
#include "Board.h"


namespace sf
{
	class Text;
	class RenderTarget;
};



class InputPrompt
{
	sf::Text* display = nullptr;
	std::string caption;
	KeyboardBuffer kbuf;

	int x, y;


public:

	InputPrompt(std::string caption, sf::Text* TextResource, int x=0, int y=0) : caption{caption}, display{TextResource}, x{x}, y{y}
	{}

	void Update();
	bool Submitted();
	std::string GetContent();
	void ClearInput();
	void SetPos(int newx, int newy);

	void SetCaption(std::string newCap);
	void Draw(sf::RenderTarget& target);
};
