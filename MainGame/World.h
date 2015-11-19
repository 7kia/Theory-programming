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

	int countUnlifeObject = 0;
	int countEntity = 0;

	emptyObjects emptyObjects;
};

void createGroup(TypeEnemy *typesEnemy, sf::Vector3i pos);

void initializeEntitys(world &world);