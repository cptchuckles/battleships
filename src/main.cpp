/**
 * /g/ Coding challenge: Battleships with AI
 */

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "InputPrompt.h"


const int WindowWidth = 640;
const int WindowHeight = 1508;
int gameState = 1; // 1=in play, 2=at win screen


sf::RenderWindow window = {
	sf::VideoMode(WindowWidth, WindowHeight),
	"/g/ battleships"
};


sf::Font arial;

sf::Text caption = {"fuck", arial, 48U};

InputPrompt prompt = {"Try cell: ", caption, 0,1424};

sf::CircleShape open{32};
sf::CircleShape full{32};
sf::CircleShape miss{32};
sf::CircleShape hit{32};
Board board_1{64, 9,10, 64,64, open, full, miss, hit};
Board board_2{64, 9,10, 64,770, open, full, miss, hit};
std::vector<IDrawable*> renderer;

bool init();
void inPlay();
void atWinScreen();

int main()
{
	if(! init()) return 1;


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		switch(gameState)
		{
		case 1:
			inPlay();
			break;
		case 2:
			atWinScreen();
			break;
		}

		for(auto item : renderer) item->Draw(window);


		window.display();
	}

	return 0;
}


bool init()
{
	window.setFramerateLimit(60);

	if(! arial.loadFromFile("c:/windows/fonts/arial.ttf"))
		return false;


	open.setFillColor(sf::Color::Blue);
	full.setFillColor(sf::Color{128,128,128,255});
	miss.setFillColor(sf::Color::White);
	hit.setFillColor(sf::Color::Red);

	board_1.SetDisplayResource(&caption);
	board_1.SetHidden(true);
	board_2.SetDisplayResource(&caption);

	board_1.RandomFill(20);

	renderer.push_back(&board_1);
	renderer.push_back(&board_2);
	renderer.push_back(&prompt);

	return true;
}


void inPlay()
{
	prompt.SetCaption("Try cell: ");
	prompt.Update();

	if(prompt.Submitted())
	{
		auto cell = board_1.GetCellFromString(prompt.GetContent());
		if(cell) board_1.Attack(cell.value());

		if(board_1.CheckDefeated()) gameState = 2;

		prompt.ClearInput();
	}
}


void atWinScreen()
{
	prompt.SetCaption("You win! Again (y/n)? ");
	prompt.Update();

	if(prompt.Submitted())
	{
		auto answer = prompt.GetContent();

		if(answer=="Y") {
			board_1.Clear();
			board_1.RandomFill(20);
			gameState = 1;

			prompt.ClearInput();
		}
		else if(answer=="N")
			window.close();
	}
}
