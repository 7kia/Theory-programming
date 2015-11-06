#pragma once
#include "GlobalVar.h"

#include "Entity.h"

struct enemyDropItems
{
	std::vector<int> minCountItems;
	std::vector<int> maxCountItems;
	std::vector<int> dropItems;
	void init(std::vector<int> idItems, std::vector<int> minAmountItems, std::vector<int> maxAmountItems);
};

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
	sizeSprite size;
	enemyDropItems drop;

	void InitOtherFeatures(sf::String texturePath, sf::String nameEnemy, dataSound &databaseSound,
												 int amountEnemySlots, float view);
};

void initializeTypeEnemy(TypeEnemy *typesEnemy, dataSound &databaseSound);