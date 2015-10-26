#include "MainPerson.h"

using namespace sf;
using namespace std;

////////////////////////////////////////////////////////////////////
// Объявление персонажа
void initializeMainPerson(MainPerson & mainPerson, dataSound &databaseSound, Item &emptyItem, UnlifeObject &emptyObject, Enemy &emptyEnemy)
{
	mainPerson.spriteEntity = new Sprite;
	mainPerson.textureEntity = new Texture;

	// Задание размера
	mainPerson.height = 36;
	mainPerson.width = 36;

	// Дальность подбора предметов
	mainPerson.radiusUse = 1;

	// Скорость ходьбы
	mainPerson.stepFirst = speedEntity;
	mainPerson.stepCurrent = speedEntity;
	mainPerson.timeAnimation = 0.f;

	// Камера
	int posX(70), posY(70);
	mainPerson.view = new View;
	mainPerson.view->setSize(640, 480);
	mainPerson.view->setCenter(posX, posY);

	// Текстура
	mainPerson.textureEntity->loadFromFile(texturePaths[idTexturePaths::mainPerson]);
	mainPerson.spriteEntity->setTexture(*mainPerson.textureEntity);
	mainPerson.spriteEntity->setTextureRect(IntRect(0, 0, mainPerson.width, mainPerson.height));

	// Звуки 
	mainPerson.soundsEntity[idSoundEntity::stepGrass] = &databaseSound.sounds[idSoundEntity::stepGrass];
	mainPerson.soundsEntity[idSoundEntity::stepStone] = &databaseSound.sounds[idSoundEntity::stepStone];

	mainPerson.findItem = new Item;
	mainPerson.findObject = new UnlifeObject;

	// Текущий выбранный тип блока
	mainPerson.emptyObject = &emptyObject;
	mainPerson.emptyItem = &emptyItem;
	mainPerson.emptyEnemy = &emptyEnemy;
	mainPerson.idSelectItem = 0;

	// Создайм и заполняем панель
	mainPerson.amountSlots = AMOUNT_ACTIVE_SLOTS;
	mainPerson.itemFromPanelQuickAccess = new Item[AMOUNT_ACTIVE_SLOTS];
	for (int i = 0; i < AMOUNT_ACTIVE_SLOTS; i++) {
		mainPerson.itemFromPanelQuickAccess[i].typeItem = emptyItem.typeItem;
	}

	// Позиция и направление
	mainPerson.currentLevelFloor = 0;
	mainPerson.currenMode = idModeEntity::build;
	mainPerson.spriteEntity->setPosition(posX, posY);
	mainPerson.direction = NONE;


	// Показатели
	mainPerson.currentHealth = 45;
	mainPerson.currentStamina = 45;
	mainPerson.currentMana = 45;

	mainPerson.currentThirst = 1;
	mainPerson.currentHungry = 1;

	mainPerson.damageMultiplirer = 1;

}
////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
// Обновление камеры
void MainPerson::updateView(RenderWindow & window)
{
	Vector2u sizeWindow = window.getSize();
	view->setSize((Vector2f)sizeWindow);// ИСПРАВЬ

	float tempX = getXPos();
	float tempY = getYPos();//считываем коорд игрока и проверяем их, чтобы убрать края

	float x = getXPos();
	float y = getYPos();

	int leftBorder = sizeWindow.x / 2;
	int rightBorder = SIZE_BLOCK * (WIDTH_MAP - BORDER1) - sizeWindow.x / 2;
	int topBorder = sizeWindow.y / 2;
	int lowBorder = SIZE_BLOCK * LONG_MAP - sizeWindow.y / 2;

	if (x < leftBorder) tempX = leftBorder;//убираем из вида левую сторону
	else if (x > rightBorder) tempX = rightBorder;//убираем из вида левую сторону
	if (y < topBorder) tempY = topBorder;//верхнюю сторону
	else if (y > lowBorder) tempY = lowBorder;//нижнюю сторону	

	view->setCenter(tempX, tempY);
}
////////////////////////////////////////////////////////////////////

void MainPerson::takeItem(Field &field, list<Item> &items, float x, float y)
{
	if (isInUseField(x, y)) {
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		// Если есть место
		if (isEmptySlot()) {

			for (std::list<Item>::iterator it = items.begin(); it != items.end(); ++it) {

				int level = it->currentLevel;
				////////////////////////////////////////////////////////////////////
				// Если нашли предмет
				if (isItem(x, y, items, findItem, findItemFromList, it, level)) {
					// Перемещаем в инвентарь
					printf("added!1\n");
					itemFromPanelQuickAccess[emptySlot] = *it;
					itemFromPanelQuickAccess[emptySlot].mainSprite->scale(normalSize);
					// Удаляем из мира
					items.erase(it);
					break;
				}
				////////////////////////////////////////////////////////////////////
			}

		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////
	}
}

void MainPerson::throwItem(Field &field, list<Item> &items)
{
	Item& currentItem = itemFromPanelQuickAccess[idSelectItem];
	if (currentItem.typeItem != emptyItem->typeItem) {
		// Определяем позицию


		Item* addItem = new Item;
		*addItem = itemFromPanelQuickAccess[idSelectItem];
		// Задаём уровень расположения
		addItem->setPosition(getXPos() / SIZE_BLOCK, getYPos() / SIZE_BLOCK, currentLevelFloor + 1);
		Vector2f posHero = { getXPos() + width / 2, getYPos() + height / 2 };// Начало отсчёта не в центре спрайта
		addItem->mainSprite->setPosition(posHero);
		addItem->mainSprite->scale(scaleItems);
		items.push_back(*addItem);
		delete addItem;

		itemFromPanelQuickAccess[idSelectItem] = *emptyItem;
	}
}

void MainPerson::useItem(Field &field, destroyObjectsAndBlocks& listDestroy, TypeItem *typesItems, list<Enemy> *enemy, list<Item> *items, list<UnlifeObject> *unlifeObjects, Event &event, float xMouse, float yMouse)
{
	Item& currentItem = itemFromPanelQuickAccess[idSelectItem];


	if (currentItem.typeItem != emptyItem->typeItem) {

		int x = xMouse / SIZE_BLOCK;
		int y = yMouse / SIZE_BLOCK;

		switch (currentItem.categoryItem) {
			////////////////////////////////////////////////////////////////////////
			// Еда
		case idCategoryItem::food:
			if (event.key.code == Mouse::Right) {
				// Утоление голода
				if (currentHungry < maxHungry) {
					currentHungry += currentItem.currentToughness;
					itemFromPanelQuickAccess[idSelectItem] = *emptyItem;
				}
			}
			break;
			////////////////////////////////////////////////////////////////////////
			// Напитки
		case idCategoryItem::bukketWithWater:	
			if (currentThirst < maxThirst) {

				// Если используем ведро с водой
				if (event.key.code == Mouse::Left) {
					int fluid = currentItem.typeItem->idBlockForUse;
					if (fluid) {

						// Пытаемся вылить на землю
						int level = currentLevelFloor + 1;
						if (field.dataMap[level][y][x] == field.charBlocks[idBlocks::air]) {
							// Выливаем в яму если стена не мешает
							if (field.dataMap[level - 1][y][x] == field.charBlocks[idBlocks::air]) {
								field.dataMap[level - 1][y][x] = field.charBlocks[fluid];
							}
							// 
							else {
								field.dataMap[level][y][x] = field.charBlocks[fluid];
							}
						}


					}
				}

				// Утоление жажды
				if (event.key.code == Mouse::Right) {
					currentThirst += currentItem.currentToughness;
				}

				if (event.key.code == Mouse::Left || event.key.code == Mouse::Right) {
					// Опустошение бутылки
					int defineType = currentItem.typeItem->idItem - 1;
					currentItem.typeItem->idItem = defineType + 1;
					currentItem.setType(typesItems[defineType]);
					currentItem.mainSprite->scale(normalSize);

				}

			}
			break;
		case idCategoryItem::bottleWithWater:
			if (event.key.code == Mouse::Right) {
				// Утоление жажды
				if (currentThirst < maxThirst) {
					// Утоление жажды
					currentThirst += currentItem.currentToughness;

					// Опустошение бутылки
					int defineType = currentItem.typeItem->idItem - 1;
					currentItem.typeItem->idItem = defineType + 1;
					currentItem.setType(typesItems[defineType]);
					currentItem.mainSprite->scale(normalSize);

				}
			}
			break;
			////////////////////////////////////////////////////////////////////////
			// Бутылки
		case idCategoryItem::bukketEmpty:// ИСПРАВЬ
			if (isInUseField(xMouse, yMouse)) {
				// Наполнение бутылки

				int level;
				// Берём воду
				if (event.key.code == Mouse::Left) {
					level = currentLevelFloor + 1;
				} else if (event.key.code == Mouse::Right) {
					level = currentLevelFloor;
				} else {
					level = -1;
				}


				if (level > -1) {
					int fluid = currentItem.typeItem->idBlockForUse;
					if (fluid) {
						if (field.dataMap[level][y][x] == field.charBlocks[fluid]) {

							field.dataMap[level][y][x] = field.charBlocks[idBlocks::air];
							// Опустошение бутылки
							int defineType = currentItem.typeItem->idItem + 1;
							currentItem.typeItem->idItem = defineType - 1;
							currentItem.setType(typesItems[defineType]);
							currentItem.mainSprite->scale(normalSize);

						}
					}
				}

			}
			break;
		case idCategoryItem::bottleEmpty:// ИСПРАВЬ
			if (isInUseField(xMouse, yMouse)) {

				// Наполнение бутылки

				int level;
				// Берём воду
				if (event.key.code == Mouse::Left) {
					level = currentLevelFloor + 1;
				} else if (event.key.code == Mouse::Right) {
					level = currentLevelFloor;
				} else {
					level = -1;
				}


				if (level > -1) {
					int fluid = currentItem.typeItem->idBlockForUse;
					if (fluid) {
						if (field.dataMap[level][y][x] == field.charBlocks[fluid]) {

							// Опустошение бутылки
							int defineType = currentItem.typeItem->idItem + 1;
							currentItem.typeItem->idItem = defineType - 1;
							currentItem.setType(typesItems[defineType]);
							currentItem.mainSprite->scale(normalSize);

						}
					}
				}


			}
			break;
			////////////////////////////////////////////////////////////////////////
		case idCategoryItem::other:
			break;
			////////////////////////////////////////////////////////////////////////
			// Блок
		case idCategoryItem::block:
			if (isInUseField(xMouse, yMouse)) {
				if (event.type == Event::MouseButtonPressed) {

					int level;
					// Устанавливаем стену
					if (event.key.code == Mouse::Left) {
						level = currentLevelFloor + 1;
					}
					// Устанавливаем пол
					else if (event.key.code == Mouse::Right) {
						level = currentLevelFloor;
					}
					// Иначе ничего
					else {
						level = -1;
					}


					if (level > -1) {
						// В данном случае обазначает количество// ИСПРАВЬ
						currentItem.currentToughness -= 1;
						// Ставим блок
						field.dataMap[level][y][x] = field.charBlocks[currentItem.typeItem->idBlockForUse];

						if (itemFromPanelQuickAccess[idSelectItem].currentToughness < 1) {
							itemFromPanelQuickAccess[idSelectItem] = *emptyItem;
						}
					}

				}
			}
			break;
			////////////////////////////////////////////////////////////////////////
			// Кирка
		case idCategoryItem::pickax:
			if (isInUseField(xMouse, yMouse)) {
				if (event.type == Event::MouseButtonPressed) {

					int level;
					// Удаляем стену
					if (event.key.code == Mouse::Left) {
						level = currentLevelFloor + 1;
					}
					// Удаляем пол
					else if (event.key.code == Mouse::Right) {
						level = currentLevelFloor;
					}
					// Иначе ничего
					else {
						level = -1;
					}

					///*
					wchar_t* block = &field.dataMap[level][y][x];
					// Ставим блок
					if (findObject != NULL) {
						if (isPickaxBreakingObject(listDestroy.pickaxBreakingObject)) {

							currentItem.currentToughness -= 1;

							unlifeObjects->erase(findObjectFromList);

							if (itemFromPanelQuickAccess[idSelectItem].currentToughness < 1) {
								itemFromPanelQuickAccess[idSelectItem] = *emptyItem;
							}
						}
					} else if (isPickaxBreakingBlock(*block, listDestroy.pickaxBreakingBlock)) {
						currentItem.currentToughness -= 1;

						//////////////////////////////
						// Выпадение предмета
						Item* addItem = new Item;

						addItem->setType(typesItems[field.findIdBlock(*block)]);
						addItem->setPosition(x, y, currentLevelFloor + 1);
						items->push_back(*addItem);

						delete addItem;
						//////////////////////////////

						*block = field.charBlocks[idBlocks::air];

						if (itemFromPanelQuickAccess[idSelectItem].currentToughness < 1) {
							itemFromPanelQuickAccess[idSelectItem] = *emptyItem;
						}

					}
					//*/					
				}
			}
			break;
			////////////////////////////////////////////////////////////////////////
			// Топор
		case idCategoryItem::axe:
			if (isInUseField(xMouse, yMouse)) {
				if (event.type == Event::MouseButtonPressed) {

					int level;
					// Удаляем стену
					if (event.key.code == Mouse::Left) {
						level = currentLevelFloor + 1;
					}
					// Удаляем пол
					else if (event.key.code == Mouse::Right) {
						level = currentLevelFloor;
					}
					// Иначе ничего
					else {
						level = -1;
					}

					///*
					wchar_t* block = &field.dataMap[level][y][x];
					// Ставим блок
					if (findObject != NULL) {
						if (isAxeBreakingObject(listDestroy.axeBreakingObject)) {

							currentItem.currentToughness -= 1;

							//////////////////////////////////////////////////
							// Выпадение предметов
							Item* addItem = new Item;
							int countItem = sizeof(findObjectFromList->typeObject->minCountItems) / sizeof(int);

							int* minAmount = findObjectFromList->typeObject->minCountItems;
							int* maxAmount = findObjectFromList->typeObject->maxCountItems;
							int* idItems = findObjectFromList->typeObject->dropItems;

							int currentAmount;
							for (int i = 0; i < countItem; i++) {

								currentAmount = minAmount[i] + rand() % (maxAmount[i] - minAmount[i] + 1);
								for (int j = 0; j < currentAmount; j++) {
									addItem->setType(typesItems[idItems[i]]);
									addItem->setPosition(x, y, currentLevelFloor + 1);
									items->push_back(*addItem);

								}

							}
							delete addItem;
							//////////////////////////////////////////////////

							unlifeObjects->erase(findObjectFromList);

							if (itemFromPanelQuickAccess[idSelectItem].currentToughness < 1) {
								itemFromPanelQuickAccess[idSelectItem] = *emptyItem;
							}


						}
					} else if (isAxeBreakingBlock(*block, listDestroy.axeBreakingBlock)) {
						currentItem.currentToughness -= 1;


						//////////////////////////////
						// Выпадение предмета
						Item* addItem = new Item;

						addItem->setType(typesItems[field.findIdBlock(*block)]);
						addItem->setPosition(x, y, currentLevelFloor + 1);
						items->push_back(*addItem);

						delete addItem;
						//////////////////////////////

						*block = field.charBlocks[idBlocks::air];

						if (itemFromPanelQuickAccess[idSelectItem].currentToughness < 1) {
							itemFromPanelQuickAccess[idSelectItem] = *emptyItem;
						}

					}
					//*/					
				}
			}
			break;
			////////////////////////////////////////////////////////////////////////
			// Оружие
		case idCategoryItem::weapon:
			if (isInUseField(xMouse, yMouse)) {
				if (event.key.code == Mouse::Left) {

					if (findEnemy != NULL) {
						if (findEnemy->currentLevelFloor == currentLevelFloor) {

							currentItem.currentToughness -= 1;

							//////////////////////////////////////////////////
							// Выпадение предметов
							Item* addItem = new Item;
							TypeEnemy& typeEnemy = *findEnemyFromList->type;
							int countItem = sizeof(typeEnemy.minCountItems) / sizeof(int);

							int* minAmount = typeEnemy.minCountItems;
							int* maxAmount = typeEnemy.maxCountItems;
							int* idItems = typeEnemy.dropItems;

							int currentAmount;
							for (int i = 0; i < countItem; i++) {

								currentAmount = minAmount[i] + rand() % (maxAmount[i] - minAmount[i] + 1);
								for (int j = 0; j < currentAmount; j++) {
									addItem->setType(typesItems[idItems[i]]);
									addItem->setPosition(x, y, currentLevelFloor + 1);
									items->push_back(*addItem);

								}

							}
							delete addItem;
							//////////////////////////////////////////////////

							enemy->erase(findEnemyFromList);

							if (itemFromPanelQuickAccess[idSelectItem].currentToughness < 1) {
								itemFromPanelQuickAccess[idSelectItem] = *emptyItem;
							}


						}
					}
					//*/					
				}
			}
			break;
			////////////////////////////////////////////////////////////////////////
		default:
			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////
// Разрушаемый блок или нет
bool MainPerson::isAxeBreakingBlock(wchar_t block, wchar_t *axeBreakingBlocks) {
	int i = 0;
	while (axeBreakingBlocks[i] != u'\0') {
		if (axeBreakingBlocks[i] == block) {
			return true;
		}
		i++;
	}
	return false;
}
bool MainPerson::isAxeBreakingObject(String* axeBreakingObject) {
	for (size_t i = 0; i < AMOUNT_AXE_BREAKING_OBJECTS; i++) {
		if (findObject->typeObject->name == axeBreakingObject[i]) {
			return true;
		}
	}
	return false;
}
bool MainPerson::isPickaxBreakingBlock(wchar_t block, wchar_t *pickaxBreakingBlocks) {
	int i = 0;
	while (pickaxBreakingBlocks[i] != u'\0') {
		if (pickaxBreakingBlocks[i] == block) {
			return true;
		}
		i++;
	}
	return false;
}
bool MainPerson::isPickaxBreakingObject(String* pickaxBreakingObject) {
	for (size_t i = 0; i < AMOUNT_PICKAX_BREAKING_OBJECTS; i++) {
		std::cout << (string)pickaxBreakingObject[i] << "pix" << std::endl;
		if (findObject->typeObject->name == pickaxBreakingObject[i]) {
			return true;
		}
	}
	return false;
}
////////////////////////////////////////////////////////////////////////////////////

// Взаимодействие с лестницами
void MainPerson::actionMain(Field &field, list<UnlifeObject> *unlifeObjects, destroyObjectsAndBlocks& listDestroy, list<Item> *items, float xPos, float yPos)
{
	if (isInUseField(xPos, yPos)) {
		/////////////////////////////////////////////////////////////////////////////
		// Взаимодейстиве с блоками
		if (currentLevelFloor >= 0 && currentLevelFloor < HEIGHT_MAP - 1) {
			// Если блок лестница
			int x = xPos / SIZE_BLOCK;
			int y = yPos / SIZE_BLOCK;
			if (wcschr(listDestroy.ladder, field.dataMap[currentLevelFloor + 1][y][x]) != NULL) {
				// Чтобы точка отсчёта была у лестницы
				spriteEntity->setPosition(x * SIZE_BLOCK, y * SIZE_BLOCK);
				currentLevelFloor += 1;

			}

		}
		/////////////////////////////////////////////////////////////////////////////
		// Взаимодейстиве с предметами

		/////////////////////////////////////////////////////////////////////////////

	}
	
}

void MainPerson::actionAlternate(Field &field, list<UnlifeObject> *unlifeObjects, destroyObjectsAndBlocks& listDestroy, list<Item> *items, float xPos, float yPos)
{
	if (isInUseField(xPos, yPos)) {
		/////////////////////////////////////////////////////////////////////////////
		// Взаимодейстиве с блоками
		if (currentLevelFloor >= 1) {
			int x = xPos / SIZE_BLOCK;
			int y = yPos / SIZE_BLOCK;
			// Если блок лестница
			if (wcschr(listDestroy.ladder, field.dataMap[currentLevelFloor][y][x]) != NULL) {
				// Чтобы точка отсчёта была у лестницы
				spriteEntity->setPosition(x * SIZE_BLOCK, y * SIZE_BLOCK);
				currentLevelFloor -= 1;

			}

		}
		/////////////////////////////////////////////////////////////////////////////
		// Взаимодейстиве с предметами

		/////////////////////////////////////////////////////////////////////////////
	}
}

////////////////////////////////////////////////////////////////////
// Использую потом (не ВКЛЮЧЕНА)
void MainPerson::computeAngle(RenderWindow &window)
{
	Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
	Vector2f pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)

	float dX = pos.x - spriteEntity->getPosition().x - width / 2;//вектор , колинеарный прямой, которая пересекает спрайт и курсор
	float dY = pos.y - spriteEntity->getPosition().y - height / 2;//он же, координата y
	rotation = (atan2(dY, dX)) * 180 / PI;//получаем угол в радианах и переводим его в градусы
}
////////////////////////////////////////////////////////////////////
// View
void MainPerson::getCoordinateForView(float x, float y)//функция для считывания координат игрока
{
	view->setCenter(x, y);//следим за игроком, передавая его координаты. 
}

// Возможно пригодится (не ВКЛЮЧЕНА)
void MainPerson::viewmap(float time)
{
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		view->move(0.1*time, 0);//скроллим карту вправо (см урок, когда мы двигали героя - всё тоже самое)
	}

	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		view->move(0, 0.1*time);//скроллим карту вниз (см урок, когда мы двигали героя - всё тоже самое)
	}

	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		view->move(-0.1*time, 0);//скроллим карту влево (см урок, когда мы двигали героя - всё тоже самое)
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		view->move(0, -0.1*time);//скроллим карту вправо (см урок, когда мы двигали героя - всё тоже самое)
	}

}
// Возможно пригодится (не ВКЛЮЧЕНА)
void MainPerson::changeview()
{
	if (Keyboard::isKeyPressed(Keyboard::U)) {
		view->zoom(1.0100f); //масштабируем, уменьшение
							 //view.zoom(1.0006f); //тоже самое помедленнее соответственно
	}

	if (Keyboard::isKeyPressed(Keyboard::R)) {
		//view.setRotation(90);//сразу же задает поворот камере
		view->rotate(1);//постепенно поворачивает камеру (отрицательное значение - в обратную сторону)
	}


	if (Keyboard::isKeyPressed(Keyboard::I)) {
		view->setSize(640, 480);//устанавливает размер камеры (наш исходный)
	}

	if (Keyboard::isKeyPressed(Keyboard::P)) {
		view->setSize(540, 380);//например другой размер
	}

}
////////////////////////////////////////////////////////////////////