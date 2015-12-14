#include "UseBlocksAndObjects.h"

using namespace sf;
using namespace std;

void Entity::useBlock(Vector3i pos, world &world,
					  Item & currentItem)
{

	TypeUnlifeObject *typesUnlifeObjects = world.typesObjects.typesUnlifeObject;

	Field &field = world.field;
	vector<UnlifeObject> &unlifeObjects = *world.unlifeObjects;

	bool useForAnyLevel = pos.z > -1;
	if (useForAnyLevel) {
		bool successfullUse;

		wchar_t *block = &field.dataMap[pos.z][pos.y][pos.x];

		int idUseBlock = currentItem.typeItem->idAdd.idBlockForUse;
		int idUseObject = currentItem.typeItem->idAdd.idUnlideOnjectForUse;

		bool isIdBlock = idUseBlock > -1;
		bool isAir = *block == field.charBlocks[idBlocks::air];
		if (isIdBlock && isAir) {
			*block = field.charBlocks[idUseBlock];
			successfullUse = true;
		}
		// Неживой объет
		else if (idUseObject > -1) {
			UnlifeObject* addObject = new UnlifeObject;

			addObject->setType(typesUnlifeObjects[idUseObject]);
			addObject->setPosition(pos.x + 1, pos.y + 1, currentLevelFloor + 1);
			unlifeObjects.push_back(*addObject);

			delete addObject;
			successfullUse = true;
		}
		else {
			successfullUse = false;
		}

		////////////////////////////////
		// Если успешно применён
		if (successfullUse) {
			breakItem(currentItem);
		}
		////////////////////////////////
	}

}

void Entity::upgradeObject(UnlifeObject &object, world &world)
{
	redefineObject &redefine = object.typeObject->redefine;
	Sprite &spriteObject = *object.spriteObject;
	Vector2f currentPos = spriteObject.getPosition();
	Vector2i posOnMap = { int((currentPos.x + SIZE_BLOCK / 2) / SIZE_BLOCK),
		int((currentPos.y + SIZE_BLOCK / 2) / SIZE_BLOCK) };

	TypeUnlifeObject &nextType = world.typesObjects.typesUnlifeObject[redefine.id];

	Vector3i posItems = { posOnMap.x - 1, posOnMap.y - 1, currentLevelFloor + 1 };
	object.dropObject(posItems, world, true);

	object.setType(nextType);
	object.setPosition(posOnMap.x, posOnMap.y, object.currentLevel);
}


void Entity::useAsBukketWithWater(Item &currentItem, world &world, Event event)
{
	TypeItem *typesItems = world.typesObjects.typesItem;
	Field& field = world.field;

	bool pouredWater = event.key.code == Mouse::Left;
	if (pouredWater) {

		int idUseBlock = currentItem.typeItem->idAdd.idBlockForUse;
		if (idUseBlock) {

			int level = currentLevelFloor + 1;
			int x = founds.currentTarget.x;
			int y = founds.currentTarget.y;

			bool isWall = field.dataMap[level][y][x] != field.charBlocks[idBlocks::air];
			if (isWall == false) {

				bool isFloor = field.dataMap[level - 1][y][x] != field.charBlocks[idBlocks::air];
				if (isFloor == false) {
					field.dataMap[level - 1][y][x] = field.charBlocks[idUseBlock];
					minusAmount(currentItem);
				}
				else {
					field.dataMap[level][y][x] = field.charBlocks[idUseBlock];
					minusAmount(currentItem);
				}

			}

		}

	}

	bool drinking = event.key.code == Mouse::Right;
	bool isThirts = thirst.currentThirst < thirst.maxThirst;
	if (drinking && isThirts) {
		thirst.currentThirst += currentItem.currentToughness;
		redefineType(currentItem, world, -1);
	}

}
