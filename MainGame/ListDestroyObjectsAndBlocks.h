#pragma once
#include <SFML/Audio.hpp>

#include <iostream>
#include <string>

struct destroyObjectsAndBlocks
{
	sf::String axeBreakingObject[AMOUNT_AXE_BREAKING_OBJECTS];
	sf::String pickaxBreakingObject[AMOUNT_PICKAX_BREAKING_OBJECTS];

	unsigned int axeBreakingBlock[AMOUNT_AXE_BREAKING_BLOCKS];
	unsigned int pickaxBreakingBlock[AMOUNT_PICKAX_BREAKING_BLOCKS];
};