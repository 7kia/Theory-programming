#pragma once
#include "Entity.h"

class MainPerson : public Entity
{
public:
	// ������ ���������
	void modeProcess(Field &field, sf::Event &eventPerson, int x, int y);
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
	// ������ "�������" � "������ ��������"
	void actionMain(Field &field, int x, int y);
	void actionAlternative(Field &field, int x, int y);
private:

};

void initializeMainPerson(MainPerson & Entity, dataSound &databaseSound);