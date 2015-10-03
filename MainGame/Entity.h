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
	// ������ ���������
	void modeProcess(Field &field, Event &eventPerson, int x, int y);
	// ������
	View *view;
	void getCoordinateForView(float x, float y);
	void viewmap(float time);
	void changeview();

	// ��� ����������� �������
	float rotation;
	void computeAngle(RenderWindow &window);

	// ��� �������������� � �����
	int currenMode;
	const int amountActiveSlots = 10;
	int idSelectItem;
	// ������ "�������" � "������ ��������"
	void actionMain(Field &field, int x, int y);
	void actionAlternative(Field &field, int x, int y);
};

// ���������� ���������
void initializeEntity(Entity & Entity, dataSound &databaseSound);
