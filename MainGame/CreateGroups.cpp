#include "World.h"

using namespace std;

void createGroup(world &world, std::vector<TypeEnemy*> &types, std::vector<int> amount, int square, sf::Vector3i pos)
{
	Entity addEntity;
	Vector3i posEntity = pos;

	int &countEntity = world.countEntity;

	int start = -square / 2;
	int finish = square / 2;
	if (square % 2 == 1) {
		start += 1;
	}

	posEntity += Vector3i(start, start, 0);

	for (size_t countTypes = 0; countTypes < types.size(); countTypes++) {
		for (size_t amountAdd = 0; amountAdd < amount[countTypes]; amountAdd++) {
			countEntity++;
			if (countEntity > AMOUNT_ENTITY) {
				countTypes = types.size();
				break;
			}

			addEntity.init(*types[countTypes], world, posEntity);
			assert(world.Enemys[0].getType()->id == 0);
			world.Enemys.push_back(addEntity);
			if(!isPlaceForCreate(world, posEntity))
			{
				world.Enemys.pop_back();
				assert(world.Enemys[0].getType()->id == 0);
			}
			assert(world.Enemys[0].getType()->id == 0);
			posEntity.x++;
			if (posEntity.x >  pos.x + finish) {
				posEntity.x = pos.x + start;
				posEntity.y++;
				if (posEntity.y >  pos.y + finish) {
					countTypes = types.size();
					break;
				}
			}

		}
	}

	types.clear();
	amount.clear();

}

void world::addItem(Item item)
{
	items.push_back(item);
}

TypeItem* world::getTypesItem()
{
	return typesObjects.typesItem;
}

TypeItem& world::getTypeItem(int id)
{
	assert(g_Functions::checkDiaposon(id , RESET_VALUE , idItem::amountItem));
	return typesObjects.typesItem[id];
}

TypeShoot& world::getTypeShoot(int id)
{
	assert(g_Functions::checkDiaposon(id, RESET_VALUE , amountTypeShoots));
	return typesObjects.typesShoot[id];
}

bool isPlaceForCreate(world world, Vector3i &pos)
{
	vector<Entity> &enemys = world.Enemys;
	assert(enemys.size() != 0);
	Entity &currentEntity = enemys.back();

	bool isPlace;
	Vector2f movement;
	Vector3i startPosition = pos;

	do {
		currentEntity.interactionWithMap(world.field, world.listDestroy, 0);
		currentEntity.interactionWitnUnlifeObject(world.unlifeObjects, 0);
		currentEntity.interactionWithEntity(&enemys, int(enemys.size() - 1), 0.1f);

		isPlace = !currentEntity.wasCollision;

		if (!isPlace) {
			// Сдвигаем вдоль х
			pos.x++;
			if (currentEntity.isExitFromBorder(pos.x, pos.y)) {
				pos.x = startPosition.x;
				pos.y++;
				movement.x = 0;
				if (currentEntity.isExitFromBorder(pos.x, pos.y)) {
					pos.x = startPosition.x;
					pos.y = startPosition.y;

					currentEntity.currentLevelFloor++;
					if (currentEntity.currentLevelFloor > HEIGHT_MAP) {
						currentEntity.currentLevelFloor = HEIGHT_MAP - 1;
						break;
					}

					movement.y = 0;
				}
				else {
					movement.y = float(SIZE_BLOCK);
				}
			}
			else {
				movement.x = float(SIZE_BLOCK);
			}
			// Сдвигаем вдоль y
			currentEntity.spriteEntity->move(movement);
		}
		else {
			break;
		}

	}
	while (currentEntity.wasCollision);

	return isPlace;
}

void createSmallGroupSkelets(world &world, Vector3i pos)
{
	TypeEnemy *typesEntity = world.typesObjects.typesEnemy;

	std::vector<TypeEnemy*> types;
	std::vector<int> amount;

	int *config = world.enemyWaveVariables;

	types.push_back(&typesEntity[idEntity::skeletEnemy]);
	types.push_back(&typesEntity[idEntity::skeletDiggerEnemy]);
	types.push_back(&typesEntity[idEntity::skeletBuilderEnemy]);

	amount.push_back(config[AMOUNT_SIMPLE_SKELET_IN_SMALL_GROUP]);
	amount.push_back(config[AMOUNT_SKELET_DIGGER_IN_SMALL_GROUP]);
	amount.push_back(config[AMOUNT_SKELET_BUILDER_IN_SMALL_GROUP]);

	createGroup(world, types, amount, 2, pos);
	assert(world.Enemys[0].getType()->id == 0);
}

void createMiddleGroupSkelets(world &world, Vector3i pos)
{
	TypeEnemy *typesEntity = world.typesObjects.typesEnemy;

	std::vector<TypeEnemy*> types;
	std::vector<int> amount;
	int *config = world.enemyWaveVariables;

	types.push_back(&typesEntity[idEntity::skeletEnemy]);
	types.push_back(&typesEntity[idEntity::skeletDiggerEnemy]);
	types.push_back(&typesEntity[idEntity::skeletLumbermillEnemy]);
	types.push_back(&typesEntity[idEntity::skeletMinerEnemy]);
	types.push_back(&typesEntity[idEntity::skeletBuilderEnemy]);

	amount.push_back(config[AMOUNT_SIMPLE_SKELET_IN_MIDDLE_GROUP]);
	amount.push_back(config[AMOUNT_SKELET_DIGGER_IN_MIDDLE_GROUP]);
	amount.push_back(config[AMOUNT_SKELET_LUMBER_IN_MIDDLE_GROUP]);
	amount.push_back(config[AMOUNT_SKELET_MINER_IN_MIDDLE_GROUP]);
	amount.push_back(config[AMOUNT_SKELET_BUILDER_IN_MIDDLE_GROUP]);

	createGroup(world, types, amount, 4, pos);
}

void createBigGroupSkelets(world &world, Vector3i pos)
{
	TypeEnemy *typesEntity = world.typesObjects.typesEnemy;

	std::vector<TypeEnemy*> types;
	std::vector<int> amount;
	int *config = world.enemyWaveVariables;

	types.push_back(&typesEntity[idEntity::skeletEnemy]);
	types.push_back(&typesEntity[idEntity::skeletDiggerEnemy]);
	types.push_back(&typesEntity[idEntity::skeletLumbermillEnemy]);
	types.push_back(&typesEntity[idEntity::skeletMinerEnemy]);
	types.push_back(&typesEntity[idEntity::skeletBuilderEnemy]);


	amount.push_back(config[AMOUNT_SIMPLE_SKELET_IN_BIG_GROUP]);
	amount.push_back(config[AMOUNT_SKELET_DIGGER_IN_BIG_GROUP]);
	amount.push_back(config[AMOUNT_SKELET_LUMBER_IN_BIG_GROUP]);
	amount.push_back(config[AMOUNT_SKELET_MINER_IN_BIG_GROUP]);
	amount.push_back(config[AMOUNT_SKELET_BUILDER_IN_BIG_GROUP]);

	createGroup(world, types, amount, 7, pos);
}