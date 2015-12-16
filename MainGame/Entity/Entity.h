#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include "EntityVar.h"

struct world;
struct destroyObjectsAndBlocks;
struct Field;

struct MainPerson;
struct Enemy;
struct TypeEnemy;
const int AMOUNT_ENTITY = 30;
const int AMOUNT_ACTIVE_SLOTS = 10;

const float TIME_ATTENTION_SHOW_DAMAGE = 1.5f;

const sf::Color NORMAL_COLOR(255, 255, 255, 255);
const sf::Color TRANSPARENT_COLOR(255, 255, 255, 127);

const float TIME_ATACK = 1.f;

const float MULTIPLY_STEP_ANIMATION = 5;
const int NUMBER_FOR_COMPUTE_SHIFT_WALK_ANIMATION = 6;
const int RESET_WALK_ANIMATION = 4;
const int RESET_ATACK_ANIMATION = 3;
const int SHIFT_ANIMATION_ATACK = 4;

class Entity
{
public:
	sf::Sprite *spriteEntity;
	sizeSprite size;
	entityAnimation animation;
	Directions directions;
	Step step;
	sf::Vector2f movement;

	dataSound *soundBase;
	Sound soundEntity;

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
	void choceShiftUseItem(int &shiftX, int &shiftY, bool prickBlow);
	void renderCurrentItem(sf::RenderWindow &window);

	// Передвижение. Его анимация и озвучка
	void update(const float deltaTime);
	void resetAtack();
	void playAnimationWalk(const float deltaTime);
	void playAnimationAtack(const float deltaTime);
	void playSoundAfterTime(float time, const int idSound);
	void resetTimeAnimation(float &time, float reset);

	void playAtackSound(Item &currentItem);
	void createDestroyEffect(world &world, Vector3i &pos);

	void playObjectBreakSound(int idNature);
	void playObjectDropSound(sf::Vector2f pos);
	// Взаимодейтсвие с миром
	bool isDestroyEffect(sf::Vector3i &pos, world &world);
	bool isUnlifeObject(sf::Vector3i& pos, world& world);

	void interactionWithMap(Field &field, listDestroyObjectsAndBlocks& listDestroy, const float deltaTime);
	void interactionWitnUnlifeObject(std::vector<UnlifeObject> *unlifeObjects, const float deltaTime);
	bool isInUseField(float x, float y, bool under);

	sf::Vector2i isEmptyFloor(Field &field, int currentLevel);// Есть вблизи пустые клетки
	bool isExitFromBorder(int x, int y);// Есть выход за границы карты
	bool isExitFromBorder(float x, float y);
	//Вспомагательные функции
	float getXPos();
	float getYPos();
	sf::Vector2f getPosition();

	void choiceDirectionLook(int &xShift, int &yShift);
	//////////////////////////////////////////////////////////////////////////////////////////vv
	// ITEMS
	// Использование предметов
	bool isInListBlocks(wchar_t block, std::vector<wchar_t> &listObjects);
	bool isInListIds(int id, std::vector<wchar_t>& listIds);
	bool isInListObjects(std::vector<int> &listTypes, int id);


	void transferInInventory(std::vector<Item> &items);
	void searchItem(std::vector<Item> &items, sf::Vector2f pos);
	void takeItem(world &world, sf::Vector2f pos);
	void throwItem(Field &field, std::vector<Item> &items);

	void minusAmount(Item& currentItem);
	void breakItem(Item &currentItem);

	void run();
	//////////////////////////////////////////////////////////////////////////////////////////
	void actionMain(world &world, sf::Vector2f pos);
	void actionAlternate(world &world, sf::Vector2f pos);
	//////////////////////////////////////////////////////////////////////////////////////////
	// UseItem.cpp
	void defineLevel(int &number, sf::Event event);

	void createRedefineItem(world &world, Item &currentItem, int shift);
	void takeRedefineItem(world &world);
	void redefineType(Item &currentItem, world &world, int shift);

	void useAsBottleWithWater(Item &currentItem, world &world, sf::Event event);
	void useAsHealthPotion(Item& currentItem, world& world, Event event);
	void useAsFood(Item &currentItem, sf::Event event);
	void useAsEmptyBottle(Item &currentItem, world &world, int level);
	void useAsEmptyBukket(Item &currentItem, world &world, int level);
	void useAsBukketWithWater(Item &currentItem, world &world, sf::Event event);

	void breakNearCollision(world &world);
	void useTool(sf::Vector3i &pos, world &world, Item &currentItem);
	void useToolToObject(sf::Vector3i &pos, world &world, Item &currentItem);
	void breakFindObject(Item &currentItem);

	void destroyFindObject(bool isEffect, Vector3i pos, world& world);
	int defineIdNature(Field &field, bool isEffect, sf::Vector3i pos);
	void useBlock(sf::Vector3i pos, world &world, Item & currentItem);
	void upgradeObject(UnlifeObject& object, world& world);
	//////////////////////////////////////////////////////////////////////////////
	//{                          Enemy                                         }//


	// TODO
	float rotation;

	Item *emptyItem;

	TypeEnemy *type;


	///////////////////////////////////////////////////////
	// Для уничтожения врагов
	Enemy *findEnemy;
	Enemy *emptyEnemy;
	int findEnemyFromList;
	///////////////////////////////////////////////////////
	void EnemyInit(TypeEnemy &typesEnemy , world &world , int xPos , int yPos , int level);
	void initFeatures();
	void initProtection();
	void initDamage();

	void EnemyDrop(world &world);
	void playSoundDeath(world &world);
	~Entity();

	void checkLevelHealth(Vector2f& movemoment);
	void entityStandPanic(sf::Vector2f &movemoment);

	void randomWalk(const float deltaTime);

	void takeDamage(DamageInputAndOutput damageEnemy , Item& currentItem);

	void choiceDirections(Vector2f movemoment);
	void defineDirectionLook(Vector2f movemoment);
	void choiceBlock(world &world);

	void resetFightAnimation();
	void searchWay(world &world);
	bool findLadder(world &world , sf::Vector3i pos);
	void buildLadder(world &world);
	void givenForPersonDamage(MainPerson & person);
	void hurtPerson(MainPerson &enemy , world &world , const float deltaTime);

	void checkInDirectionWalk(Field &field , float distanse , sf::Vector2i posStart , sf::Vector2i shifts);
	void redefineDirectionWalk();
	void checkBlock(Field &field , float distanse);
	void interactionWithEntity(std::vector<Enemy>* enemys , int id , const float deltaTime);
	//{                          Enemy                                         }//
	//////////////////////////////////////////////////////////////////////////////
};

bool isObject(float x, float y, std::vector<UnlifeObject> &unlifeObjects, UnlifeObject &findObject,
							int &findObjectFromList, int &current, int currentLevel);
bool isItem(float x, float y, std::vector<Item> &items, Item &findItem,
						int &findItemFromList, int &current, int currentLevel);
