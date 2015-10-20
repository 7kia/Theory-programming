#pragma once
#include <SFML\Graphics.hpp>

const int SIZE_BLOCK = 48;//32 default

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