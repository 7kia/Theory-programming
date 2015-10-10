#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include "GlobalVar.h"
#include "Sound.h"

struct TypeUnlifeObject {
public:
	// ���������
	sf::Texture* textureObject;

	// ������ �� �����
	//Sound *soundsEntity[sizeBuffer];

	// ��� ��������� � �������� ���������
	int width;
	int height;
	int pixelPosX;
	int pixelPosY;
	// ��� ��������� � ������ ���������
	int widthTransparent;
	int heightTransparent;
	int pixelXTransparent;
	int pixelYTransparent;

	// ��� �������
	sf::String nameType;

	// ����������� ��� ���������������
	bool isDestroy;
	// ���������(� �������� ��������
	int toughnessObject;

	//void Init(String *filenameTexture, int w, int h, int pixelX, int pixelY, float xPos, float yPos, int Level);
	void Init(sf::String filenameTexture, sf::String typeName, bool canDestroy, int toughness, int w, int h, int pixelX, int pixelY);
	void InitTransparent(int w, int h, int pixelX, int pixelY);
};

struct TypesUnlifeObject {
	TypeUnlifeObject *typeUnlifeObject;
	int countTypeObjects = 0;
	int maxTypeObject = 256;
};

void initializeTypeUnlifeObjects(TypesUnlifeObject *unlifeObjects, dataSound &databaseSound);