#pragma once
#include <SFML\Graphics.hpp>
#include "TypeEnemy.h"

class MainPerson;
struct TypeEnemy;
class UnlifeObject;

const float minTimeWalk = 4.f;
const float maxTimeWalk = 12.f;

class Enemy : public Entity
{
public:


};

struct foundsByEnemy
{
	foundObjects foundsObjects;
	Enemy *findEnemy;
	Enemy *emptyEnemy;
	int findEnemyFromList;
	void init(Item &item, UnlifeObject &object, Enemy &enemy);
};
