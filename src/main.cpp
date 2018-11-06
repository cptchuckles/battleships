#include <SFML/Graphics.hpp>
#include "Board.h"
#include "InputPrompt.h"

const int WindowWidth = 640;
const int WindowHeight = 1508;

int main()
{
	sf::RenderWindow window = {
		sf::VideoMode(WindowWidth, WindowHeight),
		"/g/ battleships"
	};

	window.setFramerateLimit(60);

	sf::Font arial;
	if(! arial.loadFromFile("c:/windows/fonts/arial.ttf"))
		return 1;

	sf::Text caption = {"fuck", arial, 48U};

	InputPrompt prompt = {"Try cell: ",
	                      &caption,
	                      0,1424};

	sf::CircleShape open{32};
	sf::CircleShape full{32};
	sf::CircleShape miss{32};
	sf::CircleShape hit{32};
	open.setFillColor(sf::Color::Blue);
	full.setFillColor(sf::Color{128,128,128,255});
	miss.setFillColor(sf::Color::White);
	hit.setFillColor(sf::Color::Red);

	Board board_1{64, 9, 10, open, full, miss, hit};
	Board board_2{64, 9, 10, open, full, miss, hit};
	board_1.SetDisplayResource(&caption);
	board_2.SetDisplayResource(&caption);

	board_1.RandomFill(20);

	int gameState = 1; // 1=in play, 2=at win screen

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		prompt.Update();
		if(prompt.Submitted())
		{
			if(gameState==1)
			{
				auto cell = prompt.GetCellFromInput();
				if(cell)
					board_1.Attack(cell.value().col, cell.value().row);

				if(board_1.CheckDefeated()) gameState = 2;

				prompt.ClearInput();
			}
			if(gameState==2)
			{
				prompt.SetCaption("You win! Again (y/n)? ");
				auto answer = prompt.GetContent();

				if(answer=="Y") {
					board_1.Clear();
					board_1.RandomFill(20);
					prompt.SetCaption("Try cell: ");
					prompt.ClearInput();

					gameState = 1;
				}
				else if(answer=="N")
					window.close();
			}
		}
		prompt.Draw(window);

		board_1.Draw(window, 64, 64, true);
		board_2.Draw(window, 64, 770);

		window.display();
	}

	return 0;
}
