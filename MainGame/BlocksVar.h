#pragma once
#include <SFML\Graphics.hpp>

const int SIZE_BLOCK = 48;//32 default

const int slowingStep = 4;

const int shiftForItem = -2;

typedef enum
{
	unknow,
	air,
	grass,
	dirt,
	sand,
	water,
	logOak,
	stone,
	stoneBrick,
	planksBlock,
	woodLadder,
	amountKnowBlocks
} idBlocks;