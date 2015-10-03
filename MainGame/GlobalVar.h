#pragma once
#define border1 1
#define border10 10
#define LongMap 25//������ ����� ������
#define WidthMap 40 + border1//������ ����� ������ 
#define HeightMap 4
#define sizeTile 32

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