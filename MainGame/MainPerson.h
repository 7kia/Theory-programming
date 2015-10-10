#pragma once
#include "Entity.h"

class MainPerson : public Entity
{
public:
	// режимы персонажа
	void modeProcess(Field &field, UnlifeObjects *unlifeObjects, sf::Event &eventPerson, float x, float y);
	// Камера
	sf::View *view;
	void getCoordinateForView(float x, float y);
	void viewmap(float time);
	void changeview();

	// Для направления взгляда
	float rotation;
	void computeAngle(sf::RenderWindow &window);

	// Для взаимодействия с миром
	int currenMode;
	const int amountActiveSlots = 10;
	int idSelectItem;

	// Для передвижения предмета
	UnlifeObject *findObject;
	bool isMoveItem;
	float dMoveItemX, dMoveItemY;

	// кнопка "Дествие" и "Другое действие"
	void actionMain(Field &field, int x, int y);
	void actionAlternate(Field &field, int x, int y);
private:

};

void initializeMainPerson(MainPerson & mainPerson, dataSound &databaseSound);