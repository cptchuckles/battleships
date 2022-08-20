/**
 * /g/ Coding challenge: Battleships with AI
 */

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "AIController.h"
#include "InputPrompt.h"
#include "ShipBuilder.h"
#include "KeyInput.h"

const int CellSize = 32; //pixels

const int WindowWidth = 10*CellSize;
const int WindowHeight = 24*CellSize;
const int shipSizes[] = {2,3,3,4,5};

enum class GameState {
	SETUP,
	PLAY,
	END
};

GameState state = GameState::SETUP;


sf::RenderWindow window
{
	sf::VideoMode(WindowWidth, WindowHeight),
	"/g/ battleships"
};


sf::Font arial;
sf::Text caption = {"aeiou", arial, (CellSize*3)/4};
InputPrompt prompt = {"wew lads", caption, 0,23*CellSize};

sf::CircleShape open{CellSize/2};
sf::CircleShape full{CellSize/2};
sf::CircleShape miss{CellSize/2};
sf::CircleShape hit{CellSize/2};

Board board_CPU
{
	CellSize, 9,10,
	CellSize,CellSize,
	open, full, miss, hit
};

Board board_player
{
	CellSize, 9,10,
	CellSize,CellSize * 12,
	open, full, miss, hit
};

AIController ai = {board_player, 2};

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

	if(! arial.loadFromFile("/usr/share/fonts/TTF/DejaVuSansMono.ttf"))
		return false;

	open.setFillColor(sf::Color::Blue);
	full.setFillColor(sf::Color{100,110,100,255});
	miss.setFillColor(sf::Color::White);
	hit.setFillColor(sf::Color::Red);

	board_CPU.SetDisplayResource(&caption);
	board_player.SetDisplayResource(&caption);

	board_CPU.SetHidden(true);

	renderer.push_back(&board_CPU);
	renderer.push_back(&board_player);
	renderer.push_back(&prompt);

	return true;
}


void gameReset()
{
	board_CPU.Clear();
	board_CPU.SetHidden(true);
	board_player.Clear();
	prompt.ClearInput();
	state = GameState::SETUP;
}


void gameSetup()
{
	prompt.SetCaption("Arrows, space, & return");

	static ShipBuilder* builder = nullptr;
	static int ships = 4;

	if(! builder) builder = new ShipBuilder{board_player};

	if(! builder->GetShip()) builder->ConstructShip(shipSizes[ships]);

	builder->Update(window);

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
	ShipBuilder builder = {board_CPU};

	for(int i=0; i<5; i++)
		builder.RandomShip(shipSizes[i]);
}


void inPlay()
{
	if(ai.isMyTurn())
	{
		enemyTurn();
		return;
	}

	prompt.SetCaption("Try cell: ");
	prompt.Update();

	if(KeyInput::Get().Return())
	{
		auto cell = board_CPU.GetCellFromString(prompt.GetContent());
		prompt.ClearInput();

		if(! cell) return;

		auto c = cell.value();
		
		if(board_CPU.GetCellType(c).value() & (Board::CellType::HIT | Board::CellType::MISS))
			return;

		board_CPU.Attack(c);

		if(board_CPU.CheckDefeated())
		{
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

	if(ai.Strike() && board_player.CheckDefeated())
	{
		prompt.SetCaption("You Lost! Again? (y/n): ");
		state = GameState::END;
	}
}


void atEndScreen()
{
	board_CPU.SetHidden(false);
	prompt.Update();

	if(KeyInput::Get().Return())
	{
		auto answer = prompt.GetContent();
		prompt.ClearInput();

		if(answer=="Y")
			gameReset();
		else if(answer=="N")
			window.close();
	}
}
