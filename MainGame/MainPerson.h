#pragma once
#include "Enemy.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �������� ��������
class MainPerson : public Entity
{
public:
	sf::Texture *textureEntity;

	// ������ ���������
	//void modeProcess(Field &field, std::list<UnlifeObject> *unlifeObjects, std::list<Item> *items, sf::Event &eventPerson, float x, float y);
	// ������
	sf::View *view;
	void updateView(sf::RenderWindow & window);

	// ��� ���������
	int amountSlots;

	///////////////////////////////////////////////////////
	// ��� ����������� ������
	Enemy *findEnemy;
	Enemy *emptyEnemy;
	std::list<Enemy>::iterator findEnemyFromList;
	///////////////////////////////////////////////////////
	// �������� ���������������
	int strength;// ����
	int expStrength;// ����
	int expStrengthUp;// ���������� ��� ���������
	float damageMultiplirer;// strength / 10

	int endurance;// ������������
	int expEndurace;
	int expEnduracehUp;
	///////////////////////////////////////////////////////
	void getCoordinateForView(float x, float y);
	void viewmap(float time);
	void changeview();

	// ��� ����������� �������
	float rotation;
	void computeAngle(sf::RenderWindow &window);

	void takeItem(Field &field, std::list<Item> &items, float x, float y);
	void throwItem(Field &field, std::list<Item> &items);
	void useItem(Field &field, destroyObjectsAndBlocks& listDestroy, TypeItem *typesItems, std::list<Enemy> *enemy, std::list<Item> *items, std::list<UnlifeObject> *unlifeObjects, sf::Event &event, float xMouse, float yMouse);

	bool isAxeBreakingBlock(wchar_t block, wchar_t *axeBreakingBlocks);// �������
	bool isAxeBreakingObject(String* axeBreakingObject);// �������
	bool isPickaxBreakingBlock(wchar_t block, wchar_t *pickaxBreakingBlocks);// �������
	bool isPickaxBreakingObject(sf::String* pickaxBreakingObject);// �������

	void interactionWitnUnlifeObject(std::list<UnlifeObject> *unlifeObjects, const Time & deltaTime);
	// ������ "�������" � "������ ��������"
	void actionMain(Field &field, std::list<UnlifeObject> *unlifeObjects, destroyObjectsAndBlocks& listDestroy, std::list<Item> *items, float xPos, float yPos);
	void actionAlternate(Field &field, std::list<UnlifeObject> *unlifeObjects, destroyObjectsAndBlocks& listDestroy, std::list<Item> *items, float xPos, float yPos);
private:

};

void initializeMainPerson(MainPerson & mainPerson, dataSound &databaseSound, Item &emptyItem, UnlifeObject &emptyObject, Enemy &emptyEnemy);