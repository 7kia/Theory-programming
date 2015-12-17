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
	dataSound *soundBase;

	bool isDestroy;
	int toughnessObject;

	redefineObject redefine;

	featuresSprite mainSize;
	featuresSprite transparentSize;
	objectDropItems drop;

	void Init(sf::String filenameTexture, sf::String typeName, dataSound &storage, int idType, int numberNature);
	void defineToughness(bool canDestroy, int toughness);
};

void initTree(TypeUnlifeObject *typesUnlifeObjects, dataSound &storage);
void initStones(TypeUnlifeObject *typesUnlifeObjects, dataSound &storage);
void initEmpty(TypeUnlifeObject *typesUnlifeObjects, dataSound &storage);
void initEffects(TypeUnlifeObject *typesUnlifeObjects, dataSound &storage);

void initializeTypeUnlifeObjects(TypeUnlifeObject *typesUnlifeObjects, dataSound &storage);