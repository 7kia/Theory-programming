#pragma once
#include <SFML/Graphics.hpp>
#include "GlobalVar.h"
#include "MainPerson.h"
#include "Font.h"

const int numberTextReference = 8;
const int AMOUNT_TEXT_GUI = 4;

// Информация о выделеном блоке
const int widthInfo = 280;
const int heightInfo = 135;

const int shiftXInfoText = 32;
const int shiftYInfoText = 16;

// Панель быстрого доступа
const int widthPanelQuickAccess = 607;
const int heightPanelQuickAccess = 66;

const int shiftXSelectInPanelQuickAccess = 0;
const int shiftYSelectInPanelQuickAccess = 66;

const int widthSelectInPanelQuickAccess = 72;
const int heightSelectInPanelQuickAccess = 72;

const int shiftSelect = 60;

// Индикатор голода
const int WIDTH_HUNGY_GUI = 47;// добавление gui
const int HEIGHT_HUNGY_GUI = 33;

const int LEVEL_HUNGY_GUI = 14;// добавление gui
const int LEVEL_SHIFT = 8;
const int MAX_SHIFT_HUNGRY_LEVEL = 11;

const int X_HUNGY_GUI = 0;
const int Y_HUNGY_GUI = 134;

struct GUI
{// добавление gui
	// Информация о выделеном блоке
	sf::Texture* infoSelectBlockTexture;
	sf::Sprite* infoSelectBlockSprite;

	// Панель быстрого доступа
	sf::Texture* widgetsTexture;
	sf::Sprite* panelQuickAccess;
	sf::Sprite* selectInPanelQuickAccess;

	// Индикатор голода
	sf::Texture* textureBar;
	sf::Sprite* lowHungry;
	sf::Sprite* highHungry;
	sf::Sprite* levelHungry;

	// Ссылки на текст
	sf::Text *textGui[numberTextReference];

	void setPositionGui(sf::RenderWindow &window, MainPerson &mainPerson, TextGame &textGame);
};

void initializeGUI(GUI &gui, TextGame &textGame);
