#pragma once

#include <string.h>

#include <SFML\Graphics.hpp>

const sf::String  titleGame= "MainGame v1.2.1";

const int BORDER1 = 1;
const int BORDER10 = 10;
const int LONG_MAP = 25;
const int WIDTH_MAP = 40 + BORDER1;
const int HEIGHT_MAP = 4;
const int SIZE_BLOCK = 32;

const int NUMBER_TYPE_BLOCKS = 256;
const int SIZE_NAME_BLOCKS = 20;
const int NUMBER_COORDINATES = 2;

const int MAX_UNLIFE_OBJECT = 256;
const int AMOUNT_TYPES_UNLIFE_OBJECT = 15;

const int MAX_ITEMS = 256;
const int AMOUNT_TYPES_ITEM = 15;

const int NUMBER_TEXT_STRING = 15;

const float diagonalScaleSpeed = 0.7;
const float PI = 3.14159265;

// PATHs

typedef enum {
	mainPerson,
	mapFloor,
	mapWall,
	Trees,
	infoSelectBlock,
	items,
	amountTexturePaths
} idTexturePaths;

typedef enum {
	stepGrass1,
	stepStone1,
	amountSoundPaths
} idSoundPaths;

const sf::String texturePaths[idTexturePaths::amountTexturePaths] =
{
	"recourses\\images\\mainPerson.png",
	"recourses\\images\\mapFloor.png",
	"recourses\\images\\mapWall.png",
	"recourses\\images\\Trees.png",
	"recourses\\images\\InfoWindow.png",
	"recourses\\images\\Items.png"
};

const sf::String soundPaths[idSoundPaths::amountSoundPaths] =
{
	"recourses\\sounds\\step\\grass1.ogg",
	"recourses\\sounds\\step\\stone1.ogg"
};

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

typedef enum
{
	unknow,
	air,
	grass,
	dirt,
	sand,
	water,
	wood,
	stone,
	stoneBrick,
	woodBoard,
	woodLadder,
	amountKnowBlocks
} idBlocks;

typedef enum
{
	oak,
	smallStone// камешек
} idUnlifeObject;

typedef enum
{
	smallStoneItem// камешек
} idItem;

const sf::Vector2f scaleItems = { 0.5f, 0.5f };