#pragma once
#include <SFML\Graphics.hpp>

#include "TypeItems.h"

struct Item 
{
	sf::Sprite *mainSprite;
	sf::Sprite *spriteForUse;

	sf::String nameItem;
	int categoryItem;

	TypeItem *typeItem;// Пренадлежность типу

	// Разрушаемый или нет
	bool isDestroy;
	int currentToughness;// Прочность
	int maxToughness;// максимальная прочность

	// Урон
	int cuttingDamage;// Режущий
	int crushingDamage;// Дробящий

	// Текущий уровень размещения
	int currentLevel;

	// Для анимации
	//Direction direction;// ИСПРАВЬ
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

void initializeItems(std::vector<Item> &items, TypesItem *typesItem, Item &emptyItem);