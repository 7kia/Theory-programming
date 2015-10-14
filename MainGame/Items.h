#pragma once
#include <SFML\Graphics.hpp>

// ��� ������������ �������
#include <list>     // ���������� ��������� ������
#include <iterator> // ��������� ����������

#include "GlobalVar.h"
#include "TypeItems.h"

struct Item 
{
	sf::Sprite *mainSprite;
	sf::Sprite *spriteForUse;

	sf::String nameItem;


	//int width;
	//int height;

	TypeItem *typeItem;// �������������� ����

	// ����������� ��� ���
	bool isDestroy;
	int currentToughness;// ���������

	// ������� ������� ����������
	int currentLevel;

	// ��� ��������
	//Direction direction;
	float timeAnimation;

	// ������������. ��� �������� � �������
	void update(const sf::Time & deltaTime, dataSound &databaseSound);
	void playSound(float time, float start, const int idSound);
	void resetTimeAnimation(float &time, float &reset);

	void setType(TypeItem &type);
	void setPosition(int x, int y, int Level);

	// ��������������� �������
	float getXPos();
	float getYPos();
private:

};

/*
struct Items
{
	Item *item;
	int maxItem = 256;
	int countItem = 0;
};
*/


void initializeItems(std::list<Item> &items, TypesItem *typesItem, Item &emptyItem);