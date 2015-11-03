#pragma once
#include <SFML\Graphics.hpp>

#include "Sound.h"

struct sizeMainSprite
{
	
};

struct TypeItem {
public:
	// ���������
	sf::Texture* textureItem;
	sf::Texture* textureItemForUse;

	// ������ �� �����
	//Sound *soundsEntity[sizeBuffer];// �������

	// ��� ��������� � �������� ���������
	int width;
	int height;
	int pixelPosX;
	int pixelPosY;
	// ��� ��������� � ������ ���������
	int widthForUse;
	int heightUse;
	int pixelXUse;
	int pixelYUse;

	
	sf::String name;
	int category;// ���, ������, ����
	int idItem;
	int idBlockForUse;
	int idUnlideOnjectForUse;

	// ����
	int cuttingDamage;// �������
	int crushingDamage;// ��������

	// ����������� ��� ���
	bool isDestroy;
	// ���������(� �������� ��������
	int toughnessObject;

	//void Init(String *filenameTexture, int w, int h, int pixelX, int pixelY, float xPos, float yPos, int Level);
	void Init(sf::String filenameTexture, sf::String typeName, int id, int idCategory, bool canDestroy, int toughness,
						int w, int h, int pixelX, int pixelY,
						int idBlock, int idUnlifeObject,
						int damCut, int damCrash);
	void InitForUse(sf::String filenameTextureForUse, int w, int h, int pixelX, int pixelY);
};

struct TypesItem {
	TypeItem *typesItem;
	int countTypeItem = 0;
	int maxTypeItem = 256;
};

void initializeTypesItem(TypesItem &typesItem, dataSound &databaseSound);