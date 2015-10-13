#pragma once
#include "Entity.h"

using namespace std;

class MainPerson : public Entity
{
public:
	// ������ ���������
	void modeProcess(Field &field, list<UnlifeObject> *unlifeObjects, list<Item> *items, sf::Event &eventPerson, float x, float y);
	// ������
	sf::View *view;
	void getCoordinateForView(float x, float y);
	void viewmap(float time);
	void changeview();

	// ��� ����������� �������
	float rotation;
	void computeAngle(sf::RenderWindow &window);

	// ��� �������������� � �����
	int currenMode;
	const int amountActiveSlots = 10;
	int idSelectItem;

	// ��� ������������ �������
	UnlifeObject *findObject;
	list<UnlifeObject>::iterator findObjectFromList;
	// ��� ������������ ��������
	Item *findItem;
	list<Item>::iterator findItemFromList;

	bool isMoveItem;
	float dMoveItemX, dMoveItemY;

	// ������ "�������" � "������ ��������"
	void actionMain(Field &field, int x, int y);
	void actionAlternate(Field &field, int x, int y);
private:

};

void initializeMainPerson(MainPerson & mainPerson, dataSound &databaseSound);