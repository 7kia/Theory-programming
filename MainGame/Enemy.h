#pragma once
#include "Entity.h"
#include "Items.h"

class UnlifeObject;
////////////////////////////////////
// Ходьба по карте(для противников
const float minTimeWalk = 4.f;
const float maxTimeWalk = 12.f;
////////////////////////////////////

class Enemy : public Entity
{
public:
	// Для направления взгляда
	float rotation;

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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Объявление сущности
void initializeEntitys(TypeEnemy *typesEnemy, std::vector<Enemy> &enemy, int countEnemy,
											 Item &emptyItem, UnlifeObject &emptyObject);