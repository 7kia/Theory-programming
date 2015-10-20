#include "GUI.h"

using namespace sf;

void initializeGUI(GUI &gui, TextGame &textGame)
{
	// Информация о выделеном блоке
	gui.infoSelectBlockTexture = new Texture;
	gui.infoSelectBlockSprite = new Sprite;

	gui.infoSelectBlockTexture->loadFromFile(texturePaths[idTexturePaths::infoSelectBlock]);
	gui.infoSelectBlockSprite->setTexture(*gui.infoSelectBlockTexture);
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

	Vector2f centerWindow = mainPerson.view->getCenter();
	////////////////////////////////////////////////////////////////////////
	// Окошко с информацией об указанном мышкой объекте

	// Определение позиции окошка
	Vector2u sizeWindow = window.getSize();
	Vector2f pos = { centerWindow.x + sizeWindow.x / 2 - widthInfo , centerWindow.y + sizeWindow.y / 2 - heightInfo};

	// Определение
	infoSelectBlockSprite->setPosition(pos);

	// Сдвиг текста
	const int shiftX = 8 ;
	const int shiftY = 8 ;

	// Размещение текста
	pos = { pos.x + shiftX, pos.y + shiftY };
	textGame.texts[idText::infoWindowBlock].setPosition(pos);

	// Смещаем строку на размер букв предыдущей строки вниз
	pos.y += textGame.texts[idText::infoWindowBlock].getCharacterSize();
	textGame.texts[idText::infoWindowFloor].setPosition(pos);

	pos.y += textGame.texts[idText::infoWindowFloor].getCharacterSize();
	textGame.texts[idText::infoWindowUnlifeObject].setPosition(pos);

	pos.y += textGame.texts[idText::infoWindowUnlifeObject].getCharacterSize();
	textGame.texts[idText::infoWindowItem].setPosition(pos);
	////////////////////////////////////////////////////////////////////////
	// Панель быстрого доступа
	pos = { centerWindow.x , centerWindow.y + sizeWindow.y / 2 - heightPanelQuickAccess};// ИСПРАВЬ
	panelQuickAccess->setPosition(pos);

	// Выбранный предмет
	int &idSelectItem = mainPerson.idSelectItem;
	int startPosition = widthPanelQuickAccess / 2;
	int shift = shiftSelect * idSelectItem;
	pos = { centerWindow.x - startPosition + shift, centerWindow.y + sizeWindow.y / 2 - heightPanelQuickAccess};// ИСПРАВЬ

	selectInPanelQuickAccess->setPosition(pos);


	for (int i = 0; i < AMOUNT_ACTIVE_SLOTS; i++) {
		if (mainPerson.itemFromPanelQuickAccess[i].typeItem->name != "Empty") {
			int shift = shiftSelect * (i);
			int shiftStart = 38;// ИСПРАВЬ
			pos = { centerWindow.x - startPosition + shift + shiftStart, centerWindow.y + sizeWindow.y / 2 - heightPanelQuickAccess};// ИСПРАВЬ
			mainPerson.itemFromPanelQuickAccess[i].mainSprite->setPosition(pos);
		}
	}
	////////////////////////////////////////////////////////////////////////

}