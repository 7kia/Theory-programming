#pragma once
#include <SFML\Graphics.hpp>

#include "TypeItems.h"


struct world;

struct Item 
{
	sf::Sprite *mainSprite;
	sf::Sprite *spriteForUse;

	TypeItem *typeItem;

	int amount;

	int currentToughness;
	int maxToughness;

	int currentLevel;

	// TODO
	float timeAnimation;
	void update(const float deltaTime, dataSound &databaseSound);
	void playSound(float time, float start, const int idSound);
	void resetTimeAnimation(float &time, float &reset);

	void setType(TypeItem &type);
	void setPosition(int x, int y, int Level);

	float getXPos();
	float getYPos();
};

void initializeItems(std::vector<Item> &items, TypeItem *typesItem, Item &emptyItem);

void dropBlock(world &world, sf::Vector3i &pos, int level);