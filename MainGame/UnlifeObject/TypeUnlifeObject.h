#pragma once
#include <SFML\Graphics.hpp>

#include "../Recourses.h"
#include "../Items/ItemsVar.h"
#include "../Sounds/Sound.h"
#include "../structGame/CommonStructs.h"
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
	int id;
	int idNature;
	sf::Texture* textureObject;

	// —сылки на звуки
	//Sound *soundsEntity[sizeBuffer];

	bool isDestroy;
	int toughnessObject;

	redefineObject redefine;


	featuresSprite mainSize;
	featuresSprite transparentSize;
	objectDropItems drop;

	void Init(sf::String filenameTexture, sf::String typeName, int idType, int numberNature);
	void defineToughness(bool canDestroy, int toughness);
};

void initTree(TypeUnlifeObject *typesUnlifeObjects);
void initStones(TypeUnlifeObject *typesUnlifeObjects);
void initEmpty(TypeUnlifeObject *typesUnlifeObjects);

void initializeTypeUnlifeObjects(TypeUnlifeObject *typesUnlifeObjects);