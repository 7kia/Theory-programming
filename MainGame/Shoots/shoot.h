#pragma once
#include <SFML\Graphics.hpp>

#include  <assert.h>
#include "../structGame/MyFunctions.h"
#include "TypeShoots.h"

struct shoot
{
public:
	void initPosition(sf::Vector2f dir, int lvl);
	int getLevel();
	sf::Vector2f getDirection();

	void move(const float deltaTime);
	sf::Sprite& getSprite();
	sf::FloatRect getGlobalBounds();
	TypeShoot getType();
	int getDamage(int id);
private:
	sf::Vector2f direction;
	int level;
	sf::Sprite *sprite;
	TypeShoot *type;

};
