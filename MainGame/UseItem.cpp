#include "UseItem.h"

using namespace sf;
using namespace std;

void Entity::defineLevel(int &number, Event event)
{
	if (event.key.code == Mouse::Left) {
		number = currentLevelFloor + 1;
	} else if (event.key.code == Mouse::Right) {
		number = currentLevelFloor;
	} else {
		number = -1;
	}
}

void Entity::redefineType(Item &currentItem, TypeItem *typesItems, int shift)
{
	int *idItem = &currentItem.typeItem->features.id;
	int defineType = *idItem + shift;

	*idItem = defineType - shift;
	currentItem.setType(typesItems[defineType]);
	currentItem.mainSprite->scale(normalSize);
}

void Entity::takeItem(world &world, Vector2f pos)
{
	vector<Item> &items = *world.items;
	if (founds.findItem->typeItem->features.name != founds.emptyItem->typeItem->features.name) {
		if (isInUseField(pos.x, pos.y, true)) {
			//////////////////////////////////////////////////////////////////////////////////////////////////////
			// Если есть место
			if (isEmptySlot()) {


				////////////////////////////////////////////////////////////////////
				// Если нашли предмет
				int levelItem = items[founds.findItemFromList].currentLevel;

				Sprite *spriteItem = items[founds.findItemFromList].mainSprite;
				FloatRect objectItem = spriteItem->getGlobalBounds();

				if (objectItem.contains(pos.x, pos.y) && levelItem == currentLevelFloor + 1) {
					// Перемещаем в инвентарь
					//printf("added!1\n");
					itemFromPanelQuickAccess[emptySlot] = items[founds.findItemFromList];
					itemFromPanelQuickAccess[emptySlot].mainSprite->scale(normalSize);
					// Удаляем из мира
					items.erase(items.begin() + founds.findItemFromList);
				}
				////////////////////////////////////////////////////////////////////


			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////
		}
	}
}

void Entity::useAsBottleWithWater(Item &currentItem, TypeItem *typesItems, Event event)
{
	bool drinking = event.key.code == Mouse::Right;
	bool isThirts = thirst.currentThirst < thirst.maxThirst;
	if (drinking && isThirts)
	{
		thirst.currentThirst += currentItem.currentToughness;
		redefineType(currentItem, typesItems, -1);
	}


}

void Entity::useAsEmptyBottle(Item &currentItem, TypeItem *typesItems, Field &field, int level)
{
	bool useToAnyLevel = level > -1;
	if (useToAnyLevel) {

		int idUseBlock = currentItem.typeItem->idAdd.idBlockForUse;
		if (idUseBlock) {

			int x = founds.currentTarget.x;
			int y = founds.currentTarget.y;
			wchar_t block = field.dataMap[level][y][x];
			bool isWater = block == field.charBlocks[idUseBlock];
			if (isWater) {
				redefineType(currentItem, typesItems, 1);
			}
		}
	}

}

void Entity::useAsEmptyBukket(Item &currentItem, TypeItem *typesItems, Field &field, int level)
{

	bool useToAnyLevel = level > -1;
	if (useToAnyLevel) {
		int idUseBlock = currentItem.typeItem->idAdd.idBlockForUse;
		if (idUseBlock) {

			int x = founds.currentTarget.x;
			int y = founds.currentTarget.y;

			wchar_t *block = &field.dataMap[level][y][x];
			bool isWater = *block == field.charBlocks[idUseBlock];
			if (isWater) {
				*block = field.charBlocks[idBlocks::air];
				redefineType(currentItem, typesItems, 1);
			}

		}

	}
}

void Entity::useAsFood(Item &currentItem, Event event)
{
	bool eating = event.key.code == Mouse::Right;
	bool isHungry = hungry.currentHungry < hungry.maxHungry;
	if (eating && isHungry) {
		hungry.currentHungry += currentItem.currentToughness;
		currentItem = *founds.emptyItem;
	}
}

void Entity::useAsBukketWithWater(Item &currentItem, TypeItem *typesItems, Event event, Field& field)
{
	bool drinking = event.key.code == Mouse::Right;
	bool isThirts = thirst.currentThirst < thirst.maxThirst;
	if (isThirts && drinking) {
		thirst.currentThirst += currentItem.currentToughness;
	}

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
				} else {
					field.dataMap[level][y][x] = field.charBlocks[idUseBlock];
				}

			}

		}

	}

	if (event.key.code == Mouse::Left || event.key.code == Mouse::Right) {
		int *idItem = &currentItem.typeItem->features.id;
		int defineType = *idItem - 1;

		*idItem = defineType + 1;

		currentItem.setType(typesItems[defineType]);
		currentItem.mainSprite->scale(normalSize);

	}


}

void Entity::breakItem(Item &currentItem)
{
	currentItem.currentToughness -= 1;
	if (currentItem.currentToughness < 1) {
		currentItem = *founds.emptyItem;
	}
}

void Entity::dropObject(Vector2i pos, vector<Item> &items, TypeItem* typesItems)
{
	//////////////////////////////////////////////////
	// Выпадение предметов
	Item* addItem = new Item;
	int countItem = founds.findObject->typeObject->drop.minCountItems.size();

	vector<int> &minAmount = founds.findObject->typeObject->drop.minCountItems;
	vector<int> &maxAmount = founds.findObject->typeObject->drop.maxCountItems;
	vector<int> &idItems = founds.findObject->typeObject->drop.dropItems;

	int currentAmount;
	for (int i = 0; i < countItem; i++) {

		currentAmount = minAmount[i] + rand() % (maxAmount[i] - minAmount[i] + 1);
		for (int j = 0; j < currentAmount; j++) {
			addItem->setType(typesItems[idItems[i]]);
			addItem->setPosition(pos.x + 1, pos.y + 1, currentLevelFloor + 1);
			items.push_back(*addItem);

		}

	}
	delete addItem;
	//////////////////////////////////////////////////
}

void Entity::useTool(Vector3i pos, world &world, Item &currentItem) {

	///*
	TypeItem *typesItems = world.typesObjects.typesItem;
	Field &field = world.field;
	vector<Item> &items = *world.items;
	vector<UnlifeObject> &unlifeObjects = *world.unlifeObjects;

	int x = pos.x;
	int y = pos.y;
	int level = pos.z;

	wchar_t* block = &field.dataMap[level][y][x];
	wchar_t *listBlocks = currentItem.typeItem->destroy.blocks;
	String *listObjects = currentItem.typeItem->destroy.objects;
	int countObjects = currentItem.typeItem->destroy.amountObjects;

	bool isObject = founds.findObject != founds.emptyObject;
	if (isObject) {

		if (isInListObjects(listObjects, countObjects)) {



			Vector2i posDrop = { x, y };
			dropObject(posDrop, items, typesItems);

			unlifeObjects.erase(unlifeObjects.begin() + founds.findObjectFromList);

			breakItem(currentItem);


		}
	} else if (isInListBlocks(*block, listBlocks)) {


		//////////////////////////////
		// Выпадение предмета
		Item* addItem = new Item;

		addItem->setType(typesItems[field.findIdBlock(*block)]);
		addItem->setPosition(x + 1, y + 1, currentLevelFloor + 1);
		items.push_back(*addItem);

		delete addItem;
		//////////////////////////////

		*block = field.charBlocks[idBlocks::air];

		breakItem(currentItem);

	}

}

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
		} else {
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


// TODO
void Entity::actionMain(world &world, Vector2f pos)
{

	Field &field = world.field;
	vector<UnlifeObject> &unlifeObjects = *world.unlifeObjects;
	vector<Item> &items = *world.items;
	listDestroyObjectsAndBlocks &listDestroy = *world.listDestroy;

	if (currentLevelFloor >= 0 && currentLevelFloor < HEIGHT_MAP - 1) {
		// Если блок лестница
		int x = pos.x / SIZE_BLOCK;
		int y = pos.y / SIZE_BLOCK;
		if (wcschr(listDestroy.ladder, field.dataMap[currentLevelFloor + 1][y][x]) != NULL) {

			Vector2f posOrigin = spriteEntity->getOrigin();

			spriteEntity->setPosition(x * SIZE_BLOCK + posOrigin.x, y * SIZE_BLOCK + posOrigin.y);
			currentLevelFloor += 1;

		}

	}

}

void Entity::actionAlternate(world &world, Vector2f pos)
{

	Field &field = world.field;
	vector<UnlifeObject> &unlifeObjects = *world.unlifeObjects;
	vector<Item> &items = *world.items;
	listDestroyObjectsAndBlocks &listDestroy = *world.listDestroy;

	if (currentLevelFloor >= 1) {
		int x = pos.x / SIZE_BLOCK;
		int y = pos.y / SIZE_BLOCK;
		// Если блок лестница
		if (wcschr(listDestroy.ladder, field.dataMap[currentLevelFloor][y][x]) != NULL) {

			Vector2f posOrigin = spriteEntity->getOrigin();

			spriteEntity->setPosition(x * SIZE_BLOCK + posOrigin.x, y * SIZE_BLOCK + posOrigin.y);
			currentLevelFloor -= 1;

		}

	}
}

