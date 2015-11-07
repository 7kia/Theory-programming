#pragma once
#include "GlobalVar.h"

#include "Entity.h"

struct enemyFeatures
{
	int maxHealth;
	int maxStamina;
	int maxMana;

	void init(int health, int stamina, int mana);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Сущность
struct TypeEnemy
{
	sf::Texture *textureEntity;
	sf::String name;

	sf::Sound *soundsEntity[sizeBuffer];

	int radiusUse;
	float radiuseView;

	int amountSlots;

	Step step;
	enemyFeatures features;
	entityProtection protection;
	DamageInputAndOutput damage;
	featuresSprite size;
	objectDropItems drop;

	void InitOtherFeatures(sf::String texturePath, sf::String nameEnemy, dataSound &databaseSound,
												 int amountEnemySlots, float view);
};

void initializeTypeEnemy(TypeEnemy *typesEnemy, dataSound &databaseSound);