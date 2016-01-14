#include "TypeEnemy.h"

using namespace sf;
using namespace std;

void initializeTypeEnemy(TypeEnemy *typesEnemy , TypeItem *typesItem)
{

	////////////////////////////////////////////////////////////////
	// Волк
	int id = idEntity::playerEntity;
	TypeEnemy* typeEnemy = &typesEnemy[id];

	String texturePath = texturePaths[idTexturePaths::mainPersonPath];
	String name = "MainPerson";

	objectDropItems drop;
	drop.addItem(0, 0, idItem::grassItem);

	typeEnemy->featuresSprite.init(WIDTH_PLAYER, HEIGHT_PLAYER, 0, 0);
	typeEnemy->protection.init(0.0015f, 1.f, 0.f);
	typeEnemy->protection.deathDay = false;
	typeEnemy->step.init(SPEED_ENTITY);
	typeEnemy->features.init(100, 100, 0, 20, 20);
	typeEnemy->damage.init(1, 0, 1.f, 1.f);
	typeEnemy->drop.init(drop);
	typeEnemy->view.init(RADIUSE_VIEW * 2, false , DEFAULT_RADIUSE_USE);
	typeEnemy->converse.init(true, true);
	typeEnemy->initCurrentItem(typesItem, idItem::stoneKnifeItem);
	typeEnemy->InitOtherFeatures(id, texturePath, name, AMOUNT_PLAYER_SLOTS);

	drop.clear();
	////////////////////////////////////////////////////////////////
	id = idEntity::wolfEnemy;
	typeEnemy = &typesEnemy[id];

	texturePath = texturePaths[idTexturePaths::wolfPath];
	name = "Wolf";

	drop.addItem(0 , 1 , idItem::mushroomItem);

	typeEnemy->featuresSprite.init(WIDTH_WOLF , HEIGHT_WOLF , 0 , 0);
	typeEnemy->protection.init(1.5f , 1.f , 0.f);
	typeEnemy->protection.deathDay = false;
	typeEnemy->step.init(SPEED_ENTITY);
	typeEnemy->features.init(100 , 25 , 0 , 20 , 20);
	typeEnemy->damage.init(5 , 0 , 1.f , 1.f);
	typeEnemy->drop.init(drop);
	typeEnemy->view.init(RADIUSE_VIEW * 2 , false , DEFAULT_RADIUSE_USE);
	typeEnemy->converse.init(true , true);
	typeEnemy->initCurrentItem(typesItem , idItem::emptyItem);
	typeEnemy->InitOtherFeatures(id , texturePath , name , AMOUNT_WOLF_SLOTS);

	drop.clear();
	////////////////////////////////////////////////////////////////
	id = idEntity::skeletEnemy;
	typeEnemy = &typesEnemy[id];

	texturePath = texturePaths[idTexturePaths::skeletPath];
	name = "Skelet";

	drop.addItem(0 , 1 , idItem::mushroomItem);

	typeEnemy->featuresSprite.init(WIDTH_SKELET, HEIGHT_SKELET, 0, 0);
	typeEnemy->protection.init(0.f, 1.f, 1.f);
	typeEnemy->protection.deathDay = true;
	typeEnemy->step.init(SPEED_ENTITY);
	typeEnemy->features.init(75, 0, 0, 20, 20);
	typeEnemy->damage.init(0, 5, 1.f, 1.f);
	typeEnemy->drop.init(drop);
	typeEnemy->view.init(RADIUSE_VIEW * RADIUSE_VIEW , true , DEFAULT_RADIUSE_USE);
	typeEnemy->converse.init(true, false);
	typeEnemy->initCurrentItem(typesItem, idItem::stoneKnifeItem);
	typeEnemy->InitOtherFeatures(id, texturePath, name, AMOUNT_SKELET_SLOTS);

	drop.clear();
	////////////////////////////////////////////////////////////////
	id = idEntity::skeletDiggerEnemy;

	typeEnemy = &typesEnemy[id];

	name = "Skelet digger";

	drop.addItem(0 , 1 , idItem::mushroomItem);

	typeEnemy->featuresSprite.init(WIDTH_SKELET, HEIGHT_SKELET, 0, 0);
	typeEnemy->protection.init(0.f, 1.f, 1.f);
	typeEnemy->protection.deathDay = true;
	typeEnemy->step.init(SPEED_ENTITY);
	typeEnemy->features.init(75, 0, 0, 20, 20);
	typeEnemy->damage.init(0, 5, 1.f, 1.f);
	typeEnemy->drop.init(drop);
	typeEnemy->view.init(RADIUSE_VIEW * RADIUSE_VIEW , true , DEFAULT_RADIUSE_USE);
	typeEnemy->converse.init(true, false);
	typeEnemy->initCurrentItem(typesItem, idItem::ironBackHoerItem);
	typeEnemy->InitOtherFeatures(id, texturePath, name, AMOUNT_SKELET_SLOTS);

	drop.clear();
	////////////////////////////////////////////////////////////////
	id = idEntity::skeletMinerEnemy;

	typeEnemy = &typesEnemy[id];

	name = "Skelet miner";

	drop.addItem(0 , 1 , idItem::mushroomItem);

	typeEnemy->featuresSprite.init(WIDTH_SKELET, HEIGHT_SKELET, 0, 0);
	typeEnemy->protection.init(0.f, 1.f, 1.f);
	typeEnemy->protection.deathDay = true;
	typeEnemy->step.init(SPEED_ENTITY);
	typeEnemy->features.init(75, 0, 0, 20, 20);
	typeEnemy->damage.init(0, 5, 1.f, 1.f);
	typeEnemy->drop.init(drop);
	typeEnemy->view.init(RADIUSE_VIEW * RADIUSE_VIEW , true , DEFAULT_RADIUSE_USE);
	typeEnemy->converse.init(true, false);
	typeEnemy->initCurrentItem(typesItem, idItem::stonePickaxItem);
	typeEnemy->InitOtherFeatures(id, texturePath, name, AMOUNT_SKELET_SLOTS);

	drop.clear();
	////////////////////////////////////////////////////////////////
	id = idEntity::skeletLumbermillEnemy;

	typeEnemy = &typesEnemy[id];

	name = "Skelet lumbermill";

	drop.addItem(0 , 1 , idItem::mushroomItem);

	typeEnemy->featuresSprite.init(WIDTH_SKELET, HEIGHT_SKELET, 0, 0);
	typeEnemy->protection.init(0.f, 1.f, 1.f);
	typeEnemy->protection.deathDay = true;
	typeEnemy->step.init(SPEED_ENTITY);
	typeEnemy->features.init(75, 0, 0, 20, 20);
	typeEnemy->damage.init(0, 5, 1.f, 1.f);
	typeEnemy->drop.init(drop);
	typeEnemy->view.init(RADIUSE_VIEW * RADIUSE_VIEW , true, DEFAULT_RADIUSE_USE);
	typeEnemy->converse.init(true, false);
	typeEnemy->initCurrentItem(typesItem, idItem::stoneAxeItem);
	typeEnemy->InitOtherFeatures(id, texturePath, name, AMOUNT_SKELET_SLOTS);

	drop.clear();
	////////////////////////////////////////////////////////////////
	id = idEntity::skeletBuilderEnemy;
	typeEnemy = &typesEnemy[id];

	name = "Skelet builder";

	drop.addItem(0 , 1 , idItem::mushroomItem);

	typeEnemy->featuresSprite.init(WIDTH_SKELET, HEIGHT_SKELET, 0, 0);
	typeEnemy->protection.init(0.f, 1.f, 1.f);
	typeEnemy->protection.deathDay = true;
	typeEnemy->step.init(SPEED_ENTITY);
	typeEnemy->features.init(75, 0, 0, 20, 20);
	typeEnemy->damage.init(0, 5, 1.f, 1.f);
	typeEnemy->drop.init(drop);
	typeEnemy->view.init(RADIUSE_VIEW * RADIUSE_VIEW , true, DEFAULT_RADIUSE_USE);
	typeEnemy->converse.init(true , false);
	typeEnemy->initCurrentItem(typesItem, idItem::woodLadderItem);
	typeEnemy->InitOtherFeatures(id, texturePath, name, AMOUNT_SKELET_SLOTS);

	drop.clear();
	////////////////////////////////////////////////////////////////
	id = idEntity::emptyEnemy;
	typeEnemy = &typesEnemy[id];

	name = "Empty";

	typeEnemy->featuresSprite.init(0, 0, 0, 0);
	typeEnemy->initCurrentItem(typesItem, idItem::emptyItem);
	typeEnemy->InitOtherFeatures(id, texturePath, name, 0);

	drop.clear();
}

void viewEnemy::init(float radiuse , bool feel , int distanseUse)
{
	radiuseView = radiuse;
	feelEnemy = feel;
	radiusUse = distanseUse;
}

void enemyFeatures::init(int health, int stamina, int mana, int thirst, int hungry)
{
	maxHealth = health;
	maxMana = mana;
	maxStamina = stamina;
	maxThirst = thirst;
	maxHungry = hungry;
}

void conversePlayer::init(bool enemy, bool panic)
{
	isAgressiveForPlayer = enemy;
	canPanic = panic;
}

void TypeEnemy::initCurrentItem(TypeItem *typesItem, int id)
{
	typeItem = typesItem[id];
}

void TypeEnemy::InitOtherFeatures(int idType, sf::String texturePath, sf::String nameEnemy,
																	int amountEnemySlots)
{
	textureEntity = new Texture;
	textureEntity->loadFromFile(texturePath);

	amountSlots = amountEnemySlots;

	id = idType;
	name = nameEnemy;
}
