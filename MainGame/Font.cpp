#include "Font.h"

using namespace sf;

void initializeTexts(TextGame &textGame)
{
	textGame.font = new Font;
	textGame.texts = new Text[NUMBER_TEXT_STRING];

	textGame.font->loadFromFile("recourses\\font\\CyrilicOld.ttf");

	textGame.texts[idText::infoWindowBlock].setColor(Color::Black);
	textGame.texts[idText::infoWindowBlock].setStyle(Text::Regular | Text::Underlined);
	textGame.texts[idText::infoWindowBlock].setFont(*textGame.font);
	textGame.texts[idText::infoWindowBlock].setCharacterSize(SIZE_NORMAL_TEXT);


	textGame.texts[idText::infoWindowFloor].setColor(Color::Black);
	textGame.texts[idText::infoWindowFloor].setStyle(Text::Regular | Text::Underlined);
	textGame.texts[idText::infoWindowFloor].setFont(*textGame.font);
	textGame.texts[idText::infoWindowFloor].setCharacterSize(SIZE_NORMAL_TEXT);

	textGame.texts[idText::infoWindowUnlifeObject].setColor(Color::Black);
	textGame.texts[idText::infoWindowUnlifeObject].setStyle(Text::Regular | Text::Underlined);
	textGame.texts[idText::infoWindowUnlifeObject].setFont(*textGame.font);
	textGame.texts[idText::infoWindowUnlifeObject].setCharacterSize(SIZE_NORMAL_TEXT);

	textGame.texts[idText::infoWindowItem].setColor(Color::Black);
	textGame.texts[idText::infoWindowItem].setStyle(Text::Regular | Text::Underlined);
	textGame.texts[idText::infoWindowItem].setFont(*textGame.font);
	textGame.texts[idText::infoWindowItem].setCharacterSize(SIZE_NORMAL_TEXT);
}
