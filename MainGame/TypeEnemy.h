#pragma once
#include "EntityVar.h"
#include "GlobalVar.h"
#include "ListObjectsAndBlocks.h"
#include "UnlifeObject.h"
#include "Items.h"
#include "Map.h"
#include "Sound.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
struct TypeEnemy
{
	sf::Texture *textureEntity;

	// ���
	sf::String name;

	// ������ �� �����
	sf::Sound *soundsEntity[sizeBuffer];

	// ��� �������������� � �����
	int radiusUse;
	float radiuseView;

	// ������
	float stepFirst;
	float stepCurrent;
	float timeAnimation;

	int maxHealth;
	int maxStamina;
	int maxMana;

	// ����
	float timeGivenDamage;
	int cuttingDamage;// �������� �� ���������
	int crushingDamage;// �������� �� ���������

	// ������
	float protectionCut;
	float protectionCrash;

	// ��� ���������
	int width;
	int height;
	int widthForAnimation;
	int heightForAnimation;

	// ���������� ����� ���������
	int amountSlots;

	float damageMultiplirer;

	int* minCountItems;
	int* maxCountItems;
	int* dropItems;// �������


	void Init(sf::String texturePath, sf::String nameEnemy, dataSound &databaseSound,
						int widthEnemy, int heightEnemy, int amountEnemySlots,
						int health, int stamina, int mana, float protectCut, float protectCrush,
						float view, int damCut, int damCrash, float timeDam,
						int* idItems, int* minAmountItems, int* maxAmountItems, int count);
};

struct TypesEnemy
{
	TypeEnemy* typesEnemy;
	int countType = 0;
};

void initializeTypeEnemy(TypesEnemy &typesEnemy, dataSound &databaseSound);