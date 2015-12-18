#include "CreateGroups.h"

//#include "structGame/Game.h"
using namespace std;

void createGroup(world &world, std::vector<TypeEnemy*> &types, std::vector<int> amount, int square, sf::Vector3i pos)
{
	Entity* addEntity = new Entity();

	emptyObjects &emptyObjects = world.emptyObjects;

	Item &emptyItem = emptyObjects.emptyItem;
	UnlifeObject &emptyObject = emptyObjects.emptyObject;

	Vector3i posEntity;
	int xPos, xTemp;
	int yPos, yTemp;
	int levelFloor = pos.z;

	int &countEntity = world.countEntity;

	int start = -square / 2;
	int finish = square / 2;
	if (square % 2 == 1) {
		start += 1;
	}

	xPos = pos.x + start;
	yPos = pos.y + start;

	for (size_t countTypes = 0; countTypes < types.size(); countTypes++) {
		for (size_t amountAdd = 0; amountAdd < amount[countTypes]; amountAdd++) {
			countEntity++;
			if (countEntity > AMOUNT_ENTITY) {
				// чтобы выйти из циклов
				countTypes = types.size();
				break;
			}


			xTemp = xPos;
			yTemp = yPos;
			addEntity->EnemyInit(*types[countTypes], world, xTemp, yTemp, levelFloor);

			world.Enemys.push_back(*addEntity);
			posEntity = { xTemp, yTemp, pos.z };
			isPlaceForCreate(world, posEntity);




			xPos++;
			if (xPos >  pos.x + finish) {
				xPos = pos.x + start;
				yPos++;
				if (yPos >  pos.y + finish) {
					// чтобы выйти из циклов
					countTypes = types.size();
					break;
				}
			}

		}
	}

	types.clear();
	amount.clear();

	delete addEntity;
}

bool isPlaceForCreate(world world, Vector3i &pos)
{
	// TODO
	vector<Entity> &enemys = world.Enemys;
	Entity &currentEntity = enemys[enemys.size() - 1];

	bool isPlace;
	bool moveX = false;
	bool moveY = false;
	Vector2f movemoment;
	Vector3i startPosition = pos;

	do {
		currentEntity.interactionWithMap(world.field, world.listDestroy, 0);
		currentEntity.interactionWitnUnlifeObject(world.unlifeObjects, 0);
		currentEntity.interactionWithEntity(&enemys, int(enemys.size() - 1), 0.1f);

		isPlace = currentEntity.wasCollision == false;

		if (isPlace == false) {
			// Сдвигаем вдоль х
			pos.x++;
			if (currentEntity.isExitFromBorder(pos.x, pos.y)) {
				pos.x = startPosition.x;
				pos.y++;
				movemoment.x = 0;
				if (currentEntity.isExitFromBorder(pos.x, pos.y)) {
					pos.x = startPosition.x;
					pos.y = startPosition.y;

					currentEntity.currentLevelFloor++;
					if (currentEntity.currentLevelFloor > HEIGHT_MAP) {
						currentEntity.currentLevelFloor = HEIGHT_MAP - 1;
						break;
					}

					movemoment.y = 0;
				}
				else {
					movemoment.y = float(SIZE_BLOCK);
				}
			}
			else {
				movemoment.x = float(SIZE_BLOCK);
			}
			// Сдвигаем вдоль y
			currentEntity.spriteEntity->move(movemoment);
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