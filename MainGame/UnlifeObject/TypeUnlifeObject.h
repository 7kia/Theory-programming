#pragma once
#include <SFML\Graphics.hpp>

#include "../Recourses.h"
#include "../Items/ItemsVar.h"
#include "../Sounds/Sound.h"
#include "../CommonStructs.h"
#include "UnlifeObjectVar.h"

struct TypeUnlifeObject;

struct redefineObject
{
	int id;
	float timeUpdate;
	void init(int idType, float time);
};

struct TypeUnlifeObject {
public:

	sf::String name;
	sf::Texture* textureObject;

	// —сылки на звуки
	//Sound *soundsEntity[sizeBuffer];

	bool isDestroy;
	int toughnessObject;

	redefineObject redefine;


	featuresSprite mainSize;
	featuresSprite transparentSize;
	objectDropItems drop;

	void Init(sf::String filenameTexture, sf::String typeName, bool canDestroy, int toughness);
};

void initializeTypeUnlifeObjects(TypeUnlifeObject *typesUnlifeObjects, dataSound &databaseSound);