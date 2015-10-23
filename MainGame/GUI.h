#pragma once
#include <SFML/Graphics.hpp>
#include "GlobalVar.h"
#include "MainPerson.h"
#include "Font.h"

const int numberTextReference = 8;
const int AMOUNT_TEXT_GUI = 4;

// ���������� � ��������� �����
const int widthInfo = 280;
const int heightInfo = 135;

const int shiftXInfoText = 32;
const int shiftYInfoText = 16;

// ������ �������� �������
const int widthPanelQuickAccess = 607;
const int heightPanelQuickAccess = 66;

const int shiftXSelectInPanelQuickAccess = 0;
const int shiftYSelectInPanelQuickAccess = 66;

const int widthSelectInPanelQuickAccess = 72;
const int heightSelectInPanelQuickAccess = 72;

const int shiftSelect = 60;

// ��������� ������
const int WIDTH_HUNGY_GUI = 47;// ���������� gui
const int HEIGHT_HUNGY_GUI = 33;

const int LEVEL_HUNGY_GUI = 14;
const int LEVEL_SHIFT_HUNGRY = 8;
const int MAX_SHIFT_HUNGRY_LEVEL = 11;

const int X_HUNGY_GUI = 0;
const int Y_HUNGY_GUI = 134;

// ����� �����
const int WIDTH_THIRST_GUI = 40;
const int HEIGHT_THIRST_GUI = 75;

const int LEVEL_SHIFT_THIRST = 48;// ���������� gui
const int LEVEL_THIRST = 27;

const int X_THIRST_GUI = 0;
const int Y_THIRST_GUI = 32;

// ����� ��������
const int WIDTH_BARS_GUI = 148;
const int HEIGHT_BARS_GUI = 32;

const int WIDTH_LEVEL_BAR_GUI = 134;
const int HEIGHT_LEVEL_BAR_GUI = 20;

const int X_SHIFT_BARS = 7;
const int Y_SHIFT_BARS = 8;

const int X_HEALTH_GUI = 0;
const int Y_HEALTH_GUI = 0;

const int X_LEVEL_HEALTH_GUI = WIDTH_BARS_GUI;
const int Y_LEVEL_HEALTH_GUI = 0;

// ����� ������������
const int X_LEVEL_STAMINA_GUI = WIDTH_BARS_GUI + WIDTH_LEVEL_BAR_GUI * 2;
const int Y_LEVEL_STAMINA_GUI = 0;

// ����� ����
const int X_LEVEL_MANA_GUI = WIDTH_BARS_GUI + WIDTH_LEVEL_BAR_GUI;// ���������� gui
const int Y_LEVEL_MANA_GUI = 0;

struct GUI
{// ���������� gui
	// ���������� � ��������� �����
	sf::Texture* infoSelectBlockTexture;
	sf::Sprite* infoSelectBlockSprite;

	// ������ �������� �������
	sf::Texture* widgetsTexture;
	sf::Sprite* panelQuickAccess;
	sf::Sprite* selectInPanelQuickAccess;

	// ����� ������
	sf::Texture* textureBar;
	sf::Sprite* lowHungry;
	sf::Sprite* highHungry;
	sf::Sprite* levelHungry;

	// ����� �����
	sf::Sprite* bottle;
	sf::Sprite* levelThirst;

	// ����� ��������, ������������, ����
	sf::Sprite* bar;
	sf::Sprite* levelHealth;
	sf::Sprite* levelStamina;
	sf::Sprite* levelMana;

	// ������ �� �����
	sf::Text *textGui[numberTextReference];

	void setPositionGui(sf::RenderWindow &window, MainPerson &mainPerson, TextGame &textGame);
};

void initializeGUI(GUI &gui, TextGame &textGame);
