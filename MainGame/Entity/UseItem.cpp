#include "UseItem.h"

using namespace sf;
using namespace std;


void Entity::useItem(world &world , Event &event , Vector2f pos)
{
	Item& currentItem = itemsEntity[idSelectItem];

	int x = int(pos.x / SIZE_BLOCK);
	int y = int(pos.y / SIZE_BLOCK);
	Vector3i &posUse = founds.currentTarget;

	posUse.x = x;
	posUse.y = y;

	bool isEnemy = founds.findEnemy != founds.emptyEnemy;
	//	bool isObject = founds.findObject->typeObject->id != founds.emptyObject->typeObject->id;
	bool isAtack = event.key.code == Mouse::Left;
	if (isEnemy && isAtack && isInUseField(pos, true)) {

		if (founds.findEnemy->currentLevelFloor == currentLevelFloor) {

			if (animation.currentTimeFightAnimation == 0.f) {
				currenMode = idEntityMode::atack;
			}

		}
	}
	else {

		int category = currentItem.typeItem->features.category;
		switch (category) {
		case idCategoryItem::backhoe:
		case idCategoryItem::pickax:
		case idCategoryItem::axe:
			if (isInUseField(pos, true)) {
				int level;
				defineLevel(level , event);


				posUse = { x, y, level };

				Field &field = world.field;
				wchar_t	*block = &field.dataMap[level][y][x];
				int idNature;
				idNature = field.idsNature[field.findIdBlock(*block)];

				if (idNature <= idNatureObject::Unbreaking) {
					idNature = founds.findObject->typeObject->idNature;
				}
				if (idNature != idNatureObject::Unbreaking && isInListObjects(*currentItem.typeItem->destroy , idNature)) {
					currenMode = idEntityMode::atack;
					giveDamage = false;
				}
			}
			break;
		case idCategoryItem::block:
		case idCategoryItem::unlifeObject:
			if (isInUseField(pos, false)) {
				int level;
				defineLevel(level , event);

				posUse = { x, y, level };

				useBlock(posUse , world , currentItem);
			}
			break;
		case idCategoryItem::food:
			useAsFood(currentItem , event);
			break;
		case idCategoryItem::bukketWithWater:
			useAsBukketWithWater(currentItem , world , event);
			break;
		case idCategoryItem::bottleWithWater:
			useAsBottleWithWater(currentItem , world , event);
			break;
		case idCategoryItem::healthPotion:
			useAsHealthPotion(currentItem , world , event);
			break;
		case idCategoryItem::bukketEmpty:// ÈÑÏÐÀÂÜ
			if (isInUseField(pos, true)) {
				int level;
				defineLevel(level , event);
				useAsEmptyBukket(currentItem , world , level);
			}
			break;
		case idCategoryItem::bottleEmpty:
			if (isInUseField(pos, true)) {
				int level;
				defineLevel(level , event);
				useAsEmptyBottle(currentItem , world , level);
			}
			break;
		case idCategoryItem::other:
			break;
		default:
			break;
		}
	}

}

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

	Vector3i posItem = { int(getXPos() / SIZE_BLOCK) + 1,
											int(getYPos() / SIZE_BLOCK) + 1,
											currentLevelFloor + 1 };
	addItem->setPosition(posItem);

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
		if (isInUseField(pos, true)) {
			
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

		assert(items.size() != 0);
		assert(founds.findItemFromList > RESET_COLLISION_VALUE);

		items.erase(items.begin() + founds.findItemFromList);
	}
}

void Entity::transferInInventory(vector<Item> &items)
{
	bool isFindItem = false;
	int idFindItem = founds.findItemFromList;

	int idTypeFindItem = items[idFindItem].typeItem->features.id;
	for (int i = 0; i < AMOUNT_ACTIVE_SLOTS; i++) {
		Item &item = itemsEntity[i];
		int idItem = item.typeItem->features.id;
		bool isTypesEqual = idItem == idTypeFindItem;

		if (isTypesEqual && (item.amount + 1 <= item.typeItem->maxAmount)) {
			item.amount++;
			isFindItem = true;
			break;
		}

	}

	if (isFindItem == false) {
		itemsEntity[emptySlot] = items[idFindItem];
		itemsEntity[emptySlot].mainSprite->scale(normalSize);
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
	currentItem.currentToughness -= 1;
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
	// TODO BUG :
	Item* addItem = new Item;
	int currentAmount;
	Vector3i shift = { 1 , 1 , 1 };
	Vector3i posAdd = pos + shift;
	for (size_t i = start; i < finish; i++) {
		// Generate only one item 
		currentAmount = minAmount[i] + rand() % (maxAmount[i] - minAmount[i] + 1);
		for (int j = 0; j < currentAmount; j++) {
			// Work normal
			addItem->setType(typesItems[idItems[i]]);
			addItem->setPosition(posAdd);
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
	Item &currecntItem = itemsEntity[idSelectItem];

	UnlifeObject addObject;
	Vector3i posAdd = { pos.x + 1, pos.y + 1 , pos.z };
	TypeUnlifeObject *typesObject = world.typesObjects.typesUnlifeObject;
	addObject.setType(typesObject[idUnlifeObject::destroyBlockEffect]);
	addObject.setPosition(posAdd);

	Field &field = world.field;
	wchar_t *block = &field.dataMap[pos.z][pos.y][pos.x];
	int idBlock = field.findIdBlock(*block);
	int toughness = field.toughness[idBlock];
	addObject.currentToughness = toughness - currecntItem.typeItem->damageItem.crushingDamage;

	vector<UnlifeObject> &objects = world.unlifeObjects;
	objects.push_back(addObject);

	founds.currentTarget = posAdd;
	founds.findObject = &objects[objects.size() - 1];
}

void Entity::actionMain(world &world, Vector2f pos)
{
	if (currentLevelFloor >= 0 && currentLevelFloor < HEIGHT_MAP - 1) {

		Vector2i posBlock = { int(pos.x / SIZE_BLOCK) , int(pos.y / SIZE_BLOCK) };

		Field &field = world.field;
		listDestroyObjectsAndBlocks &listDestroy = world.listDestroy;
		if (isInListBlocks(listDestroy.ladder , field.dataMap[currentLevelFloor + 1][posBlock.y][posBlock.x])) {

			Vector2f posOrigin = spriteEntity->getOrigin();
			Vector2f posCurrent = { float(posBlock.x * SIZE_BLOCK + posOrigin.x),
															float(posBlock.y * SIZE_BLOCK + posOrigin.y) };

			spriteEntity->setPosition(posCurrent.x , posCurrent.y);
			currentLevelFloor += 1;

		}
		else {
			if (founds.findObject != founds.emptyObject) {
				if (isInListObjects(listDestroy.harvestObjects , founds.findObject->typeObject->id)) {
					upgradeObject(*founds.findObject , world);
				}

			}
		}

	}

}

void Entity::actionAlternate(world &world, Vector2f pos)
{
	if (currentLevelFloor >= 1) {
		Vector2i posBlock = { int(pos.x / SIZE_BLOCK), int(pos.y / SIZE_BLOCK) };


		Field &field = world.field;
		listDestroyObjectsAndBlocks &listDestroy = world.listDestroy;
		if (isInListBlocks(listDestroy.ladder, field.dataMap[currentLevelFloor][posBlock.y][posBlock.x])) {

			Vector2f posOrigin = spriteEntity->getOrigin();

			spriteEntity->setPosition(posBlock.x * SIZE_BLOCK + posOrigin.x, posBlock.y * SIZE_BLOCK + posOrigin.y);
			currentLevelFloor -= 1;
		}
	}
}

