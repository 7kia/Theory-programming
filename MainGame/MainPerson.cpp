#include "MainPerson.h"

using namespace sf;
using namespace std;

////////////////////////////////////////////////////////////////////
// ���������� ���������
void initializeMainPerson(MainPerson & mainPerson, dataSound &databaseSound, Item &emptyItem, UnlifeObject &emptyObject, Enemy &emptyEnemy)
{
	mainPerson.spriteEntity = new Sprite;
	mainPerson.textureEntity = new Texture;

	// ������� �������
	mainPerson.height = 36;
	mainPerson.width = 36;

	// ��������� ������� ���������
	mainPerson.radiusUse = 1;

	// �������� ������
	mainPerson.stepFirst = speedEntity;
	mainPerson.stepCurrent = speedEntity;
	mainPerson.timeAnimation = 0.f;

	// ������
	int posX(70), posY(70);
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
	mainPerson.currenMode = idModeEntity::build;
	mainPerson.spriteEntity->setPosition(posX, posY);
	mainPerson.direction = NONE;


	// ����������
	mainPerson.currentHealth = 45;
	mainPerson.currentStamina = 45;
	mainPerson.currentMana = 45;

	mainPerson.currentThirst = 1;
	mainPerson.currentHungry = 1;

}
////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
// ���������� ������
void MainPerson::updateView(RenderWindow & window)
{
	Vector2u sizeWindow = window.getSize();
	view->setSize((Vector2f)sizeWindow);// �������

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
////////////////////////////////////////////////////////////////////

void MainPerson::takeItem(Field &field, list<Item> &items, float x, float y)
{
	if (isInUseField(x, y)) {
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		// ���� ���� �����
		if (isEmptySlot()) {

			for (std::list<Item>::iterator it = items.begin(); it != items.end(); ++it) {

				int level = it->currentLevel;
				////////////////////////////////////////////////////////////////////
				// ���� ����� �������
				if (isItem(x, y, items, findItem, findItemFromList, it, level)) {
					// ���������� � ���������
					printf("added!1\n");
					itemFromPanelQuickAccess[emptySlot] = *it;
					itemFromPanelQuickAccess[emptySlot].mainSprite->scale(normalSize);
					// ������� �� ����
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

void MainPerson::useItem(Field &field, destroyObjectsAndBlocks& listDestroy, TypeItem *typesItems, list<UnlifeObject> *unlifeObjects, Event &event, float xMouse, float yMouse)
{
	Item& currentItem = itemFromPanelQuickAccess[idSelectItem];


	if (currentItem.typeItem != emptyItem->typeItem) {

		int x = xMouse / SIZE_BLOCK;
		int y = yMouse / SIZE_BLOCK;

		switch (currentItem.categoryItem) {
			////////////////////////////////////////////////////////////////////////
			// ���
		case idCategoryItem::food:
			if (event.key.code == Mouse::Right) {
				// �������� ������
				if (currentHungry < maxHungry) {
					currentHungry += currentItem.currentToughness;
					itemFromPanelQuickAccess[idSelectItem] = *emptyItem;
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
			if (isInUseField(xMouse, yMouse)) {
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
			if (isInUseField(xMouse, yMouse)) {

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
			////////////////////////////////////////////////////////////////////////
			// ����
		case idCategoryItem::block:
			if (isInUseField(xMouse, yMouse)) {
				if (event.type == Event::MouseButtonPressed) {

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
						// � ������ ������ ���������� ����������// �������
						currentItem.currentToughness -= 1;
						// ������ ����
						field.dataMap[level][y][x] = field.charBlocks[currentItem.typeItem->idBlockForUse];

						if (itemFromPanelQuickAccess[idSelectItem].currentToughness < 1) {
							itemFromPanelQuickAccess[idSelectItem] = *emptyItem;
						}
					}

				}
			}
			break;
			////////////////////////////////////////////////////////////////////////
			// �����
		case idCategoryItem::pickax:
			if (isInUseField(xMouse, yMouse)) {
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

					///*
					// ������ ����
					if (findObject != NULL) {
						if (isPickaxBreakingObject(listDestroy.pickaxBreakingObject)) {

							currentItem.currentToughness -= 1;

							unlifeObjects->erase(findObjectFromList);

							if (itemFromPanelQuickAccess[idSelectItem].currentToughness < 1) {
								itemFromPanelQuickAccess[idSelectItem] = *emptyItem;
							}
						}
					} else if (isPickaxBreakingBlock(field.dataMap[level][y][x], listDestroy.pickaxBreakingBlock)) {
						currentItem.currentToughness -= 1;

						field.dataMap[level][y][x] = field.charBlocks[idBlocks::air];

						if (itemFromPanelQuickAccess[idSelectItem].currentToughness < 1) {
							itemFromPanelQuickAccess[idSelectItem] = *emptyItem;
						}

					}
					//*/					
				}
			}
			break;
			////////////////////////////////////////////////////////////////////////
			// �����
		case idCategoryItem::axe:
			if (isInUseField(xMouse, yMouse)) {
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

					///*
					// ������ ����
					if (findObject != NULL) {
						if (isAxeBreakingObject(listDestroy.axeBreakingObject)) {

							currentItem.currentToughness -= 1;

							unlifeObjects->erase(findObjectFromList);

							if (itemFromPanelQuickAccess[idSelectItem].currentToughness < 1) {
								itemFromPanelQuickAccess[idSelectItem] = *emptyItem;
							}


						}
					} else if (isAxeBreakingBlock(field.dataMap[level][y][x], listDestroy.axeBreakingBlock)) {
						currentItem.currentToughness -= 1;

						field.dataMap[level][y][x] = field.charBlocks[idBlocks::air];

						if (itemFromPanelQuickAccess[idSelectItem].currentToughness < 1) {
							itemFromPanelQuickAccess[idSelectItem] = *emptyItem;
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
// ����������� ���� ��� ���
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

// �������������� � ����������
void MainPerson::actionMain(Field &field, list<UnlifeObject> *unlifeObjects, destroyObjectsAndBlocks& listDestroy, list<Item> *items, float xPos, float yPos)
{
	if (isInUseField(xPos, yPos)) {
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

void MainPerson::actionAlternate(Field &field, list<UnlifeObject> *unlifeObjects, destroyObjectsAndBlocks& listDestroy, list<Item> *items, float xPos, float yPos)
{
	if (isInUseField(xPos, yPos)) {
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