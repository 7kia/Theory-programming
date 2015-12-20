#pragma once
const int SIZE_BLOCK = 48;//32 default

const sf::Vector2f SIZES_BLOCK = { float(SIZE_BLOCK), float(SIZE_BLOCK) };
const int slowingStep = 4;

const int shiftForItem = 0;

typedef enum
{
	NONE_BLOCK = -1,
	unknow,
	air,
	grass,
	dirt,
	sand,
	logOak,
	stone,
	stoneBrick,
	planksBlock,
	woodLadder,
	water,
	borderBlock,
	amountKnowBlocks
} idBlocks;