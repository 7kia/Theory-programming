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

void createGUITexture(Texture &texture, sf::String fileName)
{
	texture.loadFromFile(fileName);
}

void createGUI(infoAboutSelect &gui)
{
	gui.Texture = new Texture;
	gui.sprite = new Sprite;

	gui.Texture->loadFromFile(texturePaths[idTexturePaths::infoSelectBlock]);
	gui.sprite->setTexture(*gui.Texture);
	gui.sprite->setTextureRect(IntRect(0, 0, widthInfo, heightInfo));
}

void createGUI(panelQuickAccess &gui, Texture &texture)
{
	gui.spritePanel = new Sprite;
	gui.spriteSelect = new Sprite;

	gui.spritePanel->setTexture(texture);
	gui.spritePanel->setOrigin(widthPanelQuickAccess / 2, heightPanelQuickAccess / 2);// ИСПРАВЬ
	gui.spritePanel->setTextureRect(IntRect(0, 0, widthPanelQuickAccess, heightPanelQuickAccess));

	gui.spriteSelect->setTexture(texture);
	gui.spriteSelect->setOrigin(0, heightSelectInPanelQuickAccess / 2);// ИСПРАВЬ
	gui.spriteSelect->setTextureRect(IntRect(shiftXSelectInPanelQuickAccess, shiftYSelectInPanelQuickAccess, widthSelectInPanelQuickAccess, heightSelectInPanelQuickAccess));

}

void createPanels(panels &gui, Texture &texture)
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

void createGUI(sf::Sprite &itemInfoOverPanel, Texture &texture)
{
	itemInfoOverPanel.setTexture(texture);
	itemInfoOverPanel.setOrigin(WIDTH_ITEM_OVER_PANEL_INFO / 2, HEIGHT_ITEM_OVER_PANEL_INFO / 2);
	itemInfoOverPanel.setTextureRect(IntRect(X_ITEM_OVER_PANEL_INFO, Y_ITEM_OVER_PANEL_INFO,
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
void barHungry::renderBar(int& current, int& max, Vector2f centerWindow, Vector2u sizeWindow,
													RenderWindow& window)
{
	Vector2f pos;
	pos = centerWindow;
	
	renderHigh(pos, sizeWindow, window);
	renderLevel(current, max, pos, window);
	renderLow(pos, centerWindow, sizeWindow, window);
}

void barHungry::renderHigh(Vector2f& pos, Vector2u sizeWindow, RenderWindow& window)
{
	pos.x -= sizeWindow.x / 2 - float(WIDTH_BARS_GUI);
	pos.y += sizeWindow.y / 2 - float(HEIGHT_HUNGY_GUI);

	highHungry->setPosition(pos);
	window.draw(*highHungry);
}

void barHungry::renderLevel(int& current, int& max, Vector2f& pos, RenderWindow& window)
{
	float level = float(current) / max;

	pos.y += LEVEL_SHIFT_HUNGRY + MAX_SHIFT_HUNGRY_LEVEL * (1 - level);
	int currentLevel = LEVEL_HUNGY_GUI * level;
	levelHungry->setTextureRect(IntRect(X_HUNGY_GUI, Y_HUNGY_GUI + HEIGHT_HUNGY_GUI * 2, WIDTH_HUNGY_GUI, currentLevel));
	levelHungry->setPosition(pos);
	window.draw(*levelHungry);
}

void barHungry::renderLow(Vector2f& pos, Vector2f centerWindow, Vector2u sizeWindow, RenderWindow& window)
{
	pos = centerWindow;
	pos.x -= sizeWindow.x / 2 - float(WIDTH_BARS_GUI);
	pos.y += sizeWindow.y / 2 - float(HEIGHT_HUNGY_GUI);
	lowHungry->setPosition(pos);
	window.draw(*lowHungry);

}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void barThirst::renderBar(int& current, int& max, sf::Vector2f centerWindow, sf::Vector2u sizeWindow, sf::RenderWindow& window)
{
	Vector2f pos = centerWindow;
	pos.x -= sizeWindow.x / 2 - float(WIDTH_BARS_GUI);
	pos.y += sizeWindow.y / 2 - float(HEIGHT_HUNGY_GUI) - float(HEIGHT_THIRST_GUI);

	bottle->setPosition(pos);
	window.draw(*bottle);

	float level = float(current) / max;

	pos.y += LEVEL_SHIFT_THIRST + LEVEL_THIRST * (1 - level);
	int currentLevel = LEVEL_THIRST * level;
	int currentShift = LEVEL_THIRST * (1 - level);
	levelThirst->setTextureRect(IntRect(X_THIRST_GUI, Y_THIRST_GUI + HEIGHT_THIRST_GUI + currentShift, WIDTH_THIRST_GUI, currentLevel));
	levelThirst->setPosition(pos);
	window.draw(*levelThirst);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
void barMainFeatures::renderBar(int& current, int& max, sf::Sprite& sprite, Vector2f scale, sizeMainSprite &sizes, TextGame& textGame,
																sf::Vector2f& position, sf::RenderWindow& window)
{
	render(current, max, sprite, scale,
				sizes, position, window);
	renderText(current, max, scale,
						 position, window, textGame);
}


void barMainFeatures::render( int &current, int& max, Sprite &sprite, Vector2f scale,
														 sizeMainSprite &sizes, Vector2f &position, RenderWindow &window)
{

	bar->setPosition(position);
	bar->setScale(scale);
	window.draw(*bar);
	bar->setScale(normalSize);

	float level = float(current) / max;

	position.x += X_SHIFT_BARS * scale.x;
	position.y += Y_SHIFT_BARS * scale.y;
	int currentLevel = int(WIDTH_LEVEL_BAR_GUI * level);
	sprite.setTextureRect(IntRect(sizes.pixelPosX, sizes.pixelPosY, currentLevel, sizes.height));
	sprite.setPosition(position);
	sprite.setScale(scale);
	window.draw(sprite);
	sprite.setScale(normalSize);
}

void barMainFeatures::renderText(int &current, int& max, Vector2f scale,
																 Vector2f& position, RenderWindow& window, TextGame &textGame)
{
	Text* currentText = &textGame.texts[idText::levelBar];

	currentText->setString(toStringCharacter(current, max));

	int middleString = computeMiddleString(*currentText);

	// TODO
	//position.x -= middleString * scale.x;
	position.y -= (HEIGHT_BARS_GUI / 2) * scale.y;

	currentText->setPosition(position);

	//currentText->setScale(scale);
	window.draw(*currentText);
	//currentText->setScale(normalSize);
}

void barMainFeatures::renderTextEnemy(Enemy &enemy, int & current, int & max, int shift,
																			RenderWindow & window, TextGame & textGame)
{
	Text *currentText = &textGame.texts[idText::levelBar];
	Vector2f pos;
	pos = enemy.spriteEntity->getPosition();
	pos.y -= Y_SHIFT_BARS * scaleGuiForEnemy.y;
	pos.y -= enemy.height / 2 + scaleGuiForEnemy.y * HEIGHT_BARS_GUI * (2 + shift);


	currentText->setString(toStringCharacter(current, max));

	pos.x -= currentText->getString().getSize() * currentText->getCharacterSize() / 4;
	currentText->setPosition(pos);

	window.draw(*currentText);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void barMainFeatures::renderDamageForEnemy(Enemy &enemy, TextGame &textGame, RenderWindow &window, int shift)
{
	Text *currentText = &textGame.texts[idText::inputDamage];

	Vector2f pos;
	pos = enemy.spriteEntity->getPosition();
	pos.y -= enemy.height / 2 + scaleGuiForEnemy.y * HEIGHT_BARS_GUI * (3 + shift) + shiftEnemyDamage;

	// Если нанесли урон то отображаем
	int damage = enemy.damage.inputDamage;
	if (damage) {
		string stringDamage;
		intToString(damage, stringDamage);

		currentText->setString(stringDamage);


		pos.x -= currentText->getString().getSize() * currentText->getCharacterSize() / 4;
		currentText->setPosition(pos);
		window.draw(*currentText);
	}
}

void barMainFeatures::renderBarMainPerson(MainPerson &mainPerson, int &current, int &max, int shift, Sprite &sprite, sizeMainSprite &sizes,
																								Vector2f centerWindow, Vector2u sizeWindow,
																								TextGame &textGame, RenderWindow &window)
{
	Vector2f pos;
	pos.x = mainPerson.getXPos();
	pos.y += mainPerson.getYPos() - float(HEIGHT_BARS_GUI) * scaleGuiForEnemy.y * shift;

	renderBar(current, max, sprite, scaleGuiForMainPerson,
						sizes, textGame, pos, window);

}

void barMainFeatures::renderBarEnemy(Enemy &enemy, int &current, int &max, int shift, Sprite &sprite, sizeMainSprite &sizes,
																					TextGame &textGame, RenderWindow &window)
{
	int shiftBar = enemy.mana.maxMana > 0;
	Vector2f pos = enemy.spriteEntity->getPosition();
	pos.x -= scaleGuiForEnemy.x * WIDTH_BARS_GUI / 2;
	pos.y -= enemy.height / 2 + scaleGuiForEnemy.y * HEIGHT_BARS_GUI * (shift + shiftBar);


	renderDamageForEnemy(enemy, textGame, window, shiftBar);

	if(max)
	{
		renderBar(current, max, sprite, scaleGuiForEnemy,
												 sizes, textGame, pos, window);
	}
	
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
	itemInfoOverPanel.setPosition(position);
	window.draw(itemInfoOverPanel);
}

void panelQuickAccess::renderItems(::MainPerson& mainPerson, sf::Vector2f centerWindow,
																	 sf::Vector2u sizeWindow, ::sf::RenderWindow& window,
																	 TextGame &textGame, barMainFeatures &bars, itemFeatures &itemFeatures)
{
	Text *currentText;
	String nameCurrentItem = mainPerson.itemFromPanelQuickAccess[0].typeItem->features.name;
	String nameEmptyItem = mainPerson.emptyItem->typeItem->features.name;

	int startPosition = widthPanelQuickAccess / 2;
	for (int i = 0; i < AMOUNT_ACTIVE_SLOTS; i++) {

		nameCurrentItem = mainPerson.itemFromPanelQuickAccess[i].typeItem->features.name;
		if (nameCurrentItem != nameEmptyItem) {

			Item& currentItem = mainPerson.itemFromPanelQuickAccess[i];

			int shift = shiftSelect * i;
			Vector2f pos;
			pos = { centerWindow.x - startPosition + shift + SHIFT_START_ITEM_PANEL,
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
///////////////////////////////////////////////////////////////////////////////////////////////////////
void itemFeatures::renderNameItem(MainPerson& mainPerson, Vector2f& position, Vector2f centerWindow,
																			Vector2u sizeWindow, sf::RenderWindow& window, TextGame &textGame)
{
	String nameCurrentItem = mainPerson.itemFromPanelQuickAccess[mainPerson.idSelectItem].typeItem->features.name;
	Text *currentText = &textGame.texts[idText::itemGui];

	currentText->setString(nameCurrentItem);
	position = { centerWindow.x - WIDTH_ITEM_OVER_PANEL_INFO / 2 + SHIFT_FEATURES_PANEL,
		centerWindow.y + sizeWindow.y / 2 - heightPanelQuickAccess - HEIGHT_ITEM_OVER_PANEL_INFO / 2 };
	currentText->setPosition(position);
	std::cout << string(currentText->getString()) << std::endl;
	window.draw(*currentText);
}


void itemFeatures::renderValueMiddle(string string, Text* text, sf::Vector2f &position, RenderWindow &window)
{
	position.x += WIDTH_DAMAGE_GUI * SCALE_FEATURES.x;
	text->setString(string);
	text->setOrigin(string.size() / 2, text->getCharacterSize() / 2);
	text->setPosition(position);
	window.draw(*text);
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

	int startPosition = widthPanelQuickAccess / 2;
	int shift = shiftSelect * i;// TODO
	/////////////////////////////////////////////////////////////
	// Если предмет инструмент или оружие
	bool isDestroy = features->isDestroy;
	if (isDestroy) {
		pos = { centerWindow.x - startPosition + shift + SHIFT_START_ITEM_PANEL,
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


		renderIconWithScale(cutSprite, pos, window);
		renderValueMiddle(itemCut, currentText, pos, window);

		pos.x += computeSizeString(*currentText) + SHIFT_FEATURES_PANEL;
		renderIconWithScale(crashSprite, pos, window);
		renderValueMiddle(itemCrash, currentText, pos, window);
		//////////////////////////////////////////////////////////
		// Отображение характеристик

		pos.x += computeSizeString(*currentText) + SHIFT_FEATURES_PANEL;
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

		renderValueMiddle(itemToug, currentText, pos, window);
		//////////////////////////////////////////////////////////

}

///////////////////////////////////////////////////////////////////////////////////////////////////////
void GUI::setPositionGui(RenderWindow &window, MainPerson &mainPerson, vector<Enemy>& enemy, TextGame &textGame)
{

	Vector2f centerWindow = mainPerson.view->getCenter();
	Vector2u sizeWindow = window.getSize();
	Vector2f pos = { centerWindow.x + sizeWindow.x / 2 - widthInfo , centerWindow.y + sizeWindow.y / 2 - heightInfo};
	//////////////////////////////////////////////////////////
	// Окошко с информацией о выбранном предмете

	panels.infoAboutSelect.render(pos, window, textGame);
	renderTextDeath(mainPerson, centerWindow, window, textGame);
	//////////////////////////////////////////////////////////
	// Панель быстрого доступа
	pos = { centerWindow.x , centerWindow.y + sizeWindow.y / 2 - heightPanelQuickAccess / 2};// ИСПРАВЬ
	panels.panelQuickAccess.renderPanel(pos, window);
	panels.panelQuickAccess.renderSelect(mainPerson, centerWindow, sizeWindow, window);

	pos = { centerWindow.x, centerWindow.y + sizeWindow.y / 2 - heightPanelQuickAccess - Y_SHIFT_OUT_PANEL };
	panels.renderItemPanel(pos, window);

	panels.panelQuickAccess.renderItems(mainPerson, centerWindow, sizeWindow, window,
																			textGame, mainFeatures, itemFeatures);

	//////////////////////////////////////////////////////////////////////// 
	// Шкала здоровья
	sizeMainSprite sizes;
	sizes.init(WIDTH_LEVEL_BAR_GUI, HEIGHT_LEVEL_BAR_GUI, X_LEVEL_HEALTH_GUI, Y_LEVEL_HEALTH_GUI);

	int health = mainPerson.health.currentHealth;
	int healthMax = mainPerson.health.maxHealth;
	int shiftHealth = 3;
	mainFeatures.renderBarMainPerson(mainPerson, health, healthMax, shiftHealth, *mainFeatures.levelHealth,
																	 sizes, centerWindow, sizeWindow, textGame, window);

	////////////////////////////////////////////////////////////////
	// для противников
	int shiftBar;
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

			mainFeatures.renderBarEnemy(enemy[i], healthEnemy, healthMaxEnemy, shiftHelathEnemy, *mainFeatures.levelHealth,
																	sizes, textGame, window);
		}	

	}
	////////////////////////////////////////////////////////////////
	// Шкала выносливости
	sizes.init(0, HEIGHT_LEVEL_BAR_GUI, X_LEVEL_STAMINA_GUI, Y_LEVEL_STAMINA_GUI);

	int stamina = mainPerson.stamina.currentStamina;
	int staminaMax = mainPerson.stamina.maxStamina;
	int shiftStamina = 2;
	mainFeatures.renderBarMainPerson(mainPerson, stamina, staminaMax, shiftStamina, *mainFeatures.levelStamina,
																	 sizes, centerWindow, sizeWindow, textGame, window);


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
				mainFeatures.renderBarEnemy(enemy[i], staminaEnemy, staminaMaxEnemy, shiftStaminaEnemy, *mainFeatures.levelStamina,
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
	mainFeatures.renderBarMainPerson(mainPerson, mana, manaMax, shiftMana, *mainFeatures.levelMana,
																	 sizes, centerWindow, sizeWindow, textGame, window);


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
				mainFeatures.renderBarEnemy(enemy[i], manaEnemy, manaMaxEnemy, shiftManaEnemy, *mainFeatures.levelMana,
																		sizes, textGame, window);
			}

		}

	}

	////////////////////////////////////////////////////////////////////////
	hungry.renderBar(mainPerson.hungry.currentHungry, mainPerson.hungry.maxHungry, centerWindow, sizeWindow, window);
	thirst.renderBar(mainPerson.thirst.currentThirst, mainPerson.thirst.maxThirst, centerWindow, sizeWindow, window);
	////////////////////////////////////////////////////////////////////////

}