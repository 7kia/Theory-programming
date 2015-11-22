#pragma once
#include <SFML\Graphics.hpp>

#include "../Map/BlocksVar.h"
#include "../GlobalVar.h"
#include "../Sounds/Sound.h"

#include "TypeUnlifeObject.h"

struct world;
using namespace sf;

class UnlifeObject
{
public:
	sf::Sprite *spriteObject;
	sf::Sprite *transparentSpiteObject;

	//int width;
	//int height;

	TypeUnlifeObject *typeObject;// �������������� ����

	int currentToughness;
	bool isDestroy;

	// ������� ������� ����������
	int currentLevel;
	float timeLife;

	// ������������. ��� �������� � �������
	void update(const float deltaTime, dataSound &databaseSound);
	void playSound(float time, float start, const int idSound);
	void resetTimeAnimation(float &time, float &reset);

	void setType(TypeUnlifeObject &type);
	void setPosition(int x, int y, int Level);

	// ��������������� �������
	float getXPos();
	float getYPos();
private:

};

void initializeUnlifeObjects(std::vector<UnlifeObject> &unlifeObjects, TypeUnlifeObject *typesUnlifeObjects, UnlifeObject &emptyObject);
void updateUnlifeObjects(world &world, float deltaTime);
