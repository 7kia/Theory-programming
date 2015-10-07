#pragma once

#include <SFML\Graphics.hpp>

const int border1 = 1;
const int border10 = 10;
const int LongMap = 25;//размер карты высота
const int WidthMap = 40 + border1;//размер карты ширина 
const int HeightMap = 4;
const int sizeTile = 32;

const int maxUnlifeObject = 256;

// PATHs

typedef enum {
	mainPerson,
	mapFloor,
	mapWall,
	Trees,
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
	"recourses\\images\\Trees.png"
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
	oak
} idUnlifeObject;