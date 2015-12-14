#include "UseTool.h"

using namespace std;
using namespace sf;

void Entity::useTool(Vector3i &pos, world &world, Item &currentItem) {

	UnlifeObject *findObject = founds.findObject;

	int idFinded = findObject->typeObject->id;
	int idEmpty = founds.emptyObject->typeObject->id;
	bool isObject = idFinded != idEmpty && findObject;

	if (isObject) {
		useToolToObject(pos, world, currentItem);
	}
}

void Entity::useToolToObject(Vector3i &pos, world &world, Item &currentItem)
{
	resetAtack();

	UnlifeObject *findObject = founds.findObject;
	vector<int> *listBreaking = currentItem.typeItem->destroy;

	bool isDestroyEffect = findObject->typeObject->id == idUnlifeObject::destroyBlockEffect;
	bool canBreakTheItem = isInListObjects(*listBreaking, findObject->typeObject->idNature);
	if (canBreakTheItem || isDestroyEffect) {


		breakFindObject(currentItem);

		int idNature = defineIdNature(world.field, isDestroyEffect, pos);
		playObjectBreakSound(idNature);


		if (findObject->isDestroyed()) {
			if (!isInListObjects(*world.deleteUnlifeObjects, founds.findObjectFromList)) {
				destroyFindObject(isDestroyEffect, pos, world);
				breakItem(currentItem);
			}
		}



	}
}

void Entity::breakFindObject(Item &currentItem)
{
	UnlifeObject *findObject = founds.findObject;
	typeDamageItem &damageItem = currentItem.typeItem->damageItem;

	int &toughnessObject = findObject->currentToughness;
	toughnessObject -= damageItem.crushingDamage;
}

void Entity::destroyFindObject(bool isEffect, Vector3i pos, world &world)
{
	int x = pos.x;
	int y = pos.y;
	int level = pos.z;

	Field &field = world.field;
	wchar_t	*block = &field.dataMap[level][y][x];

	Vector3i posDrop = { x, y, level };
	if (isEffect) {
		dropBlock(world, posDrop, currentLevelFloor + 1);

		*block = field.charBlocks[idBlocks::air];
	}
	else {
		founds.findObject->dropObject(posDrop, world, false);
	}

}

int Entity::defineIdNature(Field & field, bool isEffect, Vector3i pos)
{
	int x = pos.x;
	int y = pos.y;
	int level = pos.z;
	UnlifeObject *findObject = founds.findObject;

	if (isEffect) {
		wchar_t	*block = &field.dataMap[level][y][x];
		return field.idsNature[field.findIdBlock(*block)];
	}
	else {
		return findObject->typeObject->idNature;
	}

}


bool Entity::isDestroyEffect(sf::Vector3i & pos, world & world)
{
	vector<UnlifeObject> &objects = *world.unlifeObjects;

	Vector2f posAdd = { float(pos.x + 1) * SIZE_BLOCK - SIZE_BLOCK / 2,
		float(pos.y + 1) * SIZE_BLOCK - SIZE_BLOCK / 2 };

	int idObject;
	Sprite *spriteCheck;
	for (int i = 0; i < objects.size(); i++) {
		idObject = objects[i].typeObject->id;
		spriteCheck = objects[i].spriteObject;
		if (idObject == idUnlifeObject::destroyBlockEffect) {
			if (spriteCheck->getGlobalBounds().contains(posAdd)) {
				// йняршкэ
				founds.findObject = &objects[i];
				return true;
			}
		}
	}

	return false;
}
