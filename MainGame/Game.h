#pragma once
#include "Sound.h"

#include "MainPerson.h"

#include "Font.h"
#include "GUI.h"

#include "EntityVar.h"


const sf::String TITLE_PROGRAM = "MainGame v1.5.2";


struct Game
{
	sf::RenderWindow window;

	GUI gui;
	TextGame textGame;

	MainPerson mainPerson;

	TypeUnlifeObject typesUnlifeObject[AMOUNT_TYPES_UNLIFE_OBJECT];


	Item emptyItem;
	UnlifeObject emptyObject;

	TypeItem typesItem[AMOUNT_TYPES_ITEM];
	
	world world;
	////////////////////////////////////
	// Ходьба по карте(для противников
	float minTimeWalk = 4.f;
	float maxTimeWalk = 12.f;// TODO

	Enemy emptyEnemy;
	TypeEnemy typesEnemy[amountEnemy];

	sf::Clock clock;

	dataSound databaseSound;

	//TODO
	int countUnlifeObject = 0;
	int countEntity = 0;

	unsigned int widthMainWindow = DEFAULT_WIDTH_WINDOW;
	unsigned int heightMainWindow = DEFAULT_HEIGHT_WINDOW;
};

void initializeGame(Game & game);

void initializeCategorysBreakingObject(Game &game);

void updateEntity(Game &game, const sf::Time deltaTime);
void renderEntitys(Game &game);

void destroyGame(Game & game);
void initializeClock(Clock &clock);
void informationAboutSelect(Game &game, float x, float y);