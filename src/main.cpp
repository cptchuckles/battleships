#include <SFML/Graphics.hpp>

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
		window.display();
	}

	return 0;
}
