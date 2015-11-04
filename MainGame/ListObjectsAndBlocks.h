#pragma once
const int AMOUNT_AXE_BREAKING_BLOCKS = 2;
const int AMOUNT_AXE_BREAKING_OBJECTS = 5;

const int AMOUNT_PICKAX_BREAKING_BLOCKS = 5;
const int AMOUNT_PICKAX_BREAKING_OBJECTS = 5;

const int AMOUNT_BACKHOE_BREAKING_BLOCKS = 5;
const int AMOUNT_BACKHOE_BREAKING_OBJECTS = 5;

struct destroyObjectsAndBlocks//Game.cpp
{
	sf::String axeBreakingObject[AMOUNT_AXE_BREAKING_OBJECTS];
	sf::String pickaxBreakingObject[AMOUNT_PICKAX_BREAKING_OBJECTS];
	sf::String backoeBreakingObject[AMOUNT_BACKHOE_BREAKING_BLOCKS];

	wchar_t axeBreakingBlock[SIZE_STRING];
	wchar_t pickaxBreakingBlock[SIZE_STRING];
	wchar_t backoeBreakingBlock[SIZE_STRING];

	wchar_t passableBlocks[SIZE_STRING];
	wchar_t notPassableFloor[SIZE_STRING];
	wchar_t slowingBlocks[SIZE_STRING];

	wchar_t ladder[SIZE_STRING];
};