#include "MainPerson.h"
#include "ItemsVar.h"
#include "EntityVar.h"
#include "ListObjectsAndBlocks.h"
#include "Map.h"

using namespace sf;
using namespace std;

////////////////////////////////////////////////////////////////////
// ���������� ���������
void initializeMainPerson(MainPerson & mainPerson, dataSound &databaseSound, Item &emptyItem, UnlifeObject &emptyObject, Enemy &emptyEnemy)
{
	mainPerson.spriteEntity = new Sprite;
	mainPerson.textureEntity = new Texture;

	// ������� �������
	mainPerson.height = 32;
	mainPerson.width = 32;

	// ��������� ������� ���������
	mainPerson.radiusUse = 1;

	// �������� ������
	mainPerson.stepFirst = SPEED_ENTITY;
	mainPerson.stepCurrent = SPEED_ENTITY;
	mainPerson.timeAnimation = 0.f;

	// ������
	int posX(64), posY(64);
	mainPerson.view = new View;
	mainPerson.view->setSize(640, 480);
	mainPerson.view->setCenter(posX, posY);

	// ��������
	mainPerson.textureEntity->loadFromFile(texturePaths[idTexturePaths::mainPerson]);
	mainPerson.spriteEntity->setTexture(*mainPerson.textureEntity);
	mainPerson.spriteEntity->setTextureRect(IntRect(0, 0, mainPerson.width, mainPerson.height));

	// ����� 
	mainPerson.soundsEntity[idSoundEntity::stepGrass] = &databaseSound.sounds[idSoundEntity::stepGrass];
	mainPerson.soundsEntity[idSoundEntity::stepStone] = &databaseSound.sounds[idSoundEntity::stepStone];

	mainPerson.findItem = new Item;
	mainPerson.findObject = new UnlifeObject;

	// ������� ��������� ��� �����
	mainPerson.emptyObject = &emptyObject;
	mainPerson.emptyItem = &emptyItem;
	mainPerson.emptyEnemy = &emptyEnemy;
	mainPerson.idSelectItem = 0;

	// ������� � ��������� ������
	mainPerson.amountSlots = AMOUNT_ACTIVE_SLOTS;
	mainPerson.itemFromPanelQuickAccess = new Item[AMOUNT_ACTIVE_SLOTS];
	for (int i = 0; i < AMOUNT_ACTIVE_SLOTS; i++) {
		mainPerson.itemFromPanelQuickAccess[i].typeItem = emptyItem.typeItem;
	}

	// ������� � �����������
	mainPerson.currentLevelFloor = 0;
	mainPerson.currenMode = idEntityMode::walk;
	mainPerson.spriteEntity->setPosition(posX, posY);

	mainPerson.timeAnimation = 0.f;
	mainPerson.timeFightAnimation = 0.f;

	mainPerson.currentTimeOutputDamage = 0.f;
	mainPerson.timeOutputDamage = 1.f;

	mainPerson.direction = NONE;
	mainPerson.directionLook = DOWN;

	// ����������
	mainPerson.currentHealth = 45;
	mainPerson.currentStamina = 35;
	mainPerson.currentMana = 10;

	mainPerson.currentThirst = 5;
	mainPerson.currentHungry = 5;

	mainPerson.protectionCut = 1.5f;
	mainPerson.protectionCrash = 1.f;

	mainPerson.damageMultiplirer = 1;

}
////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
// ���������� ������
void MainPerson::updateView(RenderWindow & window)
{
	Vector2u sizeWindow = window.getSize();
	view->setSize(Vector2f(sizeWindow));// �������

	float tempX = getXPos();
	float tempY = getYPos();//��������� ����� ������ � ��������� ��, ����� ������ ����

	float x = getXPos();
	float y = getYPos();

	int leftBorder = sizeWindow.x / 2;
	int rightBorder = SIZE_BLOCK * (WIDTH_MAP - BORDER1) - sizeWindow.x / 2;
	int topBorder = sizeWindow.y / 2;
	int lowBorder = SIZE_BLOCK * LONG_MAP - sizeWindow.y / 2;

	if (x < leftBorder) tempX = leftBorder;//������� �� ���� ����� �������
	else if (x > rightBorder) tempX = rightBorder;//������� �� ���� ����� �������
	if (y < topBorder) tempY = topBorder;//������� �������
	else if (y > lowBorder) tempY = lowBorder;//������ �������	

	view->setCenter(tempX, tempY);
}

void MainPerson::givenForPersonDamage(Enemy &enemy)
{
	float cutDamage;
	float crashDamage;

	inputCutDamage = enemy.damageMultiplirer * enemy.cuttingDamage;
	inputCrashDamage = enemy.damageMultiplirer * enemy.crushingDamage;
	//float cutDamage = damageMultiplirer * currentItem.cuttingDamage;
	//float crashDamage = damageMultiplirer * currentItem.crushingDamage;

	inputCutDamage *= protectionCut;
	inputCrashDamage *= protectionCrash;

	inputDamage = inputCutDamage + inputCrashDamage;
	currentHealth -= inputDamage;

	inputDamage = 0;// TODO
}

void MainPerson::attractionEnemy(Enemy *enemy, const Time &deltaTime)
{
	Vector2f personPoint = { getXPos(), getYPos() };
	Vector2f enemyPoint;
	Vector2f movemoment;
	float distanse;

	enemyPoint = enemy->spriteEntity->getPosition();

	distanse = distansePoints(personPoint, enemyPoint);
	// ���� ������
	if (distanse <= RADIUSE_VIEW && currentLevelFloor == enemy->currentLevelFloor) {
		// �������� �� ��������
		atack = false;
		enemy->currenMode = idEntityMode::fight;
		if (distanse >= SIZE_BLOCK) {
			// �������� ����� ��������� �����
			atack = false;
			enemy->currentTimeOutputDamage = 0.f;

			movemoment = vectorDirection(enemyPoint, personPoint);

			//printf("vector %f %f\n", movemoment.x, movemoment.y);// TODO
			// TODO:
			float zero = SIZE_BLOCK / 2;

			bool xAboutZero = movemoment.x >= -zero && movemoment.x <= zero;
			bool yAboutZero = movemoment.y >= -zero && movemoment.y <= zero;

			if (movemoment.x > zero && movemoment.y > zero) {
				enemy->direction = DOWN_RIGHT;
				enemy->directionLook = DOWN_RIGHT;
			}
			else if (movemoment.x < -zero && movemoment.y > zero) {
				enemy->direction = DOWN_LEFT;
				enemy->directionLook = DOWN_LEFT;
			}
			else if (movemoment.x < -zero && movemoment.y < -zero) {
				enemy->direction = UP_LEFT;
				enemy->directionLook = UP_LEFT;
			}
			else if (movemoment.x > zero && movemoment.y < zero) {
				enemy->direction = UP_RIGHT;
				enemy->directionLook = UP_RIGHT;
			}
			else if (movemoment.y > zero && xAboutZero) {
				enemy->direction = DOWN;
				enemy->directionLook = DOWN;
			}
			else if (movemoment.y < -zero && xAboutZero) {
				enemy->direction = UP;
				enemy->directionLook = UP;
			}
			else if (movemoment.x > zero && yAboutZero) {
				enemy->direction = RIGHT;
				enemy->directionLook = RIGHT;
			}
			else if (movemoment.x < -zero && yAboutZero) {
				enemy->direction = LEFT;
				enemy->directionLook = LEFT;
			}
			else {
				enemy->direction = NONE;
			}

			/*
			
			*/
		}
		else {
			enemy->currenMode = idEntityMode::fight;
			enemy->currentTimeOutputDamage += deltaTime.asSeconds();
			if (enemy->currentTimeOutputDamage > enemy->timeOutputDamage) {
				enemy->currentTimeOutputDamage = 0;
				givenForPersonDamage(*enemy);
			}
			
			enemy->direction = NONE;
		}

	}
	// ��� ������
	else {
		enemy->currenMode = idEntityMode::walk;
	}

}
////////////////////////////////////////////////////////////////////

void MainPerson::takeItem(Field &field, vector<Item> &items, float x, float y)
{
	if (findItem->typeItem != emptyItem->typeItem) {
		if (isInUseField(x, y, true)) {
			//////////////////////////////////////////////////////////////////////////////////////////////////////
			// ���� ���� �����
			if (isEmptySlot()) {


				////////////////////////////////////////////////////////////////////
				// ���� ����� �������
				int levelItem = items[findItemFromList].currentLevel;

				Sprite *spriteItem = items[findItemFromList].mainSprite;
				FloatRect objectItem = spriteItem->getGlobalBounds();

				if (objectItem.contains(x, y) && levelItem == currentLevelFloor + 1) {
					// ���������� � ���������
					printf("added!1\n");
					itemFromPanelQuickAccess[emptySlot] = items[findItemFromList];
					itemFromPanelQuickAccess[emptySlot].mainSprite->scale(normalSize);
					// ������� �� ����
					items.erase(items.begin() + findItemFromList);
				}
				////////////////////////////////////////////////////////////////////


			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////
		}
	}
}

void MainPerson::throwItem(Field &field, vector<Item> &items)
{
	Item& currentItem = itemFromPanelQuickAccess[idSelectItem];
	if (currentItem.typeItem != emptyItem->typeItem) {
		// ���������� �������


		Item* addItem = new Item;
		*addItem = itemFromPanelQuickAccess[idSelectItem];
		// ����� ������� ������������
		addItem->setPosition(getXPos() / SIZE_BLOCK, getYPos() / SIZE_BLOCK, currentLevelFloor + 1);
		Vector2f posHero = { getXPos() + width / 2, getYPos() + height / 2 };// ������ ������� �� � ������ �������
		addItem->mainSprite->setPosition(posHero);
		addItem->mainSprite->scale(scaleItems);
		items.push_back(*addItem);
		delete addItem;

		itemFromPanelQuickAccess[idSelectItem] = *emptyItem;
	}
}

void MainPerson::interactionWitnUnlifeObject(vector<UnlifeObject> *unlifeObjects, const Time & deltaTime)// ������� for enity and mainPerson
{
	float dx(movement.x);
	float dy(movement.y);

	float x;
	float y;
	x = getXPos();
	y = getYPos();

	// �������� �� ����� �� �����
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
				if (direction >= Direction::UP_LEFT) {
					// ����� �������� �� ��������� ���� ������ �������� �� ��������� � �����������
					x -= DIAGONAL_SCALE_SPEED * dx * deltaTime.asSeconds();
					y -= DIAGONAL_SCALE_SPEED * dy * deltaTime.asSeconds();
				} else {
					x -= dx * deltaTime.asSeconds();
					y -= dy * deltaTime.asSeconds();
				}
				direction = Direction::NONE;
				break;
			} else if (entityBound.intersects(objectAltBound) && (levelUnlifeObject == currentLevelFloor + 1)) {
				transparentSpiteObject->setColor(TRANSPARENT_COLOR);
			} else {
				transparentSpiteObject->setColor(NORMAL_COLOR);
			}

		}
	} else {
		x = (int)getXPos();
		y = (int)getYPos();
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

	// ������� ������� ����
	if (findEnemy != emptyEnemy //&& event.type == Event::MouseButtonPressed
			//&& event.type == Event::MouseMoved
			&& event.key.code == Mouse::Left) {

		if (isInUseField(xMouse, yMouse, true)) {
			if (findEnemy->currentLevelFloor == currentLevelFloor) {

				if (currentItem.isDestroy) {
					currentItem.currentToughness -= 1;
				}

				//////////////////////////////////////////////////
				// ������ � ��������� ���������
				if (findEnemy->isDeath) {

					Item* addItem = new Item;
					TypeEnemy& typeEnemy = *findEnemy->type;
					int countItem = sizeof(typeEnemy.minCountItems) / sizeof(int);

					int* minAmount = typeEnemy.minCountItems;
					int* maxAmount = typeEnemy.maxCountItems;
					int* idItems = typeEnemy.dropItems;

					int currentAmount;
					for (int i = 0; i < countItem; i++) {

						currentAmount = minAmount[i] + rand() % (maxAmount[i] - minAmount[i] + 1);
						for (int j = 0; j < currentAmount; j++) {
							addItem->setType(typesItems[idItems[i]]);
							addItem->setPosition(x + 1, y + 1, currentLevelFloor + 1);
							items->push_back(*addItem);

						}

					}
					delete addItem;
					enemy->erase(enemy->begin() + findEnemyFromList);

				}
				//////////////////////////////////////////////////
				// ����� ������� ����
				else {
					
					currentTimeOutputDamage += deltaTime.asSeconds();
					// TODO
					//printf("Time %f\n", currentTimeOutputDamage);
					//if (currentTimeOutputDamage > timeOutputDamage) {
					//	currentTimeOutputDamage = 0;
						float cutDamage = damageMultiplirer * currentItem.cuttingDamage;
					float crashDamage = damageMultiplirer * currentItem.crushingDamage;

					cutDamage *= findEnemy->protectionCut;
					crashDamage *= findEnemy->protectionCrash;

					findEnemy->inputDamage = cutDamage + crashDamage;
					findEnemy->currentHealth -= findEnemy->inputDamage;

					findEnemy->timeInputDamage = 0.f;
					//}
					
				}
				//////////////////////////////////////////////////



				if (itemFromPanelQuickAccess[idSelectItem].currentToughness < 1) {
					itemFromPanelQuickAccess[idSelectItem] = *emptyItem;
				}


			}

			//*/					
		}

	}
	// ���� ��� �� ���������
	else {

		String* listObjects;
		wchar_t* listBlocks;
		int sizeListObjects;

		bool findTool = true;

		// useTool(mouse, world, currentItem);
		switch (currentItem.categoryItem) {
			////////////////////////////////////////////////////////////////////////
			// ������
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
			// �����
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
			// �����
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
			// ���� � ������� ������
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
			switch (currentItem.categoryItem) {
			////////////////////////////////////////////////////////////////////////
			// ���
		case idCategoryItem::food:
			if (event.key.code == Mouse::Right) {
				// �������� ������
				if (currentHungry < maxHungry) {
					currentHungry += currentItem.currentToughness;
					currentItem = *emptyItem;
				}
			}
			break;
			////////////////////////////////////////////////////////////////////////
			// �������
		case idCategoryItem::bukketWithWater:
			if (currentThirst < maxThirst) {

				// ���� ���������� ����� � �����
				if (event.key.code == Mouse::Left) {
					int fluid = currentItem.typeItem->idBlockForUse;
					if (fluid) {

						// �������� ������ �� �����
						int level = currentLevelFloor + 1;
						if (field.dataMap[level][y][x] == field.charBlocks[idBlocks::air]) {
							// �������� � ��� ���� ����� �� ������
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

				// �������� �����
				if (event.key.code == Mouse::Right) {
					currentThirst += currentItem.currentToughness;
				}

				if (event.key.code == Mouse::Left || event.key.code == Mouse::Right) {
					// ����������� �������
					int defineType = currentItem.typeItem->idItem - 1;
					currentItem.typeItem->idItem = defineType + 1;
					currentItem.setType(typesItems[defineType]);
					currentItem.mainSprite->scale(normalSize);

				}

			}
			break;
		case idCategoryItem::bottleWithWater:
			if (event.key.code == Mouse::Right) {
				// �������� �����
				if (currentThirst < maxThirst) {
					// �������� �����
					currentThirst += currentItem.currentToughness;

					// ����������� �������
					int defineType = currentItem.typeItem->idItem - 1;
					currentItem.typeItem->idItem = defineType + 1;
					currentItem.setType(typesItems[defineType]);
					currentItem.mainSprite->scale(normalSize);

				}
			}
			break;
			////////////////////////////////////////////////////////////////////////
			// �������
		case idCategoryItem::bukketEmpty:// �������
			if (isInUseField(xMouse, yMouse, true)) {
				// ���������� �������

				int level;
				// ���� ����
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
							// ����������� �������
							int defineType = currentItem.typeItem->idItem + 1;
							currentItem.typeItem->idItem = defineType - 1;
							currentItem.setType(typesItems[defineType]);
							currentItem.mainSprite->scale(normalSize);

						}
					}
				}

			}
			break;
		case idCategoryItem::bottleEmpty:// �������
			if (isInUseField(xMouse, yMouse, true)) {

				// ���������� �������

				int level;
				// ���� ����
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

							// ����������� �������
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
		default:
			break;
		}
		}
		

	}

}


////////////////////////////////////////////////////////////////////////////////////
// ������� ���������� ���������
void MainPerson::useTool(float &xMouse, float &yMouse, Event &event, Field &field,
												 String* listObjects, wchar_t* listBlocks, int &sizeListObjects,
												 Item &currentItem,
												 TypeItem *typesItems, vector<Item> *items, vector<UnlifeObject> *unlifeObjects) {
	if (isInUseField(xMouse, yMouse, true)) {
		if (event.type == Event::MouseButtonPressed) {

			int level;
			// ������� �����
			if (event.key.code == Mouse::Left) {
				level = currentLevelFloor + 1;
			}
			// ������� ���
			else if (event.key.code == Mouse::Right) {
				level = currentLevelFloor;
			}
			// ����� ������
			else {
				level = -1;
			}

			int x = xMouse / SIZE_BLOCK;
			int y = yMouse / SIZE_BLOCK;
			///*
			wchar_t* block = &field.dataMap[level][y][x];
			// ������ ����
			if (findObject != emptyObject) {
				if (isInListObjects(listObjects, sizeListObjects)) {

					currentItem.currentToughness -= 1;

					//////////////////////////////////////////////////
					// ��������� ���������
					Item* addItem = new Item;
					int countItem = sizeof(findObject->typeObject->minCountItems) / sizeof(int);

					int* minAmount = findObject->typeObject->minCountItems;
					int* maxAmount = findObject->typeObject->maxCountItems;
					int* idItems = findObject->typeObject->dropItems;

					int currentAmount;
					for (int i = 0; i < countItem; i++) {

						currentAmount = minAmount[i] + rand() % (maxAmount[i] - minAmount[i] + 1);
						for (int j = 0; j < currentAmount; j++) {
							addItem->setType(typesItems[idItems[i]]);
							addItem->setPosition(x + 1, y + 1, currentLevelFloor + 1);
							items->push_back(*addItem);

						}

					}
					delete addItem;
					//////////////////////////////////////////////////

					unlifeObjects->erase(unlifeObjects->begin() + findObjectFromList);

					if (itemFromPanelQuickAccess[idSelectItem].currentToughness < 1) {
						currentItem = *emptyItem;
					}


				}
			} else if (isInListBlocks(*block, listBlocks)) {
				currentItem.currentToughness -= 1;

				//////////////////////////////
				// ��������� ��������
				Item* addItem = new Item;

				addItem->setType(typesItems[field.findIdBlock(*block)]);
				addItem->setPosition(x + 1, y + 1, currentLevelFloor + 1);
				items->push_back(*addItem);

				delete addItem;
				//////////////////////////////

				*block = field.charBlocks[idBlocks::air];

				if (itemFromPanelQuickAccess[idSelectItem].currentToughness < 1) {
					currentItem = *emptyItem;
				}

			}
		}
	}
	
}

void MainPerson::useBlock(float & xMouse, float & yMouse, sf::Event & event, Field & field,
													Item & currentItem, TypeItem * typesItems, vector<Item>* items,
													TypeUnlifeObject * typesUnlifeObjects, vector<UnlifeObject>* unlifeObjects)
{
	if (isInUseField(xMouse, yMouse, false)) {
		if (event.type == Event::MouseButtonPressed) {

			int x = xMouse / SIZE_BLOCK;
			int y = yMouse / SIZE_BLOCK;

			int level;
			// ������������� �����
			if (event.key.code == Mouse::Left) {
				level = currentLevelFloor + 1;
			}
			// ������������� ���
			else if (event.key.code == Mouse::Right) {
				level = currentLevelFloor;
			}
			// ����� ������
			else {
				level = -1;
			}


			if (level > -1) {
				bool successfullUse;

				// ������ ����
				if (currentItem.typeItem->idBlockForUse > -1
						&& field.dataMap[level][y][x] == field.charBlocks[idBlocks::air]) {
					field.dataMap[level][y][x] = field.charBlocks[currentItem.typeItem->idBlockForUse];
					successfullUse = true;
				}
				// ������� �����
				else if(currentItem.typeItem->idUnlideOnjectForUse > -1){
					UnlifeObject* addObject = new UnlifeObject;

					addObject->setType(typesUnlifeObjects[currentItem.typeItem->idUnlideOnjectForUse]);
					addObject->setPosition(x + 1, y + 1, currentLevelFloor + 1);
					unlifeObjects->push_back(*addObject);

					delete addObject;
					successfullUse = true;
				}
				else
				{
					successfullUse = false;
				}
				
				////////////////////////////////
				// ���� ������� �������
				if (successfullUse) {
					// � ������ ������ ���������� ����������// �������
					currentItem.currentToughness -= 1;
					if (currentItem.currentToughness < 1) {
						currentItem = *emptyItem;
					}
				}
				////////////////////////////////
			}

		}
	}
}
////////////////////////////////////////////////////////////////////////////////////
// ����������� ���� ��� ���
bool MainPerson::isInListBlocks(wchar_t block, wchar_t *listBlocks) {
	int i = 0;
	while (listBlocks[i] != u'\0') {
		if (listBlocks[i] == block) {
			return true;
		}
		i++;
	}
	return false;
}
bool MainPerson::isInListObjects(String* listObjects, int sizeString) {
	for (size_t i = 0; i < sizeString; i++) {
		if (findObject->typeObject->name == listObjects[i]) {
			return true;
		}
	}
	return false;
}
////////////////////////////////////////////////////////////////////////////////////

// �������������� � ����������
void MainPerson::actionMain(Field &field, vector<UnlifeObject> *unlifeObjects, destroyObjectsAndBlocks& listDestroy,
														vector<Item> *items, float xPos, float yPos)
{
	if (isInUseField(xPos, yPos, true)) {
		/////////////////////////////////////////////////////////////////////////////
		// �������������� � �������
		if (currentLevelFloor >= 0 && currentLevelFloor < HEIGHT_MAP - 1) {
			// ���� ���� ��������
			int x = xPos / SIZE_BLOCK;
			int y = yPos / SIZE_BLOCK;
			if (wcschr(listDestroy.ladder, field.dataMap[currentLevelFloor + 1][y][x]) != NULL) {
				// ����� ����� ������� ���� � ��������
				spriteEntity->setPosition(x * SIZE_BLOCK, y * SIZE_BLOCK);
				currentLevelFloor += 1;

			}

		}
		/////////////////////////////////////////////////////////////////////////////
		// �������������� � ����������

		/////////////////////////////////////////////////////////////////////////////

	}
	
}

void MainPerson::actionAlternate(Field &field, vector<UnlifeObject> *unlifeObjects, destroyObjectsAndBlocks& listDestroy,
																 vector<Item> *items, float xPos, float yPos)
{
	if (isInUseField(xPos, yPos, true)) {
		/////////////////////////////////////////////////////////////////////////////
		// �������������� � �������
		if (currentLevelFloor >= 1) {
			int x = xPos / SIZE_BLOCK;
			int y = yPos / SIZE_BLOCK;
			// ���� ���� ��������
			if (wcschr(listDestroy.ladder, field.dataMap[currentLevelFloor][y][x]) != NULL) {
				// ����� ����� ������� ���� � ��������
				spriteEntity->setPosition(x * SIZE_BLOCK, y * SIZE_BLOCK);
				currentLevelFloor -= 1;

			}

		}
		/////////////////////////////////////////////////////////////////////////////
		// �������������� � ����������

		/////////////////////////////////////////////////////////////////////////////
	}
}

////////////////////////////////////////////////////////////////////
// ��������� ����� (�� ��������)
void MainPerson::computeAngle(RenderWindow &window)
{
	Vector2i pixelPos = Mouse::getPosition(window);//�������� ����� �������
	Vector2f pos = window.mapPixelToCoords(pixelPos);//��������� �� � ������� (������ �� ����� ����)

	float dX = pos.x - spriteEntity->getPosition().x - width / 2;//������ , ����������� ������, ������� ���������� ������ � ������
	float dY = pos.y - spriteEntity->getPosition().y - height / 2;//�� ��, ���������� y
	rotation = (atan2(dY, dX)) * 180 / PI;//�������� ���� � �������� � ��������� ��� � �������
}
////////////////////////////////////////////////////////////////////
// View
void MainPerson::getCoordinateForView(float x, float y)//������� ��� ���������� ��������� ������
{
	view->setCenter(x, y);//������ �� �������, ��������� ��� ����������. 
}

// �������� ���������� (�� ��������)
void MainPerson::viewmap(float time)
{
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		view->move(0.1*time, 0);//�������� ����� ������ (�� ����, ����� �� ������� ����� - �� ���� �����)
	}

	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		view->move(0, 0.1*time);//�������� ����� ���� (�� ����, ����� �� ������� ����� - �� ���� �����)
	}

	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		view->move(-0.1*time, 0);//�������� ����� ����� (�� ����, ����� �� ������� ����� - �� ���� �����)
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		view->move(0, -0.1*time);//�������� ����� ������ (�� ����, ����� �� ������� ����� - �� ���� �����)
	}

}
// �������� ���������� (�� ��������)
void MainPerson::changeview()
{
	if (Keyboard::isKeyPressed(Keyboard::U)) {
		view->zoom(1.0100f); //������������, ����������
							 //view.zoom(1.0006f); //���� ����� ����������� ��������������
	}

	if (Keyboard::isKeyPressed(Keyboard::R)) {
		//view.setRotation(90);//����� �� ������ ������� ������
		view->rotate(1);//���������� ������������ ������ (������������� �������� - � �������� �������)
	}


	if (Keyboard::isKeyPressed(Keyboard::I)) {
		view->setSize(640, 480);//������������� ������ ������ (��� ��������)
	}

	if (Keyboard::isKeyPressed(Keyboard::P)) {
		view->setSize(540, 380);//�������� ������ ������
	}

}
////////////////////////////////////////////////////////////////////