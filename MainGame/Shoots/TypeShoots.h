#pragma once
#include <SFML\Graphics.hpp>

const sf::IntRect rectBullet(0 , 0 , 10 , 10);

typedef enum
{
	cuttingDamage ,
	crushingDamage ,
	unlifeDamage ,
	amountTypeDamage
} idTypeDamage;

typedef enum
{
	NONE_SHOOT = -1,
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