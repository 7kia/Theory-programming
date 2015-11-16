#pragma once
#include "Enemy.h"

struct world
{
	std::vector<Item>* items;
	std::vector<UnlifeObject>* unlifeObjects;
	std::vector<Enemy>* Enemys;

	listDestroyObjectsAndBlocks *listDestroy;
	Field field;
};

void initializeEntitys(TypeEnemy *typesEnemy, world &world, int countEnemy,
											 Item &emptyItem, UnlifeObject &emptyObject, Enemy &emptyEnemy);