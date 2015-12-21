#include  "Enemy.h"

using namespace std;

void createOnlyEnemy(world &world , std::vector<TypeEnemy*> &types , std::vector<int> amount)
{
	Entity* addEnemy = new Entity();
	Vector3i pos;
	pos.z = 2;

	int &countEnemy = world.countEntity;

	for (int countTypes = 0; countTypes < types.size(); countTypes++) {
		for (int amountAdd = 0; amountAdd < amount[countTypes]; amountAdd++) {
			countEnemy++;
			if (countEnemy > AMOUNT_ENTITY) {
				break;
			}

			pos.x = CENTER_WORLD.x;
			pos.y = CENTER_WORLD.y;

			addEnemy->init(*types[countTypes] , world , pos.x , pos.y , pos.z);
			world.Enemys.push_back(*addEnemy);

		}
	}

	types.clear();
	amount.clear();

	delete addEnemy;
}

void initializeEntitys(world &world)// днаюбкемхе ясымнярх 
{
	srand(time(nullptr));

	int *config = world.enemyWaveVariables;
	config[TIME_UPDATE_DIFFICULT] = config[AMOUNT_WAVE_FOR_UPDATE_DIFFICULT]
		* config[TIME_GENERATE_WAVE_ENEMYS];
	createEnemys(world);
	createEmptyEnemy(world);
}

void createEnemys(world& world)
{
	Entity* addEnemy = new Entity();

	TypeEnemy *typesEnemy = world.typesObjects.typesEnemy;
	std::vector<TypeEnemy*> types;
	std::vector<int> amount;

	types.push_back(&typesEnemy[idEntity::playerEntity]);
	amount.push_back(1);

	//types.push_back(&typesEnemy[idEntity::wolfEnemy]);
	//amount.push_back(4);

	createOnlyEnemy(world , types , amount);

	delete addEnemy;
}

void createEmptyEnemy(world& world)
{
	TypeEnemy *typesEnemy = world.typesObjects.typesEnemy;
	TypeEnemy* typeEnemy = &typesEnemy[idEntity::emptyEnemy];

	emptyObjects &emptyObjects = world.emptyObjects;
	Entity &emptyEnemy = emptyObjects.emptyEnemy;

	emptyEnemy.init(*typeEnemy , world , -1 , -1 , -1);
}

void Entity::randomWalk(const float deltaTime) {

	if (currenMode == idEntityMode::walk) {
		if (step.currentTime < step.timeWalk && directions.directionWalk != Direction::NONE_DIRECTION) {

			step.currentTime += deltaTime;

		} else {

			step.currentTime = 0;
			step.timeWalk = minTimeWalk + rand() % (int(maxTimeWalk - minTimeWalk));

			int randomDirection = 1 + rand() % Direction::AMOUNT_DIRECTION;
			directions.directionWalk = Direction(randomDirection);
			step.direction = directions.directionWalk;
		}
	}
	

}

void Entity::takeDamage(DamageInputAndOutput damageEnemy, Item &currentItem)
{
	bool isDestroy = currentItem.typeItem->features.isDestroy;
	if (isDestroy) {
		currentItem.currentToughness -= 1;
	}

	typeDamageItem damagePersonItem = currentItem.typeItem->damageItem;
	float multiplirer = damageEnemy.damageMultiplirer;


	damageEnemy.inputCutDamage = int(multiplirer * (damageEnemy.cuttingDamage + damagePersonItem.cuttingDamage));
	damageEnemy.inputCrashDamage = int(multiplirer * (damageEnemy.crushingDamage + damagePersonItem.crushingDamage));
	damageEnemy.inputUnlifeDamage = int(multiplirer * (damageEnemy.unlifeDamage + damagePersonItem.unlifeDamage));

	int cuttingDamage = currentItem.typeItem->damageItem.cuttingDamage;
	int crushingDamage = currentItem.typeItem->damageItem.crushingDamage;
	int unlifingDamage = currentItem.typeItem->damageItem.unlifeDamage;


	float cutDamage = damageEnemy.damageMultiplirer * cuttingDamage;
	float crashDamage = damageEnemy.damageMultiplirer * crushingDamage;
	float unlifeDamage = damageEnemy.damageMultiplirer * unlifingDamage;

	cutDamage *= protection.protectionCut;
	crashDamage *= protection.protectionCrash;
	unlifeDamage *= protection.protectionUnlife;

	damageEnemy.inputDamage = int(cutDamage + crashDamage + unlifeDamage);
	health.currentHealth -= damageEnemy.inputDamage;

	damage.inputDamage = damageEnemy.inputDamage;
	damageEnemy.inputDamage = 0;

	int categoryItem = currentItem.typeItem->features.category;
	if (categoryItem == idCategoryItem::weapon) {
		breakItem(currentItem);
	}


}

void Entity::redefineDirectionWalk()
{
	step.currentTime = 0;
	step.timeWalk = minTimeWalk + rand() % (int(maxTimeWalk - minTimeWalk));

	int randomDirection = 1 + rand() % Direction::AMOUNT_DIRECTION;
	directions.directionWalk = Direction(randomDirection);
}

void Entity::Drop(world& world)
{
	Field &field = world.field;
	vector<Item> &items = world.items;
	TypeItem *typesItems = world.typesObjects.typesItem;

	Item* addItem = new Item;
	TypeEnemy& typeEnemy = *type;
	size_t countItem = typeEnemy.drop.minCountItems.size();

	vector<int> &minAmount = typeEnemy.drop.minCountItems;
	vector<int> &maxAmount = typeEnemy.drop.maxCountItems;

	throwItem(field, items);

	int currentAmount;
	for (int i = 0; i < countItem; i++) {

		currentAmount = minAmount[i] + rand() % (maxAmount[i] - minAmount[i] + 2);
		for (int j = 0; j < currentAmount; j++) {
			addItem->setType(typesItems[typeEnemy.drop.dropItems[i]]);
			addItem->setPosition(founds.currentTarget.x + 1,
								 founds.currentTarget.y + 1,
								 currentLevelFloor + 1);
			world.items.push_back(*addItem);

		}

	}
	delete addItem;

}

void Entity::playSoundDeath(world& world)
{
	vector<UnlifeObject> &objects = world.unlifeObjects;
	TypeUnlifeObject *typeObjects = world.typesObjects.typesUnlifeObject;
	UnlifeObject addObject;
	sizeSprite &sizeSprite = type->featuresSprite.size;
	Vector3i pos = { int((getXPos() + sizeSprite.width / 2) / SIZE_BLOCK),
		int((getYPos() + sizeSprite.height / 2) / SIZE_BLOCK),
		currentLevelFloor + 1 };

	bool findSound = true;
	switch (type->id) {
	case idEntity::wolfEnemy:
		addObject.setType(typeObjects[idUnlifeObject::wolfDeathEffect]);
		addObject.setPosition(pos.x, pos.y, pos.z);
		break;
	case idEntity::skeletEnemy:
	case idEntity::skeletBuilderEnemy:
	case idEntity::skeletDiggerEnemy:
	case idEntity::skeletLumbermillEnemy:
	case idEntity::skeletMinerEnemy:
		addObject.setType(typeObjects[idUnlifeObject::skeletDeathEffect]);
		addObject.setPosition(pos.x, pos.y, pos.z);
		break;
	default:
		findSound = false;
		break;
	}

	if (findSound) {
		objects.push_back(addObject);

		Sound &soundObject = objects[objects.size() - 1].soundObject;

		switch (type->id) {
		case idEntity::wolfEnemy:
			::playSound(idSoundPaths::wolfDeathSound, *soundBase, soundObject, getPosition());
			break;
		case idEntity::skeletEnemy:
		case idEntity::skeletBuilderEnemy:
		case idEntity::skeletDiggerEnemy:
		case idEntity::skeletLumbermillEnemy:
		case idEntity::skeletMinerEnemy:
			::playSound(idSoundPaths::skeletonDeathSound, *soundBase, soundObject, getPosition());
			break;
		default:
			break;
		}

	}


}