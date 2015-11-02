#pragma once
#include "Sound.h"

#include "MainPerson.h"

#include "Font.h"
#include "GUI.h"
#include "UnlifeObject.h"
#include "TypeItems.h"
#include "Items.h"
#include "ListObjectsAndBlocks.h"
#include "Map.h"


const sf::String TITLE_PROGRAM = "MainGame v1.4.2";

struct Game
{
	sf::RenderWindow *window;

	GUI *gui;
	TextGame *textGame;

	MainPerson *mainPerson;

	TypesUnlifeObject *typesUnlifeObject;
	std::vector<UnlifeObject>* unlifeObjects;

	Item* emptyItem;
	UnlifeObject* emptyObject;

	TypesItem *typesItem;
	std::vector<Item>* items;

	////////////////////////////////////
	// Ходьба по карте(для противников
	float minTimeWalk = 4.f;
	float maxTimeWalk = 12.f;// TODO
	////////////////////////////////////
	// Остальные сущности
	Enemy *emptyEnemy;
	TypesEnemy *typesEnemy;
	std::vector<Enemy>* Enemys;// ДОБАВЛЕНИЕ СУЩНОСТИ
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

void renderEntitys(Game &game);

void destroyGame(Game & game);
void initializeClock(Clock &clock);
void informationAboutSelect(Game &game, float x, float y);