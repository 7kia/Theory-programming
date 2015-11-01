#pragma once
const int SIZE_BLOCK = 48;//32 default

const int slowingStep = 4;

const int shiftForItem = 0;

typedef enum
{
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
	amountKnowBlocks
} idBlocks;