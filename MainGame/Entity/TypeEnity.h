#pragma once
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


struct converseEntity
{
	bool isEntity;
	bool canPanic;
	bool avoidEntity;
	void init(bool enemy, bool panic, bool avoid);
};

struct viewEntity
{
	bool feelEntity;
	float radiuseView;
	void init(float radiuse, bool feel);
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Сущность
struct TypeEntity
{
	sf::Texture *textureEntity;
	sf::String name;
	int id;

	sf::SoundBuffer *soundsEntity[sizeBuffer];

	viewEntity view;
	converseEntity converse;

	TypeItem typeItem;
	int amountSlots;//TODO

	Step step;
	enemyFeatures features;
	entityProtection protection;
	DamageInputAndOutput damage;
	featuresSprite featuresSprite;
	objectDropItems drop;

	void initCurrentItem(TypeItem *typesItem, int id);
	void InitOtherFeatures(int idType, sf::String texturePath, sf::String nameEntity, int amountEntitySlots);
};

void initializeTypeEntity(typesObjectsInWorld &types);
