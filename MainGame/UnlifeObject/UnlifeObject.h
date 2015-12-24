#pragma once
#include <SFML\Graphics.hpp>

#include "../Map/BlocksVar.h"
#include "../GlobalVar.h"
#include "../Sounds/Sound.h"

#include "TypeUnlifeObject.h"

struct world;
struct Item;
using namespace sf;

struct UnlifeObject
{
	sf::Sprite *spriteObject;
	sf::Sprite *transparentSpiteObject;

	TypeUnlifeObject *typeObject;// Пренадлежность типу

	Sound soundObject;

	int currentToughness;
	bool isDestroy;

	int currentLevel;
	float timeLife;

	void setType(TypeUnlifeObject &type);
	void setSpriteTexture(sf::Sprite &sprite, featuresSprite features, sf::Texture &texture);
	void setPosition(sf::Vector3i pos);

	bool isDestroyed();

	void dropObject(sf::Vector3i pos, world &world, bool harvest);
	void playObjectDropSoundObject();
	void playHarvestSoundObject();

	float getXPos();
	float getYPos();
	sf::Vector2f getPosition();	

};

void initializeUnlifeObjects(std::vector<UnlifeObject> &unlifeObjects, TypeUnlifeObject *typesUnlifeObjects, UnlifeObject &emptyObject);
