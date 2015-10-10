#include "GUI.h"

using namespace sf;

void initializeGUI(GUI &gui, TextGame &textGame)
{
	gui.infoSelectBlockSprite = new Sprite;
	gui.infoSelectBlockTexture = new Texture;

	gui.textGui[idTextGui::infoWindowBlockGui] = &textGame.texts[idText::infoWindowBlock];
	gui.textGui[idTextGui::infoWindowFloorGui] = &textGame.texts[idText::infoWindowFloor];
	//gui.textGui[idTextGui::infoWindowUnlifeObjectGui] = &textGame.texts[idText::infoWindowUnlifeObject];

	gui.widthInfo = 188;
	gui.heightInfo = 100;

	// Текстура
	gui.infoSelectBlockTexture->loadFromFile(texturePaths[idTexturePaths::infoSelectBlock]);
	gui.infoSelectBlockSprite->setTexture(*gui.infoSelectBlockTexture);
	gui.infoSelectBlockSprite->setOrigin(gui.widthInfo / 2, gui.heightInfo / 2);
	gui.infoSelectBlockSprite->setTextureRect(IntRect(0, 0, gui.widthInfo, gui.heightInfo));

}

void GUI::setPositionGui(RenderWindow &window, TextGame &textGame)
{
	////////////////////////////////////////////////////////////////////////
	// Окошко с информацией об указанном мышкой объекте

	// Определение позиции окошка
	Vector2f centerWindow = window.getView().getCenter();
	Vector2u sizeWindow = window.getSize();
	Vector2f pos = { centerWindow.x + sizeWindow.x / 2 - widthInfo , centerWindow.y + sizeWindow.y / 2 - heightInfo};

	// Определение
	infoSelectBlockSprite->setPosition(pos);

	// Сдвиг текста
	const int shiftX = 8 - widthInfo / 2;
	const int shiftY = 8 - heightInfo / 2;

	// Размещение текста
	pos = { pos.x + shiftX, pos.y + shiftY };
	//textGui[idTextGui::infoWindowBlockGui]->setPosition(pos);
	textGame.texts[idText::infoWindowBlock].setPosition(pos);

	//pos.y += textGui[idTextGui::infoWindowFloorGui]->getCharacterSize();
	pos.y += textGame.texts[idText::infoWindowFloor].getCharacterSize();
	textGame.texts[idText::infoWindowFloor].setPosition(pos);
	//textGui[idTextGui::infoWindowFloorGui]->setPosition(pos);

	pos.y += textGame.texts[idText::infoWindowUnlifeObject].getCharacterSize();
	textGame.texts[idText::infoWindowUnlifeObject].setPosition(pos);
	////////////////////////////////////////////////////////////////////////
}