#include "Enemy.h"
#include "Items.h"
#include "UnlifeObject.h"
#include "EntityVar.h"
#include "Map.h"

void initializeEntitys(TypeEnemy *typesEnemy, std::vector<Enemy> &enemy, int countEnemy,
											 Item &emptyItem, UnlifeObject &emptyObject, Enemy &emptyEnemy)// ДОБАВЛЕНИЕ СУЩНОСТИ 
{

	srand(time(0)); // автоматическая случайность
									//////////////////////////////////////////////////////////////
									// Волки
	Enemy* addEnemy = new Enemy();

	TypeEnemy* typeEnemy = &typesEnemy[idEnemy::wolfEnemy];
	
	int xPos;
	int yPos;
	int levelFloor;

	for (size_t i = 1; i <= 10; i++) {
		countEnemy++;
		if (countEnemy > AMOUNT_ENTITY) {
			break;
		}

		xPos = 9 + rand() % 5;
		yPos = 9 + rand() % 5;
		levelFloor = 0;

		addEnemy->EnemyInit(*typeEnemy, emptyItem, emptyObject, xPos, yPos, levelFloor);

		enemy.push_back(*addEnemy);

	}
	//////////////////////////////////////////////////////////////
	// Скелеты
	typeEnemy = &typesEnemy[idEnemy::skeletEnemy];

	for (size_t i = 1; i <= 20; i++) {
		countEnemy++;
		if (countEnemy > AMOUNT_ENTITY) {
			break;
		}

		xPos = 9 + rand() % 5;
		yPos = 9 + rand() % 5;
		levelFloor = 0;

		addEnemy->EnemyInit(*typeEnemy, emptyItem, emptyObject, xPos, yPos, levelFloor);

		enemy.push_back(*addEnemy);

	}
	//////////////////////////////////////////////////////////////
	typeEnemy = &typesEnemy[idEnemy::emptyEnemy];
	emptyEnemy.EnemyInit(*typeEnemy, emptyItem, emptyObject, -1, -1, -1);//TODO

	delete addEnemy;

}


void Enemy::initStepSounds()
{
	soundsEntity.push_back(type->soundsEntity[idSoundEntity::stepGrass]);
	soundsEntity.push_back(type->soundsEntity[idSoundEntity::stepStone]);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Сущности
void Enemy::EnemyInit(TypeEnemy &typesEnemy, Item &emptyItem, UnlifeObject &emptyObject,
											int xPos, int yPos, int level)
{
	spriteEntity = new Sprite;

	type = &typesEnemy;

	itemFromPanelQuickAccess = new Item;
	itemFromPanelQuickAccess->setType(type->typeItem);
	idSelectItem = 0;

	size.width = type->featuresSprite.size.width;
	size.height = type->featuresSprite.size.height;

	// Дальность подбора предметов
	radiusUse = 1;

	currenMode = idEntityMode::walk;

	// Скорость ходьбы
	step.init(SPEED_ENTITY);

	// Текстура
	spriteEntity->setTexture(*type->textureEntity);
	spriteEntity->setTextureRect(IntRect(0, 0, size.width, size.height));


	initStepSounds();

	founds.init(&emptyItem, &emptyObject);

	// Позиция и направление
	currentLevelFloor = level;
	currenMode = idEntityMode::walk;

	spriteEntity->setOrigin(size.width / 2, size.height / 2);
	spriteEntity->setPosition(xPos * SIZE_BLOCK - SIZE_BLOCK / 2, yPos * SIZE_BLOCK - SIZE_BLOCK / 2);

	directions.directionWalk = NONE_DIRECTION;
	directions.directionLook = DOWN;

	////////////////////////////////////////////////////////////////////////
	// Для случайного перемещения по карте
	step.timeWalk = minTimeWalk + rand() % (int(maxTimeWalk - minTimeWalk));

	step.currentTime = 0;

	int randomDirection = 1 + rand() % Direction::AMOUNT_DIRECTION;
	directions.directionWalk = Direction(randomDirection);
	////////////////////////////////////////////////////////////////////////

	// Показатели
	health.maxHealth = type->features.maxHealth;
	health.currentHealth = health.maxHealth;

	stamina.maxStamina = type->features.maxStamina;
	stamina.currentStamina = stamina.maxStamina;

	mana.maxMana = type->features.maxMana;
	mana.currentMana = mana.maxMana;

	thirst.currentThirst = thirst.maxThirst;
	hungry.currentHungry = hungry.maxHungry;

	protection.init(type->protection.protectionCut,
									type->protection.protectionCrash);

	float timeAtack = 1.f;
	animation.init(type->damage.timeOutputDamage, timeAtack);
	damage.init(type->damage.cuttingDamage, type->damage.crushingDamage, timeAtack, 1.f);
}

Enemy::~Enemy()
{
}

void Enemy::randomWalk(const Time &deltaTime) {

	if (currenMode == idEntityMode::walk) {
		if (step.currentTime < step.timeWalk && directions.directionWalk != Direction::NONE_DIRECTION) {

			step.currentTime += deltaTime.asSeconds();

		} else {

			step.currentTime = 0;
			step.timeWalk = minTimeWalk + rand() % (int(maxTimeWalk - minTimeWalk));

			int randomDirection = 1 + rand() % Direction::AMOUNT_DIRECTION;
			directions.directionWalk = Direction(randomDirection);
			step.direction = directions.directionWalk;
		}
	}
	

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Enemy::takeDamage(DamageInputAndOutput damage, Item &currentItem)
{
	bool isDestroy = currentItem.typeItem->features.isDestroy;
	if (isDestroy) {
		currentItem.currentToughness -= 1;
	}


	typeDamageItem damagePersonItem = currentItem.typeItem->damageItem;
	float multiplirer = damage.damageMultiplirer;


	damage.inputCutDamage = multiplirer * (damage.cuttingDamage + damagePersonItem.cuttingDamage);
	damage.inputCrashDamage = multiplirer * (damage.crushingDamage + damagePersonItem.crushingDamage);
	int cuttingDamage = currentItem.typeItem->damageItem.cuttingDamage;
	int crushingDamage = currentItem.typeItem->damageItem.crushingDamage;

	float cutDamage = damage.damageMultiplirer * currentItem.typeItem->damageItem.cuttingDamage;
	float crashDamage = damage.damageMultiplirer * currentItem.typeItem->damageItem.crushingDamage;

	cutDamage *= protection.protectionCut;
	crashDamage *= protection.protectionCrash;

	damage.inputDamage = cutDamage + crashDamage;
	health.currentHealth -= damage.inputDamage;
}

void Enemy::choiceDirections(Vector2f movemoment)
{
	//TODO
	float zero = SIZE_BLOCK / 3;

	bool xAboutZero = movemoment.x >= -zero && movemoment.x <= zero;
	bool yAboutZero = movemoment.y >= -zero && movemoment.y <= zero;

	if (movemoment.x > zero && movemoment.y > zero) {
		directions.directionWalk = DOWN_RIGHT;
	} else if (movemoment.x < -zero && movemoment.y > zero) {
		directions.directionWalk = DOWN_LEFT;
	} else if (movemoment.x < -zero && movemoment.y < -zero) {
		directions.directionWalk = UP_LEFT;
	} else if (movemoment.x > zero && movemoment.y < zero) {
		directions.directionWalk = UP_RIGHT;
	} else if (movemoment.y >= zero && xAboutZero) {
		directions.directionWalk = DOWN;
	} else if (movemoment.y <= -zero && xAboutZero) {
		directions.directionWalk = UP;
	} else if (movemoment.x >= zero && yAboutZero) {
		directions.directionWalk = RIGHT;
	} else if (movemoment.x <= -zero && yAboutZero) {
		directions.directionWalk = LEFT;
	} else {
		directions.directionWalk = NONE_DIRECTION;
	}
}

void Enemy::defineDirectionLook(Vector2f movemoment)
{
	//TODO
	float zero = SIZE_BLOCK / 3;

	bool xAboutZero = movemoment.x >= -zero && movemoment.x <= zero;
	bool yAboutZero = movemoment.y >= -zero && movemoment.y <= zero;

	if (movemoment.x > zero && movemoment.y > zero) {
		directions.directionLook = DOWN_RIGHT;
	} else if (movemoment.x < -zero && movemoment.y > zero) {
		directions.directionLook = DOWN_LEFT;
	} else if (movemoment.x < -zero && movemoment.y < -zero) {
		directions.directionLook = UP_LEFT;
	} else if (movemoment.x > zero && movemoment.y < zero) {
		directions.directionLook = UP_RIGHT;
	} else if (movemoment.y >= zero && xAboutZero) {
		directions.directionLook = DOWN;
	} else if (movemoment.y <= -zero && xAboutZero) {
		directions.directionLook = UP;
	} else if (movemoment.x >= zero && yAboutZero) {
		directions.directionLook = RIGHT;
	} else if (movemoment.x <= -zero && yAboutZero) {
		directions.directionLook = LEFT;
	} else {
		directions.directionLook = NONE_DIRECTION;
	}
}


void Enemy::choiceBlock(Field &field)
{
	int x;
	int y;
	Item &currentItem = itemFromPanelQuickAccess[idSelectItem];
	int level = currentLevelFloor + 1;

	int xShift = 0;
	int yShift = 0;
	choiceDirectionLook(xShift, yShift);


	wchar_t air = field.charBlocks[idBlocks::air];

	/*
	switch(directions.directionLook)
	{
	case DOWN_LEFT:
		x = getXPos() / SIZE_BLOCK - 1;
		y = getYPos() / SIZE_BLOCK + 1;
		if (!isExitFromBorder(x, y))
		{
			field.dataMap[level][y][x] = field.charBlocks[idBlocks::air];
		}
		break;
	case DOWN_RIGHT:
		x = getXPos() / SIZE_BLOCK + 1;
		y = getYPos() / SIZE_BLOCK + 1;
		if (!isExitFromBorder(x, y)) {
			field.dataMap[level][y][x] = field.charBlocks[idBlocks::air];
		}
		break;
	case UP_LEFT:
		x = getXPos() / SIZE_BLOCK - 1;
		y = getYPos() / SIZE_BLOCK - 1;
		if (isExitFromBorder(x, y)) {
			field.dataMap[level][y][x] = field.charBlocks[idBlocks::air];
		}
		break;
	case UP_RIGHT:
		x = getXPos() / SIZE_BLOCK + 1;
		y = getYPos() / SIZE_BLOCK - 1;
		if (!isExitFromBorder(x, y)) {
			field.dataMap[level][y][x] = field.charBlocks[idBlocks::air];
		}
		break;
	case LEFT:
		x = getXPos() / SIZE_BLOCK - 1;
		y = getYPos() / SIZE_BLOCK;
		if (!isExitFromBorder(x, y)) {
			field.dataMap[level][y][x] = field.charBlocks[idBlocks::air];
		}
		break;
	case RIGHT:
		x = getXPos() / SIZE_BLOCK + 1;
		y = getYPos() / SIZE_BLOCK;
		if (!isExitFromBorder(x, y)) {
			field.dataMap[level][y][x] = field.charBlocks[idBlocks::air];
		}
		break;
	case UP:
		x = getXPos() / SIZE_BLOCK;
		y = getYPos() / SIZE_BLOCK - 1;
		if (!isExitFromBorder(x, y)) {
			field.dataMap[level][y][x] = field.charBlocks[idBlocks::air];
		}
		break;
	case DOWN:
		x = getXPos() / SIZE_BLOCK;
		y = getYPos() / SIZE_BLOCK + 1;
		if (!isExitFromBorder(x, y)) {
			field.dataMap[level][y][x] = field.charBlocks[idBlocks::air];
		}
		break;
	default:
		break;
	}
	//*/
	
	field.dataMap[collision.level][collision.y][collision.x] = air;
	
}

void Enemy::checkBlock(Field& field)
{
	if(currenMode == idEntityMode::fight)
	{
		int x = 0;
		int y = 0;
		int level = currentLevelFloor + 1;

		int countCheckingBlocks = RADIUSE_VIEW / SIZE_BLOCK;
		int count = 1;

		int xShift = 0;
		int yShift = 0;
		switch (directions.directionLook) {
		case DOWN_LEFT:
			x = getXPos() / SIZE_BLOCK - 1;
			y = getYPos() / SIZE_BLOCK + 1;
			xShift = -1;
			yShift = 1;
			break;
		case DOWN_RIGHT:
			x = getXPos() / SIZE_BLOCK + 1;
			y = getYPos() / SIZE_BLOCK + 1;
			xShift = 1;
			yShift = 1;
			break;
		case UP_LEFT:
			x = getXPos() / SIZE_BLOCK - 1;
			y = getYPos() / SIZE_BLOCK - 1;
			xShift = -1;
			yShift = -1;
			break;
		case UP_RIGHT:
			x = getXPos() / SIZE_BLOCK + 1;
			y = getYPos() / SIZE_BLOCK - 1;
			xShift = 1;
			yShift = -1;
			break;
		case LEFT:
			x = getXPos() / SIZE_BLOCK - 1;
			y = getYPos() / SIZE_BLOCK;
			xShift = -1;
			yShift = 0;
			break;
		case RIGHT:
			x = getXPos() / SIZE_BLOCK + 1;
			y = getYPos() / SIZE_BLOCK;
			xShift = 1;
			yShift = 0;
			break;
		case UP:
			x = getXPos() / SIZE_BLOCK;
			y = getYPos() / SIZE_BLOCK - 1;
			xShift = 0;
			yShift = -1;
			break;
		case DOWN:
			x = getXPos() / SIZE_BLOCK;
			y = getYPos() / SIZE_BLOCK + 1;
			xShift = 0;
			yShift = 1;
			break;
		default:
			break;
		}

		while (!isExitFromBorder(x, y) && count < countCheckingBlocks) {
			bool checkX = field.dataMap[level][y][x + xShift] != field.charBlocks[idBlocks::air];

			bool checkY = field.dataMap[level][y + yShift][x] != field.charBlocks[idBlocks::air];

			bool checkXY = field.dataMap[level][y + yShift][x + xShift] != field.charBlocks[idBlocks::air];

			bool summaryCondition = true;
			if(xShift != 0 && yShift != 0)
			{
				summaryCondition = checkXY;
			}
			if(xShift != 0)
			{
				summaryCondition = checkX;
			}
			else if (yShift != 0) {
				summaryCondition = checkY;
			}

			if (summaryCondition) {
				currenMode = idEntityMode::walk;

				if(wasCollision)
				{
					step.currentTime = 0;
					step.timeWalk = minTimeWalk + rand() % (int(maxTimeWalk - minTimeWalk));

					int randomDirection = 1 + rand() % Direction::AMOUNT_DIRECTION;
					directions.directionWalk = Direction(randomDirection);
				}
			
				break;
			}
			x += xShift;
			y += yShift;
			count++;
		}
	}

}