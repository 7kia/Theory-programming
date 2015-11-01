#pragma once
#include <SFML\Graphics.hpp>

#include "TypeItems.h"

struct Item 
{
	sf::Sprite *mainSprite;
	sf::Sprite *spriteForUse;

	sf::String nameItem;
	int categoryItem;

	TypeItem *typeItem;// �������������� ����

	// ����������� ��� ���
	bool isDestroy;
	int currentToughness;// ���������
	int maxToughness;// ������������ ���������

	// ����
	int cuttingDamage;// �������
	int crushingDamage;// ��������

	// ������� ������� ����������
	int currentLevel;

	// ��� ��������
	//Direction direction;// �������
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

void initializeItems(std::vector<Item> &items, TypesItem *typesItem, Item &emptyItem);