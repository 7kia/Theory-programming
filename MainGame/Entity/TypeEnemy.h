#pragma once
#include "../GlobalVar.h"
#include "../Shoots/shoot.h"
#include "../Map/Map.h"
#include "EntityVar.h"

struct typesObjectsInWorld;
struct enemyFeatures
{
	int maxHealth;
	int maxStamina;
	int maxMana;
	int maxThirst;
	int maxHungry;

	void init(int health, int stamina, int mana, int thirst, int hungry);
};


struct conversePlayer
{
	bool isAgressiveForPlayer;
	bool isPlayer;
	bool canPanic;
	void init(bool enemy, bool panic);
};

struct viewEnemy
{
	bool feelEnemy;
	float radiuseView;

	int radiusUse;
	void init(float radiuse, bool feel, int distanseUse);
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Сущность
struct TypeEnemy
{
	sf::Texture *textureEntity;
	sf::String name;
	int id;

	sf::SoundBuffer *soundsEntity[sizeBuffer];

	viewEnemy view;
	conversePlayer converse;

	TypeItem typeItem;
	int amountSlots;//TODO

	Step step;
	enemyFeatures features;
	entityProtection protection;
	DamageInputAndOutput damage;
	featuresSprite featuresSprite;
	objectDropItems drop;

	void initCurrentItem(TypeItem *typesItem, int id);
	void InitOtherFeatures(int idType, sf::String texturePath, sf::String nameEnemy, int amountEnemySlots);
};

void initializeTypeEnemy(TypeEnemy *typesEnemy, TypeItem *typesItem);