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

	TypeEnemy *type;


	///////////////////////////////////////////////////////
	// ��� ����������� ������
	Enemy *findEnemy;
	Enemy *emptyEnemy;
	int findEnemyFromList;
	///////////////////////////////////////////////////////
	void EnemyInit(TypeEnemy &typesEnemy, Item &emptyItem, UnlifeObject &emptyObject, int xPos, int yPos, int level);
	void EnemyDrop(world &world);
	~Enemy();

	void checkLevelHealth(Vector2f& movemoment);
	void entityStandPanic(sf::Vector2f &movemoment);

	void randomWalk(const float deltaTime);

	void takeDamage(DamageInputAndOutput damage, Item& currentItem);

	void choiceDirections(Vector2f movemoment);
	void defineDirectionLook(Vector2f movemoment);
	void choiceBlock(world &world);

	void findLadder(world &world, sf::Vector3i pos);
	void buildLadder(world &world);

	void checkInDirectionWalk(Field &field, float distanse, sf::Vector2i posStart, sf::Vector2i shifts);
	void redefineDirectionWalk();
	void checkBlock(Field &field, float distanse);
	void interactionWithEntity(std::vector<Enemy>* enemys, int id, const float deltaTime);

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
