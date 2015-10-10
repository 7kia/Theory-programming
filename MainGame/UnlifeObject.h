#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include "GlobalVar.h"
#include "Sound.h"
#include "TypeUnlifeObject.h"

using namespace sf;


class UnlifeObject
{
public:
	sf::Sprite *spriteObject;
	sf::Sprite *transparentSpiteObject;

	//int width;
	//int height;

	TypeUnlifeObject *typeObject;// Пренадлежность типу

	// Прочность
	int currentToughness;
	// Разрушаемый или перетаскиваемый
	bool isDestroy;

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
	void setPosition(int x, int y, int Level);

	// Вспомагательные функции
	float getXPos();
	float getYPos();
private:

};

struct UnlifeObjects
{
	UnlifeObject *unlifeObject;
	int maxObject = 256;
	int countObject = 0;
};

void initializeUnlifeObjects(UnlifeObjects *unlifeObjects, TypesUnlifeObject *typesUnlifeObjects);