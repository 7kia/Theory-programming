#include "Game.h"

void initializeGame(Game & game)
{
	game.databaseSound = new dataSound;
	game.clock = new Clock;
	game.field = new Field;
	game.mainPerson = new MainPerson;
	game.unlifeObjects = new UnlifeObjects;

	initializeSound(game.databaseSound);// �� �������
	initializeField(*game.field);
	initializeMainPerson(*game.mainPerson, *game.databaseSound);
	initializeUnlifeObjects(game.unlifeObjects, *game.databaseSound);
	//initializeEntity(*game.mainPerson, *game.databaseSound);
	initializeClock(*game.clock);
}

void destroyGame(Game & game)
{
	// ������� �����
	delete game.mainPerson;

	// �����
	delete game.databaseSound;

	// �����
	delete game.field;

	// ����
	delete game.clock;

	delete game.unlifeObjects;

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