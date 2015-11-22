#include "Font.h"

using namespace sf;

void initializeTexts(TextProgram &textProgram)
{
	textProgram.font.loadFromFile("recourses\\font\\CyrilicOld.ttf");// MAINGAME

	Text& pathImage = textProgram.texts[idText::numberClock];
	pathImage.setColor(Color::White);
	pathImage.setStyle(Text::Regular | Text::Underlined);
	pathImage.setFont(textProgram.font);
	pathImage.setCharacterSize(SIZE_NORMAL_TEXT);

	//int widthString = currentText.getCharacterSize() * sizeof(currentText.getString()) / sizeof(char) / 2;
	//currentText.setOrigin(widthString, 0);

}
