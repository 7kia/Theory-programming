#pragma once
// Для динамических списков
#include <list>
#include <iterator>

#include "Sound.h"

#include "MainPerson.h"

#include "Font.h"
#include "GUI.h"

#include <math.h>

struct Game
{
	RenderWindow *window;

	GUI *gui;
	TextGame *textGame;

	MainPerson *mainPerson;

	TypesUnlifeObject *typesUnlifeObject;
	std::list<UnlifeObject>* unlifeObjects;

	Item* emptyItem;
	UnlifeObject* emptyObject;

	TypesItem *typesItem;
	std::list<Item>* items;


	////////////////////////////////////
	// Остальные сущности
	Enemy *emptyEnemy;
	std::list<Enemy>* Enemys;// ДОБАВЛЕНИЕ СУЩНОСТИ
	////////////////////////////////////

	destroyObjectsAndBlocks* listDestroy;

	Field *field;

	sf::Clock *clock;

	dataSound *databaseSound;

	int countUnlifeObject = 0;
	int countEntity = 0;

	unsigned int widthMainWindow = DEFAULT_WIDTH_WINDOW;
	unsigned int heightMainWindow = DEFAULT_HEIGHT_WINDOW;
};

void initializeGame(Game & game);

void initializeCategorysBreakingObject(Game &game);
void initializeEntitys(Game &game);

void renderEntitys(Game &game);

void destroyGame(Game & game);
void initializeClock(Clock &clock);
void informationAboutSelect(Game &game, float x, float y);