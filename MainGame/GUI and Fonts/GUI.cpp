#include "GUI.h"

using namespace sf;
using namespace std;

void initializeGUI(GUI &gui, TextGame &textGame)
{
	createGUITexture(gui.widgetsTexture, texturePaths[idTexturePaths::widgets]);
	createPanels(gui.panels, gui.widgetsTexture);

	createGUITexture(gui.textureBar, texturePaths[idTexturePaths::bars]);
	createGUI(gui.hungry, &gui.textureBar);
	createGUI(gui.thirst, &gui.textureBar);
	createGUI(gui.mainFeatures, &gui.textureBar);
	createGUI(gui.itemFeatures, &gui.widgetsTexture, &gui.textureBar);

	///////////////////////////////////////////////////////////////////
	// ИСПРАВЬ
	// НЕРАБОТАЕТ
	//gui.textGui[idTextGui::infoWindowBlockGui] = &textGame.texts[idText::infoWindowBlock];
	//gui.textGui[idTextGui::infoWindowFloorGui] = &textGame.texts[idText::infoWindowFloor];
	//gui.textGui[idTextGui::infoWindowUnlifeObjectGui] = &textGame.texts[idText::infoWindowUnlifeObject];
	//gui.textGui[idTextGui::infoWindowItemGui] = &textGame.texts[idText::infoWindowItemGui];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
void barHungry::renderBar(int& current, int& max, Vector2f centerWindow, Vector2u sizeWindow,
													RenderWindow& window)
{
	Vector2f pos;
	pos = centerWindow;
	
	// TODO
	//highHungry.setScale(scaleGuiForMainPerson);
	//lowHungry.setScale(scaleGuiForMainPerson);
	//levelHungry.setScale(scaleGuiForMainPerson);

	renderHigh(pos, sizeWindow, window);
	renderLevel(current, max, pos, window);
	renderLow(pos, centerWindow, sizeWindow, window);
}

void barHungry::renderHigh(Vector2f& pos, Vector2u sizeWindow, RenderWindow& window)
{
	//* scaleGuiForMainPerson.x
	// * scaleGuiForMainPerson.y
	pos.x -= sizeWindow.x / 2 - float(WIDTH_BARS_GUI) ;
	pos.y += sizeWindow.y / 2 - float(HEIGHT_HUNGY_GUI);

	highHungry.setPosition(pos);
	window.draw(highHungry);
}

void barHungry::renderLevel(int& current, int& max, Vector2f& pos, RenderWindow& window)
{
	float level = float(current) / max;

	// * scaleGuiForMainPerson.y
	pos.y += (LEVEL_SHIFT_HUNGRY + MAX_SHIFT_HUNGRY_LEVEL * (1 - level));
	int currentLevel = int(LEVEL_HUNGY_GUI * level);
	levelHungry.setTextureRect(IntRect(X_HUNGY_GUI, Y_HUNGY_GUI + HEIGHT_HUNGY_GUI * 2, WIDTH_HUNGY_GUI, currentLevel));
	levelHungry.setPosition(pos);
	window.draw(levelHungry);
}

void barHungry::renderLow(Vector2f pos, Vector2f centerWindow, Vector2u sizeWindow, RenderWindow& window)
{
	//* scaleGuiForMainPerson.x
	//* scaleGuiForMainPerson.y
	pos = centerWindow;
	pos.x -= sizeWindow.x / 2 - float(WIDTH_BARS_GUI) ;
	pos.y += sizeWindow.y / 2 - float(HEIGHT_HUNGY_GUI) ;
	lowHungry.setPosition(pos);
	window.draw(lowHungry);

}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void barThirst::renderBar(int& current, int& max, sf::Vector2f centerWindow, sf::Vector2u sizeWindow, sf::RenderWindow& window)
{
	Vector2f pos = centerWindow;
	// * scaleGuiForMainPerson.x
	//* scaleGuiForMainPerson.x
	pos.x -= sizeWindow.x / 2 - float(WIDTH_BARS_GUI);
	pos.y += sizeWindow.y / 2 - float(HEIGHT_HUNGY_GUI) - float(HEIGHT_THIRST_GUI) ;


	//TODO
	//bottle.setScale(scaleGuiForMainPerson);
	bottle.setPosition(pos);
	window.draw(bottle);

	float level = float(current) / max;

	pos.y += LEVEL_SHIFT_THIRST + LEVEL_THIRST * (1 - level);
	int currentLevel = int(LEVEL_THIRST * level);
	int currentShift = int(LEVEL_THIRST * (1 - level));
	// TODO
	//levelThirst.setScale(scaleGuiForMainPerson);
	levelThirst.setTextureRect(IntRect(X_THIRST_GUI, Y_THIRST_GUI + HEIGHT_THIRST_GUI + currentShift, WIDTH_THIRST_GUI, currentLevel));
	levelThirst.setPosition(pos);
	window.draw(levelThirst);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
void GUI::renderTextDeath(MainPerson &mainPerson, sf::Vector2f position, sf::RenderWindow& window, TextGame& textGame)
{
	Text *currentText = &textGame.texts[idText::mainPersonIsDeath];
	currentText->setPosition(position);
	if (mainPerson.isDeath) {
		window.draw(*currentText);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
void GUI::setPositionGui(RenderWindow &window, MainPerson &mainPerson, vector<Enemy>& enemy, TextGame &textGame)
{

	Vector2f centerWindow = mainPerson.view->getCenter();
	Vector2u sizeWindow = window.getSize();
	featuresWindow featuresWindow;
	Vector2f pos = { centerWindow.x + sizeWindow.x / 2 - widthInfo , centerWindow.y + sizeWindow.y / 2 - heightInfo};

	featuresWindow.size = sizeWindow;
	featuresWindow.center = centerWindow;
	featuresWindow.window = &window;
	//////////////////////////////////////////////////////////
	// Окошко с информацией о выбранном предмете

	panels.infoAboutSelect.render(pos, window, textGame);
	renderTextDeath(mainPerson, centerWindow, window, textGame);
	//////////////////////////////////////////////////////////
	// Панель быстрого доступа
	pos = { centerWindow.x , centerWindow.y + sizeWindow.y / 2 - heightPanelQuickAccess / 2};// ИСПРАВЬ
	panels.panelQuickAccess.renderPanel(pos, window);
	panels.panelQuickAccess.renderSelect(mainPerson, featuresWindow);

	pos = { centerWindow.x, centerWindow.y + sizeWindow.y / 2 - heightPanelQuickAccess - Y_SHIFT_OUT_PANEL };
	panels.renderItemPanel(pos, window);

	panels.panelQuickAccess.renderItems(mainPerson, featuresWindow,
																			textGame, mainFeatures, itemFeatures);

	//////////////////////////////////////////////////////////////////////// 
	// Шкала здоровья
	featuresSprite sizes;
	sizes.init(WIDTH_LEVEL_BAR_GUI, HEIGHT_LEVEL_BAR_GUI, X_LEVEL_HEALTH_GUI, Y_LEVEL_HEALTH_GUI);

	int health = mainPerson.health.currentHealth;
	int healthMax = mainPerson.health.maxHealth;
	int shiftHealth = 3;
	mainFeatures.renderBarMainPerson(mainPerson, health, healthMax, shiftHealth, mainFeatures.levelHealth,
																	 sizes, featuresWindow, textGame);

	////////////////////////////////////////////////////////////////
	// для противников
	int shiftHelathEnemy = 2;
	int healthEnemy;
	int healthMaxEnemy;

	bool isFindedEnemy;
	bool isInView;
	for (int i = 0; i != enemy.size(); ++i) {

		isFindedEnemy = i == mainPerson.findEnemyFromList;
		isInView = enemy[i].currentLevelFloor >= mainPerson.currentLevelFloor - 1
						&& enemy[i].currentLevelFloor <= mainPerson.currentLevelFloor + 1;

		if (isInView && isFindedEnemy) {

			healthEnemy = enemy[i].health.currentHealth;
			healthMaxEnemy = enemy[i].health.maxHealth;

			mainFeatures.renderBarEnemy(enemy[i], healthEnemy, healthMaxEnemy, shiftHelathEnemy, mainFeatures.levelHealth,
																	sizes, textGame, window);
		}	

	}
	////////////////////////////////////////////////////////////////
	// Шкала выносливости
	sizes.init(0, HEIGHT_LEVEL_BAR_GUI, X_LEVEL_STAMINA_GUI, Y_LEVEL_STAMINA_GUI);

	int stamina = mainPerson.stamina.currentStamina;
	int staminaMax = mainPerson.stamina.maxStamina;
	int shiftStamina = 2;
	mainFeatures.renderBarMainPerson(mainPerson, stamina, staminaMax, shiftStamina, mainFeatures.levelStamina,
																	 sizes, featuresWindow, textGame);


	////////////////////////////////////////////////////////////////
	// для противников

	int shiftStaminaEnemy = 1;
	int staminaEnemy;
	int staminaMaxEnemy;

	for (int i = 0; i != enemy.size(); ++i) {

		isFindedEnemy = i == mainPerson.findEnemyFromList;
		isInView = enemy[i].currentLevelFloor >= mainPerson.currentLevelFloor - 1
			&& enemy[i].currentLevelFloor <= mainPerson.currentLevelFloor + 1;

		if (isInView && isFindedEnemy) {

			staminaEnemy = enemy[i].stamina.currentStamina;
			staminaMaxEnemy = enemy[i].stamina.maxStamina;

			if (staminaMaxEnemy) {
				mainFeatures.renderBarEnemy(enemy[i], staminaEnemy, staminaMaxEnemy, shiftStaminaEnemy, mainFeatures.levelStamina,
																		sizes, textGame, window);
			}
			
		}

	}
	
	////////////////////////////////////////////////////////////////
	// Шкала маны
	sizes.init(0, HEIGHT_LEVEL_BAR_GUI, X_LEVEL_MANA_GUI, Y_LEVEL_MANA_GUI);

	int mana = mainPerson.mana.currentMana;
	int manaMax = mainPerson.mana.maxMana;
	int shiftMana = 1;
	mainFeatures.renderBarMainPerson(mainPerson, mana, manaMax, shiftMana, mainFeatures.levelMana,
																	 sizes, featuresWindow, textGame);


	int shiftManaEnemy = 0;
	int manaEnemy;
	int manaMaxEnemy;

	for (int i = 0; i != enemy.size(); ++i) {

		isFindedEnemy = i == mainPerson.findEnemyFromList;
		isInView = enemy[i].currentLevelFloor >= mainPerson.currentLevelFloor - 1
			&& enemy[i].currentLevelFloor <= mainPerson.currentLevelFloor + 1;

		if (isInView && isFindedEnemy) {

			manaEnemy = enemy[i].mana.currentMana;
			manaMaxEnemy = enemy[i].mana.maxMana;

			if (staminaMaxEnemy) {
				mainFeatures.renderBarEnemy(enemy[i], manaEnemy, manaMaxEnemy, shiftManaEnemy, mainFeatures.levelMana,
																		sizes, textGame, window);
			}

		}

	}

	////////////////////////////////////////////////////////////////////////
	hungry.renderBar(mainPerson.hungry.currentHungry, mainPerson.hungry.maxHungry, centerWindow, sizeWindow, window);
	thirst.renderBar(mainPerson.thirst.currentThirst, mainPerson.thirst.maxThirst, centerWindow, sizeWindow, window);
	////////////////////////////////////////////////////////////////////////

}

GUI::~GUI()
{
	//delete *textGui;// TODO
}