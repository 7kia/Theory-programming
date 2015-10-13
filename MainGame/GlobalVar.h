#pragma once
#include <SFML\Graphics.hpp>

#include "Paths.h"
#include "ItemsVar.h"
#include "BlocksVar.h"
#include "UnlifeObjectVar.h"

const sf::String  titleGame= "MainGame v1.2.1";

const int BORDER1 = 1;
const int BORDER10 = 10;
const int LONG_MAP = 25;
const int WIDTH_MAP = 40 + BORDER1;
const int HEIGHT_MAP = 4;

const int NUMBER_COORDINATES = 2;

const int NUMBER_TEXT_STRING = 15;

const float diagonalScaleSpeed = 0.7;
const float PI = 3.14159265;

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