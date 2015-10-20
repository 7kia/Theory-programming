#pragma once
#include <SFML\Graphics.hpp>

#include "Sound.h"

struct TypeItem {
public:
	// Текструра
	sf::Texture* textureItem;
	sf::Texture* textureItemForUse;

	// Ссылки на звуки
	//Sound *soundsEntity[sizeBuffer];// ИСПРАВЬ

	// Для отрисовки в основном состоянии
	int width;
	int height;
	int pixelPosX;
	int pixelPosY;
	// Для отрисовки в другом состоянии
	int widthForUse;
	int heightUse;
	int pixelXUse;
	int pixelYUse;

	
	sf::String name;
	int category;// Еда, оружие, блок
	int idBlockForUse;
	int idUnlideOnjectForUse;

	// Разрушаемый или нет
	bool isDestroy;
	// Прочность(в условных единицах
	int toughnessObject;

	//void Init(String *filenameTexture, int w, int h, int pixelX, int pixelY, float xPos, float yPos, int Level);
	void Init(sf::String filenameTexture, sf::String typeName, int idCategory, bool canDestroy, int toughness, int w, int h, int pixelX, int pixelY, int idBlock, int idUnlifeObject);
	void InitForUse(sf::String filenameTextureForUse, int w, int h, int pixelX, int pixelY);
};

struct TypesItem {
	TypeItem *typesItem;
	int countTypeItem = 0;
	int maxTypeItem = 256;
};

void initializeTypesItem(TypesItem &typesItem, dataSound &databaseSound);