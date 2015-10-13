#ifndef MAP_H
#define MAP_H

#include <SFML\Graphics.hpp>

#include "GlobalVar.h"
#include "UnlifeObject.h"
#include "Items.h"

const sf::String namesBlocks[idBlocks::amountKnowBlocks] =
{
	"Unknow",
	"Air",
	"Grass",
	"Dirt",
	"Sand",
	"Water",
	"Wood",
	"Stone",
	"Stone brick",
	"Wood board",
	"Wood ladder"
};

struct Field
{
	int BLOCK_SIZE;

	wchar_t (*dataMap)[LONG_MAP][WIDTH_MAP];// �����
	int countBlocks = 0;
	wchar_t (*charBlocks);// ���������� ����������� ������
	int (*coordinateBloks)[NUMBER_COORDINATES];// ���������� ����������
	//const sf::String (*nameBlocks) = namesBlocks;

	sf::Sprite *floorSprite;
	sf::Texture *floorTexture;

	sf::Sprite *wallSprite;
	sf::Texture *wallTexture;

	void initializeDataBlocks();// ������ ������
	void setSprite(sf::Sprite *sprite, int l, int i, int j);// ������� �������
	void setTypeSprite(int personLevelFloor, int l, int i, int j);// ������ ��� ��� �����?
	sf::String findCharBlocks(char block);
	bool isObject(float x, float y, std::list<UnlifeObject> *unlifeObjects, UnlifeObject *&findObject, std::list<UnlifeObject>::iterator &findObjectFromList, int currentLevel);
	bool isItem(float x, float y, std::list<Item> *items, Item *&findItem, std::list<Item>::iterator &findItemFromList, int currentLevel);
};

void initializeField(Field & field);
void readMap(wchar_t(*dataMap)[LONG_MAP][WIDTH_MAP], const char *fileName);

#endif MAP_H