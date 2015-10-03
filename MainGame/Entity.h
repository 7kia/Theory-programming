#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include "GlobalVar.h"
#include "Map.h"
#include "Sound.h"

#define speedEntity 150.f

using namespace sf;

typedef enum
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	UP_LEFT,
	UP_RIGHT,
	DOWN_LEFT,
	DOWN_RIGHT
} Direction;


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
	// режимы персонажа
	void modeProcess(Field &field, Event &eventPerson, int x, int y);
	// Камера
	View *view;
	void getCoordinateForView(float x, float y);
	void viewmap(float time);
	void changeview();

	// Для направления взгляда
	float rotation;
	void computeAngle(RenderWindow &window);

	// Для взаимодействия с миром
	int currenMode;
	const int amountActiveSlots = 10;
	int idSelectItem;
	// кнопка "Дествие" и "Другое действие"
	void actionMain(Field &field, int x, int y);
	void actionAlternative(Field &field, int x, int y);
};

// Объявление персонажа
void initializeEntity(Entity & Entity, dataSound &databaseSound);
