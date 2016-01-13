#include "shoot.h"

using namespace sf;

void shoot::setPosition(sf::Vector2f pos , int lvl)
{
	sprite.setPosition(pos);
	level = lvl;
}

void shoot::setDirection(sf::Vector2f dir)
{
	direction = dir;
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
	direction.x *= (1.f - accelerationBullet.x);
	direction.y *= (1.f - accelerationBullet.y);

	Vector2f shift = direction;
	shift *= deltaTime;

	sprite.move(shift);
}

sf::Sprite& shoot::getSprite()
{
	return sprite;
}

sf::FloatRect shoot::getGlobalBounds()
{
	return sprite.getGlobalBounds();
}

TypeShoot shoot::getType()
{
	return *type;
}

int shoot::getDamage(int id)
{
	assert(g_Functions::checkDiaposon(id , RESET_VALUE , amountTypeDamage));
	return type->damageShoot[id];
}

void shoot::setType(TypeShoot &defineType)
{
	type = &defineType;

	sprite.setTexture(*type->textureShoot);
	sprite.setTextureRect(rectBullet);
}

