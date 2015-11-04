#pragma once
#include <SFML/Audio.hpp>

#include <iostream>
#include <string>

struct destroyObjectsAndBlocks
{
	sf::String axeBreakingObject[AMOUNT_AXE_BREAKING_OBJECTS];
	sf::String pickaxBreakingObject[AMOUNT_PICKAX_BREAKING_OBJECTS];

	wchar_t axeBreakingBlock[SIZE_STRING];
	wchar_t pickaxBreakingBlock[SIZE_STRING];
};