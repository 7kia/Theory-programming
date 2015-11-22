#pragma once
#include "../GlobalVar.h"

#include "Entity.h"


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


struct converseEnemy
{
	bool isEnemy;
	bool canPanic;
	bool avoidEnemy;
	void init(bool enemy, bool panic, bool avoid);
};

struct viewEnemy
{
	bool feelEnemy;
	float radiuseView;
	void init(float radiuse, bool feel);
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Сущность
struct TypeEnemy
{
	sf::Texture *textureEntity;
	sf::String name;

	sf::Sound *soundsEntity[sizeBuffer];

	viewEnemy view;
	converseEnemy converse;

	TypeItem typeItem;
	int amountSlots;//TODO

	Step step;
	enemyFeatures features;
	entityProtection protection;
	DamageInputAndOutput damage;
	featuresSprite featuresSprite;
	objectDropItems drop;

	void initCurrentItem(TypeItem *typesItem, int id);
	void InitOtherFeatures(sf::String texturePath, sf::String nameEnemy, dataSound &databaseSound,
												 int amountEnemySlots);
};

void initializeTypeEnemy(typesObjectsInWorld &types, dataSound &databaseSound);