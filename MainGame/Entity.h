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
	int cuttingDamage = 0;// Значение по умолчанию
	int crushingDamage = 1;// Значение по умолчанию

	int outputDamage;

	int inputDamage;
	int inputCutDamage;
	int inputCrashDamage;

	float timeInputDamage;// Показывает урон в течении ... секунд

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
	// Для взаимодействия с миром
	int currenMode;
	Item *itemFromPanelQuickAccess;
	int idSelectItem;

	bool isEmptySlot();
	int emptySlot;


	bool isMoveItem;
	float dMoveItemX, dMoveItemY;

	//////////////////////////////////////////////////
	// Индикаторы

	// Показатели
	sf::Sprite* bar;
	sf::Sprite* levelHealth;// ИСПРАВЬ
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
	// Передвижение. Его анимация и озвучка
	void update(const Time & deltaTime, dataSound &databaseSound);
	void playAnimationWalk(const Time & deltaTime, dataSound & databaseSound);
	void playAnimationAtack(const Time & deltaTime, dataSound & databaseSound);
	void playSound(float time, float &start, const int idSound);
	void resetTimeAnimation(float &time, float &reset);

	// Взаимодейтсвие с миром
	void interactionWithMap(Field &field, destroyObjectsAndBlocks& listDestroy, const Time & deltaTime);
	bool isInUseField(float x, float y, bool under);

	sf::Vector2i isEmptyFloor(Field &field, int currentLevel);// Есть вблизи пустые клетки
	bool isExitFromBorder(int x, int y);// Есть выход за границы карты
																			//Вспомагательные функции
	float getXPos();
	float getYPos();

	//////////////////////////////////////////////////////////////////////////////////////////vv
	// ITEMS
	// Использование предметов
	bool isInListBlocks(wchar_t block, wchar_t * listBlocks);
	bool isInListObjects(String * listObjects, int sizeString);


	void takeItem(Field &field, std::vector<Item> &items, float x, float y);
	void throwItem(Field &field, std::vector<Item> &items);


	void useTool(float &xMouse, float &yMouse, Event &event, Field &field,
							 sf::String* listObjects, wchar_t* listBlocks, int &sizeListObjects,
							 Item &currentItem,
							 TypeItem *typesItems, std::vector<Item> *items, std::vector<UnlifeObject> *unlifeObjects);
	void useBlock(float & xMouse, float & yMouse, sf::Event & event, Field & field,
								Item & currentItem, TypeItem * typesItems, std::vector<Item>* items,
								TypeUnlifeObject * typesUnlifeObjects, std::vector<UnlifeObject>* unlifeObjects);
	//////////////////////////////////////////////////////////////////////////////////////////
	//private:

};

bool isObject(float x, float y, std::vector<UnlifeObject> &unlifeObjects, UnlifeObject &findObject,
							int &findObjectFromList, int &current, int currentLevel);
bool isItem(float x, float y, std::vector<Item> &items, Item &findItem,
						int &findItemFromList, int &current, int currentLevel);
