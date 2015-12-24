#pragma once
#include <SFML/Graphics.hpp>

const int SIZE_BIG_TEXT = 32;
const int SIZE_NORMAL_TEXT = 18;
const int SIZE_SMALL_TEXT = 14;

const sf::String TEXT_AWARD = "Award";
const sf::String TEXT_HELP_AWARD = "Items will drop in center map.";
const sf::String TEXT_NUMBER_WAVE_START = "You survived ";
const sf::String TEXT_NUMBER_WAVE_END = " wave(s)";
const sf::String TEXT_VICTORY = "Victory";
const sf::String TEXT_UNDER_VICTORY = "You end game.";

// TODO
// Для окошка с подсказками по управлению
const sf::String TEXT_MANAGEMENT = "Management";

const int SHIFT_Y_AWARD_TITLE_TEXT = 20;
const int SHIFT_Y_AWARD_HELP_TEXT = 40;


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

	panelText,
	panelHelpText,
	panelWaveText,
	panelTitleText,
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
void initPanelText(TextGame &textGame);
void initOtherText(TextGame &textGame);
