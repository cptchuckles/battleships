#include <SFML/Graphics.hpp>
#include "Board.h"

const int WindowWidth = 640;
const int WindowHeight = 1408;

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

	sf::Text caption = {"Window works!", arial, 64U};
	//caption.setPosition( 15.0F, 15.0F );

	sf::CircleShape open{32};
	sf::CircleShape full{32};
	sf::CircleShape hit{32};
	open.setFillColor(sf::Color::Blue);
	full.setFillColor(sf::Color::White);
	hit.setFillColor(sf::Color::Red);

	Board board_1{ 64, 9, 10, open, full, hit };
	Board board_2{ 64, 9, 10, open, full, hit };

	board_1.setCell(5, 7, Board::CellType::FULL);
	board_1.setCell(2, 9, Board::CellType::HIT);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(caption);

		board_1.Draw(window, 0, 64);
		board_2.Draw(window, 0, 750);

		window.display();
	}

	return 0;
}
