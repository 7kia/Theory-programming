#pragma once
#include <SFML/Graphics.hpp>
#include "GlobalVar.h"

const int SIZE_BIG_TEXT = 32;
const int SIZE_NORMAL_TEXT = 18;
const int SIZE_SMALL_TEXT = 14;

typedef enum {
	infoWindowBlock,
	infoWindowFloor,
	infoWindowUnlifeObject,
	infoWindowItem,
	infoEntity,
	inputDamage,
	levelBar,
	itemGui,
	mainPersonIsDeath,
	amountTexts
} idText;

struct TextGame {
	sf::Font *font;
	sf::Text *texts;
};

void initializeTexts(TextGame &textGame);
