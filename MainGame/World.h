#pragma once
#include "World.h"
#include "Enemy.h"

struct typesObjectsInWorld
{
	TypeItem typesItem[AMOUNT_TYPES_ITEM];
	TypeEnemy typesEnemy[amountEnemy];
	TypeUnlifeObject typesUnlifeObject[AMOUNT_TYPES_UNLIFE_OBJECT];

};

struct emptyObjects
{
		Item emptyItem;
	UnlifeObject emptyObject;
	Enemy emptyEnemy;
};

struct world
{
	std::vector<Item>* items;
	std::vector<UnlifeObject>* unlifeObjects;
	std::vector<Enemy>* Enemys;
	typesObjectsInWorld typesObjects;
	listDestroyObjectsAndBlocks *listDestroy;
	Field field;

	sf::Clock worldTime;
	bool waveEnemysCreated = false;
	float lastSecond = 0;

	int countUnlifeObject = 0;
	int countEntity = 0;

	emptyObjects emptyObjects;
};

void createOnlyEnemy(world &world, std::vector<TypeEnemy*> &types, std::vector<int> amount);

void createGroup(world &world, std::vector<TypeEnemy*> &types, std::vector<int> amount, int square, sf::Vector3i pos);
void createSmallGroupSkelets(world &world, Vector3i pos);

void initializeEntitys(world &world);