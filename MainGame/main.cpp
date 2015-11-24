#include <SFML/Graphics.hpp>

#include "Game.h"

const float TIME_PER_FRAME = 1.f / 60.f;

using namespace sf;
using namespace std;

void startGame()
{
	// ќбъ€вление игры
	Game *game = new Game();
	initializeGame(*game);

	RenderWindow &window = game->window;
	MainPerson &mainPerson = game->mainPerson;

	Time timeSinceLastUpdate = Time::Zero;

	while (window.isOpen())
	{
		timeSinceLastUpdate += game->clock.restart();
		while (timeSinceLastUpdate.asSeconds() > TIME_PER_FRAME) {
			timeSinceLastUpdate -= seconds(TIME_PER_FRAME);
			game->update(TIME_PER_FRAME);

		}
		game->render();	
		game->showFPS(timeSinceLastUpdate);
		//writeMap(game->field->dataMap);
	}
	destroyGame(*game);
}

int main()
{
	startGame();
	return 0;
}

