#pragma once
#include "World.h"
#include "Enemy.h"

struct typesObjectsInWorld
{
	TypeItem typesItem[AMOUNT_TYPES_ITEM];
	TypeEnemy typesEnemy[amountEnemy];
	TypeUnlifeObject typesUnlifeObject[AMOUNT_TYPES_UNLIFE_OBJECT];

};

struct world
{
	std::vector<Item>* items;
	std::vector<UnlifeObject>* unlifeObjects;
	std::vector<Enemy>* Enemys;
	typesObjectsInWorld typesObjects;
	listDestroyObjectsAndBlocks *listDestroy;
	Field field;
};



void initializeEntitys(TypeEnemy *typesEnemy, world &world, int countEnemy,
											 Item &emptyItem, UnlifeObject &emptyObject, Enemy &emptyEnemy);