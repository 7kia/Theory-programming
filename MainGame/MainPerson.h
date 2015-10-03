#pragma once
#include "Entity.h"

class MainPerson : public Entity
{
public:
	// режимы персонажа
	void modeProcess(Field &field, Event &eventPerson, int x, int y);
	// Камера
	View *view;
	void getCoordinateForView(float x, float y);
	void viewmap(float time);
	void changeview();

	// Для направления взгляда
	float rotation;
	void computeAngle(RenderWindow &window);

	// Для взаимодействия с миром
	int currenMode;
	const int amountActiveSlots = 10;
	int idSelectItem;
	// кнопка "Дествие" и "Другое действие"
	void actionMain(Field &field, int x, int y);
	void actionAlternative(Field &field, int x, int y);
private:

};

void initializeMainPerson(MainPerson & Entity, dataSound &databaseSound);