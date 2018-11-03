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

	sf::Text caption = {"fuck", arial, 36U};

	InputPrompt prompt = {"Try Cell:",
						  std::make_unique<sf::Text>(caption),
						  0,1444};

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

	board_1.setCell(0,0, Board::CellType::FULL);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		if(prompt.Update()) {
			prompt.TryCellFromInput(board_1);
			prompt.ClearInput();
		}
		prompt.Draw(window);

		board_1.Draw(window, 64, 0, true);
		board_2.Draw(window, 64, 704);

		window.display();
	}

	return 0;
}
