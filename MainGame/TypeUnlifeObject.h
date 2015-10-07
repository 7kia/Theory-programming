#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include "GlobalVar.h"
#include "Sound.h"

struct TypeUnlifeObject {
public:
	// ���������
	sf::Texture *textureObject;

	// ������ �� �����
	//Sound *soundsEntity[sizeBuffer];

	// ��� ��������� � �������� ���������
	int width;
	int height;
	int pixelPosX;
	int pixelPosY;
	// ��� ��������� � ������ ���������
	int widthAlternative;
	int heightAlternative;
	int pixelXAlternative;
	int pixelYAlternative;

	// ��� �������
	char typeObject[20];

	//void Init(String *filenameTexture, int w, int h, int pixelX, int pixelY, float xPos, float yPos, int Level);
	void Init(sf::String filenameTexture, char *typeName, int w, int h, int pixelX, int pixelY);
	void InitAlternate(int w, int h, int pixelX, int pixelY);
};

struct TypesUnlifeObject {
	TypeUnlifeObject *typeUnlifeObject;
	int countTypeObjects = 0;
	int maxTypeObject = 256;
};

void initializeTypeUnlifeObjects(TypesUnlifeObject *unlifeObjects, dataSound &databaseSound);