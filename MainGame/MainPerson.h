#pragma once
#include "World.h"

class MainPerson : public Entity
{
public:
	sf::Texture *textureEntity;

	void initStepSounds(dataSound& databaseSound);

	sf::View *view;
	void updateView(sf::RenderWindow & window);

	int amountSlots;

	Enemy *findEnemy;
	Enemy *emptyEnemy;
	int findEnemyFromList;
	void initFounds(Item& item, UnlifeObject& object, Enemy& enemy);

	void givenForPersonDamage(Enemy & enemy);
	void updateAtack(world &world, TypeItem* typesItems, const sf::Time &deltaTime);
	void attractionEnemy(Enemy &enemy, world &world, TypeItem *typesItems, TypeUnlifeObject *typesObject,
											 const Time &deltaTime);
	/*
		///////////////////////////////////////////////////////
	// Основные характерисктики
	int strength;// сила
	int expStrength;// опыт
	int expStrengthUp;// количество для повышения

	int endurance;// выносливость
	int expEndurace;
	int expEnduracehUp;
	///////////////////////////////////////////////////////
	*/

	void getCoordinateForView(float x, float y);
	void viewmap(float time);
	void changeview();

	float rotation;
	void computeAngle(sf::RenderWindow &window);


	void useItem(world &world, listDestroyObjectsAndBlocks& listDestroy, const sf::Time &deltaTime,
							 TypeItem *typesItems, TypeUnlifeObject *typesUnlifeObjects, sf::Event &event, float xMouse, float yMouse);


private:

};

void initializeMainPerson(MainPerson & mainPerson, dataSound &databaseSound,
													Item &emptyItem, UnlifeObject &emptyObject, Enemy &emptyEnemy);