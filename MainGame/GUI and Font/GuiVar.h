#pragma once
#include <SFML/Graphics.hpp>
#include "../MainPerson.h"
#include "Font.h"

const int numberTextReference = 8;
const int AMOUNT_TEXT_GUI = 4;

// Информация о выделеном блоке
const int widthInfo = 280;
const int heightInfo = 135;

const int shiftXInfoText = 32;
const int shiftYInfoText = 16;

// Панель быстрого доступа
const int SHIFT_START_ITEM_PANEL = 38;
const int SHIFT_NAME_ITEM_PANEL = 10;

const int widthPanelQuickAccess = 607;
const int heightPanelQuickAccess = 66;

const int shiftXSelectInPanelQuickAccess = 0;
const int shiftYSelectInPanelQuickAccess = 66;

const int widthSelectInPanelQuickAccess = 72;
const int heightSelectInPanelQuickAccess = 72;

const int shiftSelect = 60;
const float SCALE_TEXT_BARS = 0.8f;
// Индикатор голода
const int WIDTH_HUNGY_GUI = 47;// добавление gui
const int HEIGHT_HUNGY_GUI = 33;

const int LEVEL_HUNGY_GUI = 14;
const int LEVEL_SHIFT_HUNGRY = 8;
const int MAX_SHIFT_HUNGRY_LEVEL = 11;

const int X_HUNGY_GUI = 0;
const int Y_HUNGY_GUI = 134;

// Шкала жажды
const int WIDTH_THIRST_GUI = 40;
const int HEIGHT_THIRST_GUI = 75;

const int LEVEL_SHIFT_THIRST = 48;// добавление gui
const int LEVEL_THIRST = 27;

const int X_THIRST_GUI = 0;
const int Y_THIRST_GUI = 32;

// Шкала здоровья
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

// Шкала выносливости
const int X_LEVEL_STAMINA_GUI = WIDTH_BARS_GUI + WIDTH_LEVEL_BAR_GUI * 2;
const int Y_LEVEL_STAMINA_GUI = 0;

// Шкала маны
const int X_LEVEL_MANA_GUI = WIDTH_BARS_GUI + WIDTH_LEVEL_BAR_GUI;// добавление gui
const int Y_LEVEL_MANA_GUI = 0;

const sf::Vector2f scaleGuiForEnemy = { 0.5f, 0.5f };
const sf::Vector2f scaleGuiForMainPerson = { 0.5f, 0.5f };
const sf::Vector2f normalSizeGuiForEnemy = { 1.f, 1.f };

// Отображение нанесйнного урона
const int shiftEnemyDamage = 5;

// Окошко над панелью быстрого доступа
const int WIDTH_ITEM_OVER_PANEL_INFO = 600;
const int HEIGHT_ITEM_OVER_PANEL_INFO = 60;

const int X_ITEM_OVER_PANEL_INFO = 0;
const int Y_ITEM_OVER_PANEL_INFO = heightPanelQuickAccess + heightSelectInPanelQuickAccess;
// Отображение характеристик предмета
const int AMOUNT_DAMAGE_FEATURES = 2;

const int SHIFT_FEATURES_PANEL = 10;

const int WIDTH_DAMAGE_GUI = 58;
const int HEIGHT_DAMAGE_GUI = 58;

const sf::Vector2f SCALE_FEATURES = { 0.5f, 0.5f };
const int Y_SHIFT_OUT_PANEL = 32;

const int X_CRASH_DAMAGE_GUI = 40;
const int Y_CRASH_DAMAGE_GUI = 32;

const int X_CUT_DAMAGE_GUI = X_CRASH_DAMAGE_GUI + WIDTH_DAMAGE_GUI;
const int Y_CUT_DAMAGE_GUI = Y_CRASH_DAMAGE_GUI;

const int X_HUNGRY_ITEM_GUI = X_CUT_DAMAGE_GUI + WIDTH_DAMAGE_GUI;
const int Y_HUNGRY_ITEM_GUI = Y_CRASH_DAMAGE_GUI;

const int X_THIRST_ITEM_GUI = X_HUNGRY_ITEM_GUI + WIDTH_DAMAGE_GUI;
const int Y_THIRST_ITEM_GUI = Y_CRASH_DAMAGE_GUI;
