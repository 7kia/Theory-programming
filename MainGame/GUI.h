#pragma once
#include <SFML/Graphics.hpp>
#include "GlobalVar.h"
#include "MainPerson.h"
#include "Font.h"

const int numberTextReference = 8;
const int AMOUNT_TEXT_GUI = 4;

// Информация о выделеном блоке
const int widthInfo = 188;
const int heightInfo = 100;

// Панель быстрого доступа
const int widthPanelQuickAccess = 607;
const int heightPanelQuickAccess = 66;

const int shiftXSelectInPanelQuickAccess = 0;
const int shiftYSelectInPanelQuickAccess = 66;

const int widthSelectInPanelQuickAccess = 72;
const int heightSelectInPanelQuickAccess = 72;

const int shiftSelect = 60;



struct GUI
{
	// Информация о выделеном блоке
	sf::Texture* infoSelectBlockTexture;
	sf::Sprite* infoSelectBlockSprite;

	// Панель быстрого доступа
	sf::Texture* widgetsTexture;
	sf::Sprite* panelQuickAccess;
	sf::Sprite* selectInPanelQuickAccess;


	// Ссылки на текст
	sf::Text *textGui[numberTextReference];

	void setPositionGui(sf::RenderWindow &window, MainPerson &mainPerson, TextGame &textGame);
};

void initializeGUI(GUI &gui, TextGame &textGame);
