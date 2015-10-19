#include "Font.h"

using namespace sf;

void initializeTexts(TextProgram &textProgram)
{
	textProgram.font = new Font;
	textProgram.texts = new Text[4];//idText::amountTextsGui

	textProgram.font->loadFromFile("recourses\\font\\CyrilicOld.ttf");// MAINGAME

	Text& pathImage = textProgram.texts[idText::pathImage];
	pathImage.setColor(Color::Black);
	pathImage.setStyle(Text::Regular | Text::Underlined);
	pathImage.setFont(*textProgram.font);
	pathImage.setCharacterSize(SIZE_NORMAL_TEXT);

	Text& currentImageGui = textProgram.texts[idText::currentImageGui];
	currentImageGui = textProgram.texts[idText::currentImageGui];
	currentImageGui.setColor(Color::Black);
	currentImageGui.setStyle(Text::Regular | Text::Underlined);
	currentImageGui.setFont(*textProgram.font);
	currentImageGui.setCharacterSize(SIZE_NORMAL_TEXT);

	//int widthString = currentText.getCharacterSize() * sizeof(currentText.getString()) / sizeof(char) / 2;
	//currentText.setOrigin(widthString, 0);


}
