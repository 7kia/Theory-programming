#include "UseTool.h"

using namespace std;
using namespace sf;

void Entity::useTool(Vector3i &pos, world &world, Item &currentItem) {

	UnlifeObject &findObject = *founds.findObject;

	int idFinded = founds.findObject->typeObject->id;
	int idEmpty = founds.emptyObject->typeObject->id;
	bool isObject = idFinded != idEmpty && &findObject;

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

	int idNature = defineIdNature(world.field, isDestroyEffect, pos);
	bool canBreakTheItem = isInListObjects(*listBreaking, idNature);


	if (canBreakTheItem) {

		breakFindObject(currentItem);
		playObjectBreakSound(idNature);
		if (findObject->isDestroyed()) {
			vector<int> &deleteUnlifeObjects = world.deleteUnlifeObjects;
			int &idFinded = founds.findObjectFromList;
			if (!isInListObjects(deleteUnlifeObjects, idFinded) && idFinded > -1) {

				destroyFindObject(isDestroyEffect, pos, world);
				deleteUnlifeObjects.push_back(idFinded);

				breakItem(currentItem);
			}

			founds.currentTarget = RESET_VECTOR_3I;
			idFinded = RESET_COLLISION_VALUE;
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

void Entity::breakNearCollision(world &world)
{
	Item &currentItem = itemFromPanelQuickAccess[idSelectItem];
	vector<int> *listBreaking = currentItem.typeItem->destroy;
	Field &field = world.field;

	Vector3i &posUse = founds.currentTarget;
	int idNature = defineIdNature(world , posUse);

	bool canBreakTheItem = isInListObjects(*listBreaking, idNature);
	if (canBreakTheItem) {

		wchar_t	*block = &field.dataMap[posUse.z][posUse.y][posUse.x];
		bool isObject = isUnlifeObject(posUse , world);

		if (!isObject && *block != field.charBlocks[idBlocks::air]) {
			createDestroyEffect(world, posUse);
			playObjectBreakSound(idNature);
			resetAtack();
		}
		else if(isObject){
			useTool(posUse, world, itemFromPanelQuickAccess[idSelectItem]);
		}

	}

	
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
	UnlifeObject *findObject = founds.findObject;

	if (isEffect) {
		wchar_t	*block = &field.dataMap[pos.z][pos.y][pos.x];
		return field.idsNature[field.findIdBlock(*block)];
	}
	else {
		return findObject->typeObject->idNature;
	}

}

int Entity::defineIdNature(world & world , sf::Vector3i pos)
{
	Field &field = world.field;
	wchar_t	*block = &field.dataMap[pos.z][pos.y][pos.x];

	bool isObject = isUnlifeObject(pos , world);

	int idNature;
	idNature = field.idsNature[field.findIdBlock(*block)];

	if (idNature <= idNatureObject::Unbreaking) {
		if (isObject) {
			return founds.findObject->typeObject->idNature;
		}
		else {
			return idNatureObject::Unbreaking;
		}
	}
	return idNature;
}

bool Entity::isDestroyEffect(sf::Vector3i & pos, world & world)
{
	vector<UnlifeObject> &objects = world.unlifeObjects;

	Vector2f posAdd = { float(pos.x + 1) * SIZE_BLOCK - SIZE_BLOCK / 2,
											float(pos.y + 1) * SIZE_BLOCK - SIZE_BLOCK / 2 };

	int idObject;
	Sprite *spriteCheck;
	for (int i = 0; i < objects.size(); i++) {
		idObject = objects[i].typeObject->id;
		spriteCheck = objects[i].spriteObject;
		if (idObject == idUnlifeObject::destroyBlockEffect) {
			if (spriteCheck->getGlobalBounds().contains(posAdd)) {
				// TODO
				founds.findObject = &objects[i];
				return true;
			}
		}
	}

	return false;
}

bool Entity::isUnlifeObject(sf::Vector3i & pos, world & world)
{
	vector<UnlifeObject> &objects = world.unlifeObjects;

	Vector2f posAdd = { float(pos.x + 1) * SIZE_BLOCK - SIZE_BLOCK / 2,
		float(pos.y + 1) * SIZE_BLOCK - SIZE_BLOCK / 2 };

	int idObject;
	Sprite *spriteCheck;
	for (int i = 0; i < objects.size(); i++) {
		idObject = objects[i].typeObject->id;
		spriteCheck = objects[i].spriteObject;
			if (spriteCheck->getGlobalBounds().contains(posAdd)) {
				// TODO
				founds.findObject = &objects[i];
				return true;
			}
	}

	return false;
}