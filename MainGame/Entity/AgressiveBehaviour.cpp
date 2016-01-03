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
		Vector2f movement;
		if (noAtack) {
			currenMode = idEntityMode::fight;

			movement = vectorDirection(searcherPoint , enemyPoint);

			checkLevelHealth(movement);
			defineDirectionLook(movement);

			if (feelEnemy == false) {
				checkBlock(world.field , distanse);
			}

			bool isFight = currenMode == idEntityMode::fight;
			if (isFight) {

				choiceDirections(movement);

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
						getCurrentTarget() = RESET_VECTOR_3I;
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

					if (getCurrentTarget() != RESET_VECTOR_3I) {
						breakNearCollision(world);
					}
				}

			}
		}
	}
	else {
		getCurrentTarget() = RESET_VECTOR_3I;
	}
}

void Entity::checkLevelHealth(Vector2f &movement)
{
	entityHealth &healthEnemy = health;
	bool isLowHealth = healthEnemy.currentHealth < (healthEnemy.maxHealth / 4);
	bool canPanic = type->converse.canPanic;
	if (isLowHealth && canPanic) {
		entityStandPanic(movement);
	}
	else {
		currenMode = idEntityMode::fight;
	}
}

void Entity::defineDirectionLook(Vector2f movement)
{
	bool xAboutZero = movement.x >= -BORDER_VALUE_FOR_DIRECTION && movement.x <= BORDER_VALUE_FOR_DIRECTION;
	bool yAboutZero = movement.y >= -BORDER_VALUE_FOR_DIRECTION && movement.y <= BORDER_VALUE_FOR_DIRECTION;

	if (movement.x > BORDER_VALUE_FOR_DIRECTION && movement.y > BORDER_VALUE_FOR_DIRECTION) {
		directions.directionLook = DOWN_RIGHT;
	}
	else if (movement.x < -BORDER_VALUE_FOR_DIRECTION && movement.y > BORDER_VALUE_FOR_DIRECTION) {
		directions.directionLook = DOWN_LEFT;
	}
	else if (movement.x < -BORDER_VALUE_FOR_DIRECTION && movement.y < -BORDER_VALUE_FOR_DIRECTION) {
		directions.directionLook = UP_LEFT;
	}
	else if (movement.x > BORDER_VALUE_FOR_DIRECTION && movement.y < BORDER_VALUE_FOR_DIRECTION) {
		directions.directionLook = UP_RIGHT;
	}
	else if (movement.y >= BORDER_VALUE_FOR_DIRECTION && xAboutZero) {
		directions.directionLook = DOWN;
	}
	else if (movement.y <= -BORDER_VALUE_FOR_DIRECTION && xAboutZero) {
		directions.directionLook = UP;
	}
	else if (movement.x >= BORDER_VALUE_FOR_DIRECTION && yAboutZero) {
		directions.directionLook = RIGHT;
	}
	else if (movement.x <= -BORDER_VALUE_FOR_DIRECTION && yAboutZero) {
		directions.directionLook = LEFT;
	}
	else {
		directions.directionLook = NONE_DIRECTION;
	}
}

void Entity::choiceBlock(world &world)
{
	Vector3i &posBlock = collision.posBlock;

	Field &field = world.field;
	wchar_t	*block = &field.dataMap[posBlock.z][posBlock.y][posBlock.x];
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
		getCurrentTarget() = collision.posBlock;
	}
	if (idNature != idNatureObject::Unbreaking) {
		currenMode = idEntityMode::atack;
		giveDamage = false;
	}
}

void Entity::choiceDirections(Vector2f movement)
{
	bool xAboutZero = movement.x >= -BORDER_VALUE_FOR_DIRECTION && movement.x <= BORDER_VALUE_FOR_DIRECTION;
	bool yAboutZero = movement.y >= -BORDER_VALUE_FOR_DIRECTION && movement.y <= BORDER_VALUE_FOR_DIRECTION;

	if (movement.x > BORDER_VALUE_FOR_DIRECTION && movement.y > BORDER_VALUE_FOR_DIRECTION) {
		directions.directionWalk = DOWN_RIGHT;
	}
	else if (movement.x < -BORDER_VALUE_FOR_DIRECTION && movement.y > BORDER_VALUE_FOR_DIRECTION) {
		directions.directionWalk = DOWN_LEFT;
	}
	else if (movement.x < -BORDER_VALUE_FOR_DIRECTION && movement.y < -BORDER_VALUE_FOR_DIRECTION) {
		directions.directionWalk = UP_LEFT;
	}
	else if (movement.x > BORDER_VALUE_FOR_DIRECTION && movement.y < BORDER_VALUE_FOR_DIRECTION) {
		directions.directionWalk = UP_RIGHT;
	}
	else if (movement.y >= BORDER_VALUE_FOR_DIRECTION && xAboutZero) {
		directions.directionWalk = DOWN;
	}
	else if (movement.y <= -BORDER_VALUE_FOR_DIRECTION && xAboutZero) {
		directions.directionWalk = UP;
	}
	else if (movement.x >= BORDER_VALUE_FOR_DIRECTION && yAboutZero) {
		directions.directionWalk = RIGHT;
	}
	else if (movement.x <= -BORDER_VALUE_FOR_DIRECTION && yAboutZero) {
		directions.directionWalk = LEFT;
	}
	else {
		directions.directionWalk = NONE_DIRECTION;
	}
}

void Entity::checkBlock(Field& field , float distanse)
{
	Vector2i startPosition = { 0, 0 };
	Vector2i shifts = { 0, 0 };

	switch (directions.directionLook) {
	case DOWN_LEFT:
		startPosition.x = getXPosOnMap() - 1;
		startPosition.y = getYPosOnMap() + 1;
		shifts.x = -1;
		shifts.y = 1;
		break;
	case DOWN_RIGHT:
		startPosition.x = getXPosOnMap() + 1;
		startPosition.y = getYPosOnMap() + 1;
		shifts.x = 1;
		shifts.y = 1;
		break;
	case UP_LEFT:
		startPosition.x = getXPosOnMap() - 1;
		startPosition.y = getYPosOnMap() - 1;
		shifts.x = -1;
		shifts.y = -1;
		break;
	case UP_RIGHT:
		startPosition.x = getXPosOnMap() + 1;
		startPosition.y = getYPosOnMap() - 1;
		shifts.x = 1;
		shifts.y = -1;
		break;
	case LEFT:
		startPosition.x = getXPosOnMap() - 1;
		startPosition.y = getYPosOnMap();
		shifts.x = -1;
		shifts.y = 0;
		break;
	case RIGHT:
		startPosition.x = getXPosOnMap() + 1;
		startPosition.y = getYPosOnMap();
		shifts.x = 1;
		shifts.y = 0;
		break;
	case UP:
		startPosition.x = getXPosOnMap();
		startPosition.y = getYPosOnMap() - 1;
		shifts.x = 0;
		shifts.y = -1;
		break;
	case DOWN:
		startPosition.x = getXPosOnMap();
		startPosition.y = getYPosOnMap() + 1;
		shifts.x = 0;
		shifts.y = 1;
		break;
	default:
		break;
	}

	checkInDirectionWalk(field , distanse , startPosition , shifts);
}

void Entity::checkInDirectionWalk(Field &field , float distanse , sf::Vector2i posStart , sf::Vector2i shifts)
{
	int level = currentLevelFloor + 1;
	int x = posStart.x;
	int y = posStart.y;


	int countCheckingBlocks = int(distanse / SIZE_BLOCK);
	int count = 1;
	while (!isExitFromBorder(x , y) && count < countCheckingBlocks) {

		bool checkX = field.dataMap[level][y][x + shifts.x] != field.charBlocks[idBlocks::air];
		bool checkY = field.dataMap[level][y + shifts.y][x] != field.charBlocks[idBlocks::air];
		bool checkXAndY = field.dataMap[level][y + shifts.y][x + shifts.x] != field.charBlocks[idBlocks::air];
		bool summaryCondition = false;
		if (shifts.x != 0 && shifts.y != 0) {
			summaryCondition = checkXAndY;
		}
		if (shifts.x != 0) {
			summaryCondition = checkX;
		}
		else if (shifts.y != 0) {
			summaryCondition = checkY;
		}

		if (summaryCondition) {
			currenMode = idEntityMode::walk;
			if (wasCollision) {
				redefineDirectionWalk();
			}
			break;
		}
		x += shifts.x;
		y += shifts.y;
		count++;
	}
}

void Entity::searchNearCollision(world & world)
{
	Field &field = world.field;
	Vector3i posUse;
	int x = getXPosOnMap();
	int y = getYPosOnMap();
	bool needExit = false;
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			posUse = { x + j, y + i, currentLevelFloor + 1 };
			if (field.dataMap[posUse.z][posUse.y][posUse.x] != field.charBlocks[idBlocks::air]
					|| isUnlifeObject(posUse , world)) {
				getCurrentTarget() = posUse;
				needExit = true;
				break;
			}
		}
		if(needExit)
		{
			break;
		}
	}

}

void Entity::searchWay(world &world)
{
	Item &itemEnemy = getCurrentItem();

	Vector3i posEnemy = { getXPosOnMap(),
												getYPosOnMap(),
												currentLevelFloor + 1 };

	if (!findLadder(world , posEnemy)) {

		String nameCurrentItem = itemEnemy.getName();
		String nameEmptyItem = getRefOnEmptyItem()->getName();

		bool isLadder = (itemEnemy.getIdCategory() == idCategoryItem::block);
		bool isNotEmpty = (nameCurrentItem != nameEmptyItem);

		if (isNotEmpty && isLadder) {
			buildLadder(world);
		}

	}
}

void Entity::buildLadder(world &world)
{
	int x = getXPosOnMap();
	int y = getYPosOnMap();
	int level = currentLevelFloor + 1;

	Item &currentItem = getCurrentItem();

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

	int x = getXPosOnMap();
	int y = getYPosOnMap();
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
