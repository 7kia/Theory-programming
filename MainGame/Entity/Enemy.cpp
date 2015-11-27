#include "../World.h"
#include "EntityVar.h"

using namespace std;

void createOnlyEnemy(world &world, std::vector<TypeEnemy*> &types, std::vector<int> amount)
{
	Enemy* addEnemy = new Enemy();

	emptyObjects &emptyObjects = world.emptyObjects;

	Item &emptyItem = emptyObjects.emptyItem;
	UnlifeObject &emptyObject = emptyObjects.emptyObject;

	int xPos;
	int yPos;
	int levelFloor = 1;

	int &countEnemy = world.countEntity;

	for (int countTypes = 0; countTypes < types.size(); countTypes++) {
		for (int amountAdd = 0; amountAdd < amount[countTypes]; amountAdd++) {
			countEnemy++;
			if (countEnemy > AMOUNT_ENTITY) {
				break;
			}

			xPos = 5;
			yPos = 11;

			addEnemy->EnemyInit(*types[countTypes], emptyItem, emptyObject, xPos, yPos, levelFloor);
			world.Enemys->push_back(*addEnemy);

		}
	}

	types.clear();
	amount.clear();

	delete addEnemy;
}

bool isPlaceForCreate(world world, Enemy* enemy, Vector3i &pos)
{
	// TODO
	enemy->interactionWithMap(world.field, *world.listDestroy, 0);
	enemy->interactionWitnUnlifeObject(world.unlifeObjects, 0);

	bool isPlace = true;
	while (pos.z < HEIGHT_MAP && enemy->wasCollision == false) {

		isPlace = true;
		while (enemy->wasCollision) {
			pos.x++;
			if (enemy->isExitFromBorder(pos.x, pos.y)) {

				pos.x = 0;
				enemy->spriteEntity->move(float(-(pos.x + 1) * SIZE_BLOCK), 0.f);

				pos.y++;
				if (enemy->isExitFromBorder(pos.x, pos.y)) {
					pos.y--;// TODO
					isPlace = false;
					enemy->wasCollision = false;
					break;
				} else {
					enemy->spriteEntity->move(0.f, float(SIZE_BLOCK));
				}


			} else {
				enemy->spriteEntity->move(float(SIZE_BLOCK), 0.f);
			}

			enemy->interactionWithMap(world.field, *world.listDestroy, 0);
			enemy->interactionWitnUnlifeObject(world.unlifeObjects, 0);
		}

		pos.z++;
	}

	return isPlace;
}

void createGroup(world &world, std::vector<TypeEnemy*> &types, std::vector<int> amount, int square, sf::Vector3i pos)
{
	Enemy* addEnemy = new Enemy();

	emptyObjects &emptyObjects = world.emptyObjects;

	Item &emptyItem = emptyObjects.emptyItem;
	UnlifeObject &emptyObject = emptyObjects.emptyObject;

	int xPos, xTemp;
	int yPos, yTemp;
	int levelFloor = pos.z;

	int &countEnemy = world.countEntity;

	int start = -square / 2;
	int finish = square / 2;
	if(square % 2 == 1)
	{
		start += 1;
	}

	xPos = pos.x + start;
	yPos = pos.y + start;

	for (size_t countTypes = 0; countTypes < types.size(); countTypes++) {
		for (size_t amountAdd = 0; amountAdd < amount[countTypes]; amountAdd++) {
			countEnemy++;
			if (countEnemy > AMOUNT_ENTITY) {
				// чтобы выйти из циклов
				countTypes = types.size();
				break;
			}


			xTemp = xPos;
			yTemp = yPos;
			addEnemy->EnemyInit(*types[countTypes], emptyItem, emptyObject, xTemp, yTemp, levelFloor);

			if(isPlaceForCreate(world, addEnemy, pos))
			{
				world.Enemys->push_back(*addEnemy);
			}

			

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

	int *config = world.configVariable;

	types.push_back(&typesEnemy[idEnemy::skeletEnemy]);
	types.push_back(&typesEnemy[idEnemy::skeletDiggerEnemy]);
	types.push_back(&typesEnemy[idEnemy::skeletBuilderEnemy]);

	amount.push_back(config[AMOUNT_SIMPLE_SKELET_IN_SMALL_GROUP]);
	amount.push_back(config[AMOUNT_SKELET_DIGGER_IN_SMALL_GROUP]);
	amount.push_back(config[AMOUNT_SKELET_BUILDER_IN_SMALL_GROUP]);

	createGroup(world, types, amount, 2, pos);
}

void createMiddleGroupSkelets(world &world, Vector3i pos)
{
	TypeEnemy *typesEnemy = world.typesObjects.typesEnemy;

	std::vector<TypeEnemy*> types;
	std::vector<int> amount;
	int *config = world.configVariable;

	types.push_back(&typesEnemy[idEnemy::skeletEnemy]);
	types.push_back(&typesEnemy[idEnemy::skeletDiggerEnemy]);
	types.push_back(&typesEnemy[idEnemy::skeletLumbermillEnemy]);
	types.push_back(&typesEnemy[idEnemy::skeletMinerEnemy]);
	types.push_back(&typesEnemy[idEnemy::skeletBuilderEnemy]);

	amount.push_back(config[AMOUNT_SIMPLE_SKELET_IN_MIDDLE_GROUP]);
	amount.push_back(config[AMOUNT_SKELET_DIGGER_IN_MIDDLE_GROUP]);
	amount.push_back(config[AMOUNT_SKELET_LUMBER_IN_MIDDLE_GROUP]);
	amount.push_back(config[AMOUNT_SKELET_MINER_IN_MIDDLE_GROUP]);
	amount.push_back(config[AMOUNT_SKELET_BUILDER_IN_MIDDLE_GROUP]);

	createGroup(world, types, amount, 4, pos);
}

void createBigGroupSkelets(world &world, Vector3i pos)
{
	TypeEnemy *typesEnemy = world.typesObjects.typesEnemy;

	std::vector<TypeEnemy*> types;
	std::vector<int> amount;
	int *config = world.configVariable;

	types.push_back(&typesEnemy[idEnemy::skeletEnemy]);
	types.push_back(&typesEnemy[idEnemy::skeletDiggerEnemy]);
	types.push_back(&typesEnemy[idEnemy::skeletLumbermillEnemy]);
	types.push_back(&typesEnemy[idEnemy::skeletMinerEnemy]);
	types.push_back(&typesEnemy[idEnemy::skeletBuilderEnemy]);
	
	amount.push_back(config[AMOUNT_SIMPLE_SKELET_IN_BIG_GROUP]);
	amount.push_back(config[AMOUNT_SKELET_DIGGER_IN_BIG_GROUP]);
	amount.push_back(config[AMOUNT_SKELET_LUMBER_IN_BIG_GROUP]);
	amount.push_back(config[AMOUNT_SKELET_MINER_IN_BIG_GROUP]);
	amount.push_back(config[AMOUNT_SKELET_BUILDER_IN_BIG_GROUP]);

	createGroup(world, types, amount, 5, pos);
}

void initializeEntitys(world &world)// ДОБАВЛЕНИЕ СУЩНОСТИ 
{
	srand(time(nullptr)); // автоматическая случайность

	int *config = world.configVariable;
	config[TIME_UPDATE_DIFFICULT] = config[AMOUNT_WAVE_FOR_UPDATE_DIFFICULT]
																	* config[TIME_GENERATE_WAVE_ENEMYS];
	//////////////////////////////////////////////////////////////
	Enemy* addEnemy = new Enemy();

	TypeEnemy *typesEnemy = world.typesObjects.typesEnemy;
	std::vector<TypeEnemy*> types;
	std::vector<int> amount;

	types.push_back(&typesEnemy[idEnemy::wolfEnemy]);
	amount.push_back(4);

	//createOnlyEnemy(world, types, amount);
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


	initStepSounds();

	founds.init(&emptyItem, &emptyObject);

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


	damage.inputCutDamage = int(multiplirer * (damage.cuttingDamage + damagePersonItem.cuttingDamage));
	damage.inputCrashDamage = int(multiplirer * (damage.crushingDamage + damagePersonItem.crushingDamage));
	int cuttingDamage = currentItem.typeItem->damageItem.cuttingDamage;
	int crushingDamage = currentItem.typeItem->damageItem.crushingDamage;

	float cutDamage = damage.damageMultiplirer * cuttingDamage;
	float crashDamage = damage.damageMultiplirer * crushingDamage;

	cutDamage *= protection.protectionCut;
	crashDamage *= protection.protectionCrash;

	damage.inputDamage = int(cutDamage + crashDamage);
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
	//TypeItem *typesItem = world.typesObjects.typesItem;
	Item &currentItem = itemFromPanelQuickAccess[idSelectItem];

	int x = collision.x;
	int y = collision.y;
	int level = collision.level;//currentLevelFloor + 1;

	int xShift = 0;
	int yShift = 0;
	choiceDirectionLook(xShift, yShift);

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

void Enemy::findLadder(world &world, Vector3i pos)
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
			}
		}
	}
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
		float dx(movement.x);
		float dy(movement.y);

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
						if (directions.directionWalk >= Direction::UP_LEFT) {
							// Чтобы скорость по диагонали была равной скорости по вертикали и горизонтали
							x -= DIAGONAL_SCALE_SPEED * dx * deltaTime;
							y -= DIAGONAL_SCALE_SPEED * dy * deltaTime;
						} else {
							x -= dx * deltaTime;
							y -= dy * deltaTime;
						}
						wasCollision = true;

						findEnemy = &objects[i];
						findEnemyFromList = i;
						directions.directionWalk = NONE_DIRECTION;
						break;
					}

				}

			}
		

		spriteEntity->setPosition(x, y);
		movement = { 0.f, 0.f };

	}
}