#pragma once
#include "../World.h"

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
	void updateAtack(world &world, const float deltaTime);
	void hurtPerson(Enemy &enemy, world &world, const float deltaTime);
	void attractionEnemy(Enemy &enemy, world &world, const float deltaTime);
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


	void useItem(world &world, Event &event, Vector2f pos);

	void playSoundChoiseItem();

private:

};

void initializeMainPerson(MainPerson &mainPerson, world &world);

