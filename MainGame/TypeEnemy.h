#pragma once
#include "EntityVar.h"
#include "GlobalVar.h"
#include "ListObjectsAndBlocks.h"
#include "UnlifeObject.h"
#include "Items.h"
#include "Map.h"
#include "Sound.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Сущность
struct TypeEnemy
{
	sf::Texture *textureEntity;

	// Имя
	sf::String name;

	// Ссылки на звуки
	sf::Sound *soundsEntity[sizeBuffer];

	// Для взаимодействия с миром
	int radiusUse;

	// Ходьба
	float stepFirst;
	float stepCurrent;
	float timeAnimation;

	int maxHealth;
	int maxStamina;
	int maxMana;

	// Для отрисовки
	int width;
	int height;
	int widthForAnimation;
	int heightForAnimation;

	// Количество ячеек инвентаря
	int amountSlots;

	float damageMultiplirer;

	int* minCountItems;
	int* maxCountItems;
	int* dropItems;// ИСПРАВЬ


	void Init(sf::String texturePath, sf::String nameEnemy, dataSound &databaseSound,
						int widthEnemy, int heightEnemy, int amountEnemySlots,
						int health, int stamina, int mana,
						int* idItems, int* minAmountItems, int* maxAmountItems, int count);
};

struct TypesEnemy
{
	TypeEnemy* typesEnemy;
	int countType = 0;
};

void initializeTypeEnemy(TypesEnemy &typesEnemy, dataSound &databaseSound);