#include "GUI.h"

using namespace sf;

void initializeGUI(GUI &gui, TextGame &textGame)
{
	// Информация о выделеном блоке
	gui.infoSelectBlockTexture = new Texture;
	gui.infoSelectBlockSprite = new Sprite;

	gui.infoSelectBlockTexture->loadFromFile(texturePaths[idTexturePaths::infoSelectBlock]);
	gui.infoSelectBlockSprite->setTexture(*gui.infoSelectBlockTexture);
	gui.infoSelectBlockSprite->setOrigin(widthInfo / 2, heightInfo / 2);
	gui.infoSelectBlockSprite->setTextureRect(IntRect(0, 0, widthInfo, heightInfo));

	// Панель быстрого доступа
	gui.widgetsTexture = new Texture;
	gui.panelQuickAccess = new Sprite;
	gui.selectInPanelQuickAccess = new Sprite;

	gui.widgetsTexture->loadFromFile(texturePaths[idTexturePaths::widgets]);
	gui.panelQuickAccess->setTexture(*gui.widgetsTexture);
	gui.panelQuickAccess->setOrigin(widthPanelQuickAccess / 2, heightPanelQuickAccess / 2);// ИСПРАВЬ
	gui.panelQuickAccess->setTextureRect(IntRect(0, 0, widthPanelQuickAccess, heightPanelQuickAccess));

	gui.selectInPanelQuickAccess->setTexture(*gui.widgetsTexture);
	gui.selectInPanelQuickAccess->setOrigin(0, heightSelectInPanelQuickAccess / 2);// ИСПРАВЬ
	gui.selectInPanelQuickAccess->setTextureRect(IntRect(shiftXSelectInPanelQuickAccess, shiftYSelectInPanelQuickAccess, widthSelectInPanelQuickAccess, heightSelectInPanelQuickAccess));

	// ИСПРАВЬ
	// НЕРАБОТАЕТ
	//gui.textGui[idTextGui::infoWindowBlockGui] = &textGame.texts[idText::infoWindowBlock];
	//gui.textGui[idTextGui::infoWindowFloorGui] = &textGame.texts[idText::infoWindowFloor];
	//gui.textGui[idTextGui::infoWindowUnlifeObjectGui] = &textGame.texts[idText::infoWindowUnlifeObject];
	//gui.textGui[idTextGui::infoWindowItemGui] = &textGame.texts[idText::infoWindowItemGui];
}

void GUI::setPositionGui(RenderWindow &window, MainPerson &mainPerson, TextGame &textGame)
{

	Vector2f centerWindow = window.getView().getCenter();
	////////////////////////////////////////////////////////////////////////
	// Окошко с информацией об указанном мышкой объекте

	// Определение позиции окошка
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

	pos.y += textGame.texts[idText::infoWindowItem].getCharacterSize();
	textGame.texts[idText::infoWindowItem].setPosition(pos);
	////////////////////////////////////////////////////////////////////////
	// Панель быстрого доступа
	pos = { centerWindow.x, centerWindow.y + sizeWindow.y / 2 - heightPanelQuickAccess * 2 };// ИСПРАВЬ
	panelQuickAccess->setPosition(pos);

	// Выбранный предмет
	int amountSlots = mainPerson.amountActiveSlots;
	int &idSelectItem = mainPerson.idSelectItem;
	int startPosition = widthPanelQuickAccess / 2;
	int shift = shiftSelect * (idSelectItem - 1);
	pos = { centerWindow.x - startPosition + shift, centerWindow.y + sizeWindow.y / 2 - heightPanelQuickAccess * 2 };// ИСПРАВЬ
	selectInPanelQuickAccess->setPosition(pos);
	////////////////////////////////////////////////////////////////////////

}