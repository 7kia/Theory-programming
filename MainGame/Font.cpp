#include "Font.h"

using namespace sf;

void initializeTexts(TextGame &textGame)
{
	textGame.font = new Font;
	textGame.texts = new Text[NUMBER_TEXT_STRING];

	textGame.font->loadFromFile("recourses\\font\\CyrilicOld.ttf");

	Text* currentText = &textGame.texts[idText::infoWindowBlock];
	currentText->setColor(Color::Black);
	currentText->setStyle(Text::Regular | Text::Underlined);
	currentText->setFont(*textGame.font);
	currentText->setCharacterSize(SIZE_NORMAL_TEXT);

	currentText = &textGame.texts[idText::infoWindowFloor];
	currentText->setColor(Color::Black);
	currentText->setStyle(Text::Regular | Text::Underlined);
	currentText->setFont(*textGame.font);
	currentText->setCharacterSize(SIZE_NORMAL_TEXT);

	currentText = &textGame.texts[idText::infoWindowUnlifeObject];
	currentText->setColor(Color::Black);
	currentText->setStyle(Text::Regular | Text::Underlined);
	currentText->setFont(*textGame.font);
	currentText->setCharacterSize(SIZE_NORMAL_TEXT);

	currentText = &textGame.texts[idText::infoWindowItem];
	currentText->setColor(Color::Black);
	currentText->setStyle(Text::Regular | Text::Underlined);
	currentText->setFont(*textGame.font);
	currentText->setCharacterSize(SIZE_NORMAL_TEXT);
}
