#include "GUI.h"

using namespace sf;
using namespace std;

void initializeGUI(GUI &gui, TextGame &textGame)
{

	createGUITexture(gui.widgetsTexture, texturePaths[idTexturePaths::widgets]);
	createPanels(gui.panels, gui.widgetsTexture);

	createGUITexture(gui.textureBar, texturePaths[idTexturePaths::bars]);
	createGUI(gui.hungry, gui.textureBar);
	createGUI(gui.thirst, gui.textureBar);
	createGUI(gui.mainFeatures, gui.textureBar);
	createGUI(gui.itemFeatures, gui.widgetsTexture, gui.textureBar);

	///////////////////////////////////////////////////////////////////
	// ИСПРАВЬ
	// НЕРАБОТАЕТ
	//gui.textGui[idTextGui::infoWindowBlockGui] = &textGame.texts[idText::infoWindowBlock];
	//gui.textGui[idTextGui::infoWindowFloorGui] = &textGame.texts[idText::infoWindowFloor];
	//gui.textGui[idTextGui::infoWindowUnlifeObjectGui] = &textGame.texts[idText::infoWindowUnlifeObject];
	//gui.textGui[idTextGui::infoWindowItemGui] = &textGame.texts[idText::infoWindowItemGui];
}

void createGUITexture(Texture *texture, sf::String fileName)
{
	texture = new Texture;
	texture->loadFromFile(fileName);
}

void createGUI(infoAboutSelect &gui)
{
	gui.Texture = new Texture;
	gui.sprite = new Sprite;

	gui.Texture->loadFromFile(texturePaths[idTexturePaths::infoSelectBlock]);
	gui.sprite->setTexture(*gui.Texture);
	gui.sprite->setTextureRect(IntRect(0, 0, widthInfo, heightInfo));
}

void createGUI(panelQuickAccess &gui, Texture *texture)
{
	gui.spritePanel = new Sprite;
	gui.spriteSelect = new Sprite;

	gui.spritePanel->setTexture(*texture);
	gui.spritePanel->setOrigin(widthPanelQuickAccess / 2, heightPanelQuickAccess / 2);// ИСПРАВЬ
	gui.spritePanel->setTextureRect(IntRect(0, 0, widthPanelQuickAccess, heightPanelQuickAccess));

	gui.spriteSelect->setTexture(*texture);
	gui.spriteSelect->setOrigin(0, heightSelectInPanelQuickAccess / 2);// ИСПРАВЬ
	gui.spriteSelect->setTextureRect(IntRect(shiftXSelectInPanelQuickAccess, shiftYSelectInPanelQuickAccess, widthSelectInPanelQuickAccess, heightSelectInPanelQuickAccess));

}

void createPanels(panels &gui, Texture *texture)
{
	createGUI(gui.infoAboutSelect);
	createGUI(gui.panelQuickAccess, texture);
	createGUI(gui.itemInfoOverPanel, texture);
}

void createGUI(barHungry &gui, Texture *texture)
{
	gui.lowHungry = new Sprite;
	gui.highHungry = new Sprite;
	gui.levelHungry = new Sprite;

	gui.lowHungry->setTexture(*texture);
	gui.lowHungry->setTextureRect(IntRect(X_HUNGY_GUI, Y_HUNGY_GUI, WIDTH_HUNGY_GUI, HEIGHT_HUNGY_GUI));

	gui.highHungry->setTexture(*texture);
	gui.highHungry->setTextureRect(IntRect(X_HUNGY_GUI, Y_HUNGY_GUI + HEIGHT_HUNGY_GUI, WIDTH_HUNGY_GUI, HEIGHT_HUNGY_GUI));

	gui.levelHungry->setTexture(*texture);
	gui.levelHungry->setTextureRect(IntRect(X_HUNGY_GUI, Y_HUNGY_GUI + HEIGHT_HUNGY_GUI * 2, WIDTH_HUNGY_GUI, LEVEL_HUNGY_GUI));
}

void createGUI(barThirst &gui, Texture *texture)
{
	gui.bottle = new Sprite;
	gui.levelThirst = new Sprite;

	// Жажды
	gui.bottle->setTexture(*texture);
	gui.bottle->setTextureRect(IntRect(X_THIRST_GUI, Y_THIRST_GUI, WIDTH_THIRST_GUI, HEIGHT_THIRST_GUI));

	gui.levelThirst->setTexture(*texture);
	gui.levelThirst->setTextureRect(IntRect(X_THIRST_GUI, Y_THIRST_GUI + HEIGHT_THIRST_GUI, WIDTH_THIRST_GUI, LEVEL_THIRST));

}

void createGUI(sf::Sprite *itemInfoOverPanel, Texture *texture)
{
	itemInfoOverPanel = new Sprite;

	itemInfoOverPanel->setTexture(*texture);
	itemInfoOverPanel->setOrigin(WIDTH_ITEM_OVER_PANEL_INFO / 2, HEIGHT_ITEM_OVER_PANEL_INFO / 2);
	itemInfoOverPanel->setTextureRect(IntRect(X_ITEM_OVER_PANEL_INFO, Y_ITEM_OVER_PANEL_INFO,
																		WIDTH_ITEM_OVER_PANEL_INFO, HEIGHT_ITEM_OVER_PANEL_INFO));
}

void createGUI(itemFeatures& gui, Texture *textureWidgets, Texture *textureBars)
{


	gui.cutSprite = new Sprite;
	gui.crashSprite = new Sprite;
	gui.hungrySprite = new Sprite;
	gui.thirstSprite = new Sprite;

	gui.crashSprite->setTexture(*textureBars);
	gui.crashSprite->setOrigin(WIDTH_DAMAGE_GUI / 2, HEIGHT_DAMAGE_GUI / 2);
	gui.crashSprite->setTextureRect(IntRect(X_CRASH_DAMAGE_GUI, Y_CRASH_DAMAGE_GUI, WIDTH_DAMAGE_GUI, HEIGHT_DAMAGE_GUI));

	gui.cutSprite->setTexture(*textureBars);
	gui.cutSprite->setOrigin(WIDTH_DAMAGE_GUI / 2, HEIGHT_DAMAGE_GUI / 2);
	gui.cutSprite->setTextureRect(IntRect(X_CUT_DAMAGE_GUI, Y_CUT_DAMAGE_GUI, WIDTH_DAMAGE_GUI, HEIGHT_DAMAGE_GUI));

	gui.hungrySprite->setTexture(*textureBars);
	gui.hungrySprite->setOrigin(WIDTH_DAMAGE_GUI / 2, HEIGHT_DAMAGE_GUI / 2);
	gui.hungrySprite->setTextureRect(IntRect(X_HUNGRY_ITEM_GUI, Y_HUNGRY_ITEM_GUI, WIDTH_DAMAGE_GUI, HEIGHT_DAMAGE_GUI));

	gui.thirstSprite->setTexture(*textureBars);
	gui.thirstSprite->setOrigin(WIDTH_DAMAGE_GUI / 2, HEIGHT_DAMAGE_GUI / 2);
	gui.thirstSprite->setTextureRect(IntRect(X_THIRST_ITEM_GUI, Y_THIRST_ITEM_GUI, WIDTH_DAMAGE_GUI, HEIGHT_DAMAGE_GUI));
}

void createGUI(barMainFeatures &gui, Texture *texture)
{
	gui.bar = new Sprite;
	gui.levelHealth = new Sprite;
	gui.levelStamina = new Sprite;
	gui.levelMana = new Sprite;

	// Здоровья
	gui.bar->setTexture(*texture);
	gui.bar->setTextureRect(IntRect(X_HEALTH_GUI, Y_HEALTH_GUI, WIDTH_BARS_GUI, HEIGHT_BARS_GUI));

	gui.levelHealth->setTexture(*texture);
	gui.levelHealth->setTextureRect(IntRect(X_LEVEL_HEALTH_GUI, Y_LEVEL_HEALTH_GUI, WIDTH_LEVEL_BAR_GUI, HEIGHT_LEVEL_BAR_GUI));

	gui.levelStamina->setTexture(*texture);
	gui.levelStamina->setTextureRect(IntRect(X_LEVEL_STAMINA_GUI, Y_LEVEL_STAMINA_GUI, WIDTH_LEVEL_BAR_GUI, HEIGHT_LEVEL_BAR_GUI));

	gui.levelMana->setTexture(*texture);
	gui.levelMana->setTextureRect(IntRect(X_LEVEL_MANA_GUI, Y_LEVEL_MANA_GUI, WIDTH_LEVEL_BAR_GUI, HEIGHT_LEVEL_BAR_GUI));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
void infoAboutSelect::render(Vector2f position, RenderWindow &window, TextGame &textGame)
{
	sprite->setPosition(position);
	window.draw(*sprite);

	Text* currentText = &textGame.texts[idText::infoWindowBlock];
	position = { position.x + shiftXInfoText , position.y + shiftYInfoText };
	currentText->setPosition(position);
	window.draw(*currentText);

	for (int i = idText::infoWindowFloor; i <= idText::infoEntity; i++)
	{
		currentText = &textGame.texts[i];
		position.y += textGame.texts[i - 1].getCharacterSize();
		currentText->setPosition(position);
		window.draw(*currentText);
	}
}

void GUI::renderTextDeath(MainPerson &mainPerson, sf::Vector2f position, sf::RenderWindow& window, TextGame& textGame)
{
	Text *currentText = &textGame.texts[idText::mainPersonIsDeath];
	currentText->setPosition(position);
	if (mainPerson.isDeath) {
		window.draw(*currentText);
	}
}

void panelQuickAccess::renderPanel(Vector2f position, RenderWindow& window)
{
	spritePanel->setPosition(position);
	window.draw(*spritePanel);
}

void panelQuickAccess::renderSelect(MainPerson& mainPerson, Vector2f centerWindow, Vector2u sizeWindow, RenderWindow& window)
{
	int &idSelectItem = mainPerson.idSelectItem;
	int startPosition = widthPanelQuickAccess / 2;
	int shift = shiftSelect * idSelectItem;
	Vector2f position;
	position = { centerWindow.x - startPosition + shift, centerWindow.y + sizeWindow.y / 2 - heightPanelQuickAccess / 2 };// ИСПРАВЬ

	spriteSelect->setPosition(position);
	window.draw(*spriteSelect);
}

void panels::renderItemPanel(sf::Vector2f position, RenderWindow& window)
{
	itemInfoOverPanel->setPosition(position);
	window.draw(*itemInfoOverPanel);
}

void panelQuickAccess::renderItems(::MainPerson& mainPerson, sf::Vector2f centerWindow,
																	 sf::Vector2u sizeWindow, ::sf::RenderWindow& window,
																	 TextGame &textGame, barMainFeatures &bars, itemFeatures &itemFeatures)
{
	Text *currentText;
	String nameCurrentItem = mainPerson.itemFromPanelQuickAccess[0].typeItem->features.name;
	String nameEmptyItem = mainPerson.emptyItem->typeItem->features.name;
	for (int i = 0; i < AMOUNT_ACTIVE_SLOTS; i++) {

		nameCurrentItem = mainPerson.itemFromPanelQuickAccess[i].typeItem->features.name;
		if (nameCurrentItem != nameEmptyItem) {

			Item& currentItem = mainPerson.itemFromPanelQuickAccess[i];

			int shift = shiftSelect * (i);
			Vector2f pos;
			pos = { centerWindow.x - SHIFT_START_ITEM_PANEL + shift + SHIFT_START_ITEM_PANEL,
				centerWindow.y + sizeWindow.y / 2 - heightPanelQuickAccess / 2 };// ИСПРАВЬ
			currentItem.mainSprite->setPosition(pos);
			window.draw(*currentItem.mainSprite);

			
			if (mainPerson.idSelectItem == i)
			{
				itemFeatures.renderFeatures(mainPerson, centerWindow, sizeWindow,
											 window, textGame, bars);
			}
				
		}

	}

}

void itemFeatures::renderNameItem(MainPerson& mainPerson, Vector2f& position, Vector2f centerWindow,
																			Vector2u sizeWindow, sf::RenderWindow& window, TextGame &textGame)
{
	String nameCurrentItem = mainPerson.itemFromPanelQuickAccess[0].typeItem->features.name;
	Text *currentText = &textGame.texts[idText::itemGui];

	currentText->setString(nameCurrentItem);
	position = { centerWindow.x - WIDTH_ITEM_OVER_PANEL_INFO / 2 + SHIFT_FEATURES_PANEL,
		centerWindow.y + sizeWindow.y / 2 - heightPanelQuickAccess - HEIGHT_ITEM_OVER_PANEL_INFO / 2 };
	currentText->setPosition(position);
	window.draw(*currentText);
}


void itemFeatures::renderValueMiddle(Text* text, sf::Vector2f position)
{
}

void itemFeatures::renderIconWithScale(Sprite* sprite, sf::Vector2f position, sf::RenderWindow& window)
{
	sprite->setPosition(position);
	sprite->setScale(SCALE_FEATURES);
	window.draw(*sprite);
}

void itemFeatures::renderBar(Sprite *sprite, sf::Vector2f position, sf::RenderWindow& window)
{
	sprite->setPosition(position);
	sprite->setScale(scaleGuiForEnemy);
	window.draw(*sprite);
	sprite->setScale(normalSizeGuiForEnemy);
}

void itemFeatures::renderFeatures(MainPerson& mainPerson, Vector2f centerWindow,
																	Vector2u sizeWindow, RenderWindow& window,
																	TextGame &textGame, barMainFeatures &bars)
{

	String nameCurrentItem = mainPerson.itemFromPanelQuickAccess[0].typeItem->features.name;
	String nameEmptyItem = mainPerson.emptyItem->typeItem->features.name;
	Text *currentText = &textGame.texts[idText::itemGui];

	Vector2f posName;// Сначала выписываем характеристики, потом имя(так как имя перед ними)
	renderNameItem(mainPerson, posName, centerWindow,
								 sizeWindow, window, textGame);

	int i = mainPerson.idSelectItem;
	int paritySize = currentText->getString().getSize() % 2;
	int shiftName = currentText->getCharacterSize();// TODO
	int halfSizeString = shiftName * (2 - paritySize) + computeSizeString(*currentText) / 2;
	//////////////////////////////////////////////


	Item& currentItem = mainPerson.itemFromPanelQuickAccess[i];
	TypeItem *typeItem = currentItem.typeItem;
	featuresItem *features = &typeItem->features;
	int categoryItem = typeItem->features.category;
	Vector2f pos;

	int shift = 20;// TODO
	/////////////////////////////////////////////////////////////
	// Если предмет инструмент или оружие
	bool isDestroy = features->isDestroy;
	if (isDestroy) {
		pos = { centerWindow.x - SHIFT_START_ITEM_PANEL + shift + SHIFT_START_ITEM_PANEL,
			centerWindow.y + sizeWindow.y / 2 - heightPanelQuickAccess / 2 };
		// то отображаем прочность
		pos.x -= SIZE_ITEM / 2;
		pos.y += SIZE_ITEM / 2 - HEIGHT_BARS_GUI * 0.5 * scaleItems.y;

		renderBar(bars.bar, pos, window);

		float levelToughness = float(currentItem.currentToughness) / currentItem.maxToughness;

		pos.x += X_SHIFT_BARS * scaleGuiForEnemy.x;
		pos.y += Y_SHIFT_BARS * scaleGuiForEnemy.y;
		int currentToughness = WIDTH_LEVEL_BAR_GUI * levelToughness;
		bars.levelStamina->setTextureRect(IntRect(X_LEVEL_STAMINA_GUI, Y_LEVEL_STAMINA_GUI, currentToughness, HEIGHT_LEVEL_BAR_GUI));

		renderBar(bars.levelStamina, pos, window);
	}
	////////////////////////////////
	// Характеристики
	if (mainPerson.idSelectItem == i) {

		//////////////////////////////////////////////////////////
		// Отображение характеристик
		pos = { posName.x + halfSizeString,
			centerWindow.y + sizeWindow.y / 2 - heightPanelQuickAccess - Y_SHIFT_OUT_PANEL };
		// Перевод из числа в строку
		int itemCutDam = typeItem->damageItem.cuttingDamage;
		int itemCrashDam = typeItem->damageItem.crushingDamage;

		string itemCut;
		string itemCrash;

		intToString(itemCutDam, itemCut);
		intToString(itemCrashDam, itemCrash);

		////////////////
		// Режущий урон
		renderIconWithScale(cutSprite, pos, window);

		pos.x += WIDTH_DAMAGE_GUI * SCALE_FEATURES.x;
		currentText->setString(itemCut);
		currentText->setOrigin(itemCut.size() / 2, currentText->getCharacterSize() / 2);
		currentText->setPosition(pos);
		window.draw(*currentText);
		////////////////
		// Дробящий урон
		pos.x += computeSizeString(*currentText) + SHIFT_FEATURES_PANEL;
		crashSprite->setPosition(pos);
		crashSprite->setScale(SCALE_FEATURES);
		window.draw(*crashSprite);

		pos.x += WIDTH_DAMAGE_GUI * SCALE_FEATURES.x;
		currentText->setString(itemCrash);
		currentText->setOrigin(itemCut.size() / 2, currentText->getCharacterSize() / 2);
		currentText->setPosition(pos);
		window.draw(*currentText);
		////////////////
		//////////////////////////////////////////////////////////
		// Отображение характеристик

		pos.x += computeSizeString(*currentText) + SHIFT_FEATURES_PANEL;
		// Перевод из числа в строку
		int itemToughness = currentItem.currentToughness;

		string itemToug;

		intToString(itemToughness, itemToug);

		////////////////
		// Голод
		if (categoryItem == idCategoryItem::food) {
			hungrySprite->setPosition(pos);
			hungrySprite->setScale(SCALE_FEATURES);
			window.draw(*hungrySprite);
		}
		////////////////
		// Жажда
		else if (categoryItem == idCategoryItem::bottleWithWater
						 || categoryItem == idCategoryItem::bukketWithWater) {
			thirstSprite->setPosition(pos);
			thirstSprite->setScale(SCALE_FEATURES);
			window.draw(*thirstSprite);
		}
		////////////////
		// Другое не показываем
		else {
			itemToug = "";// ИСПРАВЬ
		}

		pos.x += WIDTH_DAMAGE_GUI * SCALE_FEATURES.x;
		currentText->setString(itemToug);
		currentText->setOrigin(itemToug.size() / 2, currentText->getCharacterSize() / 2);
		currentText->setPosition(pos);
		window.draw(*currentText);
		//////////////////////////////////////////////////////////
	}
	////////////////////////////////

	/////////////////////////////////////////////////////////////
}

void GUI::setPositionGui(RenderWindow &window, MainPerson &mainPerson, vector<Enemy>& enemy, TextGame &textGame)
{

	Vector2f centerWindow = mainPerson.view->getCenter();
	Vector2u sizeWindow = window.getSize();
	Vector2f pos = { centerWindow.x + sizeWindow.x / 2 - widthInfo , centerWindow.y + sizeWindow.y / 2 - heightInfo};

	panels.infoAboutSelect.render(pos, window, textGame);
	renderTextDeath(mainPerson, centerWindow, window, textGame);

	pos = { centerWindow.x , centerWindow.y + sizeWindow.y / 2 - heightPanelQuickAccess / 2};// ИСПРАВЬ
	panels.panelQuickAccess.renderPanel(pos, window);
	panels.panelQuickAccess.renderSelect(mainPerson, centerWindow, sizeWindow, window);

	pos = { centerWindow.x, centerWindow.y + sizeWindow.y / 2 - heightPanelQuickAccess - Y_SHIFT_OUT_PANEL };
	panels.renderItemPanel(pos, window);
	//////////////////////////////////////////////////////////
	// Окошко с информацией о выбранном предмете

	//////////////////////////////////////////////////////////////////////// 
	// Шкала здоровья
	pos = centerWindow;

	pos.x -= sizeWindow.x / 2;
	pos.y += sizeWindow.y / 2 - float(HEIGHT_BARS_GUI) * 3;

	bar->setPosition(pos);
	window.draw(*bar);

	float level = float(mainPerson.currentHealth) / mainPerson.maxHealth;

	pos.x += X_SHIFT_BARS;
	pos.y += Y_SHIFT_BARS;
	int currentLevel = WIDTH_LEVEL_BAR_GUI * level;
	levelHealth->setTextureRect(IntRect(X_LEVEL_HEALTH_GUI, Y_LEVEL_HEALTH_GUI, currentLevel, HEIGHT_LEVEL_BAR_GUI));
	levelHealth->setPosition(pos);
	window.draw(*levelHealth);

	////////////////////////////////
	// Количество здоровья
	currentText = &textGame.texts[idText::levelBar];

	////////////////
	// Перевод из числа в строку
	int health = mainPerson.currentHealth;
	int healthMax = mainPerson.maxHealth;

	currentText->setString(toStringCharacter(health, healthMax));
	////////////////
	// Задание позиции
	int middleString = computeMiddleString(*currentText);

	pos = { pos.x + WIDTH_LEVEL_BAR_GUI / 2 - middleString, pos.y - Y_SHIFT_BARS / 2 };
	currentText->setPosition(pos);
	window.draw(*currentText);
	////////////////////////////////

	////////////////////////////////////////////////////////////////
	// для противников
	int shiftBar;

	for (int i = 0; i != enemy.size(); ++i) {
		if (enemy[i].currentLevelFloor >= mainPerson.currentLevelFloor - 1
				&& enemy[i].currentLevelFloor <= mainPerson.currentLevelFloor + 1
				&& i == mainPerson.findEnemyFromList) {

			shiftBar = enemy[i].maxMana > 0;
			pos = enemy[i].spriteEntity->getPosition();
			pos.x -= scaleGuiForEnemy.x * WIDTH_BARS_GUI / 2;
			pos.y -= enemy[i].height / 2 + scaleGuiForEnemy.y * HEIGHT_BARS_GUI * (2 + shiftBar);


			bar->setPosition(pos);
			bar->setScale(scaleGuiForEnemy);
			window.draw(*bar);
			bar->setScale(normalSizeGuiForEnemy);

			level = float(enemy[i].currentHealth) / enemy[i].maxHealth;

			pos.x += X_SHIFT_BARS * scaleGuiForEnemy.x;
			pos.y += Y_SHIFT_BARS * scaleGuiForEnemy.y;
			currentLevel = WIDTH_LEVEL_BAR_GUI * level;
			levelHealth->setTextureRect(IntRect(X_LEVEL_HEALTH_GUI, Y_LEVEL_HEALTH_GUI, currentLevel, HEIGHT_LEVEL_BAR_GUI));
			levelHealth->setPosition(pos);

			levelHealth->setScale(scaleGuiForEnemy);
			window.draw(*levelHealth);
			levelHealth->setScale(normalSizeGuiForEnemy);



			///*
			////////////////////////////////////////////////////////////
			// Отображение урона
			currentText = &textGame.texts[idText::inputDamage];

			// Позиция
			pos = enemy[i].spriteEntity->getPosition();
			pos.y -= enemy[i].height / 2 + scaleGuiForEnemy.y * HEIGHT_BARS_GUI * (3 + shiftBar) + shiftEnemyDamage;

			// Если нанесли урон то отображаем
			int damage = enemy[i].inputDamage;
			if (damage) {
				string stringDamage;
				intToString(damage, stringDamage);

				currentText->setString(stringDamage);


				pos.x -= currentText->getString().getSize() * currentText->getCharacterSize() / 4;
				currentText->setPosition(pos);
				window.draw(*currentText);
			}
			////////////////////////////////////////////////////////////
			// Отображение текущего здоровья
			currentText = &textGame.texts[idText::levelBar];
		
			pos = enemy[i].spriteEntity->getPosition();
			pos.y -= Y_SHIFT_BARS * scaleGuiForEnemy.y;
			pos.y -= enemy[i].height / 2 + scaleGuiForEnemy.y * HEIGHT_BARS_GUI * (2 + shiftBar);

			////////////////
			// Перевод из числа в строку
			int currentHealthEnemy = enemy[i].currentHealth;
			int maxHealthEnemy = enemy[i].maxHealth;

			currentText->setString(toStringCharacter(currentHealthEnemy, maxHealthEnemy));

			pos.x -= currentText->getString().getSize() * currentText->getCharacterSize() / 4;
			currentText->setPosition(pos);

			window.draw(*currentText);
			////////////////////////////////////////////////////////////
			//window.draw(*game.items->item[i].spriteForUse);// ИСПРАВЬ
			//*/
		}	
	}
	////////////////////////////////////////////////////////////////
	// Шкала выносливости
	pos = centerWindow;

	pos.x -= sizeWindow.x / 2;
	pos.y += sizeWindow.y / 2 - float(HEIGHT_BARS_GUI) * 2;

	bar->setPosition(pos);
	window.draw(*bar);

	level = float(mainPerson.currentStamina) / mainPerson.maxStamina;

	pos.x += X_SHIFT_BARS;
	pos.y += Y_SHIFT_BARS;
	currentLevel = WIDTH_LEVEL_BAR_GUI * level;
	levelStamina->setTextureRect(IntRect(X_LEVEL_STAMINA_GUI, Y_LEVEL_STAMINA_GUI, currentLevel, HEIGHT_LEVEL_BAR_GUI));
	levelStamina->setPosition(pos);
	window.draw(*levelStamina);

	////////////////////////////////
	// Количество выносливости
	currentText = &textGame.texts[idText::levelBar];

	////////////////
	int stamina = mainPerson.currentStamina;
	int staminaMax = mainPerson.maxStamina;

	currentText->setString(toStringCharacter(stamina, staminaMax));

	middleString = currentText->getString().getSize() * currentText->getCharacterSize() / 4;

	pos = { pos.x + WIDTH_LEVEL_BAR_GUI / 2 - middleString, pos.y - Y_SHIFT_BARS / 2 };
	currentText->setPosition(pos);
	window.draw(*currentText);
	////////////////////////////////

	////////////////////////////////////////////////////////////////
	// для противников
	for (int i = 0; i != enemy.size(); ++i) {
		if (enemy[i].currentLevelFloor >= mainPerson.currentLevelFloor - 1
				&& enemy[i].currentLevelFloor <= mainPerson.currentLevelFloor + 1
				&& i == mainPerson.findEnemyFromList) {

			if (enemy[i].maxStamina) {
				shiftBar = enemy[i].maxMana > 0;

				pos = enemy[i].spriteEntity->getPosition();
				pos.x -= scaleGuiForEnemy.x * WIDTH_BARS_GUI / 2;
				pos.y -= enemy[i].height / 2 + scaleGuiForEnemy.y * HEIGHT_BARS_GUI * (1 + shiftBar);


				bar->setPosition(pos);
				bar->setScale(scaleGuiForEnemy);
				window.draw(*bar);
				bar->setScale(normalSizeGuiForEnemy);

				level = float(enemy[i].currentStamina) / enemy[i].maxStamina;

				pos.x += X_SHIFT_BARS * scaleGuiForEnemy.x;
				pos.y += Y_SHIFT_BARS * scaleGuiForEnemy.y;
				currentLevel = WIDTH_LEVEL_BAR_GUI * level;
				levelStamina->setTextureRect(IntRect(X_LEVEL_STAMINA_GUI, Y_LEVEL_STAMINA_GUI, currentLevel, HEIGHT_LEVEL_BAR_GUI));
				levelStamina->setPosition(pos);

				levelStamina->setScale(scaleGuiForEnemy);
				window.draw(*levelStamina);
				levelStamina->setScale(normalSizeGuiForEnemy);



				///*

				////////////////////////////////////////////////////////////
				// Отображение текущей выносливости
				currentText = &textGame.texts[idText::levelBar];

				pos = enemy[i].spriteEntity->getPosition();
				pos.y -= Y_SHIFT_BARS * scaleGuiForEnemy.y;
				pos.y -= enemy[i].height / 2 + scaleGuiForEnemy.y * HEIGHT_BARS_GUI * (1 + shiftBar);

				////////////////
				int currentStaminaEnemy = enemy[i].currentStamina;
				int maxStaminaEnemy = enemy[i].maxStamina;

				currentText->setString(toStringCharacter(currentStaminaEnemy, maxStaminaEnemy));

				pos.x -= currentText->getString().getSize() * currentText->getCharacterSize() / 4;
				currentText->setPosition(pos);

				window.draw(*currentText);
				////////////////////////////////////////////////////////////
				//window.draw(*game.items->item[i].spriteForUse);// ИСПРАВЬ
				//*/
			}
			
		}

	}
	////////////////////////////////////////////////////////////////
	// Шкала маны
	pos = centerWindow;

	pos.x -= sizeWindow.x / 2;
	pos.y += sizeWindow.y / 2 - float(HEIGHT_BARS_GUI);

	bar->setPosition(pos);
	window.draw(*bar);

	level = float(mainPerson.currentMana) / mainPerson.maxMana;

	pos.x += X_SHIFT_BARS;
	pos.y += Y_SHIFT_BARS;
	currentLevel = WIDTH_LEVEL_BAR_GUI * level;
	levelMana->setTextureRect(IntRect(X_LEVEL_MANA_GUI, Y_LEVEL_MANA_GUI, currentLevel, HEIGHT_LEVEL_BAR_GUI));
	levelMana->setPosition(pos);
	window.draw(*levelMana);

	////////////////////////////////
	// Количество маны
	currentText = &textGame.texts[idText::levelBar];

	////////////////
	int mana = mainPerson.currentMana;
	int manaMax = mainPerson.maxMana;

	currentText->setString(toStringCharacter(mana, manaMax));

	middleString = currentText->getString().getSize() * currentText->getCharacterSize() / 4;

	pos = { pos.x + WIDTH_LEVEL_BAR_GUI / 2 - middleString, pos.y - Y_SHIFT_BARS / 2 };
	currentText->setPosition(pos);
	window.draw(*currentText);
	////////////////////////////////

	// для противников
	for (int i = 0; i != enemy.size(); ++i) {
		if (enemy[i].currentLevelFloor >= mainPerson.currentLevelFloor - 1
				&& enemy[i].currentLevelFloor <= mainPerson.currentLevelFloor + 1
				&& i == mainPerson.findEnemyFromList) {

			if (enemy[i].maxMana) {
				pos = enemy[i].spriteEntity->getPosition();
				pos.x -= scaleGuiForEnemy.x * WIDTH_BARS_GUI / 2;
				pos.y -= enemy[i].height / 2 + scaleGuiForEnemy.y * HEIGHT_BARS_GUI;


				bar->setPosition(pos);
				bar->setScale(scaleGuiForEnemy);
				window.draw(*bar);
				bar->setScale(normalSizeGuiForEnemy);

				level = float(enemy[i].currentMana) / enemy[i].maxMana;

				pos.x += X_SHIFT_BARS * scaleGuiForEnemy.x;
				pos.y += Y_SHIFT_BARS * scaleGuiForEnemy.y;
				currentLevel = WIDTH_LEVEL_BAR_GUI * level;
				levelMana->setTextureRect(IntRect(X_LEVEL_MANA_GUI, Y_LEVEL_MANA_GUI, currentLevel, HEIGHT_LEVEL_BAR_GUI));
				levelMana->setPosition(pos);

				levelMana->setScale(scaleGuiForEnemy);
				window.draw(*levelMana);
				levelMana->setScale(normalSizeGuiForEnemy);



				///*

				////////////////////////////////////////////////////////////
				// Отображение текущей маны
				currentText = &textGame.texts[idText::levelBar];

				pos = enemy[i].spriteEntity->getPosition();
				pos.y -= Y_SHIFT_BARS * scaleGuiForEnemy.y;
				pos.y -= enemy[i].height / 2 + scaleGuiForEnemy.y * HEIGHT_BARS_GUI;

				////////////////
				int currentManaEnemy = enemy[i].currentMana;
				int maxManaEnemy = enemy[i].maxMana;

				currentText->setString(toStringCharacter(currentManaEnemy, maxManaEnemy));

				pos.x -= currentText->getString().getSize() * currentText->getCharacterSize() / 4;
				currentText->setPosition(pos);

				window.draw(*currentText);
				////////////////////////////////////////////////////////////
				//window.draw(*game.items->item[i].spriteForUse);// ИСПРАВЬ
				//*/
			}
			
		}

	}
	////////////////////////////////////////////////////////////////////////
	// Индикатор голода
	pos = centerWindow;
	pos.x -= sizeWindow.x / 2 - float(WIDTH_BARS_GUI);
	pos.y += sizeWindow.y / 2 - float(HEIGHT_HUNGY_GUI);

	// Верхняя часть тарелки
	highHungry->setPosition(pos);
	window.draw(*highHungry);

	// Уровень голода
	level = float(mainPerson.currentHungry) / mainPerson.maxHungry;

	pos.y += LEVEL_SHIFT_HUNGRY + MAX_SHIFT_HUNGRY_LEVEL * (1 - level);
	currentLevel = LEVEL_HUNGY_GUI * level;
	levelHungry->setTextureRect(IntRect(X_HUNGY_GUI, Y_HUNGY_GUI + HEIGHT_HUNGY_GUI * 2, WIDTH_HUNGY_GUI, currentLevel));
	levelHungry->setPosition(pos);
	window.draw(*levelHungry);

	// Дно тарелки
	pos = centerWindow;
	pos.x -= sizeWindow.x / 2 - float(WIDTH_BARS_GUI);
	pos.y += sizeWindow.y / 2 - float(HEIGHT_HUNGY_GUI);
	lowHungry->setPosition(pos);
	window.draw(*lowHungry);
	////////////////////////////////////////////////////////////////////////
	// Шкала жажды
	pos = centerWindow;
	pos.x -= sizeWindow.x / 2 - float(WIDTH_BARS_GUI);
	pos.y += sizeWindow.y / 2 - float(HEIGHT_HUNGY_GUI) - float(HEIGHT_THIRST_GUI);

	bottle->setPosition(pos);
	window.draw(*bottle);

	level = float(mainPerson.currentThirst) / mainPerson.maxThirst;

	pos.y += LEVEL_SHIFT_THIRST + LEVEL_THIRST * (1 - level);
	currentLevel = LEVEL_THIRST * level;
	int currentShift = LEVEL_THIRST * (1 - level);
	levelThirst->setTextureRect(IntRect(X_THIRST_GUI, Y_THIRST_GUI + HEIGHT_THIRST_GUI + currentShift, WIDTH_THIRST_GUI, currentLevel));
	levelThirst->setPosition(pos);
	window.draw(*levelThirst);
	////////////////////////////////////////////////////////////////////////

}