#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include "Items.h"
#include "UnlifeObject.h"

struct destroyObjectsAndBlocks;
struct Field;
const int AMOUNT_ENTITY = 100;
const int AMOUNT_ACTIVE_SLOTS = 10;

const float TIME_ATTENTION_SHOW_DAMAGE = 1.5f;

const sf::Color NORMAL_COLOR(255, 255, 255, 255);
const sf::Color TRANSPARENT_COLOR(255, 255, 255, 127);

struct Directions
{
	Direction directionWalk;
	Direction directionLook;
};

struct Step
{
	float stepFirst;
	float stepCurrent;

	float timeWalk = 0;
	float currentTime = 0;

	void init(float first);
};

struct entityAnimation
{
	float timeAnimation = 0.f;
	float timeFightAnimation = 0.f;

	float timeOutputDamage;
	float currentTimeOutputDamage;

	void updateFight(const sf::Time deltaTime);

};

struct DamageInputAndOutput
{
	float damageMultiplirer;
	float timeOutputDamage;
	int cuttingDamage = 0;// �������� �� ���������
	int crushingDamage = 1;// �������� �� ���������

	int outputDamage;

	int inputDamage;
	int inputCutDamage;
	int inputCrashDamage;

	float timeInputDamage;// ���������� ���� � ������� ... ������

	void init(int cut, int crush, float time);
	void updateOutputDamage(const sf::Time deltaTime);
	void updateInputDamage(const sf::Time deltaTime);
};

struct entityHealth
{
	bool isMaxHealth = true;
	bool needMinusHealth = false;

	float timeForHealth = 0;
	float timeUpdateHealth = 0.5;

	int addHealth = 1;
	int delHealth = 2;

	int currentHealth = 100;
	int maxHealth = 100;
	void update(const sf::Time deltaTime, bool& isDeath);
};

struct entityStamina
{
	bool isMaxStamina = true;
	bool needMinusStamina = false;

	float timeForStamina = 0;
	float timeUpdateStamina = 0.5;

	int addStamina = 1;
	int delStamina = 4;

	int currentStamina = 100;
	int maxStamina = 100;
	void update(const sf::Time deltaTime, Direction directionWalk, Step& step);
};

struct entityMana
{
	bool isMaxMana = true;
	bool needMinusMana = false;

	float timeForMana = 0;
	float timeUpdateMana = 0.5;

	int addMana = 1;
	int delMana = 2;

	int currentMana = 100;
	int maxMana = 100;

	void update(const sf::Time deltaTime);
};

struct entityHungry
{
	float timeForHungry = 0;
	float timeUpdateHungry = 100;
	int currentHungry = 20;
	int maxHungry = 20;
	void update(const sf::Time deltaTime, bool& needMinusHealth);
};

struct entityThirst
{
	float timeForThirst = 0;
	float timeUpdateThirst = 60;
	int currentThirst = 20;
	int maxThirst = 20;
	void update(const sf::Time deltaTime, bool& needMinusHealth);
};

struct entityProtection
{
	float protectionCut;
	float protectionCrash;
	void init(float cut, float crash);
};

class Entity
{
public:
	// ���������
	sf::Sprite *spriteEntity;

	Directions directions;
	Step step;
	DamageInputAndOutput damage;
	entityAnimation animation;
	bool atack;

	sf::Vector2f movement;

	// ������ �� �����
	sf::Sound *soundsEntity[sizeBuffer];

	int radiusUse;
	int currentLevelFloor;

	int width;
	int height;

	//////////////////////////////////////////////////
	// ��� �������������� � �����
	int currenMode;
	Item *itemFromPanelQuickAccess;
	Item *emptyItem;// �������
	int idSelectItem;

	bool isEmptySlot();
	int emptySlot;

	/////////////////////////////////////////
	// ��� �������������� � ��������
	UnlifeObject *findObject;
	int findObjectFromList;
	UnlifeObject* emptyObject;
	/////////////////////////////////////////
	// ��� �������������� � ���������
	Item *findItem;
	int findItemFromList;
	/////////////////////////////////////////
	bool isMoveItem;
	float dMoveItemX, dMoveItemY;

	//////////////////////////////////////////////////
	// ����������

	// ����������
	sf::Sprite* bar;
	sf::Sprite* levelHealth;// �������
	sf::Sprite* levelStamina;
	sf::Sprite* levelMana;

	bool isDeath = false;
	entityHealth health;
	entityStamina stamina;
	entityMana mana;
	entityHungry hungry;
	entityThirst thirst;
	entityProtection protection;


	// ������������. ��� �������� � �������
	void update(const Time & deltaTime, dataSound &databaseSound);
	void playAnimationWalk(const Time & deltaTime, dataSound & databaseSound);
	void playAnimationAtack(const Time& deltaTime, dataSound& databaseSound);
	void playSound(float time, float &start, const int idSound);
	void resetTimeAnimation(float &time, float &reset);

	// �������������� � �����
	void interactionWithMap(Field &field, destroyObjectsAndBlocks& listDestroy, const Time & deltaTime);
	bool isInUseField(float x, float y, bool under);

	sf::Vector2i isEmptyFloor(Field &field, int currentLevel);// ���� ������ ������ ������
	bool isExitFromBorder(int x, int y);// ���� ����� �� ������� �����
																			//��������������� �������
	float getXPos();
	float getYPos();

	//private:

};

bool isObject(float x, float y, std::vector<UnlifeObject> &unlifeObjects, UnlifeObject &findObject,
							int &findObjectFromList, int &current, int currentLevel);
bool isItem(float x, float y, std::vector<Item> &items, Item &findItem,
						int &findItemFromList, int &current, int currentLevel);
