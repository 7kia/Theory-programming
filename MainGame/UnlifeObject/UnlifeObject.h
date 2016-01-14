#pragma once
#include <SFML\Graphics.hpp>


#include "../GlobalVar.h"
#include "../Sounds/Sound.h"

#include "TypeUnlifeObject.h"

struct world;
struct shoot;
struct TypeShoot;

struct Item;
using namespace sf;

struct UnlifeObject
{
	sf::Sprite *spriteObject;
	sf::Sprite *transparentSpiteObject;

	TypeUnlifeObject *typeObject;// Пренадлежность типу
	int getIdType();


	Sound soundObject;

	int currentToughness;
	bool isDestroy;

	int getLevel();
	float timeLife;

	void createBullet(std::vector<shoot>& shoots , TypeShoot &type , int level);

	void setType(TypeUnlifeObject &type);

	void setSpriteTexture(sf::Sprite &sprite, featuresSprite &features, sf::Texture &texture);
	void setPosition(sf::Vector3i pos);

	void setMainColor(sf::Color color);
	void setTransparentColor(sf::Color color);

	bool isDestroyed();

	void dropObject(sf::Vector3i pos, world &world, bool harvest);
	void playObjectDropSoundObject();
	void playHarvestSoundObject();

	sf::FloatRect getMainGlobalBounds();
	sf::FloatRect getTransparentGlobalBounds();

	const sizeSprite& getMainSize();
	const sizeSprite& getTransparentSize();


	float getXPos();
	float getYPos();
	const sizeSprite & getSize();
	sf::Vector2f getPosition();	

private:
	int currentLevel;

};

void initializeUnlifeObjects(std::vector<UnlifeObject> &unlifeObjects, TypeUnlifeObject *typesUnlifeObjects, UnlifeObject &emptyObject);
