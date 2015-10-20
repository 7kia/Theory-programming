#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include "GlobalVar.h"
#include "UnlifeObject.h"
#include "Items.h"
#include "Map.h"
#include "Sound.h"

const float speedEntity = 350.f;

const sf::Color NORMAL_COLOR(255, 255, 255, 255);
const sf::Color TRANSPARENT_COLOR(255, 255, 255, 127);

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
	void interactionWitnUnlifeObject(std::list<UnlifeObject> *unlifeObjects, const Time & deltaTime);
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

bool isObject(float x, float y, std::list<UnlifeObject> *unlifeObjects, UnlifeObject *&findObject, std::list<UnlifeObject>::iterator &findObjectFromList, std::list<UnlifeObject>::iterator &current, int currentLevel);
bool isItem(float x, float y, std::list<Item> &items, Item *&findItem, std::list<Item>::iterator &findItemFromList, std::list<Item>::iterator &current, int currentLevel);
