#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include "GlobalVar.h"
#include "Sound.h"

using namespace sf;

struct TypeUnlifeObject
{
public:
	// ���������
	sf::Texture *textureObject;

	// ������ �� �����
	//Sound *soundsEntity[sizeBuffer];

	// ��� ���������
	int width;
	int height;
	int pixelPosX;
	int pixelPosY;

	int widthAlternative;
	int heightAlternative;
	int pixelXAlternative;
	int pixelYAlternative;

	// ��� �������
	char typeObject[20];

	//void Init(String *filenameTexture, int w, int h, int pixelX, int pixelY, float xPos, float yPos, int Level);
	void Init(const char *filenameTexture, char *typeName, int w, int h, int pixelX, int pixelY);

};

class UnlifeObject
{
public:
	sf::Sprite *spriteObject;

	// ������� ������� ����������
	int currentLevel;

	// ��� ��������
	Direction direction;
	float timeAnimation;

	// ������������. ��� �������� � �������
	void update(const Time & deltaTime, dataSound &databaseSound);
	void playSound(float time, float start, const int idSound);
	void resetTimeAnimation(float &time, float &reset);

	void setType(TypeUnlifeObject &type);
	void setPosition(float x, float y, int Level);

	// ��������������� �������
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