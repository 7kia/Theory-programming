#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include "GlobalVar.h"
#include "Sound.h"

using namespace sf;

struct TypeUnlifeObject
{
public:
	// Текструра
	sf::Texture *textureObject;

	// Ссылки на звуки
	//Sound *soundsEntity[sizeBuffer];

	// Для отрисовки
	int width;
	int height;
	int pixelPosX;
	int pixelPosY;

	int widthAlternative;
	int heightAlternative;
	int pixelXAlternative;
	int pixelYAlternative;

	// Тип объекта
	char typeObject[20];

	//void Init(String *filenameTexture, int w, int h, int pixelX, int pixelY, float xPos, float yPos, int Level);
	void Init(const char *filenameTexture, char *typeName, int w, int h, int pixelX, int pixelY);

};

class UnlifeObject
{
public:
	sf::Sprite *spriteObject;

	// Текущий уровень размещения
	int currentLevel;

	// Для анимации
	Direction direction;
	float timeAnimation;

	// Передвижение. Его анимация и озвучка
	void update(const Time & deltaTime, dataSound &databaseSound);
	void playSound(float time, float start, const int idSound);
	void resetTimeAnimation(float &time, float &reset);

	void setType(TypeUnlifeObject &type);
	void setPosition(float x, float y, int Level);

	// Вспомагательные функции
	float getXPos();
	float getYPos();
private:

};


struct TypesUnlifeObject
{
	TypeUnlifeObject *typeUnlifeObject;
	int countTypeObjects = 0;
	int maxTypeObject = 256;
};

struct UnlifeObjects
{
	UnlifeObject *unlifeObject;
	int maxObject = 256;
	int countObject = 0;
};

void initializeTypeUnlifeObjects(TypesUnlifeObject *unlifeObjects, dataSound &databaseSound);
void initializeUnlifeObjects(UnlifeObjects *unlifeObjects, TypesUnlifeObject *typesUnlifeObjects);