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
	TypeItem *typesItems = world.typesObjects.typesItem;
	int *idItem = &currentItem.typeItem->features.id;
	int defineType = *idItem + shift;

	*idItem = defineType - shift;

	vector<Item> &items = *world.items;
	Item *addItem = new Item;
	addItem->setType(typesItems[defineType]);

	Vector2f posItem = { getXPos() / SIZE_BLOCK, getYPos() / SIZE_BLOCK};

	addItem->setPosition(int(posItem.x + 1),
											 int(posItem.y + 1),
											 currentLevelFloor + 1);
	items.push_back(*addItem);
	delete addItem;

	Vector2f posPerson = { getXPos() , getYPos() };

	founds.findItemFromList = int(world.items->size() - 1);
	founds.findItem = &items[founds.findItemFromList];

	takeItem(world, posPerson);
	minusAmount(currentItem);
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

void Entity::takeItem(world &world, Vector2f pos)
{
	vector<Item> &items = *world.items;
	String nameFindItem = founds.findItem->typeItem->features.name;
	String nameEmptyItem = founds.emptyItem->typeItem->features.name;


	if (nameFindItem != nameEmptyItem) {
		if (isInUseField(pos.x, pos.y, true)) {
			//////////////////////////////////////////////////////////////////////////////////////////////////////
			// Если есть место
			if (isEmptySlot()) {


				////////////////////////////////////////////////////////////////////
				// Если нашли предмет
				int levelItem = items[founds.findItemFromList].currentLevel;

				Sprite *spriteItem = items[founds.findItemFromList].mainSprite;
				FloatRect objectItem = spriteItem->getGlobalBounds();

				bool onOneLevel = levelItem == currentLevelFloor + 1;
				if (objectItem.contains(pos.x, pos.y) && onOneLevel) {

					transferInInventory(items);

					items.erase(items.begin() + founds.findItemFromList);
				}
				////////////////////////////////////////////////////////////////////

				playSound(idSoundPaths::luggage1Sound, *soundBase, soundEntity, getPosition());

			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////
		}
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
				} else {
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

void Entity::breakItem(Item &currentItem)
{
	currentItem.currentToughness -= 1;//&& currentItem.amount < 1
	if (currentItem.currentToughness < 1) {
		currentItem.amount--;
		if(currentItem.amount < 1)
			currentItem = *founds.emptyItem;
	}
}

void Entity::playObjectDropSoundObject()
{
	UnlifeObject &findObject = *founds.findObject;
	TypeUnlifeObject &typeObject = *findObject.typeObject;

	switch (typeObject.idNature) {
	case idNatureObject::woodNature:
		playSound(treeDropSound, *soundBase, soundEntity, getPosition());
		break;
	default:
		break;
	}
}

void Entity::playHarvestSoundObject()
{
	UnlifeObject &findObject = *founds.findObject;
	TypeUnlifeObject &typeObject = *findObject.typeObject;

	switch (typeObject.idNature) {
	case idNatureObject::woodNature:
		playSound(forage1Sound, *soundBase, soundEntity, getPosition());
		break;
	default:
		break;
	}
}

void Entity::createDestroyEffect(world &world, Vector3i &pos)
{
	Field &field = world.field;
	UnlifeObject addObject;
	TypeUnlifeObject *typesObject = world.typesObjects.typesUnlifeObject;

	addObject.setType(typesObject[idUnlifeObject::destroyBlockEffect]);
	addObject.setPosition(pos.x + 1, pos.y + 1 , pos.z);

	defineToughnesBlock(addObject, pos, field);

	vector<UnlifeObject> &objects = *world.unlifeObjects;
	objects.push_back(addObject);
	founds.findObject = &objects[objects.size() - 1];

	if(objects.size() > 1)
	{
			Vector2f posAdd = addObject.spriteObject->getPosition();
	for (int i = 0; i < objects.size() - 1; i++) {
		if (objects[i].spriteObject->getGlobalBounds().contains(posAdd)) {
			vector<int> &deleteUnlifeObjects = *world.deleteUnlifeObjects;
			if (isInListObjects(deleteUnlifeObjects, i) == false) {
				deleteUnlifeObjects.push_back(i);
			}
		}

	}

	}

}

void Entity::defineToughnesBlock(UnlifeObject &object, Vector3i pos, Field &field)
{	
	Item &currecntItem = itemFromPanelQuickAccess[idSelectItem];
	wchar_t *block = &field.dataMap[pos.z][pos.y][pos.x];
	int idBlock = field.findIdBlock(*block);
	int toughness = field.toughness[idBlock];
	object.currentToughness = toughness - currecntItem.typeItem->damageItem.crushingDamage;

}


bool Entity::isDestroyEffect(sf::Vector3i & pos, world & world)
{
	vector<UnlifeObject> &objects = *world.unlifeObjects;

	Vector2f posAdd = { float(pos.x + 1) * SIZE_BLOCK - SIZE_BLOCK / 2,
		float(pos.y + 1) * SIZE_BLOCK - SIZE_BLOCK / 2 };

	int idObject;
	Sprite *spriteCheck;
	size_t i = 0;
	while (i < objects.size()) {


		idObject = objects[i].typeObject->id;
		spriteCheck = objects[i].spriteObject;
		if (idObject == idUnlifeObject::destroyBlockEffect) {
			if (spriteCheck->getGlobalBounds().contains(posAdd)) {
				founds.findObject = &objects[i];
				return true;
			}
		}

		i++;
	}

	return false;
}

// TODO
void Entity::actionMain(world &world, Vector2f pos)
{

	Field &field = world.field;
	listDestroyObjectsAndBlocks &listDestroy = *world.listDestroy;

	if (currentLevelFloor >= 0 && currentLevelFloor < HEIGHT_MAP - 1) {

		int x = int(pos.x / SIZE_BLOCK);
		int y = int(pos.y / SIZE_BLOCK);
		if (isInListBlocks(field.dataMap[currentLevelFloor + 1][y][x], *listDestroy.ladder)) {

			Vector2f posOrigin = spriteEntity->getOrigin();
			Vector2f posCurrent = { float(x * SIZE_BLOCK + posOrigin.x), float(y * SIZE_BLOCK + posOrigin.y) };

			spriteEntity->setPosition(posCurrent.x, posCurrent.y);
			currentLevelFloor += 1;

		} else if (isInListObjects(*listDestroy.harvestObjects, founds.findObject->typeObject->id))
		{
			upgradeObject(*founds.findObject, world);
		}

	}

}

void Entity::actionAlternate(world &world, Vector2f pos)
{

	Field &field = world.field;
	listDestroyObjectsAndBlocks &listDestroy = *world.listDestroy;

	if (currentLevelFloor >= 1) {
		int x = int(pos.x / SIZE_BLOCK);
		int y = int(pos.y / SIZE_BLOCK);
		// Если блок лестница
		if (isInListBlocks(field.dataMap[currentLevelFloor][y][x], *listDestroy.ladder)) {

			Vector2f posOrigin = spriteEntity->getOrigin();

			spriteEntity->setPosition(x * SIZE_BLOCK + posOrigin.x, y * SIZE_BLOCK + posOrigin.y);
			currentLevelFloor -= 1;

		}

	}
}

