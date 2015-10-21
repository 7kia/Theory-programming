#pragma once
#include "Entity.h"
#include "Items.h"
#include "UnlifeObject.h"
#include "ListDestroyObjectsAndBlocks.h"// ИСПРАВЬ

const int AMOUNT_ACTIVE_SLOTS = 10;

class MainPerson : public Entity
{
public:
	// режимы персонажа
	//void modeProcess(Field &field, std::list<UnlifeObject> *unlifeObjects, std::list<Item> *items, sf::Event &eventPerson, float x, float y);
	// Камера
	sf::View *view;
	void updateView(sf::RenderWindow & window);

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
	std::list<UnlifeObject>::iterator findObjectFromList;
	UnlifeObject* emptyObject;
	// Для передвижения предмета
	Item *findItem;
	std::list<Item>::iterator findItemFromList;

	bool isMoveItem;
	float dMoveItemX, dMoveItemY;
	//////////////////////////////////////////////////
	void takeItem(Field &field, std::list<Item> &items, float x, float y);
	void throwItem(Field &field, std::list<Item> &items);
	void useItem(Field &field, destroyObjectsAndBlocks& listDestroy, std::list<UnlifeObject> *unlifeObjects, sf::Event &event, int x, int y);

	bool isAxeBreakingBlock(wchar_t block);// ИСПРАВЬ
	bool isAxeBreakingObject(String* axeBreakingObject);// ИСПРАВЬ
	bool isPickaxBreakingBlock(wchar_t block);// ИСПРАВЬ
	bool isPickaxBreakingObject(sf::String* pickaxBreakingObject);// ИСПРАВЬ

	// кнопка "Дествие" и "Другое действие"
	void actionMain(Field &field, std::list<UnlifeObject> *unlifeObjects, std::list<Item> *items, int x, int y);
	void actionAlternate(Field &field, std::list<UnlifeObject> *unlifeObjects, std::list<Item> *items, int x, int y);
private:

};

void initializeMainPerson(MainPerson & mainPerson, dataSound &databaseSound, Item &emptyItem, UnlifeObject &emptyObject);