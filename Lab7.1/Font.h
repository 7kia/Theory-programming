#pragma once
#include <SFML/Graphics.hpp>

const int NUMBER_TEXT_STRING = 2;

const int SIZE_NORMAL_TEXT = 16;
const int SIZE_SMALL_TEXT = 12;

typedef enum {
	numberClock,
	amountTextsGui
} idText;

const int AMOUNT_NUMBERS = 12;
struct TextProgram {
	sf::Font font;
	sf::Text texts[AMOUNT_NUMBERS];
};

void initializeTexts(TextProgram &textProgram);
