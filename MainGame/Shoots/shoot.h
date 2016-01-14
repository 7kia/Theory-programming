#pragma once
#include <SFML\Graphics.hpp>

#include  <assert.h>
#include "../structGame/MyFunctions.h"
#include "TypeShoots.h"

const float ABOUT_ZERO_VALUE_SPEED_BULLET = 50.f;
const float DISTANSE_ATACK_FOR_HIGH_LEVEL = 100.f;
const float COEFFICIENT_SHIFT_BULLET_FROM_SHOOTER = 2.f;

typedef enum
{
	NONE_TYPE_OBJECT,
	typeUnlifeObject,
	typeEntity,
	amountTypeObject
} idTypeObject;


struct shoot
{
public:
	void init(sf::Vector2f pos , sf::Vector2f direction,
						sizeSprite sizeShooter, int level);

	void setType(TypeShoot &defineType);
	TypeShoot getType();
	int getIdType();

	void setPosition(sf::Vector2f pos, int lvl);
	int getLevel();

	void setDirection(sf::Vector2f dir);
	sf::Vector2f getDirection();

	void move(const float &deltaTime);

	sf::Sprite& getSprite();
	sf::FloatRect getGlobalBounds();
	int getDamage(int id);

private:
	sf::Sprite sprite;
	TypeShoot *type;

	sf::Vector2f direction = RESET_VECTOR_2F;
	int level = RESET_VALUE;

};
