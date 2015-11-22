#pragma once
#include <SFML/Graphics.hpp>

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

	void InitText(int id, sf::Color color, sf::Uint32 style, int charSize);
};

void createTextsAndFonts(TextGame &textGame);
void initializeTexts(TextGame &textGame);

void initTextAboutSelect(TextGame& textGame);
void initDeathText(TextGame &textGame);
