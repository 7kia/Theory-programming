#pragma once
#include "Enemy.h"

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
	void updateAtack(std::vector<Enemy>* enemy, std::vector<Item>* items, TypeItem* typesItems);
	void attractionEnemy(Enemy &enemy, const Time &deltaTime);
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

	void useItem(Field &field, destroyObjectsAndBlocks& listDestroy, const sf::Time &deltaTime,
							 TypeItem *typesItems, TypeUnlifeObject *typesUnlifeObjects, std::vector<Enemy> *enemy,
							 std::vector<Item> *items, std::vector<UnlifeObject> *unlifeObjects, sf::Event &event, float xMouse, float yMouse);

	void interactionWitnUnlifeObject(std::vector<UnlifeObject> *unlifeObjects, const Time & deltaTime);

	// кнопка "Дествие" и "Другое действие"
	void actionMain(Field &field, std::vector<UnlifeObject> *unlifeObjects, destroyObjectsAndBlocks& listDestroy,
									std::vector<Item> *items, float xPos, float yPos);
	void actionAlternate(Field &field, std::vector<UnlifeObject> *unlifeObjects, destroyObjectsAndBlocks& listDestroy,
											 std::vector<Item> *items, float xPos, float yPos);
private:

};

void initializeMainPerson(MainPerson & mainPerson, dataSound &databaseSound,
													Item &emptyItem, UnlifeObject &emptyObject, Enemy &emptyEnemy);