#pragma once
#include "../World.h"

const float SCALE_VIEW = 1.5f;

class MainPerson : public Entity
{
public:
	sf::Texture *textureEntity;

	sf::View *view;
	sf::Listener *listener;
	void updateView(sf::RenderWindow & window);

	int amountSlots;

	Enemy *findEnemy;
	Enemy *emptyEnemy;
	int findEnemyFromList;
	void initFounds(Item& item, UnlifeObject& object, Enemy& enemy);

	void killFindEnemy(world &world);
	void hurtEnemy(Item &currentItem, const float deltaTime);
	void updateAtack(world &world, const float deltaTime);

	void attractionEnemy(Enemy &enemy, world &world, const float deltaTime);

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

