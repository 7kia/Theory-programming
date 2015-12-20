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

void Entity::minusAmount(Item &currentItem)
{
	currentItem.amount--;
	if (currentItem.amount < 1)
		currentItem = *founds.emptyItem;
}

void Entity::redefineType(Item &currentItem, world &world, int shift)
{
	createRedefineItem(world, currentItem, shift);
	takeRedefineItem(world);
	minusAmount(currentItem);
}

void Entity::createRedefineItem(world &world, Item &currentItem, int shift)
{
	int *idItem = &currentItem.typeItem->features.id;
	int defineType = *idItem + shift;
	*idItem = defineType - shift;

	Item *addItem = new Item;

	TypeItem *typesItems = world.typesObjects.typesItem;
	addItem->setType(typesItems[defineType]);

	Vector2f posItem = { getXPos() / SIZE_BLOCK, getYPos() / SIZE_BLOCK };
	addItem->setPosition(int(posItem.x + 1),
						 int(posItem.y + 1),
						 currentLevelFloor + 1);

	vector<Item> &items = world.items;
	items.push_back(*addItem);

	delete addItem;
}

void Entity::takeRedefineItem(world & world)
{
	vector<Item> &items = world.items;
	Vector2f posPerson = { getXPos() , getYPos() };

	founds.findItemFromList = int(world.items.size() - 1);
	founds.findItem = &items[founds.findItemFromList];

	takeItem(world, posPerson);
}

void Entity::takeItem(world &world, Vector2f pos)
{
	vector<Item> &items = world.items;
	String nameFindItem = founds.findItem->typeItem->features.name;
	String nameEmptyItem = founds.emptyItem->typeItem->features.name;


	if (nameFindItem != nameEmptyItem) {
		if (isInUseField(pos.x, pos.y, true)) {
			
			if (isEmptySlot() && founds.findItemFromList > RESET_COLLISION_VALUE) {
				searchItem(items , pos);
				playSound(idSoundPaths::luggage1Sound , *soundBase , soundEntity , getPosition());
			}
		}
	}
}

void Entity::searchItem(vector<Item> &items, Vector2f pos)
{
	int levelItem = items[founds.findItemFromList].currentLevel;

	Sprite *spriteItem = items[founds.findItemFromList].mainSprite;
	FloatRect objectItem = spriteItem->getGlobalBounds();

	bool onOneLevel = levelItem == currentLevelFloor + 1;
	bool itemIsFind = objectItem.contains(pos.x, pos.y) && onOneLevel;
	if (itemIsFind) {

		transferInInventory(items);

		items.erase(items.begin() + founds.findItemFromList);
	}
}


void Entity::transferInInventory(vector<Item> &items)
{
	bool isFindItem = false;
	int idFindItem = items[founds.findItemFromList].typeItem->features.id;
	for (int i = 0; i < AMOUNT_ACTIVE_SLOTS; i++) {
		Item &item = itemFromPanelQuickAccess[i];
		int idItem = item.typeItem->features.id;
		bool isTypesEqual = idItem == idFindItem;

		if (isTypesEqual && (item.amount + 1 <= item.typeItem->maxAmount)) {
			item.amount++;
			isFindItem = true;
			break;
		}

	}

	if (isFindItem == false) {
		itemFromPanelQuickAccess[emptySlot] = items[founds.findItemFromList];
		itemFromPanelQuickAccess[emptySlot].mainSprite->scale(normalSize);
	}
}

void Entity::useAsBottleWithWater(Item &currentItem, world &world, Event event)
{
	bool drinking = event.key.code == Mouse::Right;
	bool isThirts = thirst.currentThirst < thirst.maxThirst;
	if (drinking && isThirts)
	{
		thirst.currentThirst += currentItem.currentToughness;
		redefineType(currentItem, world, -1);
	}

}

void Entity::useAsHealthPotion(Item &currentItem, world &world, Event event)
{
	bool drinking = event.key.code == Mouse::Right;
	bool lowHealth = health.currentHealth < (health.maxHealth / 2);
	if (drinking && lowHealth) {
		health.currentHealth += currentItem.currentToughness;
		redefineType(currentItem, world, -(idItem::healthPotionItem - idItem::glassBottleItem - 1));
	}

}

void Entity::useAsEmptyBottle(Item &currentItem, world &world, int level)
{
	Field &field = world.field;
	bool useToAnyLevel = level > -1;
	if (useToAnyLevel) {

		int idUseBlock = currentItem.typeItem->idAdd.idBlockForUse;
		if (idUseBlock) {

			int x = founds.currentTarget.x;
			int y = founds.currentTarget.y;
			wchar_t block = field.dataMap[level][y][x];
			bool isWater = block == field.charBlocks[idUseBlock];
			if (isWater) {
				redefineType(currentItem, world, 1);
			}
		}
	}

}

void Entity::useAsEmptyBukket(Item &currentItem, world &world, int level)
{
	Field &field = world.field;
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
				redefineType(currentItem, world, 1);
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

		minusAmount(currentItem);
	}
}

void Entity::breakItem(Item &currentItem)
{
	currentItem.currentToughness -= 1;//&& currentItem.amount < 1
	if (currentItem.currentToughness < 1) {
		currentItem.amount--;
		if(currentItem.amount < 1)
			currentItem = *founds.emptyItem;
	}
}

void UnlifeObject::playObjectDropSoundObject()
{
	switch (typeObject->idNature) {
	case idNatureObject::woodNature:
		playSound(treeDropSound, *typeObject->soundBase, soundObject, getPosition());
		break;
	default:
		break;
	}
}

void UnlifeObject::playHarvestSoundObject()
{
	switch (typeObject->idNature) {
	case idNatureObject::woodNature:
		playSound(forage1Sound, *typeObject->soundBase, soundObject, getPosition());
		break;
	default:
		break;
	}
}

void UnlifeObject::dropObject(Vector3i pos, world &world, bool harvest)
{
	//////////////////////////////////////////////////
	// Выпадение предметов

	vector<Item> &items = world.items;
	TypeItem *typesItems = world.typesObjects.typesItem;

	size_t countItem = typeObject->drop.minCountItems.size();

	vector<int> &minAmount = typeObject->drop.minCountItems;
	vector<int> &maxAmount = typeObject->drop.maxCountItems;
	vector<int> &idItems = typeObject->drop.dropItems;

	size_t start = 0;
	size_t finish = countItem;

	if(harvest)
	{
		start = 1;
	}
	///////////////////////////////////////
	// TODO BUG
	Item* addItem = new Item;
	int currentAmount;
	for (size_t i = start; i < finish; i++) {

		currentAmount = minAmount[i] + rand() % (maxAmount[i] - minAmount[i] + 1);
		for (int j = 0; j < currentAmount; j++) {
			addItem->setType(typesItems[idItems[i]]);
			addItem->setPosition(pos.x + 1, pos.y + 1, pos.z + 1);
			items.push_back(*addItem);

		}

	}
	delete addItem;
	///////////////////////////////////////
	if(harvest)
	{
		playHarvestSoundObject();	
	}
	else
	{
		playObjectDropSoundObject();
	}
}

void Entity::createDestroyEffect(world &world, Vector3i &pos)
{
	Item &currecntItem = itemFromPanelQuickAccess[idSelectItem];

	UnlifeObject addObject;
	TypeUnlifeObject *typesObject = world.typesObjects.typesUnlifeObject;
	addObject.setType(typesObject[idUnlifeObject::destroyBlockEffect]);
	addObject.setPosition(pos.x + 1, pos.y + 1 , pos.z);

	Field &field = world.field;
	wchar_t *block = &field.dataMap[pos.z][pos.y][pos.x];
	int idBlock = field.findIdBlock(*block);
	int toughness = field.toughness[idBlock];
	addObject.currentToughness = toughness - currecntItem.typeItem->damageItem.crushingDamage;

	vector<UnlifeObject> &objects = world.unlifeObjects;
	objects.push_back(addObject);

	founds.currentTarget = { pos.x + 1, pos.y + 1, pos.z };
	founds.findObject = &objects[objects.size() - 1];
}

void Entity::actionMain(world &world, Vector2f pos)
{
	if (currentLevelFloor >= 0 && currentLevelFloor < HEIGHT_MAP - 1) {

		int x = int(pos.x / SIZE_BLOCK);
		int y = int(pos.y / SIZE_BLOCK);

		Field &field = world.field;
		listDestroyObjectsAndBlocks &listDestroy = world.listDestroy;
		if (isInListBlocks(listDestroy.ladder, field.dataMap[currentLevelFloor + 1][y][x])) {

			Vector2f posOrigin = spriteEntity->getOrigin();
			Vector2f posCurrent = { float(x * SIZE_BLOCK + posOrigin.x), float(y * SIZE_BLOCK + posOrigin.y) };

			spriteEntity->setPosition(posCurrent.x, posCurrent.y);
			currentLevelFloor += 1;

		} 
		else
		{
			if(founds.findObject != founds.emptyObject)
			{
							if (isInListObjects(listDestroy.harvestObjects, founds.findObject->typeObject->id))
		{
			upgradeObject(*founds.findObject, world);
		}

			}
		}

	}

}

void Entity::actionAlternate(world &world, Vector2f pos)
{
	if (currentLevelFloor >= 1) {
		int x = int(pos.x / SIZE_BLOCK);
		int y = int(pos.y / SIZE_BLOCK);

		Field &field = world.field;
		listDestroyObjectsAndBlocks &listDestroy = world.listDestroy;
		if (isInListBlocks(listDestroy.ladder, field.dataMap[currentLevelFloor][y][x])) {

			Vector2f posOrigin = spriteEntity->getOrigin();

			spriteEntity->setPosition(x * SIZE_BLOCK + posOrigin.x, y * SIZE_BLOCK + posOrigin.y);
			currentLevelFloor -= 1;
		}
	}
}

