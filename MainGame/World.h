#pragma once
#include "Entity/Entity.h"

enum idEnemyWaveVariable
{
	CURRENT_DIFFICULT,
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

	amountIdsEnemyWaveVariable
};

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
	Entity emptyEnemy;
};

enum TimeDay {
	day,
	night
};

struct world
{
	std::vector<Item> items;
	std::vector<UnlifeObject> unlifeObjects;
	std::vector<Entity> Enemys;

	std::vector<int> deleteItems;
	std::vector<int> deleteUnlifeObjects;
	std::vector<int> deleteEnemys;

	void initializeCategorysBreakingObject();
	void initializePlayer(View& view, Listener& listener);
	typesObjectsInWorld typesObjects;
	listDestroyObjectsAndBlocks listDestroy;
	Field field;

	TimeDay timeDay = day;
	dataSound databaseSound;

	View view;
	Listener listener;
	Entity *mainPerson;

	int enemyWaveVariables[idEnemyWaveVariable::amountIdsEnemyWaveVariable];

	sf::Clock worldTime;
	bool waveEnemysCreated = false;
	float lastSecond = 0;

	int countUnlifeObject = 0;
	int countEntity = 0;

	emptyObjects emptyObjects;

	void deleteObjects();
};

void createOnlyEnemy(world &world, std::vector<TypeEnemy*> &types, std::vector<int> amount);

bool isPlaceForCreate(world world, sf::Vector3i &pos);
void createGroup(world &world, std::vector<TypeEnemy*> &types, std::vector<int> amount, int square, sf::Vector3i pos);

void createSmallGroupSkelets(world &world, sf::Vector3i pos);
void createMiddleGroupSkelets(world &world, sf::Vector3i pos);
void createBigGroupSkelets(world &world, sf::Vector3i pos);

void initializeEntitys(world &world);
void createEnemys(world &world);
void createEmptyEnemy(world &world);