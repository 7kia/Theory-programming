#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include "TypeEnemy.h"

const int AMOUNT_ENTITY = 100;
const int AMOUNT_ACTIVE_SLOTS = 10;

const sf::Color NORMAL_COLOR(255, 255, 255, 255);
const sf::Color TRANSPARENT_COLOR(255, 255, 255, 127);

class Entity 
{
public:
	// ���������
	sf::Sprite *spriteEntity;

	// ��� ��������
	Direction direction;
	float stepFirst;
	float stepCurrent;
	float timeAnimation;
	sf::Vector2f movement;

	// ������ �� �����
	sf::Sound *soundsEntity[sizeBuffer];

	// ��� �������������� � �����
	float timeWalk = 0;
	float currentTime = 0;

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
	std::list<UnlifeObject>::iterator findObjectFromList;
	UnlifeObject* emptyObject;
	/////////////////////////////////////////
	// ��� �������������� � ���������
	Item *findItem;
	std::list<Item>::iterator findItemFromList;
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

	int inputDamage;

	bool isDeath = false;
	////////////////////////////
	// ��������
	bool isMaxHealth = true;
	bool needMinusHealth = false;

	float timeForHealth = 0;
	float timeUpdateHealth = 0.5;

	int addHealth = 1;
	int delHealth = 2;

	int currentHealth = 100;
	int maxHealth = 100;
	////////////////////////////
	// ������������
	bool isMaxStamina = true;
	bool needMinusStamina = false;

	float timeForStamina = 0;
	float timeUpdateStamina = 0.5;

	int addStamina = 1;
	int delStamina = 4;

	int currentStamina = 100;
	int maxStamina = 100;
	////////////////////////////
	// ����
	bool isMaxMana = true;
	bool needMinusMana = false;

	float timeForMana = 0;
	float timeUpdateMana = 0.5;

	int addMana = 1;
	int delMana = 2;

	int currentMana = 100;
	int maxMana = 100;
	////////////////////////////
	// �����
	float timeForHungry = 0;
	float timeUpdateHungry = 100;
	int currentHungry = 20;
	int maxHungry = 20;

	////////////////////////////
	// �����
	float timeForThirst = 0;
	float timeUpdateThirst = 60;
	int currentThirst = 20;
	int maxThirst = 20;
	////////////////////////////


	//////////////////////////////////////////////////
	// ������
	float protectionCut;
	float protectionCrash;
	//////////////////////////////////////////////////

	// ������������. ��� �������� � �������
	void update(const Time & deltaTime, dataSound &databaseSound);
	void playSound(float time, float &start, const int idSound);
	void resetTimeAnimation(float &time, float &reset);
	
	// �������������� � �����
	void interactionWithMap(Field &field, destroyObjectsAndBlocks& listDestroy, const Time & deltaTime);
	bool isInUseField(float x, float y);
	
	sf::Vector2i isEmptyFloor(Field &field, int currentLevel);// ���� ������ ������ ������
	bool isExitFromBorder(int x, int y);// ���� ����� �� ������� �����
	//��������������� �������
	float getXPos();
	float getYPos();

//private:

};

bool isObject(float x, float y, std::list<UnlifeObject> *unlifeObjects, UnlifeObject *&findObject, std::list<UnlifeObject>::iterator &findObjectFromList, std::list<UnlifeObject>::iterator &current, int currentLevel);
bool isItem(float x, float y, std::list<Item> &items, Item *&findItem, std::list<Item>::iterator &findItemFromList, std::list<Item>::iterator &current, int currentLevel);
