#pragma once
#include <SFML\Graphics.hpp>
#include "TypeEnemy.h"

struct TypeEnemy;
class UnlifeObject;


const float minTimeWalk = 4.f;
const float maxTimeWalk = 12.f;

class Enemy : public Entity
{
public:
	// Для направления взгляда
	float rotation;

	void initStepSounds();

	// Для взаимодействия с миром
	int currenMode;
	Item *items;
	Item *emptyItem;// ИСПРАВЬ
	int idSelectItem;

	float radiuseView;

	TypeEnemy *type;
	///////////////////////////////////////////////////////
	// Для уничтожения врагов
	Enemy *findEnemy;
	Enemy *emptyEnemy;
	int findEnemyFromList;
	///////////////////////////////////////////////////////
	void EnemyInit(TypeEnemy &typesEnemy, Item &emptyItem, UnlifeObject &emptyObject, int xPos, int yPos, int level);
	~Enemy();


	void randomWalk(const sf::Time &deltaTime);
private:

};

struct foundsByEnemy
{
	foundObjects foundsObjects;
	Enemy *findEnemy;
	Enemy *emptyEnemy;
	int findEnemyFromList;
	void init(Item &item, UnlifeObject &object, Enemy &enemy);
};

void initializeEntitys(TypeEnemy *typesEnemy, std::vector<Enemy> &enemy, int countEnemy,
											 Item &emptyItem, UnlifeObject &emptyObject);