#pragma once
//#ifndef GAME_H
//#define GAME_H

// Для динамических списков
#include <list>     // подключаем заголовок списка
#include <iterator> // заголовок итераторов


#include "Sound.h"
#include "MainPerson.h"
#include "UnlifeObject.h"
#include "Items.h"
#include "Font.h"
#include "GUI.h"

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



	TypesItem *typesItem;
	std::list<Item>* items;
	
	//Items *items;

	Field *field;
	sf::Clock *clock;

	dataSound *databaseSound;

	int countUnlifeObject = 0;

	unsigned int widthMainWindow = 800;
	unsigned int heightMainWindow = 600;
};

void initializeGame(Game & game);
void destroyGame(Game & game);
void initializeClock(Clock &clock);
void informationAboutSelect(Game &game, float x, float y);


//#endif GAME_H