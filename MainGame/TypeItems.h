#pragma once
#include <SFML\Graphics.hpp>

#include "Sound.h"

struct sizeMainSprite
{
	int width;
	int height;
	int pixelPosX;
	int pixelPosY;
	void init(int w, int h, int xPixPos, int yPixPos);
};

struct sizeAlternativeSprite
{
	int widthForUse;
	int heightForUse;
	int pixelXForUse;
	int pixelYForUse;
	void init(int w, int h, int xPixPos, int yPixPos);
};

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

	sizeMainSprite sizeMain;
	sizeAlternativeSprite sizeAlternative;
	typeDamageItem damageItem;
	idCreateObjects idAdd;

	void Init(sf::String filenameTexture, featuresItem featuresAddItem,
						sizeMainSprite sizeMainSprite, idCreateObjects idCreated, typeDamageItem damage);
	void InitForUse(sf::String filenameTextureForUse, sizeAlternativeSprite size);
};

void initializeTypesItem(TypeItem *typesItem, dataSound &databaseSound);