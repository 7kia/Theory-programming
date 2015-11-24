#pragma once
#include "../Entity/Enemy.h"


const int TIME_GENERATE_WAVE_ENEMYS = 2;
const int	AMOUNT_WAVE_FOR_UPDATE_DIFFICULT = 2;
const int TIME_UPDATE_DIFFICULT = TIME_GENERATE_WAVE_ENEMYS * AMOUNT_WAVE_FOR_UPDATE_DIFFICULT;

const int AMOUNT_SIMPLE_SKELET_IN_SMALL_GROUP = 2;
const int AMOUNT_SKELET_DIGGER_IN_SMALL_GROUP = 1;
const int AMOUNT_SKELET_BUILDER_IN_SMALL_GROUP = 1;

const int AMOUNT_SIMPLE_SKELET_IN_MIDDLE_GROUP = 1;
const int AMOUNT_SKELET_DIGGER_IN_MIDDLE_GROUP = 1;
const int AMOUNT_SKELET_LUMBER_IN_MIDDLE_GROUP = 1;
const int AMOUNT_SKELET_MINER_IN_MIDDLE_GROUP = 1;
const int AMOUNT_SKELET_BUILDER_IN_MIDDLE_GROUP = 3;

const int AMOUNT_SIMPLE_SKELET_IN_BIG_GROUP = 4;
const int AMOUNT_SKELET_DIGGER_IN_BIG_GROUP = 2;
const int AMOUNT_SKELET_LUMBER_IN_BIG_GROUP = 2;
const int AMOUNT_SKELET_MINER_IN_BIG_GROUP = 2;
const int AMOUNT_SKELET_BUILDER_IN_BIG_GROUP = 4;
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
	int difficult = 0;
	bool waveEnemysCreated = false;
	float lastSecond = 0;

	int countUnlifeObject = 0;
	int countEntity = 0;

	emptyObjects emptyObjects;
};

void createOnlyEnemy(world &world, std::vector<TypeEnemy*> &types, std::vector<int> amount);

bool isPlaceForCreate(world world, Enemy* enemy, sf::Vector3i &pos);
void createGroup(world &world, std::vector<TypeEnemy*> &types, std::vector<int> amount, int square, sf::Vector3i pos);

void createSmallGroupSkelets(world &world, Vector3i pos);
void createMiddleGroupSkelets(world &world, Vector3i pos);
void createBigGroupSkelets(world &world, Vector3i pos);

void initializeEntitys(world &world);