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
	std::vector<int> *harvestObjects;
	std::vector<int> *none;

	std::vector<wchar_t> *passableBlocks;
	std::vector<wchar_t> *notPassableFloor;
	std::vector<wchar_t> *slowingBlocks;

	std::vector<wchar_t> *ladder;

	std::vector<int> *stoneKnife;
	std::vector<int> *axe;
	std::vector<int> *backhoe;
	std::vector<int> *pickax;


};