#pragma once
#include <SFML\Graphics.hpp>

#include  <assert.h>
#include "../structGame/MyFunctions.h"
#include "TypeShoots.h"

const float ABOUT_ZERO_VALUE_SPEED_BULLET = 50.f;

typedef enum
{
	NONE_TYPE_OBJECT,
	typeUnlifeObject,
	typeEntity,
	amountTypeObject
} idTypeObject;

struct dataSourceShoot
{
	int idObject = RESET_VALUE;
	idTypeObject idType = NONE_TYPE_OBJECT;
};

struct shoot
{
public:
	void setPosition(sf::Vector2f pos, int lvl);
	void setDirection(sf::Vector2f dir);
	int getLevel();
	sf::Vector2f getDirection();

	void move(const float deltaTime);
	sf::Sprite& getSprite();
	sf::FloatRect getGlobalBounds();
	TypeShoot getType();
	int getDamage(int id);
	void setType(TypeShoot &defineType);

private:
	sf::Sprite sprite;
	TypeShoot *type;

	sf::Vector2f direction = RESET_VECTOR_2F;
	int level = RESET_VALUE;

	dataSourceShoot dataSource;

};
