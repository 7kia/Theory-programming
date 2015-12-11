#include "../Recourses.h"
#include "../World.h"
using namespace sf;
using namespace std;

void initializeTypeEntity(typesObjectsInWorld &types)
{

	TypeEntity *typesEntity = types.typesEntity;
	TypeItem *typesItem = types.typesItem;
	////////////////////////////////////////////////////////////////
	// Волк
	int id = idEntity::mainPersonEntity;
	TypeEntity* typeEntity = &typesEntity[id];

	String texturePath = texturePaths[idTexturePaths::mainPersonPath];
	String name = "Main person";

	objectDropItems drop;
	drop.addItem(0, 0, idItem::dirtItem);

	typeEntity->featuresSprite.init(WIDTH_MAIN_PERSON, HEIGHT_MAIN_PERSON, 0, 0);
	typeEntity->protection.init(1.5f, 1.f, 0.f);
	typeEntity->protection.deathDay = false;
	typeEntity->step.init(SPEED_ENTITY);
	typeEntity->features.init(100, 100, 0, 20, 20);
	typeEntity->damage.init(5, 0, 1.f, 1.f);
	typeEntity->drop.init(drop);
	typeEntity->view.init(RADIUSE_VIEW * 2, true);
	typeEntity->converse.init(true, true, false);
	typeEntity->initCurrentItem(typesItem, idItem::stoneKnifeItem);
	typeEntity->InitOtherFeatures(id, texturePath, name, AMOUNT_ACTIVE_SLOTS);

	drop.clear();
	////////////////////////////////////////////////////////////////
	// Волк
	id = idEntity::wolfEntity;
	typeEntity = &typesEntity[id];

	texturePath = texturePaths[idTexturePaths::wolf];
	name = "Wolf";

	drop.addItem(1, 4, idItem::rawMeatWolfItem);

	typeEntity->featuresSprite.init(WIDTH_WOLF, HEIGHT_WOLF, 0, 0);
	typeEntity->protection.init(1.5f, 1.f, 0.f);
	typeEntity->protection.deathDay = false;
	typeEntity->step.init(SPEED_ENTITY);
	typeEntity->features.init(100, 25, 0, 20, 20);
	typeEntity->damage.init(5, 0, 1.f, 1.f);
	typeEntity->drop.init(drop);
	typeEntity->view.init(RADIUSE_VIEW * 2, false);
	typeEntity->converse.init(true, true, false);
	typeEntity->initCurrentItem(typesItem, idItem::emptyItem);
	typeEntity->InitOtherFeatures(id, texturePath, name, AMOUNT_WOLF_SLOTS);

	drop.clear();
	////////////////////////////////////////////////////////////////
	// Скелет
	id = idEntity::skeletEntity;
	typeEntity = &typesEntity[id];

	texturePath = texturePaths[idTexturePaths::skelet];
	name = "Skelet";

	drop.addItem( 1, 2, idItem::dirtItem );

	typeEntity->featuresSprite.init(WIDTH_SKELET, HEIGHT_SKELET, 0, 0);
	typeEntity->protection.init(0.f, 1.f, 1.f);
	typeEntity->protection.deathDay = true;
	typeEntity->step.init(SPEED_ENTITY);
	typeEntity->features.init(75, 0, 0, 20, 20);
	typeEntity->damage.init(0, 5, 1.f, 1.f);
	typeEntity->drop.init(drop);
	typeEntity->view.init(RADIUSE_VIEW, true);
	typeEntity->converse.init(true, false, false);
	typeEntity->initCurrentItem(typesItem, idItem::stoneKnifeItem);
	typeEntity->InitOtherFeatures(id, texturePath, name, AMOUNT_SKELET_SLOTS);

	drop.clear();
	////////////////////////////////////////////////////////////////
	id = idEntity::skeletDiggerEntity;

	typeEntity = &typesEntity[id];

	name = "Skelet digger";

	drop.addItem(1, 2, idItem::dirtItem);

	typeEntity->featuresSprite.init(WIDTH_SKELET, HEIGHT_SKELET, 0, 0);
	typeEntity->protection.init(0.f, 1.f, 1.f);
	typeEntity->protection.deathDay = true;
	typeEntity->step.init(SPEED_ENTITY);
	typeEntity->features.init(75, 0, 0, 20, 20);
	typeEntity->damage.init(0, 5, 1.f, 1.f);
	typeEntity->drop.init(drop);
	typeEntity->view.init(RADIUSE_VIEW, true);
	typeEntity->converse.init(true, false, false);
	typeEntity->initCurrentItem(typesItem, idItem::ironBackHoerItem);
	typeEntity->InitOtherFeatures(id, texturePath, name, AMOUNT_SKELET_SLOTS);

	drop.clear();
	////////////////////////////////////////////////////////////////
	id = idEntity::skeletMinerEntity;

	typeEntity = &typesEntity[id];

	name = "Skelet miner";

	drop.addItem(1, 2, idItem::dirtItem);

	typeEntity->featuresSprite.init(WIDTH_SKELET, HEIGHT_SKELET, 0, 0);
	typeEntity->protection.init(0.f, 1.f, 1.f);
	typeEntity->protection.deathDay = true;
	typeEntity->step.init(SPEED_ENTITY);
	typeEntity->features.init(75, 0, 0, 20, 20);
	typeEntity->damage.init(0, 5, 1.f, 1.f);
	typeEntity->drop.init(drop);
	typeEntity->view.init(RADIUSE_VIEW, true);
	typeEntity->converse.init(true, false, false);
	typeEntity->initCurrentItem(typesItem, idItem::stonePickaxItem);
	typeEntity->InitOtherFeatures(id, texturePath, name, AMOUNT_SKELET_SLOTS);

	drop.clear();
	////////////////////////////////////////////////////////////////
	id = idEntity::skeletLumbermillEntity;

	typeEntity = &typesEntity[id];

	name = "Skelet lumbermill";

	drop.addItem(1, 2, idItem::dirtItem);

	typeEntity->featuresSprite.init(WIDTH_SKELET, HEIGHT_SKELET, 0, 0);
	typeEntity->protection.init(0.f, 1.f, 1.f);
	typeEntity->protection.deathDay = true;
	typeEntity->step.init(SPEED_ENTITY);
	typeEntity->features.init(75, 0, 0, 20, 20);
	typeEntity->damage.init(0, 5, 1.f, 1.f);
	typeEntity->drop.init(drop);
	typeEntity->view.init(RADIUSE_VIEW, true);
	typeEntity->converse.init(true, false, false);
	typeEntity->initCurrentItem(typesItem, idItem::stoneAxeItem);
	typeEntity->InitOtherFeatures(id, texturePath, name, AMOUNT_SKELET_SLOTS);

	drop.clear();
	////////////////////////////////////////////////////////////////
	id = idEntity::skeletBuilderEntity;
	typeEntity = &typesEntity[id];

	name = "Skelet builder";

	drop.addItem(1, 2, idItem::dirtItem);

	typeEntity->featuresSprite.init(WIDTH_SKELET, HEIGHT_SKELET, 0, 0);
	typeEntity->protection.init(0.f, 1.f, 1.f);
	typeEntity->protection.deathDay = true;
	typeEntity->step.init(SPEED_ENTITY);
	typeEntity->features.init(75, 0, 0, 20, 20);
	typeEntity->damage.init(0, 5, 1.f, 1.f);
	typeEntity->drop.init(drop);
	typeEntity->view.init(RADIUSE_VIEW, true);
	typeEntity->converse.init(true, false, false);
	typeEntity->initCurrentItem(typesItem, idItem::woodLadderItem);
	typeEntity->InitOtherFeatures(id, texturePath, name, AMOUNT_SKELET_SLOTS);

	drop.clear();
	////////////////////////////////////////////////////////////////
	id = idEntity::emptyEntity;
	typeEntity = &typesEntity[id];

	name = "Empty";

	typeEntity->featuresSprite.init(0, 0, 0, 0);
	typeEntity->initCurrentItem(typesItem, idItem::emptyItem);
	typeEntity->InitOtherFeatures(id, texturePath, name, 0);

	drop.clear();
}


void viewEntity::init(float radiuse, bool feel)
{
	radiuseView = radiuse;
	feelEntity = feel;
}

void enemyFeatures::init(int health, int stamina, int mana, int thirst, int hungry)
{
	maxHealth = health;
	maxMana = mana;
	maxStamina = stamina;
	maxThirst = thirst;
	maxHungry = hungry;
}

void converseEntity::init(bool enemy, bool panic, bool avoid)
{
	isEntity = enemy;
	canPanic = panic;
	avoidEntity = avoid;
}

void TypeEntity::initCurrentItem(TypeItem *typesItem, int id)
{
	typeItem = typesItem[id];
}

void TypeEntity::InitOtherFeatures(int idType, sf::String texturePath, sf::String nameEntity,
																	int amountEntitySlots)
{
	textureEntity = new Texture;
	textureEntity->loadFromFile(texturePath);

	amountSlots = amountEntitySlots;

	id = idType;
	name = nameEntity;
}
