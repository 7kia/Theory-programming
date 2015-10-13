#pragma once
#include <SFML\Graphics.hpp>

const int SIZE_BLOCK = 32;

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