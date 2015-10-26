#pragma once
#include "Entity.h"

class Enemy : public Entity
{
public:
	// режимы персонажа

	// Для направления взгляда
	float rotation;

	// Для взаимодействия с миром
	int currenMode;
	Item *items;
	Item *emptyItem;// ИСПРАВЬ
	int idSelectItem;


	TypeEnemy *type;
	///////////////////////////////////////////////////////
	// Для уничтожения врагов
	Enemy *findEnemy;
	Enemy *emptyEnemy;
	std::list<Enemy>::iterator findEnemyFromList;
	///////////////////////////////////////////////////////

	void EnemyInit(TypeEnemy &typesEnemy, Item &emptyItem, UnlifeObject &emptyObject, int xPos, int yPos, int level);
	~Enemy();
private:

};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Объявление сущности
void initializeEntitys(TypesEnemy *typesEnemy, std::list<Enemy> &enemy, int countEnemy,
											 Item &emptyItem, UnlifeObject &emptyObject);