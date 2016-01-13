#pragma once
#include <SFML\Graphics.hpp>

#include "../Recourses.h"
#include "../structGame/MyFunctions.h"
const sf::IntRect rectBullet(0 , 0 , 10 , 10);
const sf::Vector2f startSpeedBullet(2000.f , 2000.f);
const sf::Vector2f accelerationBullet(0.01f , 0.01f);

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