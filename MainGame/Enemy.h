#pragma once
#include "Entity.h"

class Enemy : public Entity
{
public:
	// ������ ���������

	// ��� ����������� �������
	float rotation;

	// ��� �������������� � �����
	int currenMode;
	Item *items;
	Item *emptyItem;// �������
	int idSelectItem;


	TypeEnemy *type;
	///////////////////////////////////////////////////////
	// ��� ����������� ������
	Enemy *findEnemy;
	Enemy *emptyEnemy;
	std::list<Enemy>::iterator findEnemyFromList;
	///////////////////////////////////////////////////////

	void EnemyInit(TypeEnemy &typesEnemy, Item &emptyItem, UnlifeObject &emptyObject, int xPos, int yPos, int level);
	~Enemy();
private:

};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���������� ��������
void initializeEntitys(TypesEnemy *typesEnemy, std::list<Enemy> &enemy, int countEnemy,
											 Item &emptyItem, UnlifeObject &emptyObject);