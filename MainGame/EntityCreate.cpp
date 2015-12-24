#include "World.h"


void Entity::init(TypeEnemy &typesEnemy , world &world ,
									Vector3i posEntity)
{
	type = &typesEnemy;

	soundBase = &world.databaseSound;

	initItems(world);
	step.init(SPEED_ENTITY);

	setSpriteEntity();
	initPosition(posEntity);
	initRandowWalk();

	emptyObjects &emptyObjects = world.emptyObjects;
	founds.init(emptyObjects);

	initFeatures();
	initProtection();
	initDamage();
}

void Entity::initItems(world &world)
{
	itemFromPanelQuickAccess = new Item[type->amountSlots];
	idSelectItem = 0;
	itemFromPanelQuickAccess[idSelectItem].setType(type->typeItem);
	itemFromPanelQuickAccess[idSelectItem].amount = type->typeItem.maxAmount;
	for (int i = 1; i < type->amountSlots; i++) {
		itemFromPanelQuickAccess[i].setType(*world.emptyObjects.emptyItem.typeItem);
	}
}

void Entity::setSpriteEntity()
{
	spriteEntity = new Sprite;
	sizeSprite  &sizes = type->featuresSprite.size;
	spriteEntity->setTexture(*type->textureEntity);
	spriteEntity->setTextureRect(IntRect(0 , 0 , sizes.width , sizes.height));
}

void Entity::initPosition(Vector3i pos)
{
	currentLevelFloor = pos.z;
	currenMode = idEntityMode::walk;

	sizeSprite  &size = type->featuresSprite.size;
	spriteEntity->setOrigin(float(size.width / 2) , float(size.height / 2));
	spriteEntity->setPosition(float(pos.x * SIZE_BLOCK - SIZE_BLOCK / 2) ,
													 float(pos.y * SIZE_BLOCK - SIZE_BLOCK / 2));
	directions.directionWalk = NONE_DIRECTION;
	directions.directionLook = DOWN;
}

void Entity::initRandowWalk()
{
	currenMode = idEntityMode::walk;

	step.timeWalk = minTimeWalk + rand() % (int(maxTimeWalk - minTimeWalk));

	step.currentTime = 0;

	int randomDirection = 1 + rand() % Direction::AMOUNT_DIRECTION;
	directions.directionWalk = Direction(randomDirection);
}

void foundObjects::init(emptyObjects & emptyObjects)
{
	emptyItem = &emptyObjects.emptyItem;
	emptyEnemy = &emptyObjects.emptyEnemy;
	emptyObject = &emptyObjects.emptyObject;

}

void Entity::initFeatures()
{
	health.maxHealth = type->features.maxHealth;
	health.currentHealth = health.maxHealth;

	stamina.maxStamina = type->features.maxStamina;
	stamina.currentStamina = stamina.maxStamina;

	mana.maxMana = type->features.maxMana;
	mana.currentMana = mana.maxMana;

	thirst.currentThirst = thirst.maxThirst;
	hungry.currentHungry = hungry.maxHungry;
}

void Entity::initProtection()
{
	protection.init(type->protection.protectionCut ,
									type->protection.protectionCrash ,
									type->protection.protectionUnlife);

	protection.deathDay = type->protection.deathDay;
}

void Entity::initDamage()
{
	animation.init(type->damage.timeOutputDamage , TIME_ATACK);
	damage.init(type->damage.cuttingDamage , type->damage.crushingDamage , TIME_ATACK , 1.f);
}
