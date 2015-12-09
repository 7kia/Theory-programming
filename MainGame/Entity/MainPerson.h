#pragma once
#include "../World.h"

class MainPerson : public Entity
{
public:
	sf::Texture *textureEntity;
	void updateView(sf::RenderWindow & window, sf::View &view);

	void givenForPersonDamage(Entity & enemy);
	void updateAtack(world &world, const float deltaTime);
	void hurtPerson(Entity &enemy, world &world, const float deltaTime);
	void attractionEntity(Entity &enemy, world &world, const float deltaTime);

	void getCoordinateForView(sf::Vector2f pos, View &view);

	void computeAngle(sf::RenderWindow &window);


	void useItem(world &world, Event &event, Vector2f pos);

	void playSoundChoiseItem();

private:

};

void initializeMainPerson(MainPerson &mainPerson, world &world, sf::View &view);

