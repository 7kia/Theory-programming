#pragma once
#include "Entity.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Основной персонаж
class MainPerson : public Entity
{
public:
	// режимы персонажа
	//void modeProcess(Field &field, std::list<UnlifeObject> *unlifeObjects, std::list<Item> *items, sf::Event &eventPerson, float x, float y);
	// Камера
	sf::View *view;
	void updateView(sf::RenderWindow & window);


	// Для уничтожения врагов
	Enemy *findEnemy;
	Enemy *emptyEnemy;
	std::list<Enemy>::iterator findEnemyFromList;

	void getCoordinateForView(float x, float y);
	void viewmap(float time);
	void changeview();

	// Для направления взгляда
	float rotation;
	void computeAngle(sf::RenderWindow &window);

	void takeItem(Field &field, std::list<Item> &items, float x, float y);
	void throwItem(Field &field, std::list<Item> &items);
	void useItem(Field &field, destroyObjectsAndBlocks& listDestroy, TypeItem *typesItems, std::list<UnlifeObject> *unlifeObjects, sf::Event &event, float xMouse, float yMouse);

	bool isAxeBreakingBlock(wchar_t block, wchar_t *axeBreakingBlocks);// ИСПРАВЬ
	bool isAxeBreakingObject(String* axeBreakingObject);// ИСПРАВЬ
	bool isPickaxBreakingBlock(wchar_t block, wchar_t *pickaxBreakingBlocks);// ИСПРАВЬ
	bool isPickaxBreakingObject(sf::String* pickaxBreakingObject);// ИСПРАВЬ

	// кнопка "Дествие" и "Другое действие"
	void actionMain(Field &field, std::list<UnlifeObject> *unlifeObjects, destroyObjectsAndBlocks& listDestroy, std::list<Item> *items, float xPos, float yPos);
	void actionAlternate(Field &field, std::list<UnlifeObject> *unlifeObjects, destroyObjectsAndBlocks& listDestroy, std::list<Item> *items, float xPos, float yPos);
private:

};

void initializeMainPerson(MainPerson & mainPerson, dataSound &databaseSound, Item &emptyItem, UnlifeObject &emptyObject, Enemy &emptyEnemy);