#include "shoot.h"

using namespace sf;

void shoot::initPosition(sf::Vector2f dir , int lvl)
{
	direction = dir;
	level = lvl;
}

int shoot::getLevel()
{
	return level;
}

sf::Vector2f shoot::getDirection()
{
	return direction;
}

void shoot::move(const float deltaTime)
{
	Vector2f vectorShift = direction;

	vectorShift.x *= deltaTime;
	vectorShift.y *= deltaTime;

	sprite->move(vectorShift);
}

sf::Sprite& shoot::getSprite()
{
	return *sprite;
}

sf::FloatRect shoot::getGlobalBounds()
{
	return sprite->getGlobalBounds();
}

TypeShoot shoot::getType()
{
	return *type;
}

int shoot::getDamage(int id)
{
	assert((id < 0) && (id > amountTypeDamage));
	return type->damageShoot[id];
}
