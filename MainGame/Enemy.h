#pragma once
#include "Entity.h"
#include "Items.h"

class UnlifeObject;
////////////////////////////////////
// ������ �� �����(��� �����������
const float minTimeWalk = 4.f;
const float maxTimeWalk = 12.f;
////////////////////////////////////

class Enemy : public Entity
{
public:
	// ��� ����������� �������
	float rotation;

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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���������� ��������
void initializeEntitys(TypeEnemy *typesEnemy, std::vector<Enemy> &enemy, int countEnemy,
											 Item &emptyItem, UnlifeObject &emptyObject);