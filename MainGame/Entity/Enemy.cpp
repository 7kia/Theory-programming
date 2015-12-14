#include "../World.h"
#include "EntityVar.h"

using namespace std;

void createOnlyEnemy(world &world, std::vector<TypeEnemy*> &types, std::vector<int> amount)
{
	Enemy* addEnemy = new Enemy();

	emptyObjects &emptyObjects = world.emptyObjects;

	Item &emptyItem = emptyObjects.emptyItem;
	UnlifeObject &emptyObject = emptyObjects.emptyObject;

	Vector3i pos;
	pos.z = 1;

	int &countEnemy = world.countEntity;

	for (int countTypes = 0; countTypes < types.size(); countTypes++) {
		for (int amountAdd = 0; amountAdd < amount[countTypes]; amountAdd++) {
			countEnemy++;
			if (countEnemy > AMOUNT_ENTITY) {
				break;
			}

			pos.x = 5;
			pos.y = 11;

			addEnemy->EnemyInit(*types[countTypes], world, pos.x, pos.y, pos.z);
			world.Enemys->push_back(*addEnemy);
			isPlaceForCreate(world, pos);

		}
	}

	types.clear();
	amount.clear();

	delete addEnemy;
}

void initializeEntitys(world &world)// ДОБАВЛЕНИЕ СУЩНОСТИ 
{
	srand(time(nullptr)); // автоматическая случайность

	int *config = world.enemyWaveVariables;
	config[TIME_UPDATE_DIFFICULT] = config[AMOUNT_WAVE_FOR_UPDATE_DIFFICULT]
																	* config[TIME_GENERATE_WAVE_ENEMYS];
	//////////////////////////////////////////////////////////////
	Enemy* addEnemy = new Enemy();

	
	TypeEnemy *typesEnemy = world.typesObjects.typesEnemy;
	std::vector<TypeEnemy*> types;
	std::vector<int> amount;

	types.push_back(&typesEnemy[idEntity::wolfEnemy]);
	amount.push_back(4);

	createOnlyEnemy(world, types, amount);
	//////////////////////////////////////////////////////////////
	TypeEnemy* typeEnemy = &typesEnemy[idEntity::emptyEnemy];

	emptyObjects &emptyObjects = world.emptyObjects;
	Item &emptyItem = emptyObjects.emptyItem;
	UnlifeObject &emptyObject = emptyObjects.emptyObject;
	Enemy &emptyEnemy = emptyObjects.emptyEnemy;

	emptyEnemy.EnemyInit(*typeEnemy, world, -1, -1, -1);//TODO

	delete addEnemy;

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Сущности
void Enemy::EnemyInit(TypeEnemy &typesEnemy, world &world,
											int xPos, int yPos, int level)
{
	spriteEntity = new Sprite;

	type = &typesEnemy;

	soundBase = &world.databaseSound;

	itemFromPanelQuickAccess = new Item;
	itemFromPanelQuickAccess->setType(type->typeItem);
	idSelectItem = 0;
	itemFromPanelQuickAccess[idSelectItem].amount = type->typeItem.maxAmount;

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


	emptyObjects &emptyObjects = world.emptyObjects;
	founds.init(&emptyObjects.emptyItem, &emptyObjects.emptyObject);

	// Позиция и направление
	currentLevelFloor = level;
	currenMode = idEntityMode::walk;

	spriteEntity->setOrigin(float(size.width / 2), float(size.height / 2));
	spriteEntity->setPosition(float(xPos * SIZE_BLOCK - SIZE_BLOCK / 2),
														float(yPos * SIZE_BLOCK - SIZE_BLOCK / 2));

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
									type->protection.protectionCrash,
									type->protection.protectionUnlife);
	protection.deathDay = type->protection.deathDay;

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


	damage.inputCutDamage = int(multiplirer * (damage.cuttingDamage + damagePersonItem.cuttingDamage));
	damage.inputCrashDamage = int(multiplirer * (damage.crushingDamage + damagePersonItem.crushingDamage));
	damage.inputUnlifeDamage = int(multiplirer * (damage.unlifeDamage + damagePersonItem.unlifeDamage));

	int cuttingDamage = currentItem.typeItem->damageItem.cuttingDamage;
	int crushingDamage = currentItem.typeItem->damageItem.crushingDamage;
	int unlifingDamage = currentItem.typeItem->damageItem.unlifeDamage;


	float cutDamage = damage.damageMultiplirer * cuttingDamage;
	float crashDamage = damage.damageMultiplirer * crushingDamage;
	float unlifeDamage = damage.damageMultiplirer * unlifingDamage;

	cutDamage *= protection.protectionCut;
	crashDamage *= protection.protectionCrash;
	unlifeDamage *= protection.protectionUnlife;

	damage.inputDamage = int(cutDamage + crashDamage + unlifeDamage);
	health.currentHealth -= damage.inputDamage;

	int categoryItem = currentItem.typeItem->features.category;
	if (categoryItem == idCategoryItem::weapon) {
		breakItem(currentItem);
	}


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
	//TypeItem *typesItem = world.typesObjects.typesItem;
	Item &currentItem = itemFromPanelQuickAccess[idSelectItem];

	int x = collision.x;
	int y = collision.y;
	int level = collision.level;//currentLevelFloor + 1;

	int xShift = 0;
	int yShift = 0;
	choiceDirectionLook(xShift, yShift);

	founds.currentTarget = { x, y, level };

	/////////////////////////////////////////////
	Field &field = world.field;
	wchar_t	*block = &field.dataMap[level][y][x];
	int idNature;
	idNature = field.idsNature[field.findIdBlock(*block)];

	if (idNature != idNatureObject::Unbreaking) {
		currenMode = idEntityMode::atack;
		giveDamage = false;
	}
	//Vector3i pos = {  };
	//useTool(pos, world, currentItem);

	//bool isObject = founds.findObject != founds.emptyObject;
	//if (isObject) {

	// Building
	//field.dataMap[currentLevelFloor][y][x] = currentItem.typeItem->idAdd.idBlockForUse;
	

	//}

}

void Enemy::resetFightAnimation()
{
	animation.currentTimeFightAnimation = 0.f;
}

void Enemy::searchWay(world &world)
{
	Item &itemEnemy = itemFromPanelQuickAccess[idSelectItem];

	Vector3i posEnemy = { int(getXPos() / SIZE_BLOCK),
		int(getXPos() / SIZE_BLOCK),
		collision.level };

	if (findLadder(world, posEnemy)) {

		String nameCurrentItem = itemEnemy.typeItem->features.name;
		String nameEmptyItem = founds.emptyItem->typeItem->features.name;

		bool isLadder = itemEnemy.typeItem->features.category == idCategoryItem::block;
		bool isNotEmpty = nameCurrentItem != nameEmptyItem;

		if (isNotEmpty && isLadder) {
			buildLadder(world);
		}

	}
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

	int x = int(getXPos() / SIZE_BLOCK);
	int y = int(getYPos() / SIZE_BLOCK);
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


bool Enemy::findLadder(world &world, Vector3i pos)
{

	int x = int(getXPos() / SIZE_BLOCK);
	int y = int(getYPos() / SIZE_BLOCK);
	int level = pos.z;//currentLevelFloor + 1;

	Field &field = world.field;
	wchar_t(*map)[LONG_MAP][WIDTH_MAP] = field.dataMap;
	wchar_t ladder = field.charBlocks[idBlocks::woodLadder];
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {// TODO
			if (map[level][y + j][x + i] == ladder) {//(x + float(i) / 2) * SIZE_BLOCK,   (y + float(j) / 2) * SIZE_BLOCK
				Vector2f posLadder = { float(x + i) * SIZE_BLOCK, float(y + j) * SIZE_BLOCK };
				actionMain(world, posLadder);
				return true;
			}
		}
	}
	return false;
}

void Enemy::checkInDirectionWalk(Field &field, float distanse, sf::Vector2i posStart, sf::Vector2i shifts)
{
	int level = currentLevelFloor + 1;
	int x = posStart.x;
	int y = posStart.y;
	int xShift = shifts.x;
	int yShift = shifts.y;


	int countCheckingBlocks = int(distanse / SIZE_BLOCK);
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

void Enemy::checkBlock(Field& field, float distanse)
{
	int x = 0;
	int y = 0;

	int xShift = 0;
	int yShift = 0;
	switch (directions.directionLook) {
	case DOWN_LEFT:
		x = int(getXPos() / SIZE_BLOCK - 1);
		y = int(getYPos() / SIZE_BLOCK + 1);
		xShift = -1;
		yShift = 1;
		break;
	case DOWN_RIGHT:
		x = int(getXPos() / SIZE_BLOCK + 1);
		y = int(getYPos() / SIZE_BLOCK + 1);
		xShift = 1;
		yShift = 1;
		break;
	case UP_LEFT:
		x = int(getXPos() / SIZE_BLOCK - 1);
		y = int(getYPos() / SIZE_BLOCK - 1);
		xShift = -1;
		yShift = -1;
		break;
	case UP_RIGHT:
		x = int(getXPos() / SIZE_BLOCK + 1);
		y = int(getYPos() / SIZE_BLOCK - 1);
		xShift = 1;
		yShift = -1;
		break;
	case LEFT:
		x = int(getXPos() / SIZE_BLOCK - 1);
		y = int(getYPos() / SIZE_BLOCK);
		xShift = -1;
		yShift = 0;
		break;
	case RIGHT:
		x = int(getXPos() / SIZE_BLOCK + 1);
		y = int(getYPos() / SIZE_BLOCK);
		xShift = 1;
		yShift = 0;
		break;
	case UP:
		x = int(getXPos() / SIZE_BLOCK);
		y = int(getYPos() / SIZE_BLOCK - 1);
		xShift = 0;
		yShift = -1;
		break;
	case DOWN:
		x = int(getXPos() / SIZE_BLOCK);
		y = int(getYPos() / SIZE_BLOCK + 1);
		xShift = 0;
		yShift = 1;
		break;
	default:
		break;
	}

	Vector2i startPosition = { x, y };
	Vector2i shifts = { xShift, yShift };
	checkInDirectionWalk(field, distanse, startPosition, shifts);
}

void Enemy::interactionWithEntity(vector<Enemy> *enemys, int id, const float deltaTime)// ИСПРАВЬ for enity and mainPerson
{
	if (wasCollision == false) {
		float &dx(movement.x);
		float &dy(movement.y);

		float x;
		float y;
		x = getXPos();
		y = getYPos();

		
			Sprite *spriteObject;
			FloatRect objectBound;

			int levelUnlifeObject;
			FloatRect entityBound;
			entityBound = spriteEntity->getGlobalBounds();


			vector<Enemy> &objects = *enemys;
			for (int i = 0; i != objects.size(); ++i) {

				if (id != i && findEnemyFromList != -1) {
					levelUnlifeObject = objects[i].currentLevelFloor;

					spriteObject = objects[i].spriteEntity;
					objectBound = spriteObject->getGlobalBounds();


					if (entityBound.intersects(objectBound) && (levelUnlifeObject == currentLevelFloor)) {
						dx = dy = 0;
						wasCollision = true;

						findEnemy = &objects[i];
						findEnemyFromList = i;
						directions.directionWalk = NONE_DIRECTION;
						break;
					}

				}

			}
		


	}
}
