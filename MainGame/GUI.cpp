#include "GUI.h"

using namespace sf;
using namespace std;

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

	gui.textureBar = new Texture;
	// Шкала голода
	gui.lowHungry = new Sprite;
	gui.highHungry = new Sprite;
	gui.levelHungry = new Sprite;
	// Шкала жажды
	gui.bottle = new Sprite;
	gui.levelThirst = new Sprite;

	// Шкала здоровья
	gui.bar = new Sprite;
	gui.levelHealth = new Sprite;
	gui.levelStamina = new Sprite;
	gui.levelMana = new Sprite;
	///////////////////////////////////////////////////////////////////
	// Шкалы

	// добавление gui

	// Голода
	gui.textureBar->loadFromFile(texturePaths[idTexturePaths::bars]);

	gui.lowHungry->setTexture(*gui.textureBar);
	gui.lowHungry->setTextureRect(IntRect(X_HUNGY_GUI, Y_HUNGY_GUI, WIDTH_HUNGY_GUI, HEIGHT_HUNGY_GUI));

	gui.highHungry->setTexture(*gui.textureBar);
	gui.highHungry->setTextureRect(IntRect(X_HUNGY_GUI, Y_HUNGY_GUI + HEIGHT_HUNGY_GUI, WIDTH_HUNGY_GUI, HEIGHT_HUNGY_GUI));

	gui.levelHungry->setTexture(*gui.textureBar);
	gui.levelHungry->setTextureRect(IntRect(X_HUNGY_GUI, Y_HUNGY_GUI + HEIGHT_HUNGY_GUI * 2, WIDTH_HUNGY_GUI, LEVEL_HUNGY_GUI));

	// Жажды
	gui.bottle->setTexture(*gui.textureBar);
	gui.bottle->setTextureRect(IntRect(X_THIRST_GUI, Y_THIRST_GUI, WIDTH_THIRST_GUI, HEIGHT_THIRST_GUI));

	gui.levelThirst->setTexture(*gui.textureBar);
	gui.levelThirst->setTextureRect(IntRect(X_THIRST_GUI, Y_THIRST_GUI + HEIGHT_THIRST_GUI, WIDTH_THIRST_GUI, LEVEL_THIRST));

	// Здоровья
	gui.bar->setTexture(*gui.textureBar);
	gui.bar->setTextureRect(IntRect(X_HEALTH_GUI, Y_HEALTH_GUI, WIDTH_BARS_GUI, HEIGHT_BARS_GUI));

	gui.levelHealth->setTexture(*gui.textureBar);
	gui.levelHealth->setTextureRect(IntRect(X_LEVEL_HEALTH_GUI, Y_LEVEL_HEALTH_GUI, WIDTH_LEVEL_BAR_GUI, HEIGHT_LEVEL_BAR_GUI));

	gui.levelStamina->setTexture(*gui.textureBar);
	gui.levelStamina->setTextureRect(IntRect(X_LEVEL_STAMINA_GUI, Y_LEVEL_STAMINA_GUI, WIDTH_LEVEL_BAR_GUI, HEIGHT_LEVEL_BAR_GUI));

	gui.levelMana->setTexture(*gui.textureBar);
	gui.levelMana->setTextureRect(IntRect(X_LEVEL_MANA_GUI, Y_LEVEL_MANA_GUI, WIDTH_LEVEL_BAR_GUI, HEIGHT_LEVEL_BAR_GUI));


	///////////////////////////////////////////////////////////////////
	// ИСПРАВЬ
	// НЕРАБОТАЕТ
	//gui.textGui[idTextGui::infoWindowBlockGui] = &textGame.texts[idText::infoWindowBlock];
	//gui.textGui[idTextGui::infoWindowFloorGui] = &textGame.texts[idText::infoWindowFloor];
	//gui.textGui[idTextGui::infoWindowUnlifeObjectGui] = &textGame.texts[idText::infoWindowUnlifeObject];
	//gui.textGui[idTextGui::infoWindowItemGui] = &textGame.texts[idText::infoWindowItemGui];
}

void GUI::setPositionGui(RenderWindow &window, MainPerson &mainPerson, list<Enemy>& enemy, TextGame &textGame)
{

	Vector2f centerWindow = mainPerson.view->getCenter();
	////////////////////////////////////////////////////////////////////////
	// Окошко с информацией об указанном мышкой объекте

	// Определение позиции окошка
	Vector2u sizeWindow = window.getSize();
	Vector2f pos = { centerWindow.x + sizeWindow.x / 2 - widthInfo , centerWindow.y + sizeWindow.y / 2 - heightInfo};

	// Определение
	infoSelectBlockSprite->setPosition(pos);
	window.draw(*infoSelectBlockSprite);

	// Размещение текста
	Text* currentText = &textGame.texts[idText::infoWindowBlock];
	pos = { pos.x + shiftXInfoText , pos.y + shiftYInfoText };
	currentText->setPosition(pos);
	window.draw(*currentText);

	// Смещаем строку на размер букв предыдущей строки вниз
	currentText = &textGame.texts[idText::infoWindowFloor];
	pos.y += textGame.texts[idText::infoWindowBlock].getCharacterSize();
	currentText->setPosition(pos);
	window.draw(*currentText);

	currentText = &textGame.texts[idText::infoWindowUnlifeObject];
	pos.y += textGame.texts[idText::infoWindowFloor].getCharacterSize();
	currentText->setPosition(pos);
	window.draw(*currentText);

	currentText = &textGame.texts[idText::infoWindowItem];
	pos.y += textGame.texts[idText::infoWindowUnlifeObject].getCharacterSize();
	currentText->setPosition(pos);
	window.draw(*currentText);

	currentText = &textGame.texts[idText::infoEntity];
	pos.y += textGame.texts[idText::infoWindowItem].getCharacterSize();
	currentText->setPosition(pos);
	window.draw(*currentText);

	// Текст о смерти
	currentText = &textGame.texts[idText::mainPersonIsDeath];
	currentText->setPosition(centerWindow);
	if (mainPerson.isDeath) {
		window.draw(*currentText);
	}
	////////////////////////////////////////////////////////////////////////
	// Панель быстрого доступа
	pos = { centerWindow.x , centerWindow.y + sizeWindow.y / 2 - heightPanelQuickAccess / 2};// ИСПРАВЬ
	panelQuickAccess->setPosition(pos);
	window.draw(*panelQuickAccess);

	// Выбранный предмет
	int &idSelectItem = mainPerson.idSelectItem;
	int startPosition = widthPanelQuickAccess / 2;
	int shift = shiftSelect * idSelectItem;
	pos = { centerWindow.x - startPosition + shift, centerWindow.y + sizeWindow.y / 2 - heightPanelQuickAccess / 2};// ИСПРАВЬ

	selectInPanelQuickAccess->setPosition(pos);
	window.draw(*selectInPanelQuickAccess);

	for (int i = 0; i < AMOUNT_ACTIVE_SLOTS; i++) {
		if (mainPerson.itemFromPanelQuickAccess[i].typeItem->name != mainPerson.emptyItem->typeItem->name) {
			Item& currentItem = mainPerson.itemFromPanelQuickAccess[i];

			int shift = shiftSelect * (i);
			int shiftStart = 38;// ИСПРАВЬ
			pos = { centerWindow.x - startPosition + shift + shiftStart, centerWindow.y + sizeWindow.y / 2 - heightPanelQuickAccess / 2};// ИСПРАВЬ
			currentItem.mainSprite->setPosition(pos);
			window.draw(*currentItem.mainSprite);

			if (currentItem.isDestroy) {
				///*
				pos.x -= SIZE_ITEM / 2;
				pos.y += SIZE_ITEM / 2 - HEIGHT_BARS_GUI * 0.5 * scaleItems.y;

				bar->setPosition(pos);
				bar->setScale(scaleGuiForEnemy);
				window.draw(*bar);
				bar->setScale(normalSizeGuiForEnemy);

				float levelToughness = (float)currentItem.currentToughness / currentItem.typeItem->toughnessObject;// текущая на макс.

				pos.x += X_SHIFT_BARS * scaleGuiForEnemy.x;
				pos.y += Y_SHIFT_BARS * scaleGuiForEnemy.y;
				int currentToughness = WIDTH_LEVEL_BAR_GUI * levelToughness;
				levelStamina->setTextureRect(IntRect(X_LEVEL_STAMINA_GUI, Y_LEVEL_STAMINA_GUI, currentToughness, HEIGHT_LEVEL_BAR_GUI));
				levelStamina->setPosition(pos);

				levelStamina->setScale(scaleGuiForEnemy);
				window.draw(*levelStamina);
				levelStamina->setScale(normalSizeGuiForEnemy);
				//*/
			}
			

		}
	}

	//////////////////////////////////////////////////////////////////////// 
	// Шкала здоровья
	pos = centerWindow;

	pos.x -= sizeWindow.x / 2;
	pos.y += sizeWindow.y / 2 - (float)HEIGHT_BARS_GUI * 3;

	bar->setPosition(pos);
	window.draw(*bar);

	float level = (float)mainPerson.currentHealth / mainPerson.maxHealth;

	pos.x += X_SHIFT_BARS;
	pos.y += Y_SHIFT_BARS;
	int currentLevel = WIDTH_LEVEL_BAR_GUI * level;
	levelHealth->setTextureRect(IntRect(X_LEVEL_HEALTH_GUI, Y_LEVEL_HEALTH_GUI, currentLevel, HEIGHT_LEVEL_BAR_GUI));
	levelHealth->setPosition(pos);
	window.draw(*levelHealth);

	// для противников
	for (std::list<Enemy>::iterator it = enemy.begin(); it != enemy.end(); ++it) {
		if (it->currentLevelFloor == mainPerson.currentLevelFloor) {

			pos = it->spriteEntity->getPosition();
			pos.x -= scaleGuiForEnemy.x * WIDTH_BARS_GUI / 2;
			pos.y -= it->height / 2 + scaleGuiForEnemy.y * HEIGHT_BARS_GUI;


			bar->setPosition(pos);
			bar->setScale(scaleGuiForEnemy);
			window.draw(*bar);
			bar->setScale(normalSizeGuiForEnemy);

			level = (float)it->currentHealth / it->maxHealth;

			pos.x += X_SHIFT_BARS * scaleGuiForEnemy.x;
			pos.y += Y_SHIFT_BARS * scaleGuiForEnemy.y;
			currentLevel = WIDTH_LEVEL_BAR_GUI * level;
			levelHealth->setTextureRect(IntRect(X_LEVEL_HEALTH_GUI, Y_LEVEL_HEALTH_GUI, currentLevel, HEIGHT_LEVEL_BAR_GUI));
			levelHealth->setPosition(pos);

			levelHealth->setScale(scaleGuiForEnemy);
			window.draw(*levelHealth);
			levelHealth->setScale(normalSizeGuiForEnemy);

			/*
			// Отображение урона
			currentText = &textGame.texts[idText::inputDamage];

			string damage = "";
			char inputChar;
			int count = 0;

			//strrev(damage);
			// Запись
			do {
				inputChar = it->inputDamage % 10 + '0';
				damage[count] = inputChar;
				count++;
				it->inputDamage /= 10;
			} while (it->inputDamage > 0);

			// Перевёртыш
			for (size_t i = 0; i < count / 2; i++) {
				damage[i] = inputChar;
				damage[i] = damage[count - i];
				damage[count - i] = inputChar;
			}

			std::cout << "damage string " <<  damage << std::endl;
			currentText->setString((string)it->inputDamage);
			window.draw(*currentText);

			//window.draw(*game.items->item[i].spriteForUse);// ИСПРАВЬ
			//*/
		}

	}
	//////////////////////////////////////
	// Шкала выносливости
	pos = centerWindow;

	pos.x -= sizeWindow.x / 2;
	pos.y += sizeWindow.y / 2 - (float)HEIGHT_BARS_GUI * 2;

	bar->setPosition(pos);
	window.draw(*bar);

	level = (float)mainPerson.currentStamina / mainPerson.maxStamina;

	pos.x += X_SHIFT_BARS;
	pos.y += Y_SHIFT_BARS;
	currentLevel = WIDTH_LEVEL_BAR_GUI * level;
	levelStamina->setTextureRect(IntRect(X_LEVEL_STAMINA_GUI, Y_LEVEL_STAMINA_GUI, currentLevel, HEIGHT_LEVEL_BAR_GUI));
	levelStamina->setPosition(pos);
	window.draw(*levelStamina);
	//////////////////////////////////////
	// Шкала выносливости
	pos = centerWindow;

	pos.x -= sizeWindow.x / 2;
	pos.y += sizeWindow.y / 2 - (float)HEIGHT_BARS_GUI;

	bar->setPosition(pos);
	window.draw(*bar);

	level = (float)mainPerson.currentMana / mainPerson.maxMana;

	pos.x += X_SHIFT_BARS;
	pos.y += Y_SHIFT_BARS;
	currentLevel = WIDTH_LEVEL_BAR_GUI * level;
	levelMana->setTextureRect(IntRect(X_LEVEL_MANA_GUI, Y_LEVEL_MANA_GUI, currentLevel, HEIGHT_LEVEL_BAR_GUI));
	levelMana->setPosition(pos);
	window.draw(*levelMana);
	////////////////////////////////////////////////////////////////////////
	// Индикатор голода
	pos = centerWindow;
	pos.x -= sizeWindow.x / 2 - (float)WIDTH_BARS_GUI;
	pos.y += sizeWindow.y / 2 - (float)HEIGHT_HUNGY_GUI;

	// Верхняя часть тарелки
	highHungry->setPosition(pos);
	window.draw(*highHungry);

	// Уровень голода
	level = (float)mainPerson.currentHungry / mainPerson.maxHungry;

	pos.y += LEVEL_SHIFT_HUNGRY + MAX_SHIFT_HUNGRY_LEVEL * (1 - level);
	currentLevel = LEVEL_HUNGY_GUI * level;
	levelHungry->setTextureRect(IntRect(X_HUNGY_GUI, Y_HUNGY_GUI + HEIGHT_HUNGY_GUI * 2, WIDTH_HUNGY_GUI, currentLevel));
	levelHungry->setPosition(pos);
	window.draw(*levelHungry);

	// Дно тарелки
	pos = centerWindow;
	pos.x -= sizeWindow.x / 2 - (float)WIDTH_BARS_GUI;
	pos.y += sizeWindow.y / 2 - (float)HEIGHT_HUNGY_GUI;
	lowHungry->setPosition(pos);
	window.draw(*lowHungry);
	////////////////////////////////////////////////////////////////////////
	// Шкала жажды
	pos = centerWindow;
	pos.x -= sizeWindow.x / 2 - (float)WIDTH_BARS_GUI;
	pos.y += sizeWindow.y / 2 - (float)HEIGHT_HUNGY_GUI - (float)HEIGHT_THIRST_GUI;

	bottle->setPosition(pos);
	window.draw(*bottle);

	level = (float)mainPerson.currentThirst / mainPerson.maxThirst;

	pos.y += LEVEL_SHIFT_THIRST + LEVEL_THIRST * (1 - level);
	currentLevel = LEVEL_THIRST * level;
	int currentShift = LEVEL_THIRST * (1 - level);
	levelThirst->setTextureRect(IntRect(X_THIRST_GUI, Y_THIRST_GUI + HEIGHT_THIRST_GUI + currentShift, WIDTH_THIRST_GUI, currentLevel));
	levelThirst->setPosition(pos);
	window.draw(*levelThirst);
	////////////////////////////////////////////////////////////////////////

}