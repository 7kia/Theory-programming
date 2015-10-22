#pragma once
#include <SFML\Graphics.hpp>

#include <iostream>
#include <string>

#include "Paths.h"
#include "ItemsVar.h"
#include "BlocksVar.h"
#include "UnlifeObjectVar.h"

const sf::String TITLE_PROGRAM = "MainGame v1.2.5";
const sf::String stringDeathPerson = "Death";

const int DEFAULT_WIDTH_WINDOW = 1200;
const int DEFAULT_HEIGHT_WINDOW = 550;

const int BORDER1 = 1;
const int BORDER10 = 10;
const int LONG_MAP = 25;
const int WIDTH_MAP = 40 + BORDER1;
const int HEIGHT_MAP = 4;

const int NUMBER_COORDINATES = 2;

const int NUMBER_TEXT_STRING = 15;

const float DIAGONAL_SCALE_SPEED = 0.7;
const float PI = 3.14159265;// ÈÑÏÐÀÂÜ

const int SIZE_STRING = 256;

typedef enum
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	UP_LEFT,
	UP_RIGHT,
	DOWN_LEFT,
	DOWN_RIGHT
} Direction;