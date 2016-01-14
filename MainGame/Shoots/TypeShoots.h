#pragma once
#include <SFML\Graphics.hpp>

#include "../Recourses.h"
#include "../structGame/MyFunctions.h"
#include "../structGame/CommonStructs.h"

const int WIDTH_BULLET = 10;
const int HEIGHT_BULLET = 10;
const sf::IntRect rectBullet(0 , 0 , WIDTH_BULLET , HEIGHT_BULLET);

const int WIDTH_MINE_EXPLOSION = 100;
const int HEIGHT_MINE_EXPLOSION = 100;

const sf::IntRect rectMineExplosion(0 , 0 , WIDTH_MINE_EXPLOSION , HEIGHT_MINE_EXPLOSION);


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
	mineExplosionShoot,
	amountTypeShoots
} idTypeShoots;

struct TypeShoot
{
	sf::Texture *textureShoot;
	sf::IntRect rectSprite;

	int damageShoot[amountTypeDamage];
	int idType = RESET_VALUE;
	void init(int id, int idTexture, 
						const sf::String *pathTexture, sf::IntRect rectTexture,
						int *typesDamage);
	~TypeShoot();
};

void initTypeShoots(TypeShoot *typesShoots);