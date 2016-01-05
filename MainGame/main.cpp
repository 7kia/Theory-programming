#include <SFML/Graphics.hpp>


#include "structGame/Game.h"

const float TIME_PER_FRAME = 1.f / 60.f;

using namespace sf;
using namespace std;

void startGame()
{
	Game *game = new Game();
	// TODO : delete
	assert(game->world.Enemys[ID_PLAYER_IN_LIST].itemsEntity[0].getType() != game->world.emptyObjects.emptyItem.getType());

	RenderWindow &window = game->window;

	Time timeSinceLastUpdate = Time::Zero;

	assert(game->world.Enemys[ID_PLAYER_IN_LIST].itemsEntity[0].getType() != game->world.emptyObjects.emptyItem.getType());

	while (window.isOpen())
	{
		assert(game->world.Enemys[ID_PLAYER_IN_LIST].itemsEntity[0].getType() != game->world.emptyObjects.emptyItem.getType());

		timeSinceLastUpdate += game->clock.restart();
		while (timeSinceLastUpdate.asSeconds() > TIME_PER_FRAME) {
			timeSinceLastUpdate -= seconds(TIME_PER_FRAME);
			assert(game->world.Enemys[ID_PLAYER_IN_LIST].itemsEntity[0].getType() != game->world.emptyObjects.emptyItem.getType());

			game->update(TIME_PER_FRAME);
			assert(game->world.Enemys[ID_PLAYER_IN_LIST].itemsEntity[0].getType() != game->world.emptyObjects.emptyItem.getType());

		}
		assert(game->world.Enemys[ID_PLAYER_IN_LIST].itemsEntity[0].getType() != game->world.emptyObjects.emptyItem.getType());

		game->render();	
		assert(game->world.Enemys[ID_PLAYER_IN_LIST].itemsEntity[0].getType() != game->world.emptyObjects.emptyItem.getType());

		game->showFPS(timeSinceLastUpdate);
		assert(game->world.Enemys[ID_PLAYER_IN_LIST].itemsEntity[0].getType() != game->world.emptyObjects.emptyItem.getType());

	}
	destroyGame(*game);
}

int main()
{
	startGame();
	return 0;
}

