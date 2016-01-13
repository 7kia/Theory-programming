#include "UseItem.h"

using namespace sf;
using namespace std;


void Entity::useItem(world &world , Event &event , Vector2f pos)
{
	Item& currentItem = getCurrentItem();

	Vector3i &posUse = getCurrentTarget();

	posUse.x = Math::inMapCoordinate(pos.x);
	posUse.y = Math::inMapCoordinate(pos.y);

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

		switch (currentItem.getIdCategory()) {
		case idCategoryItem::backhoe:
		case idCategoryItem::pickax:
		case idCategoryItem::axe:
			if (isInUseField(pos, true)) {
				int level;
				defineLevel(level , event);

				Field &field = world.field;
				wchar_t	*block = &field.dataMap[level][posUse.y][posUse.x];
				int idNature;
				idNature = field.idsNature[field.findIdBlock(*block)];

				if (idNature <= idNatureObject::Unbreaking) {
					idNature = getFindUnlifeObject().typeObject->idNature;
				}
				if ((idNature != idNatureObject::Unbreaking) && g_Functions::isInListObjects(*currentItem.getListDestroy(), idNature)) {
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

				posUse.z = level;

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
		case idCategoryItem::distanceWeapon:
			
			useAsRifle(currentItem , world);
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
		currentItem = *getRefOnEmptyItem();
}

void Entity::redefineType(Item &currentItem, world &world, int shift)
{
	createRedefineItem(world, currentItem, shift);
	takeRedefineItem(world);
	minusAmount(currentItem);
}

void Entity::createRedefineItem(world &world, Item &currentItem, int shift)
{
	int defineType = currentItem.getIdType() + shift;

	Item addItem;
	addItem.setType(world.getTypeItem(defineType));

	Vector3i posItem = { Math::inMapCoordinate(getXPos()) + 1,
											Math::inMapCoordinate(getYPos()) + 1,
											getLevelWall() };
	addItem.setPosition(posItem);

	world.addItem(addItem);

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
	int idFindItem = getIdFindItem();

	if (idFindItem > RESET_VALUE) {

		String nameFindItem = getFindItem().getName();
		String nameEmptyItem = getRefOnEmptyItem()->getName();


		if (nameFindItem != nameEmptyItem) {
			if (isInUseField(pos , true)) {

				if (isEmptySlot() && (idFindItem > RESET_VALUE)) {
					searchItem(world.items , pos);

				

					playSound(idSoundPaths::luggage1Sound , *soundBase , soundEntity , getPosition());
				}
			}
		}
	}
}

void Entity::searchItem(vector<Item> &items, Vector2f pos)
{
	int idFindItem = getIdFindItem();
		Item &findItem = items[idFindItem];

		FloatRect objectItem = findItem.getGlobalBounds();

		bool onOneLevel = (findItem.getLevelOnMap() == getLevelWall());
		bool itemIsFind = objectItem.contains(pos) && onOneLevel;
		if (itemIsFind) {
		

			transferInInventory(items);
		

			assert(items.size() != 0);
			assert(idFindItem > RESET_VALUE);

			items.erase(items.begin() + idFindItem);
		}

}

void Entity::transferInInventory(vector<Item> &items)
{
	bool isFindItem = false;
	int idFindItem = getIdFindItem();

	int idTypeFindItem = items[idFindItem].getIdType();
	int idTypeItem;
	bool isTypesEqual;
	Item *item = &itemsEntity[0];
	bool slotIsEmpty;



	for (int i = 0; i < AMOUNT_ACTIVE_SLOTS; i++) {

		item = &itemsEntity[i];
		idTypeItem = item->getIdType();
		isTypesEqual = (idTypeItem == idTypeFindItem);
		slotIsEmpty = (idTypeItem == idItem::emptyItem);

		if (isTypesEqual && !slotIsEmpty && 
				((item->getAmount() + 1) <= item->getMaxAmount())) {
			item->increaseAmount(1);
			isFindItem = true;
			break;
		}

	}


	if (!isFindItem) {
	

		fillEmptySlot(items[idFindItem]);
	

		getEmtySlot().setScale(normalSize);
	

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

		int idUseBlock = currentItem.getIdAddObject(idBlockForUse);
		if (idUseBlock) {

			int x = getCurrentTarget().x;
			int y = getCurrentTarget().y;
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
		int idUseBlock = currentItem.getIdAddObject(idBlockForUse);
		if (idUseBlock) {

			int x = getCurrentTarget().x;
			int y = getCurrentTarget().y;

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
			currentItem = *getRefOnEmptyItem();
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
	Item &currecntItem = getCurrentItem();

	UnlifeObject addObject;
	Vector3i posAdd = { pos.x + 1, pos.y + 1 , pos.z };
	TypeUnlifeObject *typesObject = world.typesObjects.typesUnlifeObject;
	addObject.setType(typesObject[idUnlifeObject::destroyBlockEffect]);
	addObject.setPosition(posAdd);

	Field &field = world.field;
	wchar_t *block = &field.dataMap[pos.z][pos.y][pos.x];
	int idBlock = field.findIdBlock(*block);
	int toughness = field.toughness[idBlock];
	addObject.currentToughness = toughness - currecntItem.getDamage(crushingDamage);

	vector<UnlifeObject> &objects = world.unlifeObjects;
	objects.push_back(addObject);

	getCurrentTarget() = posAdd;
	founds.findObject = &objects[objects.size() - 1];
}

void Entity::actionMain(world &world, Vector2f pos)
{
	if (currentLevelFloor >= 0 && currentLevelFloor < HEIGHT_MAP - 1) {

		Vector2i posBlock = Math::inMapCoordinate(pos);

		Field &field = world.field;
		listDestroyObjectsAndBlocks &listDestroy = world.listDestroy;

		wchar_t *charBlocks = field.charBlocks;
		wchar_t(*map)[LONG_MAP][WIDTH_MAP] = field.dataMap;
		//int x = posOnMap.x;
		//int y = posOnMap.y;

		bool checkOverLadder = (map[currentLevelFloor + 2][posBlock.y][posBlock.x] == charBlocks[idBlocks::air])
									|| (map[currentLevelFloor + 2][posBlock.y][posBlock.x] == charBlocks[idBlocks::woodLadder]);

		if (g_Functions::isInListBlocks(listDestroy.ladder , field.dataMap[currentLevelFloor + 1][posBlock.y][posBlock.x])
				&& checkOverLadder) {

			Vector2f posOrigin = spriteEntity->getOrigin();
			Vector2f posCurrent = { float(posBlock.x * SIZE_BLOCK + posOrigin.x),
															float(posBlock.y * SIZE_BLOCK + posOrigin.y) };

			spriteEntity->setPosition(posCurrent.x , posCurrent.y);
			currentLevelFloor += 1;

		}
		else {
			if (founds.findObject != founds.emptyObject) {
				if (g_Functions::isInListObjects(listDestroy.harvestObjects , founds.findObject->typeObject->id)) {
					upgradeObject(*founds.findObject , world);
				}

			}
		}

	}

}

void Entity::actionAlternate(world &world, Vector2f pos)
{
	if (currentLevelFloor >= 1) {

		Vector2i posBlock = Math::inMapCoordinate(pos);
		Field &field = world.field;

		wchar_t *charBlocks = field.charBlocks;
		wchar_t(*map)[LONG_MAP][WIDTH_MAP] = field.dataMap;

		bool checkUnderLadder = (map[currentLevelFloor + 1][posBlock.y][posBlock.x] == charBlocks[idBlocks::air]);

		listDestroyObjectsAndBlocks &listDestroy = world.listDestroy;
		if (g_Functions::isInListBlocks(listDestroy.ladder, field.dataMap[currentLevelFloor][posBlock.y][posBlock.x])
				&& checkUnderLadder) {

			Vector2f posOrigin = spriteEntity->getOrigin();

			spriteEntity->setPosition(posBlock.x * SIZE_BLOCK + posOrigin.x, posBlock.y * SIZE_BLOCK + posOrigin.y);
			currentLevelFloor -= 1;
		}
	}
}

void Entity::createBullet(vector<shoot>& shoots , TypeShoot &type)
{
	shoot addShoot;
	addShoot.setType(type);

	Vector2f shiftBullet = directions.directionToTarget;
	shiftBullet.x *= getWidth() * 2;
	shiftBullet.y *= getHeight() * 2;
	addShoot.setPosition(getPosition() + shiftBullet , getLevelWall());

	Vector2f speedBullet = directions.directionToTarget;
	speedBullet.x *= startSpeedBullet.x;
	speedBullet.y *= startSpeedBullet.y;

	addShoot.setDirection(speedBullet);
	shoots.push_back(addShoot);
}