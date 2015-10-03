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
	// Текструра
	Sprite *spriteObject;
	Texture *textureEntity;
	
	// Для движения
	Direction direction;
	int stepFirst;
	int stepCurrent;
	float timeAnimation;
	Vector2f movement;

	// Для взаимодействия с миром
	int currentLevelFloor;
	int currentLevel;
	// Ссылки на звуки
	Sound *soundsEntity[sizeBuffer];

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
	
	//Вспомагательные функции
	float getXPos();
	float getYPos();

//private:

};

// Объявление персонажа
void initializeEntity(Entity & Entity, dataSound &databaseSound);
