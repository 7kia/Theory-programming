#pragma once
#include <SFML\Graphics.hpp>

#include <math.h>
#include <wchar.h>
#include <assert.h>

#include <iostream>
#include <string>
#include <sstream>// Для перевода числа в строку

#include "Recourses.h"
#include "Items/ItemsVar.h"
#include "Map/BlocksVar.h"
#include "UnlifeObject/UnlifeObjectVar.h"

#include "../structGame/MyFunctions.h"

const sf::String stringDeathPerson = "DEATH";

const int DEFAULT_WIDTH_WINDOW = 1200;
const int DEFAULT_HEIGHT_WINDOW = 500;


/////////////////////////////
// TODO
const int WIDTH_PLAYER = 32;
const int HEIGHT_PLAYER = 32;
const int AMOUNT_PLAYER_SLOTS = 10;


const int WIDTH_WOLF = 81;
const int HEIGHT_WOLF = 81;
const int AMOUNT_WOLF_SLOTS = 8;

const int WIDTH_SKELET = 32;
const int HEIGHT_SKELET = 32;
const int AMOUNT_SKELET_SLOTS = 8;
/////////////////////////////

const int BORDER1 = 1;
const int BORDER10 = 10;
const int LONG_MAP = 25;
const int WIDTH_MAP = 40 + BORDER1;
const int HEIGHT_MAP = 4;

const sf::Vector2i CENTER_WORLD = { WIDTH_MAP / 2, LONG_MAP / 2 };

const int NUMBER_COORDINATES = 2;

const int NUMBER_TEXT_STRING = 15;

const float DIAGONAL_SCALE_SPEED = 0.7f;
const float PI = 3.14159265f;// ИСПРАВЬ

const int SIZE_STRING = 256;

const char DIVIDE_SYMBOL = '/';

typedef enum
{
	NONE_DIRECTION,
	UP,
	UP_RIGHT,
	RIGHT,
	DOWN_RIGHT,
	DOWN,

	UP_LEFT,
	LEFT,
	DOWN_LEFT,

	AMOUNT_DIRECTION
} Direction;

typedef enum
{
	Unbreaking = -1,
	woodNature = 0,
	stoneNature,
	groundNature,
	sandNature,
	waterNature
} idNatureObject;