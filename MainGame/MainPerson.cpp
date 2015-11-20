
#include "ItemsVar.h"
#include "EntityVar.h"
#include "Font.h"


#include "UseItem.h"
using namespace sf;
using namespace std;

////////////////////////////////////////////////////////////////////
// ���������� ���������
void initializeMainPerson(MainPerson & mainPerson, dataSound &databaseSound, emptyObjects &emptyObjects)
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

	mainPerson.initFounds(emptyObjects.emptyItem, emptyObjects.emptyObject, emptyObjects.emptyEnemy);

	// ������� � ��������� ������
	mainPerson.idSelectItem = 0;
	mainPerson.amountSlots = AMOUNT_ACTIVE_SLOTS;
	mainPerson.itemFromPanelQuickAccess = new Item[AMOUNT_ACTIVE_SLOTS];
	for (int i = 0; i < AMOUNT_ACTIVE_SLOTS; i++) {
		mainPerson.itemFromPanelQuickAccess[i].typeItem = emptyObjects.emptyItem.typeItem;
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
	/*
	if (x < leftBorder) tempX = leftBorder;//������� �� ���� ����� �������
	else if (x > rightBorder) tempX = rightBorder;//������� �� ���� ����� �������
	if (y < topBorder) tempY = topBorder;//������� �������
	else if (y > lowBorder) tempY = lowBorder;//������ �������	
	//*/
	

	view->setCenter(tempX, tempY);
}

void MainPerson::initFounds(::Item &item, UnlifeObject& object, ::Enemy& enemy)
{
	founds.init(&item, &object);
	emptyEnemy = &enemy;
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


void MainPerson::updateAtack(world &world, const Time &deltaTime)
{
	TypeItem *typesItems = world.typesObjects.typesItem;
	Item& currentItem = itemFromPanelQuickAccess[idSelectItem];
	Field &field = world.field;
	vector<Enemy> &enemy = *world.Enemys;
	vector<Item> &items = *world.items;

	bool isAtack = currenMode == idEntityMode::atack;
	bool isEnemy = findEnemy->type->name != emptyEnemy->type->name;
	if (isAtack && isEnemy) {

		if (findEnemy->isDeath) {

			Item* addItem = new Item;
			TypeEnemy& typeEnemy = *findEnemy->type;
			int countItem = typeEnemy.drop.minCountItems.size();

			vector<int> &minAmount = typeEnemy.drop.minCountItems;
			vector<int> &maxAmount = typeEnemy.drop.maxCountItems;
			vector<int> &idItems = typeEnemy.drop.dropItems;

			findEnemy->throwItem(field, items);

			int currentAmount;
			for (int i = 0; i < countItem; i++) {

				currentAmount = minAmount[i] + rand() % (maxAmount[i] - minAmount[i] + 2);
				for (int j = 0; j < currentAmount; j++) {
					addItem->setType(typesItems[typeEnemy.drop.dropItems[i]]);
					addItem->setPosition(founds.currentTarget.x + 1, founds.currentTarget.y + 1, currentLevelFloor + 1);
					world.items->push_back(*addItem);

				}

			}
			delete addItem;
			if (findEnemyFromList) {
				enemy.erase(enemy.begin() + findEnemyFromList);
			}
			else
			{
				enemy.clear();//TODO
			}

			//if (giveDamage) {
				animation.currentTimeFightAnimation = 0.f;

				currenMode = idEntityMode::walk;
				giveDamage = false;
				
			//}
			

				breakItem(currentItem);
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


				breakItem(currentItem);
			}

		}
	}
}


void MainPerson::attractionEnemy(Enemy &enemy, world &world, const Time &deltaTime)
{
	typesObjectsInWorld &types = world.typesObjects;
	TypeEnemy *typesEnemy = types.typesEnemy;
	TypeItem *typesItem = types.typesItem;

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

	bool onLevelEnemy = currentLevelFloor == enemy.currentLevelFloor;
	bool onLevel = onLevelEnemy || feelEnemy;
	if (distanse <= radiuseView && onLevel) {
		enemy.currenMode = idEntityMode::fight;

		movemoment = vectorDirection(enemyPoint, personPoint);
		enemy.checkLevelHealth(movemoment);
		enemy.defineDirectionLook(movemoment);

		// TODO
		bool isFight = enemy.currenMode == idEntityMode::fight;
		if (feelEnemy != true)
			enemy.checkBlock(world.field);

		isFight = enemy.currenMode == idEntityMode::fight;
		if (isFight) {

			enemy.choiceDirections(movemoment);
			step.currentTime = 0;
			Item &itemEnemy = enemy.itemFromPanelQuickAccess[enemy.idSelectItem];

			if (enemy.wasCollision) {

				if (!onLevelEnemy && feelEnemy) {
					Vector3i posEnemy = { int(enemy.getXPos() / SIZE_BLOCK), 
						int(enemy.getXPos() / SIZE_BLOCK),
						enemy.collision.level };
					enemy.findLadder(world, posEnemy);
				}


				String nameCurrentItem = itemEnemy.typeItem->features.name;
				String nameEmptyItem = founds.emptyItem->typeItem->features.name;

				bool isLadder = itemEnemy.typeItem->features.category == idCategoryItem::block;
				bool isNotEmpty = nameCurrentItem != nameEmptyItem;
				if (isNotEmpty && onLevelEnemy) {
					enemy.choiceBlock(world);
				} else if (isNotEmpty && isLadder) {
					enemy.buildLadder(world);
				}

			} 
			else {

				bool noNearFight = distanse >= SIZE_BLOCK;
				if (noNearFight) {
					enemy.animation.currentTimeFightAnimation = 0.f;
				} else if (onLevelEnemy) {
					enemy.currenMode = idEntityMode::atack;

					enemy.animation.currentTimeFightAnimation += deltaTime.asSeconds();
					if (enemy.animation.currentTimeFightAnimation > enemy.animation.timeFightAnimation) {
						enemy.animation.currentTimeFightAnimation = 0.f;

						enemy.currenMode = idEntityMode::fight;
						enemy.giveDamage = false;
						givenForPersonDamage(enemy);

						itemEnemy.currentToughness -= 1;
						if (itemEnemy.currentToughness < 1) {
							redefineType(itemEnemy, types.typesItem, -itemEnemy.typeItem->features.id);
						}
					}

					directions.directionWalk = NONE_DIRECTION;
				}

			}


		}

	}

}
	

////////////////////////////////////////////////////////////////////

void MainPerson::useItem(world &world, const Time &deltaTime,
												Event &event, Vector2f pos)
{

	TypeEnemy *typesEnemy = world.typesObjects.typesEnemy;
	TypeItem *typesItem = world.typesObjects.typesItem;
	Field &field = world.field;
	vector<Item> &items = *world.items;
	vector<UnlifeObject> &unlifeObjects = *world.unlifeObjects;
	Item& currentItem = itemFromPanelQuickAccess[idSelectItem];



	int x = pos.x / SIZE_BLOCK;
	int y = pos.y / SIZE_BLOCK;
	founds.currentTarget = { x, y };

	bool isEnemy = findEnemy != emptyEnemy;
	bool isAtack = event.key.code == Mouse::Left;
	if (isEnemy && isAtack) {

		if (isInUseField(pos.x, pos.y, true)) {
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
			if (isInUseField(pos.x, pos.y, true)) {
				int level;
				defineLevel(level, event);

				int x = founds.currentTarget.x;
				int y = founds.currentTarget.y;

				Vector3i pos = { x, y, level };
				useTool(pos, world, currentItem);
			}
			break;
			////////////////////////////////////////////////////////////////////////
			// ���� � ������� ������
		case idCategoryItem::block:
		case idCategoryItem::unlifeObject:
			if (isInUseField(pos.x, pos.y, false)) {
				int level;
				defineLevel(level, event);

				int x = founds.currentTarget.x;
				int y = founds.currentTarget.y;
				Vector3i pos = { x, y, level };


				useBlock(pos, world,
								 currentItem);
			}
			break;
			////////////////////////////////////////////////////////////////////////
		case idCategoryItem::food:
			useAsFood(currentItem, event);
			break;
		case idCategoryItem::bukketWithWater:
			useAsBukketWithWater(currentItem, typesItem, event, field);
			break;
		case idCategoryItem::bottleWithWater:
			useAsBottleWithWater(currentItem, typesItem, event);
			break;
		case idCategoryItem::bukketEmpty:// �������
			if (isInUseField(pos.x, pos.y, true)) {
				int level;
				defineLevel(level, event);
				useAsEmptyBukket(currentItem, typesItem, field, level);
			}
			break;
		case idCategoryItem::bottleEmpty:// �������
			if (isInUseField(pos.x, pos.y, true)) {
				int level;
				defineLevel(level, event);
				useAsEmptyBottle(currentItem, typesItem, field, level);
			}
			break;
		case idCategoryItem::other:
			break;
		default:
			break;
		}
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