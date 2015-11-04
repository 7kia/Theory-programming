#pragma once
#include "Enemy.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Основной персонаж
class MainPerson : public Entity
{
public:
	sf::Texture *textureEntity;

	// режимы персонажа
	//void modeProcess(Field &field, std::list<UnlifeObject> *unlifeObjects, std::list<Item> *items, sf::Event &eventPerson, float x, float y);
	// Камера
	sf::View *view;
	void updateView(sf::RenderWindow & window);

	// Для инвентаря
	int amountSlots;

	///////////////////////////////////////////////////////
	// Для уничтожения врагов
	Enemy *findEnemy;
	Enemy *emptyEnemy;
	std::list<Enemy>::iterator findEnemyFromList;

	void givenForPersonDamage(Enemy & enemy);
	void attractionEnemy(Enemy & enemy, const Time &deltaTime);
	///////////////////////////////////////////////////////
	// Основные характерисктики
	int strength;// сила
	int expStrength;// опыт
	int expStrengthUp;// количество для повышения

	int endurance;// выносливость
	int expEndurace;
	int expEnduracehUp;
	///////////////////////////////////////////////////////
	void getCoordinateForView(float x, float y);
	void viewmap(float time);
	void changeview();

	// Для направления взгляда
	float rotation;
	void computeAngle(sf::RenderWindow &window);

	void takeItem(Field &field, std::list<Item> &items, float x, float y);
	void throwItem(Field &field, std::list<Item> &items);
	void useItem(Field &field, destroyObjectsAndBlocks& listDestroy, TypeItem *typesItems, std::list<Enemy> *enemy, std::list<Item> *items, std::list<UnlifeObject> *unlifeObjects, sf::Event &event, float xMouse, float yMouse);
	// Использование предметов
	void useTool(float &xMouse, float &yMouse, Event &event, Field &field,
							 sf::String* listObjects, wchar_t* listBlocks, int &sizeListObjects,
							 Item &currentItem,
							 TypeItem *typesItems, std::list<Item> *items, std::list<UnlifeObject> *unlifeObjects);

	bool isInListBlocks(wchar_t block, wchar_t * listBlocks);
	bool isInListObjects(String * listObjects, int sizeString);

	void interactionWitnUnlifeObject(std::list<UnlifeObject> *unlifeObjects, const Time & deltaTime);

	// кнопка "Дествие" и "Другое действие"
	void actionMain(Field &field, std::list<UnlifeObject> *unlifeObjects, destroyObjectsAndBlocks& listDestroy, std::list<Item> *items, float xPos, float yPos);
	void actionAlternate(Field &field, std::list<UnlifeObject> *unlifeObjects, destroyObjectsAndBlocks& listDestroy, std::list<Item> *items, float xPos, float yPos);
private:

};

void initializeMainPerson(MainPerson & mainPerson, dataSound &databaseSound, Item &emptyItem, UnlifeObject &emptyObject, Enemy &emptyEnemy);