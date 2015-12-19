#pragma once
#include "../ListObjectsAndBlocks.h"
#include "../Items//Items.h"
#include "../UnlifeObject/UnlifeObject.h"
//#include "../Map/Map.h"

struct emptyObjects;
const int AMOUNT_ENEMY_ITEM = 8;

const float MULTIPLIER_OF_DAMAGE = 1.f;
const float TIME_GIVEN_DAMAGE = 1.f;

const float SPEED_ENTITY = 150.f;
const float RADIUSE_VIEW = 300.f;

const int AMOUNT_ENTITY = 30;
const int AMOUNT_ACTIVE_SLOTS = 10;

const float TIME_ATTENTION_SHOW_DAMAGE = 1.5f;

const sf::Color NORMAL_COLOR(255 , 255 , 255 , 255);
const sf::Color TRANSPARENT_COLOR(255 , 255 , 255 , 127);

const float TIME_ATACK = 1.f;

const float MULTIPLY_STEP_ANIMATION = 5;
const int NUMBER_FOR_COMPUTE_SHIFT_WALK_ANIMATION = 6;
const int RESET_WALK_ANIMATION = 4;
const int RESET_ATACK_ANIMATION = 3;
const int SHIFT_ANIMATION_ATACK = 4;

const float minTimeWalk = 4.f;
const float maxTimeWalk = 12.f;

const int ID_PLAYER_IN_LIST = 0;

enum idEntity
{
	playerEntity,
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
	int cuttingDamage = 0;// �������� �� ���������
	int crushingDamage = 1;// �������� �� ���������
	int unlifeDamage = 0;

	int outputDamage;

	int inputDamage;
	int inputCutDamage;
	int inputCrashDamage;
	int inputUnlifeDamage;

	float timeInputDamage;// ���������� ���� � ������� ... ������

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

struct Entity;
struct foundObjects {
	UnlifeObject *findObject;
	int findObjectFromList;
	UnlifeObject* emptyObject;

	sf::Vector3i currentTarget;

	Item *findItem;
	int findItemFromList;
	Item *emptyItem;

	Entity *findEnemy;
	Entity *emptyEnemy;
	int findEnemyFromList;
	void init(emptyObjects &emptyObjects);

};

struct currentCollision {
	sf::Vector3i posBlock = RESET_VECTOR_3I;
	sf::Vector2f posObject = RESET_VECTOR_2F;
	int levelObject = RESET_COLLISION_VALUE;

	wchar_t block;
	int idObject = RESET_COLLISION_VALUE;

	void initPos(int xPos, int yPos, int zPos);
	void clear();
};
