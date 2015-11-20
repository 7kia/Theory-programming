#pragma once
#include <SFML\Graphics.hpp>

#include "TypeItems.h"

struct Item 
{
	sf::Sprite *mainSprite;
	sf::Sprite *spriteForUse;

	TypeItem *typeItem;

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

	// Вспомагательные функции
	float getXPos();
	float getYPos();
private:

};

void initializeItems(std::vector<Item> &items, TypeItem *typesItem, Item &emptyItem);