#pragma once
#include <SFML\Graphics.hpp>
<<<<<<< HEAD
#include "TypeEnemy.h"

class MainPerson;
struct TypeEnemy;
class UnlifeObject;

const float minTimeWalk = 4.f;
const float maxTimeWalk = 12.f;

class Enemy : public Entity
{
public:
	// Для направления взгляда
	float rotation;

	// Для взаимодействия с миром
	idEntityMode currenMode;
	Item *items;
	Item *emptyItem;// ИСПРАВЬ
	int idSelectItem;

	TypeEnemy *type;
=======
>>>>>>> master

/*
#include "TypeEntity.h"

<<<<<<< HEAD
	///////////////////////////////////////////////////////
	// Для уничтожения врагов
	Enemy *findEnemy;
	Enemy *emptyEnemy;
	int findEnemyFromList;
	///////////////////////////////////////////////////////
	void EnemyInit(TypeEnemy &typesEnemy, world &world, int xPos, int yPos, int level);
	void initFeatures();
	void initProtection();
	void initDamage();

	void EnemyDrop(world &world);
	void playSoundDeath(world &world);
	~Enemy();

	void checkLevelHealth(Vector2f& movemoment);
	void entityStandPanic(sf::Vector2f &movemoment);

	void randomWalk(const float deltaTime);

	void takeDamage(DamageInputAndOutput damage, Item& currentItem);

	void choiceDirections(Vector2f movemoment);
	void defineDirectionLook(Vector2f movemoment);
	void choiceBlock(world &world);

	void resetFightAnimation();
	void searchWay(world &world);
	bool findLadder(world &world, sf::Vector3i pos);
	void buildLadder(world &world);
	void givenForPersonDamage(MainPerson & person);
	void hurtPerson(MainPerson &enemy, world &world, const float deltaTime);
=======

struct TypeEntity;
class UnlifeObject;
>>>>>>> master


<<<<<<< HEAD
=======
const float minTimeWalk = 4.f;
const float maxTimeWalk = 12.f;
>>>>>>> master


struct foundsByEntity
{
	foundObjects foundsObjects;
	Entity *findEntity;
	Entity *emptyEntity;
	void init(Item &item, UnlifeObject &object, Entity &enemy);
};

*/
