#pragma once
#include "World.h"

class MainPerson : public Entity
{
public:
	sf::Texture *textureEntity;

	sf::View *view;
	void updateView(sf::RenderWindow & window);

	int amountSlots;

	Enemy *findEnemy;
	Enemy *emptyEnemy;
	int findEnemyFromList;
	void initFounds(Item& item, UnlifeObject& object, Enemy& enemy);

	void givenForPersonDamage(Enemy & enemy);
	void updateAtack(world &world, const sf::Time &deltaTime);
	void attractionEnemy(Enemy &enemy, world &world, const Time &deltaTime);
	/*
		///////////////////////////////////////////////////////
	// �������� ���������������
	int strength;// ����
	int expStrength;// ����
	int expStrengthUp;// ���������� ��� ���������

	int endurance;// ������������
	int expEndurace;
	int expEnduracehUp;
	///////////////////////////////////////////////////////
	*/

	void getCoordinateForView(float x, float y);
	void viewmap(float time);
	void changeview();

	float rotation;
	void computeAngle(sf::RenderWindow &window);


	void useItem(world &world, const Time &deltaTime,
							 Event &event, Vector2f pos);


private:

};

void initializeMainPerson(MainPerson & mainPerson, dataSound &databaseSound,
													emptyObjects &emptyObjects);

