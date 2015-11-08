#include "MainPerson.h"
#include "ItemsVar.h"
#include "EntityVar.h"
#include "ListObjectsAndBlocks.h"
#include "Map.h"
#include "Font.h"

using namespace sf;
using namespace std;

////////////////////////////////////////////////////////////////////
// ���������� ���������
void initializeMainPerson(MainPerson & mainPerson, dataSound &databaseSound, Item &emptyItem, UnlifeObject &emptyObject, Enemy &emptyEnemy)
{
	mainPerson.spriteEntity = new Sprite;
	mainPerson.textureEntity = new Texture;

	// ������� �������
	mainPerson.size.init(32, 32);

	// ��������� ������� ���������
	mainPerson.radiusUse = 1;

	// �������� ������
	mainPerson.step.init(SPEED_ENTITY);
	mainPerson.animation.timeAnimation = 0.f;

	// ������
	int posX(64), posY(64);
	mainPerson.view = new View;
	mainPerson.view->setSize(640, 480);
	mainPerson.view->setCenter(posX, posY);

	// TODO
	sf::Listener::setUpVector(0.f, 1.f, 0.f);
	sf::Listener::setGlobalVolume(100.f);

	// ��������
	mainPerson.textureEntity->loadFromFile(texturePaths[idTexturePaths::mainPerson]);
	mainPerson.spriteEntity->setTexture(*mainPerson.textureEntity);
	mainPerson.spriteEntity->setTextureRect(IntRect(0, 0, mainPerson.size.width, mainPerson.size.height));
	// ����� 
	mainPerson.soundsEntity[idSoundEntity::stepGrass] = &databaseSound.sounds[idSoundEntity::stepGrass];
	mainPerson.soundsEntity[idSoundEntity::stepStone] = &databaseSound.sounds[idSoundEntity::stepStone];


	mainPerson.founds.init(&emptyItem, &emptyObject);
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

	entityAnimation &animation = mainPerson.animation;
	animation.timeAnimation = 0.f;
	animation.timeFightAnimation = 0.f;
	animation.currentTimeFightAnimation = 0.f;
	animation.timeOutputDamage = 1.f;

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
// ���������� ������
void MainPerson::updateView(RenderWindow & window)
{
	Vector2u sizeWindow = window.getSize();
	view->setSize(Vector2f(sizeWindow));// �������

	float tempX = getXPos();
	float tempY = getYPos();//��������� ����� ������ � ��������� ��, ����� ������ ����

	// TODO
	sf::Listener::setPosition(tempX, tempY, 0);

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

void MainPerson::attractionEnemy(Enemy *enemy, const Time &deltaTime)
{
	Vector2f personPoint = { getXPos(), getYPos() };
	Vector2f enemyPoint;
	Vector2f movemoment;
	float distanse;

	enemyPoint = enemy->spriteEntity->getPosition();

	distanse = distansePoints(personPoint, enemyPoint);
	// ���� ������
	Directions &directions = enemy->directions;
	entityAnimation &animation = enemy->animation;
	if (distanse <= RADIUSE_VIEW && currentLevelFloor == enemy->currentLevelFloor) {
		enemy->currenMode = idEntityMode::fight;
		if (distanse >= SIZE_BLOCK) {
			enemy->animation.currentTimeFightAnimation = 0.f;

			movemoment = vectorDirection(enemyPoint, personPoint);

			// TODO:
			float zero = SIZE_BLOCK / 2;

			bool xAboutZero = movemoment.x >= -zero && movemoment.x <= zero;
			bool yAboutZero = movemoment.y >= -zero && movemoment.y <= zero;

			if (movemoment.x > zero && movemoment.y > zero) {
				directions.directionWalk = DOWN_RIGHT;
				directions.directionLook = DOWN_RIGHT;
			}
			else if (movemoment.x < -zero && movemoment.y > zero) {
				directions.directionWalk = DOWN_LEFT;
				directions.directionLook = DOWN_LEFT;
			}
			else if (movemoment.x < -zero && movemoment.y < -zero) {
				directions.directionWalk = UP_LEFT;
				directions.directionLook = UP_LEFT;
			}
			else if (movemoment.x > zero && movemoment.y < zero) {
				directions.directionWalk = UP_RIGHT;
				directions.directionLook = UP_RIGHT;
			}
			else if (movemoment.y >= zero && xAboutZero) {
				directions.directionWalk = DOWN;
				directions.directionLook = DOWN;
			}
			else if (movemoment.y <= -zero && xAboutZero) {
				directions.directionWalk = UP;
				directions.directionLook = UP;
			}
			else if (movemoment.x >= zero && yAboutZero) {
				directions.directionWalk = RIGHT;
				directions.directionLook = RIGHT;
			}
			else if (movemoment.x <= -zero && yAboutZero) {
				directions.directionWalk = LEFT;
				directions.directionLook = LEFT;
			}
			else {
				directions.directionWalk = NONE_DIRECTION;
			}

			/*
			
			*/
		}
		else {
			//printf("vector %f %f\n", movemoment.x, movemoment.y);// TODO
			//printf("%f %d\n", distanse, enemy->directions.directionWalk);


			animation.currentTimeFightAnimation += deltaTime.asSeconds();
			if (animation.currentTimeFightAnimation > animation.timeOutputDamage) {
				animation.currentTimeFightAnimation = 0.f;
				givenForPersonDamage(*enemy);
			}
			currenMode = idEntityMode::fight;
			directions.directionWalk = NONE_DIRECTION;
		}

	}
	// ��� ������
	else {
		currenMode = idEntityMode::walk;
	}

}
////////////////////////////////////////////////////////////////////

void MainPerson::takeItem(Field &field, vector<Item> &items, float x, float y)
{
	if (founds.findItem->typeItem->features.name != founds.emptyItem->typeItem->features.name) {
		if (isInUseField(x, y, true)) {
			//////////////////////////////////////////////////////////////////////////////////////////////////////
			// ���� ���� �����
			if (isEmptySlot()) {


				////////////////////////////////////////////////////////////////////
				// ���� ����� �������
				int levelItem = items[founds.findItemFromList].currentLevel;

				Sprite *spriteItem = items[founds.findItemFromList].mainSprite;
				FloatRect objectItem = spriteItem->getGlobalBounds();

				if (objectItem.contains(x, y) && levelItem == currentLevelFloor + 1) {
					// ���������� � ���������
					//printf("added!1\n");
					itemFromPanelQuickAccess[emptySlot] = items[founds.findItemFromList];
					itemFromPanelQuickAccess[emptySlot].mainSprite->scale(normalSize);
					// ������� �� ����
					items.erase(items.begin() + founds.findItemFromList);
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
	if (currentItem.typeItem != founds.emptyItem->typeItem) {
		// ���������� �������


		Item* addItem = new Item;
		*addItem = itemFromPanelQuickAccess[idSelectItem];
		// ����� ������� ������������
		addItem->setPosition(getXPos() / SIZE_BLOCK, getYPos() / SIZE_BLOCK, currentLevelFloor + 1);
		Vector2f posHero = { getXPos() + size.width / 2, getYPos() + size.height / 2 };// ������ ������� �� � ������ �������
		addItem->mainSprite->setPosition(posHero);
		addItem->mainSprite->scale(scaleItems);
		items.push_back(*addItem);
		delete addItem;

		itemFromPanelQuickAccess[idSelectItem] = *founds.emptyItem;
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
				if (directions.directionWalk >= Direction::UP_LEFT) {
					// ����� �������� �� ��������� ���� ������ �������� �� ��������� � �����������
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

	// ������� ������� ����
	if (findEnemy != emptyEnemy //&& event.type == Event::MouseButtonPressed
			//&& event.type == Event::MouseMoved
			&& event.key.code == Mouse::Left) {

		if (isInUseField(xMouse, yMouse, true)) {
			if (findEnemy->currentLevelFloor == currentLevelFloor) {

				if (animation.currentTimeFightAnimation == 0.f) {
					currenMode = idEntityMode::fight;

					bool isDestroy = currentItem.typeItem->features.isDestroy;
					if (isDestroy) {
						currentItem.currentToughness -= 1;
					}

					//////////////////////////////////////////////////
					// ������ � ��������� ���������
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

						animation.currentTimeFightAnimation += deltaTime.asSeconds();
						// TODO
						//printf("Time %f\n", currentTimeFightAnimation);
						//if (currentTimeFightAnimation > timeOutputDamage) {
						//	currentTimeFightAnimation = 0;
						int cuttingDamage = currentItem.typeItem->damageItem.cuttingDamage;
						int crushingDamage = currentItem.typeItem->damageItem.crushingDamage;

						float cutDamage = damage.damageMultiplirer * currentItem.typeItem->damageItem.cuttingDamage;
						float crashDamage = damage.damageMultiplirer * currentItem.typeItem->damageItem.crushingDamage;

						cutDamage *= findEnemy->protection.protectionCut;
						crashDamage *= findEnemy->protection.protectionCrash;

						findEnemy->damage.inputDamage = cutDamage + crashDamage;
						findEnemy->health.currentHealth -= findEnemy->damage.inputDamage;

						findEnemy->damage.timeInputDamage = 0.f;
						//}

					}
					//////////////////////////////////////////////////



					if (itemFromPanelQuickAccess[idSelectItem].currentToughness < 1) {
						itemFromPanelQuickAccess[idSelectItem] = *founds.emptyItem;
					}



				}
				

			}

			//*/					
		}

	}
	// ���� ��� �� ���������
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
			switch (category) {
			////////////////////////////////////////////////////////////////////////
			// ���
		case idCategoryItem::food:
			if (event.key.code == Mouse::Right) {
				// �������� ������
				if (hungry.currentHungry < hungry.maxHungry) {
					hungry.currentHungry += currentItem.currentToughness;
					currentItem = *founds.emptyItem;
				}
			}
			break;
			////////////////////////////////////////////////////////////////////////
			// �������
		case idCategoryItem::bukketWithWater:
			if (thirst.currentThirst < thirst.maxThirst) {

				// ���� ���������� ����� � �����
				if (event.key.code == Mouse::Left) {
					int idUseBlock = currentItem.typeItem->idAdd.idBlockForUse;
					if (idUseBlock) {

						// �������� ������ �� �����
						int level = currentLevelFloor + 1;
						if (field.dataMap[level][y][x] == field.charBlocks[idBlocks::air]) {
							// �������� � ��� ���� ����� �� ������
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

				// �������� �����
				if (event.key.code == Mouse::Right) {
					thirst.currentThirst += currentItem.currentToughness;
				}

				if (event.key.code == Mouse::Left || event.key.code == Mouse::Right) {
					// ����������� �������
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
				// �������� �����
				if (thirst.currentThirst < thirst.maxThirst) {
					// �������� �����
					thirst.currentThirst += currentItem.currentToughness;

					// ����������� �������
					int *idItem = &currentItem.typeItem->features.id;
					int defineType = *idItem - 1;

					*idItem = defineType + 1;
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
					int idUseBlock = currentItem.typeItem->idAdd.idBlockForUse;
					if (idUseBlock) {
						if (field.dataMap[level][y][x] == field.charBlocks[idUseBlock]) {

							field.dataMap[level][y][x] = field.charBlocks[idBlocks::air];
							// ����������� �������
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
					int idUseBlock = currentItem.typeItem->idAdd.idBlockForUse;
					if (idUseBlock) {
						if (field.dataMap[level][y][x] == field.charBlocks[idUseBlock]) {

							// ����������� �������
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
			if (founds.findObject != founds.emptyObject) {
				if (isInListObjects(listObjects, sizeListObjects)) {

					currentItem.currentToughness -= 1;

					//////////////////////////////////////////////////
					// ��������� ���������
					Item* addItem = new Item;
					int countItem = founds.findObject->typeObject->drop.minCountItems.size();

					vector<int> &minAmount = founds.findObject->typeObject->drop.minCountItems;
					vector<int> &maxAmount = founds.findObject->typeObject->drop.maxCountItems;
					vector<int> &idItems = founds.findObject->typeObject->drop.dropItems;

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

					unlifeObjects->erase(unlifeObjects->begin() + founds.findObjectFromList);

					if (itemFromPanelQuickAccess[idSelectItem].currentToughness < 1) {
						currentItem = *founds.emptyItem;
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
					currentItem = *founds.emptyItem;
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

				int idUseBlock = currentItem.typeItem->idAdd.idBlockForUse;
				int idUseObject= currentItem.typeItem->idAdd.idUnlideOnjectForUse;
				// ������ ����
				if (idUseBlock > -1
						&& field.dataMap[level][y][x] == field.charBlocks[idBlocks::air]) {
					field.dataMap[level][y][x] = field.charBlocks[idUseBlock];
					successfullUse = true;
				}
				// ������� �����
				else if(idUseObject > -1){
					UnlifeObject* addObject = new UnlifeObject;

					addObject->setType(typesUnlifeObjects[idUseObject]);
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
						currentItem = *founds.emptyItem;
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
		if (founds.findObject->typeObject->name == listObjects[i]) {
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

	float dX = pos.x - spriteEntity->getPosition().x - size.width / 2;//������ , ����������� ������, ������� ���������� ������ � ������
	float dY = pos.y - spriteEntity->getPosition().y - size.height / 2;//�� ��, ���������� y
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