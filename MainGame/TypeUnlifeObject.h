#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include "GlobalVar.h"
#include "Sound.h"

struct TypeUnlifeObject {
public:
	// Текструра
	sf::Texture *textureObject;

	// Ссылки на звуки
	//Sound *soundsEntity[sizeBuffer];

	// Для отрисовки в основном состоянии
	int width;
	int height;
	int pixelPosX;
	int pixelPosY;
	// Для отрисовки в другом состоянии
	int widthAlternative;
	int heightAlternative;
	int pixelXAlternative;
	int pixelYAlternative;

	// Тип объекта
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