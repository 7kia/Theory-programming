#include "Font.h"

using namespace sf;

void initializeTexts(TextGame &textGame)
{
	textGame.font = new Font;
	textGame.texts = new Text[NUMBER_TEXT_STRING];

	textGame.font->loadFromFile("recourses\\font\\CyrilicOld.ttf");

	////////////////////////////////////////////////////////////////////
	// Информация о выделенном объекте
	Text* currentText = &textGame.texts[idText::infoWindowBlock];
	currentText->setColor(Color::White);
	currentText->setStyle(Text::Regular | Text::Underlined);
	currentText->setFont(*textGame.font);
	currentText->setCharacterSize(SIZE_NORMAL_TEXT);

	currentText = &textGame.texts[idText::infoWindowFloor];
	currentText->setColor(Color::White);
	currentText->setStyle(Text::Regular | Text::Underlined);
	currentText->setFont(*textGame.font);
	currentText->setCharacterSize(SIZE_NORMAL_TEXT);

	currentText = &textGame.texts[idText::infoWindowUnlifeObject];
	currentText->setColor(Color::White);
	currentText->setStyle(Text::Regular | Text::Underlined);
	currentText->setFont(*textGame.font);
	currentText->setCharacterSize(SIZE_NORMAL_TEXT);

	currentText = &textGame.texts[idText::infoWindowItem];
	currentText->setColor(Color::White);
	currentText->setStyle(Text::Regular | Text::Underlined);
	currentText->setFont(*textGame.font);
	currentText->setCharacterSize(SIZE_NORMAL_TEXT);

	currentText = &textGame.texts[idText::infoEntity];
	currentText->setColor(Color::White);
	currentText->setStyle(Text::Regular | Text::Underlined);
	currentText->setFont(*textGame.font);
	currentText->setCharacterSize(SIZE_NORMAL_TEXT);
	////////////////////////////////////////////////////////////////////


	currentText = &textGame.texts[idText::mainPersonIsDeath];
	currentText->setColor(Color::Black);
	currentText->setStyle(Text::Regular | Text::Underlined);
	currentText->setFont(*textGame.font);
	currentText->setCharacterSize(SIZE_BIG_TEXT);
	currentText->setString(stringDeathPerson);

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

}
