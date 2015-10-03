#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include "GlobalVar.h"
#include "Map.h"
#include "Sound.h"

#define speedEntity 150.f

using namespace sf;


class Entity 
{
public:
	// ���������
	Sprite *spriteObject;
	Texture *textureEntity;
	
	// ��� ��������
	Direction direction;
	int stepFirst;
	int stepCurrent;
	float timeAnimation;
	Vector2f movement;

	// ��� �������������� � �����
	int currentLevelFloor;
	int currentLevel;
	// ������ �� �����
	Sound *soundsEntity[sizeBuffer];

	// ��� ���������
	int width;
	int height;
	int widthForAnimation;
	int heightForAnimation;

	// ������������. ��� �������� � �������
	void update(const Time & deltaTime, dataSound &databaseSound);
	void playSound(float time, float start, const int idSound);
	void resetTimeAnimation(float &time, float &reset);
	
	// �������������� � �����
	void interactionWithMap(Field &field, const Time & deltaTime);
	
	//��������������� �������
	float getXPos();
	float getYPos();

//private:

};

// ���������� ���������
void initializeEntity(Entity & Entity, dataSound &databaseSound);
