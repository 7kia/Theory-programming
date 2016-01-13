#include <list>
#include "TypeEnemy.h"


const float SCALE_VIEW = 1.5f;
//void initializePlayer(sf::View &view , sf::Listener &listener);

struct Entity
{

public:
	~Entity();
	sf::Sprite *spriteEntity;

	entityAnimation animation;
	Directions directions;
	Step step;
	sf::Vector2f movement;

	dataSound *soundBase;
	Sound soundEntity;

	DamageInputAndOutput damage;
	bool isAtack;
	bool giveDamage;
	bool getStateGiveDamage();
	String getName();
	FloatRect getGlobalBounds();
	int currentLevelFloor;

	foundObjects founds;
	Item& getFindItem();
	void setFindItem(Item & item);
	UnlifeObject& getFindUnlifeObject();
	Entity& getFindEntity();

	Item* getRefOnEmptyItem();
	UnlifeObject* getRefOnEmptyUnlifeObject();
	Entity* getRefOnEmptyEntity();

	sf::Vector3i& getCurrentTarget();
	int getLevelFloor();
	int getLevelWall();

	int getIdFindItem();
	void setIdFindItem(int number);
	int getIdFindUnlifeObject();
	int getIdFindEntity();


	//////////////////////////////////////////////////
	// ��� �������������� � �����
	idEntityMode currenMode;
	Item *itemsEntity;
	int idSelectItem;
	Item& getCurrentItem();
	Item &getEmtySlot();
	void fillEmptySlot(Item &item);

	bool wasCollision;
	bool enemyUp;
	bool enemyDown;
	currentCollision collision;

	bool isEmptySlot();
	int emptySlot;

	int getAmountSlots();



	//////////////////////////////////////////////////
	// ����������

	bool isDeath = false;
	bool getStateDeath();

	entityHealth health;
	entityStamina stamina;
	entityMana mana;
	entityHungry hungry;
	entityProtection protection;
	void choceShiftUseItem(int &shiftX, int &shiftY, bool prickBlow);
	void renderCurrentItem(sf::RenderWindow &window);

	// ������������. ��� �������� � �������
	// Entity.cpp
	void update(const float deltaTime);
	void updateDirectionLook();

	bool isInUseField(sf::Vector2f pos, bool under);
	void playAtackSound(Item &currentItem);

	// EntityAnimation.cpp
	void playAnimationWalk(const float deltaTime);
	void playAnimationAtack(const float deltaTime);
	void playSoundAfterTime(float time, const int idSound);
	void resetTimeAnimation(float &time, float reset);

	void resetAtack();
//


	void playObjectBreakSound(int idNature);
	void playObjectDropSound(sf::Vector2f pos);
	// �������������� � �����
	bool isDestroyEffect(sf::Vector3i &pos, world &world);
	bool isUnlifeObject(sf::Vector3i& pos, world& world);

	// EntityCollision.cpp
	void interactionWithMap(Field &field, listDestroyObjectsAndBlocks& listDestroy, const float deltaTime);
	void gravitateToGround(Field &field);
	void interactionWitnShoots(std::vector<shoot>& unlifeObjects ,
														 std::vector<int> &listDelete,
														 const float deltaTime);
	void interactionWitnUnlifeObject(std::vector<UnlifeObject> &unlifeObjects, const float deltaTime);
	void interactionWithEntity(std::vector<Entity>* enemys , int id , const float deltaTime);

	//
	bool isExitFromBorder(int x, int y);// ���� ����� �� ������� �����
	bool isExitFromBorder(float x, float y);
	//��������������� �������
	float getXPos();
	float getYPos();
	sf::Vector2f getPosition();
	int getXPosOnMap();
	int getYPosOnMap();
	sf::Vector2i getMapPosition();

	float getAbsolutXPos();
	float getAbsolutYPos();
	sf::Vector2f getAbsolutPosition();

	void setPosition(sf::Vector2f pos);

	void choiceDirectionLook(int &xShift, int &yShift);
	//////////////////////////////////////////////////////////////////////////////////////////vv
	// ITEMS
	// ������������� ���������


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
	void createBullet(std::vector<shoot>& shoots , TypeShoot &type , int level);
	//////////////////////////////////////////////////////////////////////////////////////////
	// UseItem.cpp
	void defineLevel(int &number, sf::Event event);

	void createDestroyEffect(world &world , Vector3i &pos);

	void createRedefineItem(world &world, Item &currentItem, int shift);
	void takeRedefineItem(world &world);
	void redefineType(Item &currentItem, world &world, int shift);

	void useAsHealthPotion(Item& currentItem, world& world, Event event);
	void useAsFood(Item &currentItem, sf::Event event);

	void useAsRifle(Item &currentItem , world &world);
	int searchBulletInInventory();

	void breakNearCollision(world &world);
	void useTool(sf::Vector3i &pos, world &world, Item &currentItem);
	void useToolToObject(sf::Vector3i &pos, world &world, Item &currentItem);
	void breakFindObject(Item &currentItem);

	void destroyFindObject(bool isEffect, Vector3i pos, world& world);
	int defineIdNature(Field &field, bool isEffect, sf::Vector3i pos);
	int defineIdNature(world &world , sf::Vector3i pos);
	void useBlock(sf::Vector3i pos, world &world, Item & currentItem);
	void upgradeObject(UnlifeObject& object, world& world);
	//////////////////////////////////////////////////////////////////////////////
	//{                          Entity                                         }//
	float rotation = -1.f;



	const TypeEnemy* getType();
	const sizeSprite& getSize();
	int getWidth();
	int getHeight();
	int getRadiuseUse();

	void init(TypeEnemy &typesEnemy , world &world , sf::Vector3i posEntity);
	void setSpriteEntity();
	void initItems(world &world);
	void initPosition(sf::Vector3i pos);
	void initRandowWalk();
	void initFeatures();
	void initProtection();
	void initDamage();

	void Drop(world &world);
	void playSoundDeath(world &world);

	void checkLevelHealth(Vector2f& movement);
	void entityStandPanic(sf::Vector2f &movement);

	void randomWalk(const float deltaTime);

	void takeDamage(DamageInputAndOutput damageEnemy , Item& currentItem);

	void choiceDirections(Vector2f movement);
	void defineDirectionLook(Vector2f movement);
	void choiceBlock(world &world);

	void resetFightAnimation();
	void searchWay(world &world);
	bool findLadder(world &world , sf::Vector3i pos);
	void buildLadder(world &world);

	void checkInDirectionWalk(Field &field , float distanse , sf::Vector2i posStart , sf::Vector2i shifts);
	void redefineDirectionWalk();
	void checkBlock(Field &field , float distanse);
	//{                          Entity                                         }//
	//////////////////////////////////////////////////////////////////////////////
	void updateView(sf::View &view , sf::Listener &listener , sf::RenderWindow &window);

	void killFindEnemy(world &world);
	void hurtEnemy(Item &currentItem , const float deltaTime);
	void updateAtack(world &world , const float deltaTime);

	void searchEnemy(Entity &enemy , world &world , const float deltaTime);
	void searchNearCollision(world &world);
	void getCoordinateForView(sf::Vector2f position, sf::View &view);

	void computeAngle(sf::RenderWindow &window);


	void useItem(world &world , Event &event , Vector2f pos);

	void playSoundChoiseItem();

// TODO : DO PRIVATE
		TypeEnemy *type;

	private:
		Item *emptyItem;
};

