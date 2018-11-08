/**
 * Input Prompt object
 * handles taking input from player
 */

#pragma once


#include <string>
#include <optional>
#include "KeyboardBuffer.h"
#include "Board.h"
#include "IDrawable.h"



class InputPrompt : public IDrawable
{
	sf::Text& display;
	std::string caption;
	KeyboardBuffer kbuf;

	int x, y;


public:

	friend class ResourceManager;

	InputPrompt(std::string caption, sf::Text& TextResource, int x=0, int y=0) : caption{caption}, display{TextResource}, x{x}, y{y}
	{}

	void Update();
	bool Submitted();
	std::string GetContent();
	void ClearInput();
	void SetPos(int newx, int newy);

	void SetCaption(std::string newCap);
	void Draw(sf::RenderTarget& target) const override;
};
