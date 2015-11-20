#include "World.h"
#include "EntityVar.h"


void createOnlyEnemy(world &world, std::vector<TypeEnemy*> &types, std::vector<int> amount)
{
	Enemy* addEnemy = new Enemy();

	emptyObjects &emptyObjects = world.emptyObjects;

	Item &emptyItem = emptyObjects.emptyItem;
	UnlifeObject &emptyObject = emptyObjects.emptyObject;
	Enemy &emptyEnemy = emptyObjects.emptyEnemy;

	int xPos;
	int yPos;
	int levelFloor = 1;

	int &countEnemy = world.countEntity;

	int countTypes = 0;
	for (int countTypes = 0; countTypes < types.size(); countTypes++) {
		for (int amountAdd = 0; amountAdd < amount[countTypes]; amountAdd++) {
			countEnemy++;
			if (countEnemy > AMOUNT_ENTITY) {
				break;
			}

			xPos = 9 + rand() % 5;
			yPos = 9 + rand() % 5;

			addEnemy->EnemyInit(*types[countTypes], emptyItem, emptyObject, xPos, yPos, levelFloor);
			world.Enemys->push_back(*addEnemy);

		}
	}

	types.clear();
	amount.clear();

	delete addEnemy;
}

void createGroup(world &world, std::vector<TypeEnemy*> &types, std::vector<int> amount, int square, sf::Vector3i pos)
{
	Enemy* addEnemy = new Enemy();

	emptyObjects &emptyObjects = world.emptyObjects;

	Item &emptyItem = emptyObjects.emptyItem;
	UnlifeObject &emptyObject = emptyObjects.emptyObject;
	Enemy &emptyEnemy = emptyObjects.emptyEnemy;

	int xPos;
	int yPos;
	int levelFloor = pos.z;

	int &countEnemy = world.countEntity;
	bool oddSquare = square % 2;

	int start = -square / 2;
	int finish = square / 2;
	if(!oddSquare)
	{
		start += 1;
	}

	xPos = pos.x + start;
	yPos = pos.y + start;

	int countTypes = 0;
	for (int countTypes = 0; countTypes < types.size(); countTypes++) {
		for (int amountAdd = 0; amountAdd < amount[countTypes]; amountAdd++) {
			countEnemy++;
			if (countEnemy > AMOUNT_ENTITY) {
				// чтобы выйти из циклов
				countTypes = types.size();
				break;
			}



			addEnemy->EnemyInit(*types[countTypes], emptyItem, emptyObject, xPos, yPos, levelFloor);
			addEnemy->interactionWithMap(world.field, *world.listDestroy, 1.f);
			if(true)
			{
				
			}
			world.Enemys->push_back(*addEnemy);

			xPos++;
			if(xPos >  pos.x + finish)
			{
				xPos = pos.x + start;
				yPos++;
				if (yPos >  pos.y + finish) {
					// чтобы выйти из циклов
					countTypes = types.size();
					break;
				}
			}

		}
	}

	types.clear();
	amount.clear();

	delete addEnemy;
}

void createSmallGroupSkelets(world &world, Vector3i pos)
{
	TypeEnemy *typesEnemy = world.typesObjects.typesEnemy;

	std::vector<TypeEnemy*> types;
	std::vector<int> amount;

	types.push_back(&typesEnemy[idEnemy::skeletEnemy]);
	amount.push_back(3);
	types.push_back(&typesEnemy[idEnemy::skeletDiggerEnemy]);
	amount.push_back(3);
	types.push_back(&typesEnemy[idEnemy::skeletLumbermillEnemy]);
	amount.push_back(3);
	types.push_back(&typesEnemy[idEnemy::skeletMinerEnemy]);
	amount.push_back(3);
	types.push_back(&typesEnemy[idEnemy::skeletBuilderEnemy]);
	amount.push_back(3);

	createGroup(world, types, amount, 5, pos);
}
void initializeEntitys(world &world)// ДОБАВЛЕНИЕ СУЩНОСТИ 
{

	srand(time(0)); // автоматическая случайность
	//////////////////////////////////////////////////////////////
	Enemy* addEnemy = new Enemy();

	TypeEnemy *typesEnemy = world.typesObjects.typesEnemy;
	std::vector<TypeEnemy*> types;
	std::vector<int> amount;

	types.push_back(&typesEnemy[idEnemy::wolfEnemy]);
	amount.push_back(4);

	createOnlyEnemy(world, types, amount);
	//////////////////////////////////////////////////////////////
	TypeEnemy* typeEnemy = &typesEnemy[idEnemy::emptyEnemy];

	emptyObjects &emptyObjects = world.emptyObjects;
	Item &emptyItem = emptyObjects.emptyItem;
	UnlifeObject &emptyObject = emptyObjects.emptyObject;
	Enemy &emptyEnemy = emptyObjects.emptyEnemy;

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

void Enemy::randomWalk(const float deltaTime) {

	if (currenMode == idEntityMode::walk) {
		if (step.currentTime < step.timeWalk && directions.directionWalk != Direction::NONE_DIRECTION) {

			step.currentTime += deltaTime;

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


void Enemy::choiceBlock(world &world)
{
	TypeItem *typesItem = world.typesObjects.typesItem;
	Item &currentItem = itemFromPanelQuickAccess[idSelectItem];

	int x = collision.x;
	int y = collision.y;
	int level = collision.level;//currentLevelFloor + 1;

	int xShift = 0;
	int yShift = 0;
	choiceDirectionLook(xShift, yShift);



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
	
	/*
		wchar_t air = field.charBlocks[idBlocks::air];
	wchar_t *block = &field.dataMap[level][y][x];

	wchar_t *listBlocks = currentItem.typeItem->destroy.blocks;
	String *listObjects = currentItem.typeItem->destroy.objects;
	int countObjects = currentItem.typeItem->destroy.amountObjects;

	if (isInListBlocks(*block, listBlocks)) {
		*block = air;
	}
	*/
	Vector3i pos = { x, y, level };
	useTool(pos, world, currentItem);

	//bool isObject = founds.findObject != founds.emptyObject;
	//if (isObject) {

	// Building
	//field.dataMap[currentLevelFloor][y][x] = currentItem.typeItem->idAdd.idBlockForUse;
	

	//}

}

void Enemy::checkLevelHealth(Vector2f &movemoment)
{
	entityHealth &healthEnemy = health;
	bool isLowHealth = healthEnemy.currentHealth < (healthEnemy.maxHealth / 4);
	if (isLowHealth) {
		entityStandPanic(movemoment);
	}
	else {
		currenMode = idEntityMode::fight;
	}
}

void Enemy::entityStandPanic(Vector2f &movemoment)
{
	bool canPanic = type->converse.canPanic;
	currenMode = idEntityMode::panic;
	if (canPanic) {
		movemoment = { -movemoment.x, -movemoment.y };
		choiceDirections(movemoment);

		animation.currentTimeFightAnimation = 0.f;

		step.stepCurrent = step.stepFirst * 2;
		stamina.needMinusStamina = true;
	}
}

void Enemy::buildLadder(world &world)
{
	TypeItem *typesItem = world.typesObjects.typesItem;
	TypeUnlifeObject *typesObject = world.typesObjects.typesUnlifeObject;

	int x = getXPos() / SIZE_BLOCK;
	int y = getYPos() / SIZE_BLOCK;
	int level = currentLevelFloor + 1;//currentLevelFloor + 1;

	Item &currentItem = itemFromPanelQuickAccess[idSelectItem];

	Field &field = world.field;
	wchar_t(*map)[LONG_MAP][WIDTH_MAP] = field.dataMap;
	wchar_t air = field.charBlocks[idBlocks::air];
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++) {
			if (map[level][y + j][x + i] == air) {
				Vector3i pos = { x + i, y + j, level };
				useBlock(pos, world, currentItem);
			}
		}
	}




}

void Enemy::findLadder(world &world, Vector3i pos)
{
	TypeItem *typesItem = world.typesObjects.typesItem;
	int x = getXPos() / SIZE_BLOCK;
	int y = getYPos() / SIZE_BLOCK;
	int level = pos.z;//currentLevelFloor + 1;

	Field &field = world.field;
	wchar_t(*map)[LONG_MAP][WIDTH_MAP] = field.dataMap;
	wchar_t ladder = field.charBlocks[idBlocks::woodLadder];
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {// TODO
			if (map[level][y + j][x + i] == ladder) {//(x + float(i) / 2) * SIZE_BLOCK,   (y + float(j) / 2) * SIZE_BLOCK
				Vector2f posLadder = { float(x + i) * SIZE_BLOCK, float(y + j) * SIZE_BLOCK };
				actionMain(world, posLadder);
			}
		}
	}
}

void Enemy::checkInDirectionWalk(Field &field, sf::Vector2i posStart, sf::Vector2i shifts)
{
	int level = currentLevelFloor + 1;
	int x = posStart.x;
	int y = posStart.y;
	int xShift = shifts.x;
	int yShift = shifts.y;


	int countCheckingBlocks = RADIUSE_VIEW / SIZE_BLOCK;
	int count = 1;
	while (!isExitFromBorder(x, y) && count < countCheckingBlocks) {

		bool checkX = field.dataMap[level][y][x + xShift] != field.charBlocks[idBlocks::air];
		bool checkY = field.dataMap[level][y + yShift][x] != field.charBlocks[idBlocks::air];
		bool checkXAndY = field.dataMap[level][y + yShift][x + xShift] != field.charBlocks[idBlocks::air];
		bool summaryCondition = false;
		if (xShift != 0 && yShift != 0) {
			summaryCondition = checkXAndY;
		}
		if (xShift != 0) {
			summaryCondition = checkX;
		} else if (yShift != 0) {
			summaryCondition = checkY;
		}

		if (summaryCondition) {


currenMode = idEntityMode::walk;
			if (wasCollision) {
			
				

				redefineDirectionWalk();
			}

			break;
		}
		x += xShift;
		y += yShift;

		count++;
	}
}

void Enemy::redefineDirectionWalk()
{
	step.currentTime = 0;
	step.timeWalk = minTimeWalk + rand() % (int(maxTimeWalk - minTimeWalk));

	int randomDirection = 1 + rand() % Direction::AMOUNT_DIRECTION;
	directions.directionWalk = Direction(randomDirection);
}

void Enemy::checkBlock(Field& field)
{
	int x = 0;
	int y = 0;

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

	Vector2i startPosition = { x, y };
	Vector2i shifts = { xShift, yShift };
	checkInDirectionWalk(field, startPosition, shifts);
}