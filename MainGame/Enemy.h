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
	// ��� ����������� �������
	float rotation;

	void initStepSounds();

	// ��� �������������� � �����
	int currenMode;
	Item *items;
	Item *emptyItem;// �������
	int idSelectItem;

	float radiuseView;

	TypeEnemy *type;
	///////////////////////////////////////////////////////
	// ��� ����������� ������
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