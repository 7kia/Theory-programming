#pragma once
#include <SFML\Graphics.hpp>

#include "Sound.h"
#include "CommonStructs.h"

struct TypeUnlifeObject {
public:

	sf::String name;
	sf::Texture* textureObject;

	// —сылки на звуки
	//Sound *soundsEntity[sizeBuffer];

	bool isDestroy;
	int toughnessObject;

	featuresSprite mainSize;
	featuresSprite transparentSize;
	objectDropItems drop;

	void Init(sf::String filenameTexture, sf::String typeName, bool canDestroy, int toughness);
};

void initializeTypeUnlifeObjects(TypeUnlifeObject *typesUnlifeObjects, dataSound &databaseSound);