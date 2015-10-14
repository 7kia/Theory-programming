#pragma once
#include <SFML\Graphics.hpp>

// Для динамических списков
#include <list>     // подключаем заголовок списка
#include <iterator> // заголовок итераторов

#include "GlobalVar.h"
#include "TypeItems.h"

struct Item 
{
	sf::Sprite *mainSprite;
	sf::Sprite *spriteForUse;

	sf::String nameItem;


	//int width;
	//int height;

	TypeItem *typeItem;// Пренадлежность типу

	// Разрушаемый или нет
	bool isDestroy;
	int currentToughness;// Прочность

	// Текущий уровень размещения
	int currentLevel;

	// Для анимации
	//Direction direction;
	float timeAnimation;

	// Передвижение. Его анимация и озвучка
	void update(const sf::Time & deltaTime, dataSound &databaseSound);
	void playSound(float time, float start, const int idSound);
	void resetTimeAnimation(float &time, float &reset);

	void setType(TypeItem &type);
	void setPosition(int x, int y, int Level);

	// Вспомагательные функции
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