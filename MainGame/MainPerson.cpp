#include "MainPerson.h"
#include "ItemsVar.h"
#include "EntityVar.h"
#include "Map.h"
#include "Font.h"

using namespace sf;
using namespace std;

////////////////////////////////////////////////////////////////////
// Объявление персонажа
void initializeMainPerson(MainPerson & mainPerson, dataSound &databaseSound, Item &emptyItem, UnlifeObject &emptyObject, Enemy &emptyEnemy)
{
	mainPerson.spriteEntity = new Sprite;
	mainPerson.textureEntity = new Texture;

	// Задание размера
	mainPerson.size.init(32, 32);

	// Дальность подбора предметов
	mainPerson.radiusUse = 1;

	// Скорость ходьбы
	mainPerson.step.init(SPEED_ENTITY);
	mainPerson.animation.timeAnimation = 0.f;

	// Камера
	int posX(64), posY(64);
	mainPerson.view = new View;
	mainPerson.view->setSize(640, 480);
	mainPerson.view->setCenter(posX, posY);

	// TODO
	sf::Listener::setUpVector(0.f, 1.f, 0.f);
	sf::Listener::setGlobalVolume(100.f);

	// Текстура
	mainPerson.textureEntity->loadFromFile(texturePaths[idTexturePaths::mainPerson]);
	mainPerson.spriteEntity->setTexture(*mainPerson.textureEntity);
	mainPerson.spriteEntity->setTextureRect(IntRect(0, 0, mainPerson.size.width, mainPerson.size.height));

	mainPerson.initStepSounds(databaseSound);

	mainPerson.initFounds(emptyItem, emptyObject, emptyEnemy);

	// Создайм и заполняем панель
	mainPerson.idSelectItem = 0;
	mainPerson.amountSlots = AMOUNT_ACTIVE_SLOTS;
	mainPerson.itemFromPanelQuickAccess = new Item[AMOUNT_ACTIVE_SLOTS];
	for (int i = 0; i < AMOUNT_ACTIVE_SLOTS; i++) {
		mainPerson.itemFromPanelQuickAccess[i].typeItem = emptyItem.typeItem;
	}

	// Позиция и направление
	mainPerson.currentLevelFloor = 0;
	mainPerson.currenMode = idEntityMode::walk;
	mainPerson.spriteEntity->setPosition(posX, posY);

	entityAnimation &animation = mainPerson.animation;
	animation.init(1.5f, 1.f);

	Directions &directions = mainPerson.directions;
	directions.directionWalk = NONE_DIRECTION;
	directions.directionLook = DOWN;


	mainPerson.health.currentHealth = 45;
	mainPerson.stamina.currentStamina = 35;
	mainPerson.mana.currentMana = 10;

	mainPerson.thirst.currentThirst = 5;
	mainPerson.hungry.currentHungry = 5;

	entityProtection &protection = mainPerson.protection;
	protection.protectionCut = 1.5f;
	protection.protectionCrash = 1.f;

	mainPerson.damage.damageMultiplirer = 1;

}

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
// Обновление камеры
void MainPerson::updateView(RenderWindow & window)
{
	Vector2u sizeWindow = window.getSize();
	view->setSize(Vector2f(sizeWindow));// ИСПРАВЬ

	float tempX = getXPos();
	float tempY = getYPos();//считываем коорд игрока и проверяем их, чтобы убрать края

	// TODO
	sf::Listener::setPosition(tempX, tempY, 0);

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

void MainPerson::initFounds(::Item &item, UnlifeObject& object, ::Enemy& enemy)
{
	founds.init(&item, &object);
	emptyEnemy = &enemy;
}

void MainPerson::initStepSounds(dataSound& databaseSound)
{
	soundsEntity.push_back(&databaseSound.sounds[idSoundEntity::stepGrass]);
	soundsEntity.push_back(&databaseSound.sounds[idSoundEntity::stepStone]);
}

void MainPerson::givenForPersonDamage(Enemy &enemy)
{
	float cutDamage;
	float crashDamage;

	damage.inputCutDamage = enemy.damage.damageMultiplirer * enemy.damage.cuttingDamage;
	damage.inputCrashDamage = enemy.damage.damageMultiplirer * enemy.damage.crushingDamage;
	//float cutDamage = damageMultiplirer * currentItem.cuttingDamage;
	//float crashDamage = damageMultiplirer * currentItem.crushingDamage;

	damage.inputCutDamage *= protection.protectionCut;
	damage.inputCrashDamage *= protection.protectionCrash;

	damage.inputDamage = damage.inputCutDamage + damage.inputCrashDamage;
	health.currentHealth -= inputDamage;

	damage.inputDamage = 0;// TODO
}


void MainPerson::updateAtack(vector<Enemy> *enemy, vector<Item> *items, TypeItem *typesItems)
{
	Item& currentItem = itemFromPanelQuickAccess[idSelectItem];


	std::cout << string(findEnemy->type->name) << std::endl;
	if (currenMode == idEntityMode::atack
			&& findEnemy->type->name != emptyEnemy->type->name) {
		if (findEnemy->isDeath) {

			Item* addItem = new Item;
			TypeEnemy& typeEnemy = *findEnemy->type;
			int countItem = typeEnemy.drop.minCountItems.size();

			vector<int> &minAmount = typeEnemy.drop.minCountItems;
			vector<int> &maxAmount = typeEnemy.drop.maxCountItems;
			vector<int> &idItems = typeEnemy.drop.dropItems;

			int currentAmount;
			for (int i = 0; i < countItem; i++) {

				currentAmount = minAmount[i] + rand() % (maxAmount[i] - minAmount[i] + 2);
				for (int j = 0; j < currentAmount; j++) {
					addItem->setType(typesItems[typeEnemy.drop.dropItems[i]]);
					addItem->setPosition(founds.currentTarget.x + 1, founds.currentTarget.y + 1, currentLevelFloor + 1);
					items->push_back(*addItem);

				}

			}
			delete addItem;
			if (findEnemyFromList) {
				enemy->erase(enemy->begin() + findEnemyFromList);
			}
			else
			{
				enemy->clear();//TODO
			}


			if (itemFromPanelQuickAccess[idSelectItem].currentToughness < 1) {
				itemFromPanelQuickAccess[idSelectItem] = *founds.emptyItem;
			}
		} 
		else {
			printf("time %f != %f \n", animation.currentTimeFightAnimation, animation.timeFightAnimation);
			if (giveDamage) {
				findEnemy->takeDamage(damage, currentItem);
				animation.currentTimeFightAnimation = 0.f;
				printf("time!!!!!!!!!!!!!!!! %f\n", animation.currentTimeFightAnimation);
				currenMode = idEntityMode::walk;
				giveDamage = false;
				currentItem.currentToughness -= 1;
			}

		}
	}
}


void MainPerson::attractionEnemy(Enemy *enemy, const Time &deltaTime)
{
	Vector2f personPoint = { getXPos(), getYPos() };
	Vector2f enemyPoint;
	Vector2f movemoment;
	float distanse;

	enemyPoint = enemy->spriteEntity->getPosition();

	distanse = distansePoints(personPoint, enemyPoint);
	// Если увидел
	Directions &directions = enemy->directions;
	entityAnimation &animation = enemy->animation;
	if (distanse <= RADIUSE_VIEW && currentLevelFloor == enemy->currentLevelFloor) {
		enemy->currenMode = idEntityMode::fight;
		if (distanse >= SIZE_BLOCK) {
			enemy->animation.currentTimeFightAnimation = 0.f;

			movemoment = vectorDirection(enemyPoint, personPoint);
			findEnemy->choiceDirections(movemoment);

		}
		else {

			//animation.currentTimeFightAnimation += deltaTime.asSeconds();
			if (giveDamage) {
				animation.currentTimeFightAnimation = 0.f;
				giveDamage = false;
				givenForPersonDamage(*enemy);
			}
			currenMode = idEntityMode::atack;
			directions.directionWalk = NONE_DIRECTION;
		}

	}
	// Идём дальше
	else {
		currenMode = idEntityMode::walk;
	}

}
////////////////////////////////////////////////////////////////////

void MainPerson::interactionWitnUnlifeObject(vector<UnlifeObject> *unlifeObjects, const Time & deltaTime)// ИСПРАВЬ for enity and mainPerson
{
	float dx(movement.x);
	float dy(movement.y);

	float x;
	float y;
	x = getXPos();
	y = getYPos();

	// Проверка на выход за карту
	if (((x < (SIZE_BLOCK * WIDTH_MAP)) && (x >  0))
			&& (y < (SIZE_BLOCK * (LONG_MAP - 1)) && (y >  0))) {
		Sprite *spriteObject;
		FloatRect objectBound;

		int levelUnlifeObject;
		Sprite *transparentSpiteObject;
		FloatRect objectAltBound;
		FloatRect entityBound;

		vector<UnlifeObject> &objects = *unlifeObjects;
		for (int i = 0; i != objects.size(); ++i) {
			levelUnlifeObject = objects[i].currentLevel;

			spriteObject = objects[i].spriteObject;
			objectBound = spriteObject->getGlobalBounds();

			transparentSpiteObject = objects[i].transparentSpiteObject;
			objectAltBound = transparentSpiteObject->getGlobalBounds();
			entityBound = spriteEntity->getGlobalBounds();

			if (entityBound.intersects(objectBound) && (levelUnlifeObject == currentLevelFloor + 1)) {
				if (directions.directionWalk >= Direction::UP_LEFT) {
					// Чтобы скорость по диагонали была равной скорости по вертикали и горизонтали
					x -= DIAGONAL_SCALE_SPEED * dx * deltaTime.asSeconds();
					y -= DIAGONAL_SCALE_SPEED * dy * deltaTime.asSeconds();
				} else {
					x -= dx * deltaTime.asSeconds();
					y -= dy * deltaTime.asSeconds();
				}
				directions.directionWalk = NONE_DIRECTION;
				break;
			} else if (entityBound.intersects(objectAltBound) && (levelUnlifeObject == currentLevelFloor + 1)) {
				transparentSpiteObject->setColor(TRANSPARENT_COLOR);
			} else {
				transparentSpiteObject->setColor(NORMAL_COLOR);
			}

		}
	} else {
		x = int(getXPos());
		y = int(getYPos());
	}

	spriteEntity->setPosition(x, y);
	movement = { 0.f, 0.f };
}



void MainPerson::useItem(Field &field, destroyObjectsAndBlocks& listDestroy, const Time &deltaTime,
												 TypeItem *typesItems, TypeUnlifeObject *typesUnlifeObjects, vector<Enemy> *enemy,
												 vector<Item> *items, vector<UnlifeObject> *unlifeObjects, Event &event, float xMouse, float yMouse)
{
	Item& currentItem = itemFromPanelQuickAccess[idSelectItem];

	int x = xMouse / SIZE_BLOCK;
	int y = yMouse / SIZE_BLOCK;
	founds.currentTarget = { x, y };
	// Сначала наносим урон
	if (findEnemy != emptyEnemy //&& event.type == Event::MouseButtonPressed//&& event.type == Event::MouseMoved

			&& event.key.code == Mouse::Left) {

		if (isInUseField(xMouse, yMouse, true)) {
			if (findEnemy->currentLevelFloor == currentLevelFloor) {

				if (animation.currentTimeFightAnimation == 0.f) {
					currenMode = idEntityMode::atack;
				}

			}

		}


	}
	// Если это не противник
	else {

		currenMode = idEntityMode::walk;

		String* listObjects;
		wchar_t* listBlocks;
		int sizeListObjects;

		bool findTool = true;

		// useTool(mouse, world, currentItem);
		int category = currentItem.typeItem->features.category;
		switch (category) {
			////////////////////////////////////////////////////////////////////////
			// Лопата
		case idCategoryItem::backhoe:

			sizeListObjects = AMOUNT_BACKHOE_BREAKING_OBJECTS;
			listObjects = listDestroy.backoeBreakingObject;

			listBlocks = listDestroy.backoeBreakingBlock;

			// useBackhoe(mouse, world, currentItem);
			useTool(xMouse, yMouse, event, field,
							listObjects, listBlocks, sizeListObjects,
							currentItem,
							typesItems, items, unlifeObjects);

			break;
			////////////////////////////////////////////////////////////////////////
			// Кирка
		case idCategoryItem::pickax:
			sizeListObjects = AMOUNT_PICKAX_BREAKING_OBJECTS;
			listObjects = listDestroy.pickaxBreakingObject;

			listBlocks = listDestroy.pickaxBreakingBlock;

			useTool(xMouse, yMouse, event, field,
							listObjects, listBlocks, sizeListObjects,
							currentItem,
							typesItems, items, unlifeObjects);
			break;
			////////////////////////////////////////////////////////////////////////
			// Топор
		case idCategoryItem::axe:
			sizeListObjects = AMOUNT_AXE_BREAKING_OBJECTS;
			listObjects = listDestroy.axeBreakingObject;

			listBlocks = listDestroy.axeBreakingBlock;

			useTool(xMouse, yMouse, event, field,
							listObjects, listBlocks, sizeListObjects,
							currentItem,
							typesItems, items, unlifeObjects);
			break;
			////////////////////////////////////////////////////////////////////////
			// Блок и неживой объект
		case idCategoryItem::block:
		case idCategoryItem::unlifeObject:
			useBlock(xMouse, yMouse, event, field,
							 currentItem, typesItems, items,
							 typesUnlifeObjects, unlifeObjects);
			break;
			////////////////////////////////////////////////////////////////////////
		default:
			findTool = false;
			break;
		}

		if (findTool == false)
		{
			switch (category) {
			////////////////////////////////////////////////////////////////////////
			// Еда
		case idCategoryItem::food:
			if (event.key.code == Mouse::Right) {
				// Утоление голода
				if (hungry.currentHungry < hungry.maxHungry) {
					hungry.currentHungry += currentItem.currentToughness;
					currentItem = *founds.emptyItem;
				}
			}
			break;
			////////////////////////////////////////////////////////////////////////
			// Напитки
		case idCategoryItem::bukketWithWater:
			if (thirst.currentThirst < thirst.maxThirst) {

				// Если используем ведро с водой
				if (event.key.code == Mouse::Left) {
					int idUseBlock = currentItem.typeItem->idAdd.idBlockForUse;
					if (idUseBlock) {

						// Пытаемся вылить на землю
						int level = currentLevelFloor + 1;
						if (field.dataMap[level][y][x] == field.charBlocks[idBlocks::air]) {
							// Выливаем в яму если стена не мешает
							if (field.dataMap[level - 1][y][x] == field.charBlocks[idBlocks::air]) {
								field.dataMap[level - 1][y][x] = field.charBlocks[idUseBlock];
							}
							// 
							else {
								field.dataMap[level][y][x] = field.charBlocks[idUseBlock];
							}
						}


					}
				}

				// Утоление жажды
				if (event.key.code == Mouse::Right) {
					thirst.currentThirst += currentItem.currentToughness;
				}

				if (event.key.code == Mouse::Left || event.key.code == Mouse::Right) {
					// Опустошение бутылки
					int *idItem = &currentItem.typeItem->features.id;
					int defineType = *idItem - 1;

					*idItem = defineType + 1;

					currentItem.setType(typesItems[defineType]);
					currentItem.mainSprite->scale(normalSize);

				}

			}
			break;
		case idCategoryItem::bottleWithWater:
			if (event.key.code == Mouse::Right) {
				// Утоление жажды
				if (thirst.currentThirst < thirst.maxThirst) {
					// Утоление жажды
					thirst.currentThirst += currentItem.currentToughness;

					// Опустошение бутылки
					int *idItem = &currentItem.typeItem->features.id;
					int defineType = *idItem - 1;

					*idItem = defineType + 1;
					currentItem.setType(typesItems[defineType]);
					currentItem.mainSprite->scale(normalSize);

				}
			}
			break;
			////////////////////////////////////////////////////////////////////////
			// Бутылки
		case idCategoryItem::bukketEmpty:// ИСПРАВЬ
			if (isInUseField(xMouse, yMouse, true)) {
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
					int idUseBlock = currentItem.typeItem->idAdd.idBlockForUse;
					if (idUseBlock) {
						if (field.dataMap[level][y][x] == field.charBlocks[idUseBlock]) {

							field.dataMap[level][y][x] = field.charBlocks[idBlocks::air];
							// Опустошение бутылки
							int *idItem = &currentItem.typeItem->features.id;
							int defineType = *idItem + 1;

							*idItem = defineType - 1;
							currentItem.setType(typesItems[defineType]);
							currentItem.mainSprite->scale(normalSize);

						}
					}
				}

			}
			break;
		case idCategoryItem::bottleEmpty:// ИСПРАВЬ
			if (isInUseField(xMouse, yMouse, true)) {

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
					int idUseBlock = currentItem.typeItem->idAdd.idBlockForUse;
					if (idUseBlock) {
						if (field.dataMap[level][y][x] == field.charBlocks[idUseBlock]) {

							// Опустошение бутылки
							int *idItem = &currentItem.typeItem->features.id;
							int defineType = *idItem + 1;

							*idItem = defineType - 1;
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
		default:
			break;
		}
		}
		

	}

}



// Взаимодействие с лестницами
void MainPerson::actionMain(Field &field, vector<UnlifeObject> *unlifeObjects, destroyObjectsAndBlocks& listDestroy,
														vector<Item> *items, float xPos, float yPos)
{
	if (isInUseField(xPos, yPos, true)) {
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

void MainPerson::actionAlternate(Field &field, vector<UnlifeObject> *unlifeObjects, destroyObjectsAndBlocks& listDestroy,
																 vector<Item> *items, float xPos, float yPos)
{
	if (isInUseField(xPos, yPos, true)) {
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

	float dX = pos.x - spriteEntity->getPosition().x - size.width / 2;//вектор , колинеарный прямой, которая пересекает спрайт и курсор
	float dY = pos.y - spriteEntity->getPosition().y - size.height / 2;//он же, координата y
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