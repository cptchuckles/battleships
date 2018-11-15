/**
 * /g/ Coding challenge: Battleships with AI
 */

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "AIController.h"
#include "InputPrompt.h"
#include "ShipBuilder.h"
#include "KeyInput.h"


const int WindowWidth = 640;
const int WindowHeight = 1508;

enum class GameState {
	SETUP,
	PLAY,
	END
};

GameState state = GameState::SETUP;


sf::RenderWindow window = {
	sf::VideoMode(WindowWidth, WindowHeight),
	"/g/ battleships"
};


sf::Font arial;
sf::Text caption = {"aeiou", arial, 48U};
InputPrompt prompt = {"wew lads", caption, 0,1424};

sf::CircleShape open{32};
sf::CircleShape full{32};
sf::CircleShape miss{32};
sf::CircleShape hit{32};

Board board_1{64, 9,10, 64,64, open, full, miss, hit};
Board board_2{64, 9,10, 64,770, open, full, miss, hit};
AIController ai = {board_2, 0};

std::vector<IDrawable*> renderer;

bool init();
void gameReset();
void gameSetup();
void buildEnemyShips();
void inPlay();
void enemyTurn();
void atEndScreen();

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
		KeyInput::Get().Update();

		switch(state)
		{
		case GameState::SETUP :
			gameSetup();
			break;
		case GameState::PLAY :
			inPlay();
			break;
		case GameState::END :
			atEndScreen();
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
	board_2.SetDisplayResource(&caption);

	board_1.SetHidden(true);

	renderer.push_back(&board_1);
	renderer.push_back(&board_2);
	renderer.push_back(&prompt);

	return true;
}


void gameReset()
{
	board_1.Clear();
	board_1.SetHidden(true);
	board_2.Clear();
	prompt.ClearInput();
	state = GameState::SETUP;
}


void gameSetup()
{
	prompt.SetCaption("Arrows, space, & return");

	static ShipBuilder* builder = nullptr;
	static int ships = 4;
	int shipSizes[] = {2,3,3,4,5};

	if(! builder) builder = new ShipBuilder{board_2};

	if(! builder->GetShip()) builder->ConstructShip(shipSizes[ships]);

	builder->Update();
	builder->DrawBoard(window);

	if(KeyInput::Get().Return())
	{
		if(builder->FinalizeShip())
			ships--;

		if(ships < 0)
		{
			ships = 4;
			delete builder;
			builder = nullptr;
			buildEnemyShips();
			state = GameState::PLAY;
		}
	}
}


void buildEnemyShips()
{
	int shipSizes[] = {2,3,3,4,5};
	ShipBuilder builder = {board_1};

	for(int i=0; i<5; i++)
		builder.RandomShip(shipSizes[i]);
}


void inPlay()
{
	if(ai.isMyTurn()) {
		enemyTurn();
		return;
	}

	prompt.SetCaption("Try cell: ");
	prompt.Update();

	if(KeyInput::Get().Return())
	{
		auto cell = board_1.GetCellFromString(prompt.GetContent());
		prompt.ClearInput();

		//if(! cell) return;

		if(cell) board_1.Attack(cell.value());

		if(board_1.CheckDefeated()) {
			prompt.SetCaption("You Win! Again? (y/n): ");
			state = GameState::END;
			return;
		}

		ai.ActivateTurn();
	}
}


void enemyTurn()
{
	prompt.SetCaption("Enemy AI thinking...");

	if(ai.Strike()) {
		if(board_2.CheckDefeated()) {
			prompt.SetCaption("You Lost! Again? (y/n): ");
			state = GameState::END;
		}
	}
}


void atEndScreen()
{
	board_1.SetHidden(false);
	prompt.Update();

	if(KeyInput::Get().Return())
	{
		auto answer = prompt.GetContent();

		if(answer=="Y")
			gameReset();
		else if(answer=="N")
			window.close();
	}
}
