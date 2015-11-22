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

	textGame.InitText(idText::inputDamage, Color::White, Text::Regular | Text::Underlined, SIZE_NORMAL_TEXT);
	textGame.InitText(idText::levelBar, Color::White, Text::Regular | Text::Underlined, SIZE_NORMAL_TEXT);

	textGame.InitText(idText::itemGui, Color::White, Text::Regular | Text::Underlined, SIZE_NORMAL_TEXT);

	/*
	// Определение количества символов
	int sizeString = 0;
	for (int i = 0; i < SIZE_STRING; i++) {
		if (stringDeathPerson[i] != '\0') {
			sizeString += 1;
		} else {
			break;
		}
	}

	int widthText = currentText->getCharacterSize() * sizeString;
	Vector2f origin = { (float)widthText / 4 , 0.f };
	currentText->setOrigin(origin);
	*/
	
}

void initDeathText(TextGame& textGame)
{
	textGame.InitText(idText::mainPersonIsDeath, Color::White, Text::Regular | Text::Underlined, SIZE_BIG_TEXT);

	Text *currentText = &textGame.texts[idText::mainPersonIsDeath];
	int sizeString = stringDeathPerson.getSize();

	/*
	for (int i = 0; i < SIZE_STRING; i++) {
	if (stringDeathPerson[i] != '\0') {
	sizeString += 1;
	} else {
	break;
	}
	}
	*/

	defineOriginInMiddleString(*currentText);

	currentText->setString(stringDeathPerson);
}

void initTextAboutSelect(TextGame& textGame)
{
	textGame.InitText(idText::infoWindowBlock, Color::White, Text::Regular | Text::Underlined, SIZE_NORMAL_TEXT);
	textGame.InitText(idText::infoWindowFloor, Color::White, Text::Regular | Text::Underlined, SIZE_NORMAL_TEXT);
	textGame.InitText(idText::infoWindowUnlifeObject, Color::White, Text::Regular | Text::Underlined, SIZE_NORMAL_TEXT);
	textGame.InitText(idText::infoWindowItem, Color::White, Text::Regular | Text::Underlined, SIZE_NORMAL_TEXT);
	textGame.InitText(idText::infoEntity, Color::White, Text::Regular | Text::Underlined, SIZE_NORMAL_TEXT);

}