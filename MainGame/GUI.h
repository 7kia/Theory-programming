#pragma once
#include <SFML/Graphics.hpp>
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
const int SHIFT_START_ITEM_PANEL = 38;
const int SHIFT_NAME_ITEM_PANEL = 10;

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

const Vector2f scaleGuiForEnemy = { 0.4f, 0.4f };
const Vector2f normalSizeGuiForEnemy = { 1.f, 1.f };

// ����������� ����������� �����
const int shiftEnemyDamage = 5;

// ������ ��� ������� �������� �������
const int WIDTH_ITEM_OVER_PANEL_INFO = 600;
const int HEIGHT_ITEM_OVER_PANEL_INFO = 60;

const int X_ITEM_OVER_PANEL_INFO = 0;
const int Y_ITEM_OVER_PANEL_INFO = heightPanelQuickAccess + heightSelectInPanelQuickAccess;
// ����������� ������������� ��������
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

struct barHungry
{
	sf::Sprite* lowHungry;
	sf::Sprite* highHungry;
	sf::Sprite* levelHungry;
	void renderBar(int& current, int& max, sf::Vector2f centerWindow, sf::Vector2u sizeWindow,
								 sf::RenderWindow& window);
	void renderHigh(sf::Vector2f &pos, sf::Vector2u sizeWindow, sf::RenderWindow &window);
	void renderLevel(int& current, int& max, sf::Vector2f& pos, sf::RenderWindow& window);
	void renderLow(sf::Vector2f& pos, sf::Vector2f centerWindow,
								 sf::Vector2u sizeWindow, sf::RenderWindow& window);
};

struct barThirst
{
	sf::Sprite* bottle;
	sf::Sprite* levelThirst;
	void renderBar(int& current, int& max, sf::Vector2f centerWindow, sf::Vector2u sizeWindow,
								 sf::RenderWindow& window);
};

struct barMainFeatures
{
	sf::Sprite* bar;
	sf::Sprite* levelHealth;
	sf::Sprite* levelStamina;
	sf::Sprite* levelMana;
	void renderBar(int &current, int& max, sf::Sprite &sprite, sizeMainSprite &sizes,
								 TextGame &textGame, sf::Vector2f &position, sf::RenderWindow &window);
	void render(int &current, int& max, sf::Sprite &sprite,
							sizeMainSprite &sizes, sf::Vector2f &position, sf::RenderWindow &window);
	void renderText(int &current, int& max,
									sf::Vector2f &position, sf::RenderWindow &window, TextGame &textGame);

	void renderTextEnemy(Enemy & enemy, int & current, int & max, int shift,
											 sf::RenderWindow & window, TextGame & textGame);


	void renderDamageForEnemy(Enemy & enemy, TextGame & textGame, sf::RenderWindow & window, int shift);

	void renderBarMainPerson(int & current, int & max, int shift, sf::Sprite &sprite, sizeMainSprite & sizes,
													 sf::Vector2f centerWindow, sf::Vector2u sizeWindow,
													 TextGame & textGame, sf::RenderWindow & window);
	void renderBarEnemy(Enemy & enemy, int & current, int & max, int shift, Sprite &sprite,
											sizeMainSprite & sizes, TextGame & textGame, RenderWindow & window);
};

struct infoAboutSelect
{
	sf::Texture* Texture;
	sf::Sprite* sprite;
	void render(sf::Vector2f position, sf::RenderWindow &window, TextGame &textGame);
};

struct itemFeatures
{
	sf::Sprite* cutSprite;
	sf::Sprite* crashSprite;
	sf::Sprite* hungrySprite;
	sf::Sprite* thirstSprite;
	void renderValueMiddle(std::string string, Text* text, sf::Vector2f &position, sf::RenderWindow &window);
	void renderIconWithScale(Sprite *sprite, sf::Vector2f position, sf::RenderWindow &window);
	void renderBar(Sprite *sprite, sf::Vector2f position, sf::RenderWindow &window);
	void renderNameItem(::MainPerson& mainPerson, Vector2f &position, Vector2f centerWindow,
											Vector2u sizeWindow, sf::RenderWindow &window, TextGame &textGame);
	void renderFeatures(::MainPerson& mainPerson, sf::Vector2f centerWindow,
											sf::Vector2u sizeWindow, ::sf::RenderWindow& window,
											TextGame &textGame, barMainFeatures &bars);

};

struct panelQuickAccess
{
	sf::Sprite* spritePanel;
	sf::Sprite* spriteSelect;
	void renderPanel(Vector2f position, RenderWindow& window);
	void renderSelect(::MainPerson& mainPerson, sf::Vector2f centerWindow,
										sf::Vector2u sizeWindow, ::sf::RenderWindow& window);
	void renderItems(::MainPerson& mainPerson, sf::Vector2f centerWindow,
									 sf::Vector2u sizeWindow, ::sf::RenderWindow& window,
									 TextGame &textGame, barMainFeatures &bars, itemFeatures &itemFeatures);
};

struct panels
{
	infoAboutSelect infoAboutSelect;
	panelQuickAccess panelQuickAccess;
	sf::Sprite itemInfoOverPanel;
	void renderItemPanel(Vector2f position, RenderWindow& window);
};


struct GUI
{// ���������� gui

	sf::Texture widgetsTexture;
	panels panels;

	sf::Texture textureBar;
	barHungry hungry;
	barThirst thirst;
	barMainFeatures mainFeatures;
	itemFeatures itemFeatures;

	// ������ �� �����
	sf::Text *textGui[numberTextReference];

	void renderTextDeath(MainPerson &mainPerson, sf::Vector2f position, sf::RenderWindow &window, TextGame &textGame);
	void setPositionGui(sf::RenderWindow &window, MainPerson &mainPerson, std::vector<Enemy>& enemy, TextGame &textGame);
};


void initializeGUI(GUI &gui, TextGame &textGame);

void createGUITexture(Texture &texture, sf::String fileName);

void createGUI(sf::Sprite &itemInfoOverPanel, Texture &texture);
void createGUI(infoAboutSelect &gui);
void createGUI(panelQuickAccess &gui, Texture *texture);
void createPanels(panels &gui, Texture &texture);

void createGUI(barHungry &gui, Texture *texture);
void createGUI(barThirst &gui, Texture *texture);
void createGUI(barMainFeatures &gui, Texture *texture);
void createGUI(itemFeatures &gui, Texture *textureWidgets, Texture *textureBars);
