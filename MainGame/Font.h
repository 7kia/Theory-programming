#pragma once
#include <SFML/Graphics.hpp>
#include "GlobalVar.h"

const int SIZE_NORMAL_TEXT = 14;
const int SIZE_SMALL_TEXT = 10;


typedef enum {
	infoWindowBlockGui,
	infoWindowFloorGui,
	infoWindowUnlifeObjectGui,
	amountTextsGui
} idTextGui;


typedef enum {
	infoWindowBlock,
	infoWindowFloor,
	infoWindowUnlifeObject,
	amountTexts
} idText;

struct TextGame {
	sf::Font *font;
	sf::Text *texts;
};

void initializeTexts(TextGame &textGame);
