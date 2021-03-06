#include "Entity.h"

using namespace std;


void currentCollision::initPosBlock(int xPos , int yPos , int zPos)
{
	posBlock.x = xPos;
	posBlock.y = yPos;
	posBlock.z = zPos;
}

void currentCollision::clear()
{
	posObject = RESET_VECTOR_2F;
	levelObject = RESET_COLLISION_VALUE;
	posBlock = RESET_VECTOR_3I;
}

void Entity::interactionWitnUnlifeObject(vector<UnlifeObject> &unlifeObjects , const float deltaTime)// ������� for enity and mainPerson
{
	wasCollision = false;
	collision.clear();

	Sprite *spriteObject;
	FloatRect objectBound;

	int levelUnlifeObject;
	Sprite *transparentSpiteObject;
	FloatRect objectAltBound;

	spriteEntity->move(movement);
	FloatRect entityBound = spriteEntity->getGlobalBounds();
	spriteEntity->move(-movement);


	for (int i = 0; i < unlifeObjects.size(); i++) {
		levelUnlifeObject = unlifeObjects[i].currentLevel;

		spriteObject = unlifeObjects[i].spriteObject;
		objectBound = spriteObject->getGlobalBounds();

		transparentSpiteObject = unlifeObjects[i].transparentSpiteObject;
		objectAltBound = transparentSpiteObject->getGlobalBounds();

		if (entityBound.intersects(objectBound) && (levelUnlifeObject == currentLevelFloor + 1)) {
			wasCollision = true;

			collision.posObject = unlifeObjects[i].getPosition();
			collision.levelObject = unlifeObjects[i].currentLevel;

			directions.directionWalk = NONE_DIRECTION;
			break;
		}
		else if (type->id == idEntity::playerEntity) {
			if (entityBound.intersects(objectAltBound) && (levelUnlifeObject == currentLevelFloor + 1)) {
				transparentSpiteObject->setColor(TRANSPARENT_COLOR);
			}
			else {
				transparentSpiteObject->setColor(NORMAL_COLOR);
			}
		}

	}

}

void Entity::interactionWithEntity(vector<Entity> *enemys , int id , const float deltaTime)// ������� for enity and mainPerson
{
	if (!wasCollision) {
		float &dx = movement.x;
		float &dy = movement.y;

		float x;
		float y;
		x = getXPos();
		y = getYPos();


		Sprite *spriteObject;
		FloatRect objectBound;

		int levelUnlifeObject;

		spriteEntity->move(movement);
		FloatRect entityBound = spriteEntity->getGlobalBounds();
		spriteEntity->move(-movement);


		vector<Entity> &objects = *enemys;
		for (int i = 0; i != objects.size(); ++i) {

			if (id != i) {
				levelUnlifeObject = objects[i].currentLevelFloor;

				spriteObject = objects[i].spriteEntity;
				objectBound = spriteObject->getGlobalBounds();


				if (entityBound.intersects(objectBound) && (levelUnlifeObject == currentLevelFloor)) {
					wasCollision = true;

					founds.findEnemy = &objects[i];
					directions.directionWalk = NONE_DIRECTION;
					break;
				}

			}

		}
	}
}

void Entity::interactionWithMap(Field &field , listDestroyObjectsAndBlocks& listDestroy , const float deltaTime)
{
	if (!wasCollision) {
		Vector2f posEntity = getPosition();
		posEntity = posEntity + movement;

		float x = posEntity.x;
		float y = posEntity.y;

		wchar_t(*map)[LONG_MAP][WIDTH_MAP] = field.dataMap;

		if (!isExitFromBorder(posEntity.x , posEntity.y)) {
			int xPos = int(x / SIZE_BLOCK);
			int yPos = int(y / SIZE_BLOCK);

			sizeSprite &size = type->featuresSprite.size;
			float xFar = (x + size.width / 2) / SIZE_BLOCK;
			float yFar = (y + size.height / 2) / SIZE_BLOCK;
			/////////////////////////////////////////////
			// �����
			for (int i = yPos; float(i) < yFar; i++) {
				for (int j = xPos; float(j) < xFar; j++) {

					if (!isInListBlocks(listDestroy.passableBlocks , map[currentLevelFloor + 1][i][j])) {
						wasCollision = true;

						collision.initPosBlock(j , i , currentLevelFloor + 1);
					}

					if (wasCollision) {
						break;
					}
				}
			}
			/////////////////////////////////////////////
			// ���
			for (int i = yPos; float(i) < yFar; i++) {
				for (int j = xPos; float(j) < xFar; j++) {
					if (isInListBlocks(listDestroy.notPassableFloor , map[currentLevelFloor][i][j])) {
						wasCollision = true;

						collision.initPosBlock(j , i , currentLevelFloor);
					}

					if (wasCollision) {
						break;
					}
				}
			}
		}
		else {
			wasCollision = true;
		}

	}


	if (!wasCollision) {
		spriteEntity->move(movement);
	}
	else {
		directions.directionWalk = NONE_DIRECTION;
	}


	gravitateToGround(field);

	movement = { 0.f, 0.f };
}

void Entity::gravitateToGround(Field &field)
{
	Vector2i posBlock = { int(getXPos() / SIZE_BLOCK), int(getYPos() / SIZE_BLOCK) };

	wchar_t(*map)[LONG_MAP][WIDTH_MAP] = field.dataMap;

	if (map[currentLevelFloor][posBlock.y][posBlock.x] == field.charBlocks[idBlocks::air]) {
		currentLevelFloor--;
		spriteEntity->setPosition(float(posBlock.x * SIZE_BLOCK) , float(posBlock.y * SIZE_BLOCK));
	}
}

