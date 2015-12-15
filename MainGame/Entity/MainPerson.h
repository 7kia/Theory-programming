#pragma once
#include "../World.h"

const float SCALE_VIEW = 1.5f;

class MainPerson : public Entity
{
public:
	sf::Texture *textureEntity;
	void updateView(sf::RenderWindow & window, sf::View &view);

<<<<<<< HEAD
	sf::View *view;
	sf::Listener *listener;
	void updateView(sf::RenderWindow & window);

	int amountSlots;
=======
	void givenForPersonDamage(Entity & enemy);
	void updateAtack(world &world, const float deltaTime);
	void hurtPerson(Entity &enemy, world &world, const float deltaTime);
	void attractionEntity(Entity &enemy, world &world, const float deltaTime);
>>>>>>> master

	void getCoordinateForView(sf::Vector2f pos, View &view);

<<<<<<< HEAD
	void killFindEnemy(world &world);
	void hurtEnemy(Item &currentItem, const float deltaTime);
	void updateAtack(world &world, const float deltaTime);

	void attractionEnemy(Enemy &enemy, world &world, const float deltaTime);

	void getCoordinateForView(float x, float y);
	void viewmap(float time);
	void changeview();

	float rotation;
=======
>>>>>>> master
	void computeAngle(sf::RenderWindow &window);


	void useItem(world &world, Event &event, Vector2f pos);

	void playSoundChoiseItem();

private:

};

void initializeMainPerson(Entity &mainPerson, world &world, sf::View &view);

