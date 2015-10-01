#include "Game.h"

void initializeGame(Game & game)
{
	initializeSound(game.soundBuffer);// На будущее
	initializeField(game.field);
	initializeMainPerson(game.mainPerson);
	initializeClock(game.clock);
}

void destroyGame(Game & game)
{
	delete game.mainPerson.spritePerson;
	delete game.mainPerson.textureMainPerson;
	delete game.mainPerson.view;

	delete game.field.dataMap;

	delete[] game.field.floorSprite;
	delete[] game.field.wallSprite;

	delete game.field.floorTexture;
	delete game.field.wallTexture;
}

void initializeClock(Clock &clock)
{

}