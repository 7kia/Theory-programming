#ifndef ENTITY_H
#define ENTITY_H

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include "GlobalVar.h"
#include "UnlifeObject.h"
#include "Map.h"
#include "Sound.h"

const float speedEntity = 150.f;

class Entity 
{
public:
	// ���������
	sf::Sprite *spriteEntity;
	sf::Texture *textureEntity;
	
	// ��� ��������
	Direction direction;
	float stepFirst;
	float stepCurrent;
	float timeAnimation;
	sf::Vector2f movement;

	// ��� �������������� � �����
	int radiusUse;
	int currentLevelFloor;

	// ������ �� �����
	sf::Sound *soundsEntity[sizeBuffer];

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
	void interactionWitnUnlifeObject(UnlifeObjects &unlifeObjects, const Time & deltaTime);
	bool isInUseField(float x, float y);
	
	sf::Vector2i isEmptyFloor(Field &field, int currentLevel);// ���� ������ ������ ������
	bool isExitFromBorder(int x, int y);// ���� ����� �� ������� �����
	//��������������� �������
	float getXPos();
	float getYPos();

//private:

};

// ���������� ���������
void initializeEntity(Entity & Entity, dataSound &databaseSound);

#endif ENTITY_H