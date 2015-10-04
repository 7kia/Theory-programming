#pragma once

#include <SFML\Graphics.hpp>

using namespace sf;

#define border1 1
#define border10 10
#define LongMap 25//размер карты высота
#define WidthMap 40 + border1//размер карты ширина 
#define HeightMap 4
#define sizeTile 32

#define maxUnlifeObject 256

// PATHs
#define pathMainPerson "recourses\\images\\mainPerson.png"
#define pathFloor "recourses\\images\\mapFloor.png"
#define pathWall "recourses\\images\\mapWall.png"
#define pathTrees "recourses\\images\\Trees.png"
#define pathGrass1 "recourses\\sounds\\step\\grass1.ogg"
#define pathStone1 "recourses\\sounds\\step\\stone1.ogg")



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
	pine,
	oak
} idUnlifeObject;