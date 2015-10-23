#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include "GlobalVar.h"
#include "ListObjectsAndBlocks.h"
#include "UnlifeObject.h"
#include "Items.h"
#include "Map.h"
#include "Sound.h"

const float speedEntity = 350.f;

const sf::Color NORMAL_COLOR(255, 255, 255, 255);
const sf::Color TRANSPARENT_COLOR(255, 255, 255, 127);

class Entity 
{
public:
	// Текструра
	sf::Sprite *spriteEntity;
	sf::Texture *textureEntity;
	
	// Для движения
	Direction direction;
	float stepFirst;
	float stepCurrent;
	float timeAnimation;
	sf::Vector2f movement;

	// Для взаимодействия с миром
	int radiusUse;
	int currentLevelFloor;

	// Ссылки на звуки
	sf::Sound *soundsEntity[sizeBuffer];

	//////////////////////////////////////////////////
	// Индикаторы
	bool isDeath = false;



	// Здоровье
	bool isMaxHealth = true;
	bool needMinusHealth = false;

	float timeForHealth = 0;
	float timeUpdateHealth = 0.5;

	int addHealth = 1;
	int delHealth = 2;

	int currentHealth = 25;
	int maxHealth = 100;

	// Выносливость
	bool isMaxStamina = true;
	bool needMinusStamina = false;

	float timeForStamina = 0;
	float timeUpdateStamina = 0.5;

	int addStamina = 1;
	int delStamina = 4;

	int currentStamina = 25;
	int maxStamina = 100;

	// Мана
	bool isMaxMana = true;
	bool needMinusMana = false;

	float timeForMana = 0;
	float timeUpdateMana = 0.5;

	int addMana = 1;
	int delMana = 2;

	int currentMana = 25;
	int maxMana = 100;

	// Голод
	float timeForHungry = 0;
	float timeUpdateHungry = 100;
	int currentHungry = 5;
	int maxHungry = 20;


	// Жажда
	float timeForThirst = 0;
	float timeUpdateThirst = 60;
	int currentThirst = 5;
	int maxThirst = 20;


	//////////////////////////////////////////////////


	// Для отрисовки
	int width;
	int height;
	int widthForAnimation;
	int heightForAnimation;

	// Передвижение. Его анимация и озвучка
	void update(const Time & deltaTime, dataSound &databaseSound);
	void playSound(float time, float start, const int idSound);
	void resetTimeAnimation(float &time, float &reset);
	
	// Взаимодейтсвие с миром
	void interactionWithMap(Field &field, destroyObjectsAndBlocks& listDestroy, const Time & deltaTime);
	void interactionWitnUnlifeObject(std::list<UnlifeObject> *unlifeObjects, const Time & deltaTime);
	bool isInUseField(float x, float y);
	
	sf::Vector2i isEmptyFloor(Field &field, int currentLevel);// Есть вблизи пустые клетки
	bool isExitFromBorder(int x, int y);// Есть выход за границы карты
	//Вспомагательные функции
	float getXPos();
	float getYPos();

//private:

};

// Объявление персонажа
void initializeEntity(Entity & Entity, dataSound &databaseSound);

bool isObject(float x, float y, std::list<UnlifeObject> *unlifeObjects, UnlifeObject *&findObject, std::list<UnlifeObject>::iterator &findObjectFromList, std::list<UnlifeObject>::iterator &current, int currentLevel);
bool isItem(float x, float y, std::list<Item> &items, Item *&findItem, std::list<Item>::iterator &findItemFromList, std::list<Item>::iterator &current, int currentLevel);
