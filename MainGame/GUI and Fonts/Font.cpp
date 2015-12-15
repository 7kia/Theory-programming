#include "Font.h"
#include "../GlobalVar.h"

using namespace sf;

void TextGame::InitText(int id, sf::Color color, sf::Uint32 style, int charSize)
{
	Text* currentText = &texts[id];
	currentText->setColor(color);
	currentText->setStyle(style);
	currentText->setFont(*font);
	currentText->setCharacterSize(charSize);
}

void createTextsAndFonts(TextGame& textGame)
{
	textGame.font = new Font;
	textGame.texts = new Text[idText::amountTexts];
}

void initializeTexts(TextGame &textGame)
{
	textGame.font->loadFromFile("recourses\\font\\CyrilicOld.ttf");

	initTextAboutSelect(textGame);
	initDeathText(textGame);
	initPanelText(textGame);

	textGame.InitText(idText::inputDamage, Color::White, Text::Regular | Text::Underlined, SIZE_NORMAL_TEXT);
	textGame.InitText(idText::levelBar, Color::White, Text::Regular | Text::Underlined, SIZE_NORMAL_TEXT);
	textGame.InitText(idText::itemGui, Color::White, Text::Regular | Text::Underlined, SIZE_NORMAL_TEXT);
}

void initDeathText(TextGame& textGame)
{
	textGame.InitText(idText::mainPersonIsDeath, Color::White, Text::Regular | Text::Underlined, SIZE_BIG_TEXT);

	Text *currentText = &textGame.texts[idText::mainPersonIsDeath];
	size_t sizeString = stringDeathPerson.getSize();

	defineOriginInMiddleString(*currentText);

	currentText->setString(stringDeathPerson);
}

void initTextAboutSelect(TextGame& textGame)
{
	textGame.InitText(idText::infoWindowBlock, Color::White, Text::Regular, SIZE_NORMAL_TEXT);
	textGame.InitText(idText::infoWindowFloor, Color::White, Text::Regular, SIZE_NORMAL_TEXT);
	textGame.InitText(idText::infoWindowUnlifeObject, Color::White, Text::Regular, SIZE_NORMAL_TEXT);
	textGame.InitText(idText::infoWindowItem, Color::White, Text::Regular, SIZE_NORMAL_TEXT);
	textGame.InitText(idText::infoEntity, Color::White, Text::Regular, SIZE_NORMAL_TEXT);

}

void initPanelText(TextGame &textGame)
{
	textGame.InitText(idText::panelText, Color::White, Text::Regular, SIZE_NORMAL_TEXT);
	textGame.InitText(idText::panelWaveText, Color::White, Text::Regular, SIZE_NORMAL_TEXT);
	textGame.InitText(idText::panelHelpText, Color::White, Text::Regular | Text::Underlined, SIZE_BIG_TEXT);
	textGame.InitText(idText::panelTitleText, Color::White, Text::Bold, SIZE_BIG_TEXT);
}
