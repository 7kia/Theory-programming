#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include "../ListObjectsAndBlocks.h"
#include "../Items//Items.h"
#include "../UnlifeObject/UnlifeObject.h"
#include "../Map//Map.h"

#include "EntityVar.h"

struct world;
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
	void updateFight(const float deltaTime, bool &giveDamage);

};

struct DamageInputAndOutput
{
	float damageMultiplirer;
	float timeOutputDamage;
	int cuttingDamage = 0;// Значение по умолчанию
	int crushingDamage = 1;// Значение по умолчанию

	int outputDamage;

	int inputDamage;
	int inputCutDamage;
	int inputCrashDamage;

	float timeInputDamage;// Показывает урон в течении ... секунд

	void init(int cut, int crush, float time, float mult);
	void updateInputDamage(const float deltaTime);
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
	void update(const float deltaTime, bool& isDeath);
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
	void update(const float deltaTime, Direction directionWalk, Step& step);
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

	void update(const float deltaTime);
};

struct entityHungry
{
	float timeForHungry = 0;
	float timeUpdateHungry = 100;
	int currentHungry = 20;
	int maxHungry = 20;
	void update(const float deltaTime, bool& needMinusHealth);
};

struct entityThirst
{
	float timeForThirst = 0;
	float timeUpdateThirst = 60;
	int currentThirst = 20;
	int maxThirst = 20;
	void update(const float deltaTime, bool& needMinusHealth);
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
	bool isAtack;
	bool giveDamage;

	int radiusUse;
	int currentLevelFloor;

	foundObjects founds;
	//////////////////////////////////////////////////
	// Для взаимодействия с миром
	idEntityMode currenMode;
	Item *itemFromPanelQuickAccess;
	int idSelectItem;

	bool wasCollision;
	bool enemyUp;
	bool enemyDown;
	currentCollision collision;

	bool isEmptySlot();
	int emptySlot;


	bool isMoveItem;
	float dMoveItemX, dMoveItemY;

	//////////////////////////////////////////////////
	// Индикаторы

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

	// Передвижение. Его анимация и озвучка
	void update(const float deltaTime, dataSound &databaseSound);
	void playAnimationWalk(const float deltaTime, dataSound & databaseSound);
	void playAnimationAtack(const float deltaTime, dataSound & databaseSound);
	void playSound(float time, float &start, const int idSound);
	void resetTimeAnimation(float &time, float &reset);

	// Взаимодейтсвие с миром
	void interactionWithMap(Field &field, listDestroyObjectsAndBlocks& listDestroy, const float deltaTime);
	void interactionWitnUnlifeObject(std::vector<UnlifeObject> *unlifeObjects, const float deltaTime);
	bool isInUseField(float x, float y, bool under);

	sf::Vector2i isEmptyFloor(Field &field, int currentLevel);// Есть вблизи пустые клетки
	bool isExitFromBorder(int x, int y);// Есть выход за границы карты
																			//Вспомагательные функции
	float getXPos();
	float getYPos();

	void choiceDirectionLook(int &xShift, int &yShift);
	//////////////////////////////////////////////////////////////////////////////////////////vv
	// ITEMS
	// Использование предметов
	bool isInListBlocks(wchar_t block, wchar_t * listBlocks);
	bool isInListObjects(String * listObjects, int sizeString);


	void transferInInventory(std::vector<Item> &items);
	void takeItem(world &world, sf::Vector2f pos);
	void throwItem(Field &field, std::vector<Item> &items);

	void breakItem(Item &currentItem);

	void dropObject(Vector2i pos, std::vector<Item> &items, TypeItem* typesItems);

	//////////////////////////////////////////////////////////////////////////////////////////
	void actionMain(world &world, sf::Vector2f pos);
	void actionAlternate(world &world, sf::Vector2f pos);
	//////////////////////////////////////////////////////////////////////////////////////////
	// UseItem.cpp
	void defineLevel(int &number, sf::Event event);
	void redefineType(Item &currentItem, world &world, int shift);
	void useAsBottleWithWater(Item &currentItem, world &world, sf::Event event);
	void useAsFood(Item &currentItem, sf::Event event);
	void useAsEmptyBottle(Item &currentItem, world &world, int level);
	void useAsEmptyBukket(Item &currentItem, world &world, int level);
	void useAsBukketWithWater(Item &currentItem, world &world, sf::Event event);

	void useTool(sf::Vector3i pos, world &world, Item &currentItem);
	void useBlock(sf::Vector3i pos, world &world, Item & currentItem);
	//private:

};

bool isObject(float x, float y, std::vector<UnlifeObject> &unlifeObjects, UnlifeObject &findObject,
							int &findObjectFromList, int &current, int currentLevel);
bool isItem(float x, float y, std::vector<Item> &items, Item &findItem,
						int &findItemFromList, int &current, int currentLevel);
