#pragma once
#include "Entity.h"
#include "Items.h"
#include "UnlifeObject.h"

using namespace std;

const int AMOUNT_ACTIVE_SLOTS = 10;

class MainPerson : public Entity
{
public:
	// режимы персонажа
	void modeProcess(Field &field, list<UnlifeObject> *unlifeObjects, list<Item> *items, sf::Event &eventPerson, float x, float y);
	// Камера
	sf::View *view;
	void updateView(RenderWindow & window);

	void getCoordinateForView(float x, float y);
	void viewmap(float time);
	void changeview();

	// Для направления взгляда
	float rotation;
	void computeAngle(sf::RenderWindow &window);

	//////////////////////////////////////////////////
	// Для взаимодействия с миром
	int currenMode;
	Item *itemFromPanelQuickAccess;
	Item *emptyItem;// ИСПРАВЬ
	int idSelectItem;

	bool isEmptySlot();
	int emptySlot;

	// Для передвижения объекта
	UnlifeObject *findObject;
	list<UnlifeObject>::iterator findObjectFromList;
	// Для передвижения предмета
	Item *findItem;
	list<Item>::iterator findItemFromList;

	bool isMoveItem;
	float dMoveItemX, dMoveItemY;
	//////////////////////////////////////////////////
	void takeItem(Field &field, list<Item> &items, float x, float y);
	void throwItem(Field &field, list<Item> &items);
	void useItem(Field &field, Event &event, int x, int y);

	// кнопка "Дествие" и "Другое действие"
	void actionMain(Field &field, std::list<UnlifeObject> *unlifeObjects, std::list<Item> *items, int x, int y);
	void actionAlternate(Field &field, std::list<UnlifeObject> *unlifeObjects, std::list<Item> *items, int x, int y);
private:

};

void initializeMainPerson(MainPerson & mainPerson, dataSound &databaseSound, Item &emptyItem);