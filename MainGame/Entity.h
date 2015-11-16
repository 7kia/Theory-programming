#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include "ListObjectsAndBlocks.h"
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

	Direction direction;

	float timeWalk = 0;
	float currentTime = 0;

	void init(float first);
};

struct entityAnimation
{
	float timeAnimation = 0.f;
	float timeFightAnimation = 0.f;

	float timeOutputDamage;
	float currentTimeFightAnimation;

	void init(float input, float output);
	void updateFight(const sf::Time deltaTime, bool &giveDamage);

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

	void init(int cut, int crush, float time, float mult);
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

struct foundObjects
{
	UnlifeObject *findObject;
	int findObjectFromList;
	UnlifeObject* emptyObject;

	sf::Vector2i currentTarget;

	Item *findItem;
	Item *emptyItem;
	int findItemFromList;
	void init(Item *item, UnlifeObject *object);
};

struct currentCollision
{
	int x;
	int y;
	int level;
	wchar_t block;
	int idObject;

	void initPos(int xPos, int yPos, int zPos);
	void clear();
};

class Entity
{
public:
	sf::Sprite *spriteEntity;
	sizeSprite size;
	entityAnimation animation;
	Directions directions;
	Step step;
	sf::Vector2f movement;

	std::vector<sf::Sound*> soundsEntity;

	DamageInputAndOutput damage;
	bool giveDamage;

	int radiusUse;
	int currentLevelFloor;

	foundObjects founds;
	//////////////////////////////////////////////////
	// ��� �������������� � �����
	int currenMode;
	Item *itemFromPanelQuickAccess;
	int idSelectItem;

	bool wasCollision;
	currentCollision collision;

	bool isEmptySlot();
	int emptySlot;


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

	void initStepSounds(dataSound& databaseSound);

	void choceShiftUseItem(int &shiftX, int &shiftY, bool prickBlow);
	void renderCurrentItem(sf::RenderWindow &window);

	// ������������. ��� �������� � �������
	void update(const Time & deltaTime, dataSound &databaseSound);
	void playAnimationWalk(const Time & deltaTime, dataSound & databaseSound);
	void playAnimationAtack(const Time & deltaTime, dataSound & databaseSound);
	void playSound(float time, float &start, const int idSound);
	void resetTimeAnimation(float &time, float &reset);

	// �������������� � �����
	void interactionWithMap(Field &field, listDestroyObjectsAndBlocks& listDestroy, const Time & deltaTime);
	void interactionWitnUnlifeObject(std::vector<UnlifeObject> *unlifeObjects, const Time & deltaTime);
	bool isInUseField(float x, float y, bool under);

	sf::Vector2i isEmptyFloor(Field &field, int currentLevel);// ���� ������ ������ ������
	bool isExitFromBorder(int x, int y);// ���� ����� �� ������� �����
																			//��������������� �������
	float getXPos();
	float getYPos();

	void choiceDirectionLook(int &xShift, int &yShift);
	//////////////////////////////////////////////////////////////////////////////////////////vv
	// ITEMS
	// ������������� ���������
	bool isInListBlocks(wchar_t block, wchar_t * listBlocks);
	bool isInListObjects(String * listObjects, int sizeString);


	void takeItem(Field &field, std::vector<Item> &items, float x, float y);
	void throwItem(Field &field, std::vector<Item> &items);


	void useTool(Event &event, Field &field,
							 Item &currentItem,
							 TypeItem *typesItems, std::vector<Item> *items, std::vector<UnlifeObject> *unlifeObjects);
	void useBlock(float & xMouse, float & yMouse, sf::Event & event, Field & field,
								Item & currentItem, TypeItem * typesItems, std::vector<Item>* items,
								TypeUnlifeObject * typesUnlifeObjects, std::vector<UnlifeObject>* unlifeObjects);
	//////////////////////////////////////////////////////////////////////////////////////////
	// UseItem.cpp
	void defineLevel(int &number, sf::Event event);
	void redefineType(Item &currentItem, TypeItem *typesItems, int shift);

	void useAsBottleWithWater(Item &currentItem, TypeItem *typesItems, sf::Event event);
	void useAsFood(Item &currentItem, sf::Event event);
	void useAsEmptyBottle(Item &currentItem, TypeItem *typesItems, Field &field, int level);
	void useAsEmptyBukket(Item &currentItem, TypeItem *typesItems, Field &field, int level);
	void useAsBukketWithWater(Item &currentItem, TypeItem *typesItems, sf::Event event, Field &field);
	//private:

};

bool isObject(float x, float y, std::vector<UnlifeObject> &unlifeObjects, UnlifeObject &findObject,
							int &findObjectFromList, int &current, int currentLevel);
bool isItem(float x, float y, std::vector<Item> &items, Item &findItem,
						int &findItemFromList, int &current, int currentLevel);
