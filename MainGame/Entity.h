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
	// Текструра
	sf::Sprite *spriteEntity;
	sf::Texture *textureEntity;
	
	// Для движения
	Direction direction;
	float stepFirst;
	float stepCurrent;
	float timeAnimation;
	sf::Vector2f movement;

	// Для взаимодействия с миром
	int radiusUse;
	int currentLevelFloor;

	// Ссылки на звуки
	sf::Sound *soundsEntity[sizeBuffer];

	// Для отрисовки
	int width;
	int height;
	int widthForAnimation;
	int heightForAnimation;

	// Передвижение. Его анимация и озвучка
	void update(const Time & deltaTime, dataSound &databaseSound);
	void playSound(float time, float start, const int idSound);
	void resetTimeAnimation(float &time, float &reset);
	
	// Взаимодейтсвие с миром
	void interactionWithMap(Field &field, const Time & deltaTime);
	void interactionWitnUnlifeObject(UnlifeObjects &unlifeObjects, const Time & deltaTime);
	bool isInUseField(float x, float y);
	
	sf::Vector2i isEmptyFloor(Field &field, int currentLevel);// Есть вблизи пустые клетки
	bool isExitFromBorder(int x, int y);// Есть выход за границы карты
	//Вспомагательные функции
	float getXPos();
	float getYPos();

//private:

};

// Объявление персонажа
void initializeEntity(Entity & Entity, dataSound &databaseSound);

#endif ENTITY_H