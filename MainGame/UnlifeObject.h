#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include "GlobalVar.h"
#include "Sound.h"

// Размеры объектов


using namespace sf;

class UnlifeObject
{
public:
	// Текструра
	Sprite *spriteObject;
	Texture *textureObject;

	// Для анимации
	Direction direction;
	float timeAnimation;

	// Текущий уровень размещения
	int currentLevel;

	// Ссылки на звуки
	//Sound *soundsEntity[sizeBuffer];

	// Для отрисовки
	int width;
	int height;
	int pixelX;
	int pixelY;

	int widthAlternative;
	int heightAlternative;
	int pixelXAlternative;
	int pixelYAlternative;

	// Тип объекта
	char typeObject[20];

	// Передвижение. Его анимация и озвучка
	void update(const Time & deltaTime, dataSound &databaseSound);
	void playSound(float time, float start, const int idSound);
	void resetTimeAnimation(float &time, float &reset);

	//void Init(String *filenameTexture, int w, int h, int pixelX, int pixelY, float xPos, float yPos, int Level);
	void Init(const char *filenameTexture, int w, int h, int pixelX, int pixelY);
	void setPosition(float xPos, float yPos, int Level);

	//Вспомагательные функции
	float getXPos();
	float getYPos();

	//private:

};



struct UnlifeObjects
{
	UnlifeObject *unlifeObject;
	int countObjects = 0;
	int maxObject = 256;
};

void initializeUnlifeObjects(UnlifeObjects *unlifeObjects, dataSound &databaseSound);