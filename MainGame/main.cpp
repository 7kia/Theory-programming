#include <SFML/Graphics.hpp>


#include "structGame/Game.h"

const float TIME_PER_FRAME = 1.f / 60.f;

using namespace sf;
using namespace std;

void startGame()
{
	Game *game = new Game();

	RenderWindow &window = game->window;
	Entity *mainPerson = game->world.mainPerson;

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
	}
	destroyGame(*game);
}

int main()
{
	startGame();
	return 0;
}

