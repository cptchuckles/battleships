#include <SFML/Graphics.hpp>
#include <memory>
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

	Board board{ 64, 9, 10,
		std::make_unique<sf::CircleShape>(open),
		std::make_unique<sf::CircleShape>(full),
		std::make_unique<sf::CircleShape>(hit)
	};

	board.setCell(5, 7, Board::CellType::FULL);
	board.setCell(2, 9, Board::CellType::HIT);

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

		board.Draw(window, 0, 64);

		window.display();
	}

	return 0;
}
