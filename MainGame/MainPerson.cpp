#include "MainPerson.h"
#include "ItemsVar.h"
#include "EntityVar.h"
#include "Font.h"


#include "UseItem.h"
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

	mainPerson.initStepSounds(databaseSound);

	mainPerson.initFounds(emptyItem, emptyObject, emptyEnemy);

	// ������� � ��������� ������
	mainPerson.idSelectItem = 0;
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
	animation.init(1.5f, 1.f);

	Directions &directions = mainPerson.directions;
	directions.directionWalk = NONE_DIRECTION;
	directions.directionLook = DOWN;

	mainPerson.health.maxHealth = 1000;
	mainPerson.health.currentHealth = 900;
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
	Item& itemEnemy = enemy.itemFromPanelQuickAccess[enemy.idSelectItem];
	typeDamageItem damageEnemyItem = itemEnemy.typeItem->damageItem;
	DamageInputAndOutput &enemyDamege = enemy.damage;
	float cutDamage;
	float crashDamage;
	float multiplirer = enemyDamege.damageMultiplirer;


	damage.inputCutDamage = multiplirer * (enemyDamege.cuttingDamage + damageEnemyItem.cuttingDamage);
	damage.inputCrashDamage = multiplirer * (enemyDamege.crushingDamage + damageEnemyItem.crushingDamage);
	//float cutDamage = damageMultiplirer * currentItem.cuttingDamage;
	//float crashDamage = damageMultiplirer * currentItem.crushingDamage;

	damage.inputCutDamage *= protection.protectionCut;
	damage.inputCrashDamage *= protection.protectionCrash;

	damage.inputDamage = damage.inputCutDamage + damage.inputCrashDamage;
	health.currentHealth -= damage.inputDamage;

	damage.inputDamage = 0;// TODO
}


void MainPerson::updateAtack(vector<Enemy> *enemy, vector<Item> *items, TypeItem *typesItems, const Time &deltaTime)
{
	Item& currentItem = itemFromPanelQuickAccess[idSelectItem];


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

			//if (giveDamage) {
				animation.currentTimeFightAnimation = 0.f;

				currenMode = idEntityMode::walk;
				giveDamage = false;
				currentItem.currentToughness -= 1;
			//}
			

			if (itemFromPanelQuickAccess[idSelectItem].currentToughness < 1) {
				itemFromPanelQuickAccess[idSelectItem] = *founds.emptyItem;
			}
		} 
		else {
			currenMode = idEntityMode::atack;
			//animation.currentTimeFightAnimation += deltaTime.asSeconds();
			// TODO //enemy->giveDamage//
			Vector2f posPerson = { getXPos(), getYPos() };
			Vector2f posEnemy = { findEnemy->getXPos(), findEnemy->getYPos() };
			float distanse = distansePoints(posPerson, posEnemy);

			if (giveDamage && distanse <= SIZE_BLOCK * 2.5f) {
				animation.currentTimeFightAnimation = 0.f;

				currenMode = idEntityMode::walk;
				giveDamage = false;
				findEnemy->takeDamage(damage, currentItem);
			}

		}
	}
}


void MainPerson::attractionEnemy(Enemy &enemy, Field &field, const Time &deltaTime)
{
	Vector2f personPoint = { getXPos(), getYPos() };
	Vector2f enemyPoint;
	Vector2f movemoment;
	float distanse;

	enemyPoint = enemy.spriteEntity->getPosition();

	distanse = distansePoints(personPoint, enemyPoint);
	// ���� ������
	Directions &directions = enemy.directions;
	entityAnimation &animation = enemy.animation;

	float radiuseView = enemy.type->view.radiuseView;
	bool feelEnemy = enemy.type->view.feelEnemy;
	if (distanse <= radiuseView && currentLevelFloor == enemy.currentLevelFloor) {

			enemy.currenMode = idEntityMode::fight;

			movemoment = vectorDirection(enemyPoint, personPoint);

			enemy.defineDirectionLook(movemoment);

			if(feelEnemy != true)
				enemy.checkBlock(field);


			if (enemy.currenMode == idEntityMode::fight) {
			enemy.choiceDirections(movemoment);
				step.currentTime = 0;

				if (enemy.wasCollision) {

					String nameCurrentItem = enemy.itemFromPanelQuickAccess[enemy.idSelectItem].typeItem->features.name;
					String nameEmptyItem = founds.emptyItem->typeItem->features.name;
					if (nameCurrentItem != nameEmptyItem)
						enemy.choiceBlock(field);

				} 
				else 
				{
					if (distanse >= SIZE_BLOCK) {
						enemy.animation.currentTimeFightAnimation = 0.f;
					}
					else {
						enemy.currenMode = idEntityMode::atack;
						enemy.animation.currentTimeFightAnimation += deltaTime.asSeconds();
						// TODO //enemy->giveDamage//
						if (enemy.animation.currentTimeFightAnimation > enemy.animation.timeFightAnimation) {
							enemy.animation.currentTimeFightAnimation = 0.f;

							enemy.currenMode = idEntityMode::fight;
							enemy.giveDamage = false;
							givenForPersonDamage(enemy);
						}

						directions.directionWalk = NONE_DIRECTION;
					}

				}


			}

	}
	
}
////////////////////////////////////////////////////////////////////

void MainPerson::useItem(Field &field, listDestroyObjectsAndBlocks& listDestroy, const Time &deltaTime,
												 TypeItem *typesItems, TypeUnlifeObject *typesUnlifeObjects, vector<Enemy> *enemy,
												 vector<Item> *items, vector<UnlifeObject> *unlifeObjects, Event &event, float xMouse, float yMouse)
{
	Item& currentItem = itemFromPanelQuickAccess[idSelectItem];

	int x = xMouse / SIZE_BLOCK;
	int y = yMouse / SIZE_BLOCK;
	founds.currentTarget = { x, y };

	bool isEnemy = findEnemy != emptyEnemy;
	bool isAtack = event.key.code == Mouse::Left;
	if (isEnemy && isAtack) {

		if (isInUseField(xMouse, yMouse, true)) {
			if (findEnemy->currentLevelFloor == currentLevelFloor) {

				if (animation.currentTimeFightAnimation == 0.f) {
					currenMode = idEntityMode::atack;
				}

			}

		}


	}
	else {

		//currenMode = idEntityMode::walk;

		String* listObjects;
		wchar_t* listBlocks;
		int sizeListObjects;

		bool findTool = true;

		int category = currentItem.typeItem->features.category;
		switch (category) {
		case idCategoryItem::backhoe:
		case idCategoryItem::pickax:
		case idCategoryItem::axe:
			if (isInUseField(xMouse, yMouse, true)) {
				useTool(event, field,
								currentItem,
								typesItems, items, unlifeObjects);
			}
			break;
			////////////////////////////////////////////////////////////////////////
			// ���� � ������� ������
		case idCategoryItem::block:
		case idCategoryItem::unlifeObject:
			useBlock(xMouse, yMouse, event, field,
							 currentItem, typesItems, items,
							 typesUnlifeObjects, unlifeObjects);
			findTool = false;
			break;
			////////////////////////////////////////////////////////////////////////
		default:
			findTool = false;
			break;
		}



		if (findTool == false)
		{
			switch (category) {

		case idCategoryItem::food:
			useAsFood(currentItem, event);
			break;
		case idCategoryItem::bukketWithWater:
			useAsBukketWithWater(currentItem, typesItems, event, field);
			break;
		case idCategoryItem::bottleWithWater:
			useAsBottleWithWater(currentItem, typesItems, event);
			break;
		case idCategoryItem::bukketEmpty:// �������
			if (isInUseField(xMouse, yMouse, true)) {
				int level;
				defineLevel(level, event);
				useAsEmptyBukket(currentItem, typesItems, field, level);
			}
			break;
		case idCategoryItem::bottleEmpty:// �������
			if (isInUseField(xMouse, yMouse, true)) {
				int level;
				defineLevel(level, event);
				useAsEmptyBottle(currentItem, typesItems, field, level);
			}
			break;
		case idCategoryItem::other:
			break;
		default:
			break;
		}
		}
		

	}

}

// �������������� � ����������
void MainPerson::actionMain(Field &field, vector<UnlifeObject> *unlifeObjects, listDestroyObjectsAndBlocks& listDestroy,
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

void MainPerson::actionAlternate(Field &field, vector<UnlifeObject> *unlifeObjects, listDestroyObjectsAndBlocks& listDestroy,
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
	rotation = (atan2(dX, dY)) * 180 / PI - 90;//�������� ���� � �������� � ��������� ��� � �������
	if(rotation < 0)
	{
		rotation += 360;
	}
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