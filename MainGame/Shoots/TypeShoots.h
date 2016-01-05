#pragma once
#include "../Items/TypeItems.h"

const sf::IntRect rectBullet(0 , 0 , 10 , 10);

typedef enum
{
	pistolShoot,
	rifleShoot,
	heavyRifleShoot,
	amountTypeShoots
} idTypeShoots;

struct TypeShoot
{
	sf::Texture *textureShoot;
	int damageShoot[amountTypeDamage];
	void init(int id , const sf::String *pathTexture , int *typesDamage);
	~TypeShoot();
};

void initTypeShoots(TypeShoot *typesShoots);