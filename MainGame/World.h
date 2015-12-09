#pragma once
#include "../Entity/Entity.h"

/*
const int TIME_GENERATE_WAVE_ENEMYS = 2;
const int	AMOUNT_WAVE_FOR_UPDATE_DIFFICULT = 2;
const int TIME_UPDATE_DIFFICULT = TIME_GENERATE_WAVE_ENEMYS * AMOUNT_WAVE_FOR_UPDATE_DIFFICULT;

const int AMOUNT_SIMPLE_SKELET_IN_SMALL_GROUP = 2;
const int AMOUNT_SKELET_DIGGER_IN_SMALL_GROUP = 1;
const int AMOUNT_SKELET_BUILDER_IN_SMALL_GROUP = 1;

const int AMOUNT_SIMPLE_SKELET_IN_MIDDLE_GROUP = 1;
const int AMOUNT_SKELET_DIGGER_IN_MIDDLE_GROUP = 1;
const int AMOUNT_SKELET_LUMBER_IN_MIDDLE_GROUP = 0;
const int AMOUNT_SKELET_MINER_IN_MIDDLE_GROUP = 1;
const int AMOUNT_SKELET_BUILDER_IN_MIDDLE_GROUP = 3;

const int AMOUNT_SIMPLE_SKELET_IN_BIG_GROUP = 4;
const int AMOUNT_SKELET_DIGGER_IN_BIG_GROUP = 2;
const int AMOUNT_SKELET_LUMBER_IN_BIG_GROUP = 0;
const int AMOUNT_SKELET_MINER_IN_BIG_GROUP = 2;
const int AMOUNT_SKELET_BUILDER_IN_BIG_GROUP = 4;
*/


enum idEntityWaveVariable
{
	TIME_DAY,
	TIME_NIGHT,
	TIME_GENERATE_WAVE_ENEMYS,
	AMOUNT_WAVE_FOR_UPDATE_DIFFICULT,
	TIME_UPDATE_DIFFICULT,

	AMOUNT_SIMPLE_SKELET_IN_SMALL_GROUP,
	AMOUNT_SKELET_DIGGER_IN_SMALL_GROUP,
	AMOUNT_SKELET_BUILDER_IN_SMALL_GROUP,

	AMOUNT_SIMPLE_SKELET_IN_MIDDLE_GROUP,
	AMOUNT_SKELET_DIGGER_IN_MIDDLE_GROUP,
	AMOUNT_SKELET_LUMBER_IN_MIDDLE_GROUP,
	AMOUNT_SKELET_MINER_IN_MIDDLE_GROUP,
	AMOUNT_SKELET_BUILDER_IN_MIDDLE_GROUP,

	AMOUNT_SIMPLE_SKELET_IN_BIG_GROUP,
	AMOUNT_SKELET_DIGGER_IN_BIG_GROUP,
	AMOUNT_SKELET_LUMBER_IN_BIG_GROUP,
	AMOUNT_SKELET_MINER_IN_BIG_GROUP,
	AMOUNT_SKELET_BUILDER_IN_BIG_GROUP,

	amountIdsEntityWaveVariable
};

struct typesObjectsInWorld
{
	TypeItem typesItem[AMOUNT_TYPES_ITEM];
	TypeEntity typesEntity[amountEntity];
	TypeUnlifeObject typesUnlifeObject[AMOUNT_TYPES_UNLIFE_OBJECT];

};

struct emptyObjects
{
	Item emptyItem;
	UnlifeObject emptyObject;
	Entity emptyEntity;
};

enum TimeDay {
	day,
	night
};

struct world
{
	std::vector<Item>* items;
	std::vector<UnlifeObject>* unlifeObjects;
	std::vector<Entity>* Entitys;
	typesObjectsInWorld typesObjects;
	listDestroyObjectsAndBlocks *listDestroy;
	Field field;

	TimeDay timeDay = day;
	dataSound databaseSound;


	int enemyWaveVariables[idEntityWaveVariable::amountIdsEntityWaveVariable];

	sf::Clock worldTime;
	bool waveEntitysCreated = false;
	float lastSecond = 0;

	int countUnlifeObject = 0;
	int countEntity = 0;

	emptyObjects emptyObjects;
};

void createOnlyEntity(world &world, std::vector<TypeEntity*> &types, std::vector<int> amount);

bool isPlaceForCreate(world world, sf::Vector3i &pos);
void createGroup(world &world, std::vector<TypeEntity*> &types, std::vector<int> amount, int square, sf::Vector3i pos);

void createSmallGroupSkelets(world &world, Vector3i pos);
void createMiddleGroupSkelets(world &world, Vector3i pos);
void createBigGroupSkelets(world &world, Vector3i pos);

void initializeEntitys(world &world);