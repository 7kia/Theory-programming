#include "../World.h"

using namespace std;

void Entity::searchEnemy(Entity &enemy, world &world, const float deltaTime)
{
	float radiuseView = type->view.radiuseView;
	bool feelEnemy = type->view.feelEnemy;

	bool onLevelEnemy = currentLevelFloor == enemy.currentLevelFloor;
	bool onLevel = onLevelEnemy || feelEnemy;
	bool noAtack = currenMode != idEntityMode::atack;
	Vector2f enemyPoint = enemy.getPosition();
	Vector2f searcherPoint = getPosition();

	float distanse;
	distanse = distansePoints(searcherPoint , enemyPoint);

	if (distanse <= radiuseView && onLevel) {
		Vector2f movemoment;
		if (noAtack) {
			currenMode = idEntityMode::fight;

			movemoment = vectorDirection(searcherPoint , enemyPoint);

			checkLevelHealth(movemoment);
			defineDirectionLook(movemoment);

			if (feelEnemy == false) {
				checkBlock(world.field , distanse);
			}

			bool isFight = currenMode == idEntityMode::fight;
			if (isFight) {

				choiceDirections(movemoment);

				if (wasCollision) {

					if (!onLevelEnemy && feelEnemy) {
						searchWay(world);
					}
					else if (feelEnemy) {
						choiceBlock(world);
					}

				}
				else {

					bool isNearFight = distanse <= SIZE_BLOCK;
					if (isNearFight) {
						currenMode = idEntityMode::atack;
						directions.directionWalk = NONE_DIRECTION;
						founds.currentTarget = RESET_VECTOR_3I;
					}

				}

				if (currenMode == atack
						|| currenMode == fight) {
					founds.findEnemy = &enemy;
				}

			}


		}
		else {
			bool isNearFight = distanse <= SIZE_BLOCK;
			if (isNearFight) {
				if (giveDamage) {
					founds.findEnemy->takeDamage(damage , getCurrentItem());
					resetAtack();
				}
			}
			else {

				if (giveDamage) {

					searchNearCollision(world);

					if (founds.currentTarget != RESET_VECTOR_3I) {
						breakNearCollision(world);
					}
				}

			}
		}
	}
	else {
		founds.currentTarget = RESET_VECTOR_3I;
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

void Entity::defineDirectionLook(Vector2f movemoment)
{
	bool xAboutZero = movemoment.x >= -BORDER_VALUE_FOR_DIRECTION && movemoment.x <= BORDER_VALUE_FOR_DIRECTION;
	bool yAboutZero = movemoment.y >= -BORDER_VALUE_FOR_DIRECTION && movemoment.y <= BORDER_VALUE_FOR_DIRECTION;

	if (movemoment.x > BORDER_VALUE_FOR_DIRECTION && movemoment.y > BORDER_VALUE_FOR_DIRECTION) {
		directions.directionLook = DOWN_RIGHT;
	}
	else if (movemoment.x < -BORDER_VALUE_FOR_DIRECTION && movemoment.y > BORDER_VALUE_FOR_DIRECTION) {
		directions.directionLook = DOWN_LEFT;
	}
	else if (movemoment.x < -BORDER_VALUE_FOR_DIRECTION && movemoment.y < -BORDER_VALUE_FOR_DIRECTION) {
		directions.directionLook = UP_LEFT;
	}
	else if (movemoment.x > BORDER_VALUE_FOR_DIRECTION && movemoment.y < BORDER_VALUE_FOR_DIRECTION) {
		directions.directionLook = UP_RIGHT;
	}
	else if (movemoment.y >= BORDER_VALUE_FOR_DIRECTION && xAboutZero) {
		directions.directionLook = DOWN;
	}
	else if (movemoment.y <= -BORDER_VALUE_FOR_DIRECTION && xAboutZero) {
		directions.directionLook = UP;
	}
	else if (movemoment.x >= BORDER_VALUE_FOR_DIRECTION && yAboutZero) {
		directions.directionLook = RIGHT;
	}
	else if (movemoment.x <= -BORDER_VALUE_FOR_DIRECTION && yAboutZero) {
		directions.directionLook = LEFT;
	}
	else {
		directions.directionLook = NONE_DIRECTION;
	}
}

void Entity::choiceBlock(world &world)
{
	int x = collision.posBlock.x;
	int y = collision.posBlock.y;
	int level = collision.posBlock.z;

	int xShift = 0;
	int yShift = 0;
	choiceDirectionLook(xShift , yShift);


	Field &field = world.field;
	wchar_t	*block = &field.dataMap[level][y][x];
	int idNature;
	idNature = field.idsNature[field.findIdBlock(*block)];

	if (idNature <= idNatureObject::Unbreaking) {
		vector<UnlifeObject> &objects = world.unlifeObjects;
		UnlifeObject &findObject = world.emptyObjects.emptyObject;

		for (int i = 0; i < objects.size(); i++) {
			if (objects[i].getPosition() == collision.posObject) {
				findObject = objects[i];
			}
		}
		idNature = findObject.typeObject->idNature;
	}
	else {
		founds.currentTarget = { x, y, level };
	}
	if (idNature != idNatureObject::Unbreaking) {
		currenMode = idEntityMode::atack;
		giveDamage = false;
	}
}

void Entity::choiceDirections(Vector2f movemoment)
{
	bool xAboutZero = movemoment.x >= -BORDER_VALUE_FOR_DIRECTION && movemoment.x <= BORDER_VALUE_FOR_DIRECTION;
	bool yAboutZero = movemoment.y >= -BORDER_VALUE_FOR_DIRECTION && movemoment.y <= BORDER_VALUE_FOR_DIRECTION;

	if (movemoment.x > BORDER_VALUE_FOR_DIRECTION && movemoment.y > BORDER_VALUE_FOR_DIRECTION) {
		directions.directionWalk = DOWN_RIGHT;
	}
	else if (movemoment.x < -BORDER_VALUE_FOR_DIRECTION && movemoment.y > BORDER_VALUE_FOR_DIRECTION) {
		directions.directionWalk = DOWN_LEFT;
	}
	else if (movemoment.x < -BORDER_VALUE_FOR_DIRECTION && movemoment.y < -BORDER_VALUE_FOR_DIRECTION) {
		directions.directionWalk = UP_LEFT;
	}
	else if (movemoment.x > BORDER_VALUE_FOR_DIRECTION && movemoment.y < BORDER_VALUE_FOR_DIRECTION) {
		directions.directionWalk = UP_RIGHT;
	}
	else if (movemoment.y >= BORDER_VALUE_FOR_DIRECTION && xAboutZero) {
		directions.directionWalk = DOWN;
	}
	else if (movemoment.y <= -BORDER_VALUE_FOR_DIRECTION && xAboutZero) {
		directions.directionWalk = UP;
	}
	else if (movemoment.x >= BORDER_VALUE_FOR_DIRECTION && yAboutZero) {
		directions.directionWalk = RIGHT;
	}
	else if (movemoment.x <= -BORDER_VALUE_FOR_DIRECTION && yAboutZero) {
		directions.directionWalk = LEFT;
	}
	else {
		directions.directionWalk = NONE_DIRECTION;
	}
}

void Entity::checkBlock(Field& field , float distanse)
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
	checkInDirectionWalk(field , distanse , startPosition , shifts);
}

void Entity::checkInDirectionWalk(Field &field , float distanse , sf::Vector2i posStart , sf::Vector2i shifts)
{
	int level = currentLevelFloor + 1;
	int x = posStart.x;
	int y = posStart.y;
	int xShift = shifts.x;
	int yShift = shifts.y;


	int countCheckingBlocks = int(distanse / SIZE_BLOCK);
	int count = 1;
	while (!isExitFromBorder(x , y) && count < countCheckingBlocks) {

		bool checkX = field.dataMap[level][y][x + xShift] != field.charBlocks[idBlocks::air];
		bool checkY = field.dataMap[level][y + yShift][x] != field.charBlocks[idBlocks::air];
		bool checkXAndY = field.dataMap[level][y + yShift][x + xShift] != field.charBlocks[idBlocks::air];
		bool summaryCondition = false;
		if (xShift != 0 && yShift != 0) {
			summaryCondition = checkXAndY;
		}
		if (xShift != 0) {
			summaryCondition = checkX;
		}
		else if (yShift != 0) {
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

void Entity::searchNearCollision(world & world)
{
	Field &field = world.field;
	Vector3i posUse;
	int x = int(getXPos() / SIZE_BLOCK);
	int y = int(getYPos() / SIZE_BLOCK);
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			posUse = { x + j, y + i, currentLevelFloor + 1 };
			if (field.dataMap[posUse.z][posUse.y][posUse.x] != field.charBlocks[idBlocks::air]
					|| isUnlifeObject(posUse , world)) {
				founds.currentTarget = { x + j, y + i, currentLevelFloor + 1 };
				break;
			}
		}

	}

}

void Entity::searchWay(world &world)
{
	Item &itemEnemy = itemFromPanelQuickAccess[idSelectItem];

	Vector3i posEnemy = { int(getXPos() / SIZE_BLOCK),
		int(getXPos() / SIZE_BLOCK),
		currentLevelFloor + 1 };

	if (!findLadder(world , posEnemy)) {

		String nameCurrentItem = itemEnemy.typeItem->features.name;
		String nameEmptyItem = founds.emptyItem->typeItem->features.name;

		bool isLadder = itemEnemy.typeItem->features.category == idCategoryItem::block;
		bool isNotEmpty = nameCurrentItem != nameEmptyItem;

		if (isNotEmpty && isLadder) {
			buildLadder(world);
		}

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
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (map[level][y + j][x + i] == air) {
				Vector3i pos = { x + i, y + j, level };
				useBlock(pos , world , currentItem);
			}
		}
	}
}

bool Entity::findLadder(world &world , Vector3i pos)
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
				actionMain(world , posLadder);
				return true;
			}
		}
	}
	return false;
}

void Entity::resetFightAnimation()
{
	animation.currentTimeFightAnimation = 0.f;
}
