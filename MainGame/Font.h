#pragma once
#include <SFML/Graphics.hpp>
#include "GlobalVar.h"

const int SIZE_NORMAL_TEXT = 14;
const int SIZE_SMALL_TEXT = 10;


typedef enum {
	infoWindowBlockGui,
	infoWindowFloorGui,
	infoWindowUnlifeObjectGui,
	infoWindowItemGui,
	amountTextsGui
} idTextGui;


typedef enum {
	infoWindowBlock,
	infoWindowFloor,
	infoWindowUnlifeObject,
	infoWindowItem,
	amountTexts
} idText;

struct TextGame {
	sf::Font *font;
	sf::Text *texts;
};

void initializeTexts(TextGame &textGame);
