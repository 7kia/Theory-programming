#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include "GlobalVar.h"
#include "Sound.h"

// ������� ��������


using namespace sf;

class UnlifeObject
{
public:
	// ���������
	Sprite *spriteObject;
	Texture *textureObject;

	// ��� ��������
	Direction direction;
	float timeAnimation;

	// ������� ������� ����������
	int currentLevel;

	// ������ �� �����
	//Sound *soundsEntity[sizeBuffer];

	// ��� ���������
	int width;
	int height;
	int pixelX;
	int pixelY;

	int widthAlternative;
	int heightAlternative;
	int pixelXAlternative;
	int pixelYAlternative;

	// ��� �������
	char typeObject[20];

	// ������������. ��� �������� � �������
	void update(const Time & deltaTime, dataSound &databaseSound);
	void playSound(float time, float start, const int idSound);
	void resetTimeAnimation(float &time, float &reset);

	//void Init(String *filenameTexture, int w, int h, int pixelX, int pixelY, float xPos, float yPos, int Level);
	void Init(const char *filenameTexture, int w, int h, int pixelX, int pixelY);
	void setPosition(float xPos, float yPos, int Level);

	//��������������� �������
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