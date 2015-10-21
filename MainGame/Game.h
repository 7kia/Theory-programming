#pragma once
// Для динамических списков
#include <list>
#include <iterator>

#include "Sound.h"
#include "MainPerson.h"
#include "UnlifeObject.h"
#include "Items.h"
#include "Font.h"
#include "GUI.h"
#include "ListDestroyObjectsAndBlocks.h"

#include <math.h>

struct Game
{
	RenderWindow *window;

	GUI *gui;
	TextGame *textGame;

	Entity *entitys;// ИСПРАВЬ
	MainPerson *mainPerson;

	TypesUnlifeObject *typesUnlifeObject;
	std::list<UnlifeObject>* unlifeObjects;

	Item* emptyItem;
	UnlifeObject* emptyObject;

	TypesItem *typesItem;
	std::list<Item>* items;

	destroyObjectsAndBlocks* listDestroy;

	Field *field;

	sf::Clock *clock;

	dataSound *databaseSound;

	int countUnlifeObject = 0;

	unsigned int widthMainWindow = DEFAULT_WIDTH_WINDOW;
	unsigned int heightMainWindow = DEFAULT_HEIGHT_WINDOW;
};

void initializeGame(Game & game);

void initializeCategorysBreakingObject(Game &game);

void destroyGame(Game & game);
void initializeClock(Clock &clock);
void informationAboutSelect(Game &game, float x, float y);