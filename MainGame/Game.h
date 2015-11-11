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
#include "EntityVar.h"


const sf::String TITLE_PROGRAM = "MainGame v1.4.3.12";

struct Game
{
	sf::RenderWindow window;

	GUI gui;
	TextGame textGame;

	MainPerson mainPerson;

	TypesUnlifeObject typesUnlifeObject[AMOUNT_TYPES_UNLIFE_OBJECT];
	std::vector<UnlifeObject>* unlifeObjects;

	Item emptyItem;
	UnlifeObject emptyObject;

	TypeItem typesItem[AMOUNT_TYPES_ITEM];
	std::vector<Item>* items;

	////////////////////////////////////
	// ������ �� �����(��� �����������
	float minTimeWalk = 4.f;
	float maxTimeWalk = 12.f;// TODO

	Enemy emptyEnemy;
	TypeEnemy typesEnemy[amountEnemy];
	std::vector<Enemy>* Enemys;

	listDestroyObjectsAndBlocks* listDestroy;

	Field field;

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