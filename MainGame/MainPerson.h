#pragma once
#include "Entity.h"

class MainPerson : public Entity
{
public:
	// ������ ���������
	void modeProcess(Field &field, UnlifeObjects *unlifeObjects, sf::Event &eventPerson, float x, float y);
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

	// ��� ������������ ��������
	UnlifeObject *findObject;
	bool isMoveItem;
	float dMoveItemX, dMoveItemY;

	// ������ "�������" � "������ ��������"
	void actionMain(Field &field, int x, int y);
	void actionAlternate(Field &field, int x, int y);
private:

};

void initializeMainPerson(MainPerson & mainPerson, dataSound &databaseSound);