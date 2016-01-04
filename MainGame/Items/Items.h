#pragma once
#include <SFML\Graphics.hpp>

#include "TypeItems.h"


struct world;

struct Item 
{
public:
	sf::FloatRect getGlobalBounds();

	void setScale(sf::Vector2f scale);

	sf::Sprite& getSprite();
	void setColor(sf::Color color);

	const TypeItem* getType();
	sf::String getName();
	int getIdType();
	int getIdCategory();
	bool getAttributeDestroyed();
	bool getAttributeCutting();

	int getDamage(int id);
	int getIdAddObject(int id);

	int getAmount();
	int getMaxAmount();
	void increaseAmount(int number);

	int amount;

	int currentToughness;
	int maxToughness;

	int currentLevel;
	int getLevelOnMap();

	// TODO
	float timeAnimation;
	void update(const float deltaTime, dataSound &databaseSound);
	void playSound(float time, float start, const int idSound);
	void resetTimeAnimation(float &time, float &reset);

	void setType(TypeItem &type);
	void setPosition(sf::Vector3i pos);
	void setPositionSprite(sf::Vector2f pos);

	std::vector<int>* getListDestroy();


	float getXPos();
	float getYPos();

private:
	sf::Sprite *mainSprite;
	sf::Sprite *spriteForUse;

	// TODO : do private
	TypeItem *typeItem;

};

void initializeItems(std::vector<Item> &items, TypeItem *typesItem, Item &emptyItem);

void dropBlock(world &world, sf::Vector3i &pos, int level);