#pragma once
#define border1 1
#define border10 10
#define LongMap 25//размер карты высота
#define WidthMap 40 + border1//размер карты ширина 
#define HeightMap 4
#define sizeTile 32

typedef enum
{
	unknow,
	air,
	grass,
	dirt,
	water,
	wood,
	stone,
	woodBoard,
	woodLadder,
	amountKnowBlocks
} idBlocks;