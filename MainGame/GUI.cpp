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

	// добавление gui
	// Индикатор голода
	gui.textureBar = new Texture;
	gui.lowHungry = new Sprite;
	gui.highHungry = new Sprite;
	gui.levelHungry = new Sprite;


	gui.textureBar->loadFromFile(texturePaths[idTexturePaths::bars]);

	gui.lowHungry->setTexture(*gui.textureBar);
	gui.lowHungry->setTextureRect(IntRect(X_HUNGY_GUI, Y_HUNGY_GUI, WIDTH_HUNGY_GUI, HEIGHT_HUNGY_GUI));

	gui.highHungry->setTexture(*gui.textureBar);
	gui.highHungry->setTextureRect(IntRect(X_HUNGY_GUI, Y_HUNGY_GUI + HEIGHT_HUNGY_GUI, WIDTH_HUNGY_GUI, HEIGHT_HUNGY_GUI));

	gui.levelHungry->setTexture(*gui.textureBar);
	gui.levelHungry->setTextureRect(IntRect(X_HUNGY_GUI, Y_HUNGY_GUI + HEIGHT_HUNGY_GUI * 2, WIDTH_HUNGY_GUI, LEVEL_HUNGY_GUI));

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

	// Размещение текста
	pos = { pos.x + shiftXInfoText , pos.y + shiftYInfoText };
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
	pos = { centerWindow.x , centerWindow.y + sizeWindow.y / 2 - heightPanelQuickAccess / 2};// ИСПРАВЬ
	panelQuickAccess->setPosition(pos);

	// Выбранный предмет
	int &idSelectItem = mainPerson.idSelectItem;
	int startPosition = widthPanelQuickAccess / 2;
	int shift = shiftSelect * idSelectItem;
	pos = { centerWindow.x - startPosition + shift, centerWindow.y + sizeWindow.y / 2 - heightPanelQuickAccess / 2};// ИСПРАВЬ

	selectInPanelQuickAccess->setPosition(pos);


	for (int i = 0; i < AMOUNT_ACTIVE_SLOTS; i++) {
		if (mainPerson.itemFromPanelQuickAccess[i].typeItem->name != "Empty") {
			int shift = shiftSelect * (i);
			int shiftStart = 38;// ИСПРАВЬ
			pos = { centerWindow.x - startPosition + shift + shiftStart, centerWindow.y + sizeWindow.y / 2 - heightPanelQuickAccess / 2};// ИСПРАВЬ
			mainPerson.itemFromPanelQuickAccess[i].mainSprite->setPosition(pos);
		}
	}
	// добавление gui
	//////////////////////////////////////////////////////////////////////// 
	// Индикатор голода
	pos = { centerWindow.x - sizeWindow.x / 2, centerWindow.y + sizeWindow.y / 2 - (float)HEIGHT_HUNGY_GUI };

	lowHungry->setPosition(pos);
	highHungry->setPosition(pos);

	float level = (float)mainPerson.currentHungry / mainPerson.maxHungry;
	printf("%d %d\n", mainPerson.currentHungry, mainPerson.maxHungry);

	//int currentShift = HEIGHT_HUNGY_GUI * (1 - level);
	//int currentHeight = LEVEL_HUNGY_GUI * level;
	pos.y += LEVEL_SHIFT + MAX_SHIFT_HUNGRY_LEVEL * (1 - level);
	int currentLevel = LEVEL_HUNGY_GUI * level;
	levelHungry->setTextureRect(IntRect(X_HUNGY_GUI, Y_HUNGY_GUI + HEIGHT_HUNGY_GUI * 2, WIDTH_HUNGY_GUI, currentLevel));
	levelHungry->setPosition(pos);
	////////////////////////////////////////////////////////////////////////
	textGame.texts[idText::mainPersonIsDeath].setPosition(centerWindow);

}