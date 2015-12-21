//#include "../World.h"
//#include "../CreateGroups.h"
#include  "Enemy.h"

using namespace std;

void createOnlyEnemy(world &world , std::vector<TypeEnemy*> &types , std::vector<int> amount)
{
	Entity* addEnemy = new Entity();
	Vector3i pos;
	pos.z = 2;

	int &countEnemy = world.countEntity;

	for (int countTypes = 0; countTypes < types.size(); countTypes++) {
		for (int amountAdd = 0; amountAdd < amount[countTypes]; amountAdd++) {
			countEnemy++;
			if (countEnemy > AMOUNT_ENTITY) {
				break;
			}

			pos.x = CENTER_WORLD.x;
			pos.y = CENTER_WORLD.y;

			addEnemy->init(*types[countTypes] , world , pos.x , pos.y , pos.z);
			world.Enemys.push_back(*addEnemy);
			//isPlaceForCreate(world , pos);

		}
	}

	types.clear();
	amount.clear();

	delete addEnemy;
}

void initializeEntitys(world &world)// днаюбкемхе ясымнярх 
{
	srand(time(nullptr));

	int *config = world.enemyWaveVariables;
	config[TIME_UPDATE_DIFFICULT] = config[AMOUNT_WAVE_FOR_UPDATE_DIFFICULT]
		* config[TIME_GENERATE_WAVE_ENEMYS];
	createEnemys(world);
	createEmptyEnemy(world);
}

void createEnemys(world& world)
{
	Entity* addEnemy = new Entity();

	TypeEnemy *typesEnemy = world.typesObjects.typesEnemy;
	std::vector<TypeEnemy*> types;
	std::vector<int> amount;

	types.push_back(&typesEnemy[idEntity::playerEntity]);
	amount.push_back(1);

	//types.push_back(&typesEnemy[idEntity::wolfEnemy]);
	//amount.push_back(4);

	createOnlyEnemy(world , types , amount);

	delete addEnemy;
}

void createEmptyEnemy(world& world)
{
	TypeEnemy *typesEnemy = world.typesObjects.typesEnemy;
	TypeEnemy* typeEnemy = &typesEnemy[idEntity::emptyEnemy];

	emptyObjects &emptyObjects = world.emptyObjects;
	Entity &emptyEnemy = emptyObjects.emptyEnemy;

	emptyEnemy.init(*typeEnemy , world , -1 , -1 , -1);
}

void Entity::randomWalk(const float deltaTime) {

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

void Entity::takeDamage(DamageInputAndOutput damageEnemy, Item &currentItem)
{
	bool isDestroy = currentItem.typeItem->features.isDestroy;
	if (isDestroy) {
		currentItem.currentToughness -= 1;
	}

	typeDamageItem damagePersonItem = currentItem.typeItem->damageItem;
	float multiplirer = damageEnemy.damageMultiplirer;


	damageEnemy.inputCutDamage = int(multiplirer * (damageEnemy.cuttingDamage + damagePersonItem.cuttingDamage));
	damageEnemy.inputCrashDamage = int(multiplirer * (damageEnemy.crushingDamage + damagePersonItem.crushingDamage));
	damageEnemy.inputUnlifeDamage = int(multiplirer * (damageEnemy.unlifeDamage + damagePersonItem.unlifeDamage));

	int cuttingDamage = currentItem.typeItem->damageItem.cuttingDamage;
	int crushingDamage = currentItem.typeItem->damageItem.crushingDamage;
	int unlifingDamage = currentItem.typeItem->damageItem.unlifeDamage;


	float cutDamage = damageEnemy.damageMultiplirer * cuttingDamage;
	float crashDamage = damageEnemy.damageMultiplirer * crushingDamage;
	float unlifeDamage = damageEnemy.damageMultiplirer * unlifingDamage;

	cutDamage *= protection.protectionCut;
	crashDamage *= protection.protectionCrash;
	unlifeDamage *= protection.protectionUnlife;

	damageEnemy.inputDamage = int(cutDamage + crashDamage + unlifeDamage);
	health.currentHealth -= damageEnemy.inputDamage;

	damage.inputDamage = damageEnemy.inputDamage;
	damageEnemy.inputDamage = 0;

	int categoryItem = currentItem.typeItem->features.category;
	if (categoryItem == idCategoryItem::weapon) {
		breakItem(currentItem);
	}


}

void Entity::choiceDirections(Vector2f movemoment)
{
	bool xAboutZero = movemoment.x >= -BORDER_VALUE_FOR_DIRECTION && movemoment.x <= BORDER_VALUE_FOR_DIRECTION;
	bool yAboutZero = movemoment.y >= -BORDER_VALUE_FOR_DIRECTION && movemoment.y <= BORDER_VALUE_FOR_DIRECTION;

	if (movemoment.x > BORDER_VALUE_FOR_DIRECTION && movemoment.y > BORDER_VALUE_FOR_DIRECTION) {
		directions.directionWalk = DOWN_RIGHT;
	} else if (movemoment.x < -BORDER_VALUE_FOR_DIRECTION && movemoment.y > BORDER_VALUE_FOR_DIRECTION) {
		directions.directionWalk = DOWN_LEFT;
	} else if (movemoment.x < -BORDER_VALUE_FOR_DIRECTION && movemoment.y < -BORDER_VALUE_FOR_DIRECTION) {
		directions.directionWalk = UP_LEFT;
	} else if (movemoment.x > BORDER_VALUE_FOR_DIRECTION && movemoment.y < BORDER_VALUE_FOR_DIRECTION) {
		directions.directionWalk = UP_RIGHT;
	} else if (movemoment.y >= BORDER_VALUE_FOR_DIRECTION && xAboutZero) {
		directions.directionWalk = DOWN;
	} else if (movemoment.y <= -BORDER_VALUE_FOR_DIRECTION && xAboutZero) {
		directions.directionWalk = UP;
	} else if (movemoment.x >= BORDER_VALUE_FOR_DIRECTION && yAboutZero) {
		directions.directionWalk = RIGHT;
	} else if (movemoment.x <= -BORDER_VALUE_FOR_DIRECTION && yAboutZero) {
		directions.directionWalk = LEFT;
	} else {
		directions.directionWalk = NONE_DIRECTION;
	}
}

void Entity::defineDirectionLook(Vector2f movemoment)
{
	bool xAboutZero = movemoment.x >= -BORDER_VALUE_FOR_DIRECTION && movemoment.x <= BORDER_VALUE_FOR_DIRECTION;
	bool yAboutZero = movemoment.y >= -BORDER_VALUE_FOR_DIRECTION && movemoment.y <= BORDER_VALUE_FOR_DIRECTION;

	if (movemoment.x > BORDER_VALUE_FOR_DIRECTION && movemoment.y > BORDER_VALUE_FOR_DIRECTION) {
		directions.directionLook = DOWN_RIGHT;
	} else if (movemoment.x < -BORDER_VALUE_FOR_DIRECTION && movemoment.y > BORDER_VALUE_FOR_DIRECTION) {
		directions.directionLook = DOWN_LEFT;
	} else if (movemoment.x < -BORDER_VALUE_FOR_DIRECTION && movemoment.y < -BORDER_VALUE_FOR_DIRECTION) {
		directions.directionLook = UP_LEFT;
	} else if (movemoment.x > BORDER_VALUE_FOR_DIRECTION && movemoment.y < BORDER_VALUE_FOR_DIRECTION) {
		directions.directionLook = UP_RIGHT;
	} else if (movemoment.y >= BORDER_VALUE_FOR_DIRECTION && xAboutZero) {
		directions.directionLook = DOWN;
	} else if (movemoment.y <= -BORDER_VALUE_FOR_DIRECTION && xAboutZero) {
		directions.directionLook = UP;
	} else if (movemoment.x >= BORDER_VALUE_FOR_DIRECTION && yAboutZero) {
		directions.directionLook = RIGHT;
	} else if (movemoment.x <= -BORDER_VALUE_FOR_DIRECTION && yAboutZero) {
		directions.directionLook = LEFT;
	} else {
		directions.directionLook = NONE_DIRECTION;
	}
}


void Entity::choiceBlock(world &world)
{
	Item &currentItem = itemFromPanelQuickAccess[idSelectItem];

	int x = collision.posBlock.x;
	int y = collision.posBlock.y;
	int level = collision.posBlock.z;

	int xShift = 0;
	int yShift = 0;
	choiceDirectionLook(xShift, yShift);

	
	Field &field = world.field;
	wchar_t	*block = &field.dataMap[level][y][x];
	int idNature;
	idNature = field.idsNature[field.findIdBlock(*block)];

	if (idNature <= idNatureObject::Unbreaking) {
		vector<UnlifeObject> &objects = world.unlifeObjects;
		UnlifeObject &findObject = world.emptyObjects.emptyObject;

		for (int i = 0; i < objects.size(); i++)
		{
			if(objects[i].getPosition() == collision.posObject)
			{
				findObject = objects[i];
			}
		}
		idNature = findObject.typeObject->idNature;
	}
	else
	{
		founds.currentTarget = { x, y, level };
	}
	if (idNature != idNatureObject::Unbreaking) {
		currenMode = idEntityMode::atack;
		giveDamage = false;
	}
}

void Entity::resetFightAnimation()
{
	animation.currentTimeFightAnimation = 0.f;
}

void Entity::searchWay(world &world)
{
	Item &itemEnemy = itemFromPanelQuickAccess[idSelectItem];

	Vector3i posEnemy = { int(getXPos() / SIZE_BLOCK),
		int(getXPos() / SIZE_BLOCK),
		currentLevelFloor + 1 };

	if (!findLadder(world, posEnemy)) {

		String nameCurrentItem = itemEnemy.typeItem->features.name;
		String nameEmptyItem = founds.emptyItem->typeItem->features.name;

		bool isLadder = itemEnemy.typeItem->features.category == idCategoryItem::block;
		bool isNotEmpty = nameCurrentItem != nameEmptyItem;

		if (isNotEmpty && isLadder) {
			buildLadder(world);
		}

	}
}

void Entity::checkLevelHealth(Vector2f &movemoment)
{
	entityHealth &healthEnemy = health;
	bool isLowHealth = healthEnemy.currentHealth < (healthEnemy.maxHealth / 4);
	bool canPanic = type->converse.canPanic;
	if (isLowHealth && canPanic) {
		entityStandPanic(movemoment);
	}
	else {
		currenMode = idEntityMode::fight;
	}
}

void Entity::entityStandPanic(Vector2f &movemoment)
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

void Entity::buildLadder(world &world)
{
	int x = int(getXPos() / SIZE_BLOCK);
	int y = int(getYPos() / SIZE_BLOCK);
	int level = currentLevelFloor + 1;

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

bool Entity::findLadder(world &world, Vector3i pos)
{

	int x = int(getXPos() / SIZE_BLOCK);
	int y = int(getYPos() / SIZE_BLOCK);
	int level = pos.z;//currentLevelFloor + 1;

	Field &field = world.field;
	wchar_t(*map)[LONG_MAP][WIDTH_MAP] = field.dataMap;
	wchar_t ladder = field.charBlocks[idBlocks::woodLadder];
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (map[level][y + j][x + i] == ladder) {
				Vector2f posLadder = { float(x + i) * SIZE_BLOCK, float(y + j) * SIZE_BLOCK };
				actionMain(world, posLadder);
				return true;
			}
		}
	}
	return false;
}

void Entity::checkInDirectionWalk(Field &field, float distanse, sf::Vector2i posStart, sf::Vector2i shifts)
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

void Entity::redefineDirectionWalk()
{
	step.currentTime = 0;
	step.timeWalk = minTimeWalk + rand() % (int(maxTimeWalk - minTimeWalk));

	int randomDirection = 1 + rand() % Direction::AMOUNT_DIRECTION;
	directions.directionWalk = Direction(randomDirection);
}

void Entity::checkBlock(Field& field, float distanse)
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

void Entity::Drop(world& world)
{
	Field &field = world.field;
	vector<Item> &items = world.items;
	TypeItem *typesItems = world.typesObjects.typesItem;

	Item* addItem = new Item;
	TypeEnemy& typeEnemy = *type;
	size_t countItem = typeEnemy.drop.minCountItems.size();

	vector<int> &minAmount = typeEnemy.drop.minCountItems;
	vector<int> &maxAmount = typeEnemy.drop.maxCountItems;

	throwItem(field, items);

	int currentAmount;
	for (int i = 0; i < countItem; i++) {

		currentAmount = minAmount[i] + rand() % (maxAmount[i] - minAmount[i] + 2);
		for (int j = 0; j < currentAmount; j++) {
			addItem->setType(typesItems[typeEnemy.drop.dropItems[i]]);
			addItem->setPosition(founds.currentTarget.x + 1,
								 founds.currentTarget.y + 1,
								 currentLevelFloor + 1);
			world.items.push_back(*addItem);

		}

	}
	delete addItem;

}

void Entity::playSoundDeath(world& world)
{
	vector<UnlifeObject> &objects = world.unlifeObjects;
	TypeUnlifeObject *typeObjects = world.typesObjects.typesUnlifeObject;
	UnlifeObject addObject;
	sizeSprite &sizeSprite = type->featuresSprite.size;
	Vector3i pos = { int((getXPos() + sizeSprite.width / 2) / SIZE_BLOCK),
		int((getYPos() + sizeSprite.height / 2) / SIZE_BLOCK),
		currentLevelFloor + 1 };

	bool findSound = true;
	switch (type->id) {
	case idEntity::wolfEnemy:
		addObject.setType(typeObjects[idUnlifeObject::wolfDeathEffect]);
		addObject.setPosition(pos.x, pos.y, pos.z);
		break;
	case idEntity::skeletEnemy:
	case idEntity::skeletBuilderEnemy:
	case idEntity::skeletDiggerEnemy:
	case idEntity::skeletLumbermillEnemy:
	case idEntity::skeletMinerEnemy:
		addObject.setType(typeObjects[idUnlifeObject::skeletDeathEffect]);
		addObject.setPosition(pos.x, pos.y, pos.z);
		break;
	default:
		findSound = false;
		break;
	}

	if (findSound) {
		objects.push_back(addObject);

		Sound &soundObject = objects[objects.size() - 1].soundObject;

		switch (type->id) {
		case idEntity::wolfEnemy:
			::playSound(idSoundPaths::wolfDeathSound, *soundBase, soundObject, getPosition());
			break;
		case idEntity::skeletEnemy:
		case idEntity::skeletBuilderEnemy:
		case idEntity::skeletDiggerEnemy:
		case idEntity::skeletLumbermillEnemy:
		case idEntity::skeletMinerEnemy:
			::playSound(idSoundPaths::skeletonDeathSound, *soundBase, soundObject, getPosition());
			break;
		default:
			break;
		}

	}


}