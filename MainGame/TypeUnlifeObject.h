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

	sizeSprite mainSize;
	sizeSprite transparentSize;
	objectDropItems drop;

	void Init(sf::String filenameTexture, sf::String typeName, bool canDestroy, int toughness);
};

struct TypesUnlifeObject {
	TypeUnlifeObject *typeUnlifeObject;
	int countTypeObjects = 0;
	int maxTypeObject = 256;
};

void initializeTypeUnlifeObjects(TypesUnlifeObject &typesUnlifeObjects, dataSound &databaseSound);