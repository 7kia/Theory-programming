#include "Game.h"

void initializeGame(Game & game)
{
	game.databaseSound = new dataSound;
	game.clock = new Clock;
	game.field = new Field;
	game.mainPerson = new MainPerson;
	game.unlifeObjects = new UnlifeObjects;
	game.typesUnlifeObject = new TypesUnlifeObject;

	initializeSound(game.databaseSound);// На будущее
	initializeField(*game.field);

	initializeMainPerson(*game.mainPerson, *game.databaseSound);

	initializeTypeUnlifeObjects(game.typesUnlifeObject, *game.databaseSound);
	initializeUnlifeObjects(game.unlifeObjects, game.typesUnlifeObject);

	//initializeEntity(*game.mainPerson, *game.databaseSound);
	initializeClock(*game.clock);
}

void destroyGame(Game & game)
{
	
// Главный герой
	delete game.mainPerson;

	// Звуки
	delete game.databaseSound;

	// Карта
	delete game.field;

	// Часы
	delete game.clock;

	delete game.unlifeObjects;

	delete game.typesUnlifeObject;

	delete game.entitys;

	//delete *game;
/*
	delete[] game.field.floorSprite;
	//delete[] game.field.wallSprite;

	//delete game.field.floorTexture;
	delete game.field.wallTexture;
	*/
}

void initializeClock(Clock &clock)
{

}