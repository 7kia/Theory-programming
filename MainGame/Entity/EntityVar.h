#pragma once
#include "../ListObjectsAndBlocks.h"
#include "../Items//Items.h"
#include "../UnlifeObject/UnlifeObject.h"
#include "../Map//Map.h"

const int AMOUNT_ENEMY_ITEM = 8;

const float MULTIPLIER_OF_DAMAGE = 1.f;
const float TIME_GIVEN_DAMAGE = 1.f;

const float SPEED_ENTITY = 150.f;
const float RADIUSE_VIEW = 300.f;


enum idEntity
{
	wolfEnemy,
	skeletEnemy,
	skeletMinerEnemy,
	skeletLumbermillEnemy,
	skeletDiggerEnemy,
	skeletBuilderEnemy,
	emptyEnemy,
	amountEnemy
};

enum idEntityMode
{
	walk,
	fight,
	atack,
	panic,
	amountEnemyMode
};


struct Directions {
	Direction directionWalk;
	Direction directionLook;
};

struct Step {
	float stepFirst;
	float stepCurrent;

	Direction direction;

	float timeWalk = 0;
	float currentTime = 0;

	void init(float first);
};

struct entityAnimation {
	float timeAnimation = 0.f;
	float timeFightAnimation = 0.f;

	float timeOutputDamage;
	float currentTimeFightAnimation;

	void init(float input, float output);
	void updateFight(const float deltaTime, bool &giveDamage, idEntityMode &idMode);

};

struct DamageInputAndOutput {
	float damageMultiplirer;
	float timeOutputDamage;
	int cuttingDamage = 0;// Значение по умолчанию
	int crushingDamage = 1;// Значение по умолчанию
	int unlifeDamage = 0;

	int outputDamage;

	int inputDamage;
	int inputCutDamage;
	int inputCrashDamage;
	int inputUnlifeDamage;

	float timeInputDamage;// Показывает урон в течении ... секунд

	void init(int cut, int crush, float time, float mult);
	void updateInputDamage(const float deltaTime);
};

struct entityHealth {
	bool isMaxHealth = true;
	bool needMinusHealth = false;

	float timeForHealth = 0;
	float timeUpdateHealth = 0.5;

	int addHealth = 1;
	int delHealth = 2;

	int currentHealth = 100;
	int maxHealth = 100;
	void update(const float deltaTime, bool& isDeath);
};

struct entityStamina {
	bool isMaxStamina = true;
	bool needMinusStamina = false;

	float timeForStamina = 0;
	float timeUpdateStamina = 0.5;

	int addStamina = 1;
	int delStamina = 4;

	int currentStamina = 100;
	int maxStamina = 100;
	void update(const float deltaTime, Direction directionWalk, Step& step);
};

struct entityMana {
	bool isMaxMana = true;
	bool needMinusMana = false;

	float timeForMana = 0;
	float timeUpdateMana = 0.5;

	int addMana = 1;
	int delMana = 2;

	int currentMana = 100;
	int maxMana = 100;

	void update(const float deltaTime);
};

struct entityHungry {
	float timeForHungry = 0;
	float timeUpdateHungry = 100;
	int currentHungry = 20;
	int maxHungry = 20;
	void update(const float deltaTime, bool& needMinusHealth);
};

struct entityThirst {
	float timeForThirst = 0;
	float timeUpdateThirst = 60;
	int currentThirst = 20;
	int maxThirst = 20;
	void update(const float deltaTime, bool& needMinusHealth);
};

struct entityProtection {
	float protectionCut;
	float protectionCrash;
	float protectionUnlife;

	bool deathDay = false;
	void init(float cut, float crash, float unlife);
};

struct foundObjects {
	UnlifeObject *findObject;
	int findObjectFromList;
	UnlifeObject* emptyObject;

	sf::Vector3i currentTarget;

	Item *findItem;
	Item *emptyItem;
	int findItemFromList;
	void init(Item *item, UnlifeObject *object);
};

struct currentCollision {
	int x = RESET_COLLISION_VALUE;
	int y = RESET_COLLISION_VALUE;
	int level = RESET_COLLISION_VALUE;
	wchar_t block;
	int idObject = RESET_COLLISION_VALUE;

	void initPos(int xPos, int yPos, int zPos);
	void clear();
};
