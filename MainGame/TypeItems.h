#pragma once
#include <SFML\Graphics.hpp>

#include "Sound.h"
#include "CommonStructs.h"

struct typeDamageItem
{
	int cuttingDamage;// Режущий
	int crushingDamage;// Дробящий
	void init(int cut, int crush);
};

struct idCreateObjects
{
	int idBlockForUse;
	int idUnlideOnjectForUse;
	void init(int idBlock, int idObject);
};

struct featuresItem
{
	sf::String name;
	int category;
	int id;
	bool isDestroy;
	int toughness;// прочность
	void init(sf::String nameItem, int idItem, int idCategory);
	void defineToughness(bool destroy, int toughnessItem);
};

struct TypeItem {
public:
	// Текструра
	sf::Texture* textureItem;
	sf::Texture* textureItemForUse;

	// Ссылки на звуки
	//Sound *soundsEntity[sizeBuffer];// ИСПРАВЬ
	featuresItem features;

	sizeSprite sizeMain;
	sizeSprite sizeAlternative;
	typeDamageItem damageItem;
	idCreateObjects idAdd;

	void Init(sf::String filenameTexture, featuresItem featuresAddItem,
						sizeSprite sizeSprite, idCreateObjects idCreated, typeDamageItem damage);
	void InitForUse(sf::String filenameTextureForUse, sizeSprite size);
};

void initializeTypesItem(TypeItem *typesItem, dataSound &databaseSound);