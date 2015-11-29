#pragma once
#include "GlobalVar.h"
const int AMOUNT_AXE_BREAKING_BLOCKS = 2;
const int AMOUNT_AXE_BREAKING_OBJECTS = 5;

const int AMOUNT_PICKAX_BREAKING_BLOCKS = 5;
const int AMOUNT_PICKAX_BREAKING_OBJECTS = 5;

const int AMOUNT_BACKHOE_BREAKING_BLOCKS = 5;
const int AMOUNT_BACKHOE_BREAKING_OBJECTS = 5;

const int AMOUNT_HARVEST_OBJECTS = 1;

struct listDestroyObjectsAndBlocks//Game.cpp
{
	std::vector<sf::String> axeBreakingObject;
	std::vector<sf::String>  pickaxBreakingObject;
	std::vector<sf::String>  backoeBreakingObject;
	std::vector<sf::String>  harvestObjects;

	std::vector<int>  listWoodObject;
	std::vector<int>  listWoodBlock;
	std::vector<int>  listStoneObject;
	std::vector<int>  listtStoneBlock;


	std::vector<wchar_t>  axeBreakingBlock;
	std::vector<wchar_t> pickaxBreakingBlock;
	std::vector<wchar_t> backoeBreakingBlock;

	std::vector<wchar_t> passableBlocks;
	std::vector<wchar_t> notPassableFloor;
	std::vector<wchar_t> slowingBlocks;

	std::vector<wchar_t> ladder;
};