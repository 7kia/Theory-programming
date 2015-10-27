#include "TypeEnemy.h"

using namespace sf;

void initializeTypeEnemy(TypesEnemy &typesEnemy, dataSound &databaseSound)
{
	typesEnemy.typesEnemy = new TypeEnemy[idEnemy::amountEnemy];


	////////////////////////////////////////////////////////////////
	// Волк
	TypeEnemy* typeEnemy = &typesEnemy.typesEnemy[idEnemy::wolfEnemy];

	String texturePath = texturePaths[idTexturePaths::wolf];
	String name = "Wolf";

	int width = WIDTH_WOLF;
	int height = HEIGHT_WOLF;

	int* minAmountForWolf = new int[1];
	int* maxAmountForWolf = new int[1];
	int* idItemsForWolf = new int[1];

	int health = 50;
	int stamina = 50;
	int mana = 0;

	float protectCut = 1.5f;
	float protectCrush = 1.f;

	*minAmountForWolf = { 1 };
	*maxAmountForWolf = { 2 };
	*idItemsForWolf = { idItem::dirtItem };// ИСПРАВЬ

	typeEnemy->Init(texturePath, name, databaseSound, width, height, AMOUNT_WOLF_SLOTS, 
									health, stamina, mana, protectCut, protectCrush,
									idItemsForWolf, minAmountForWolf, maxAmountForWolf, 1);

	delete minAmountForWolf;
	delete maxAmountForWolf;
	delete idItemsForWolf;
	////////////////////////////////////////////////////////////////
	// Волк
	typeEnemy = &typesEnemy.typesEnemy[idEnemy::skeletEnemy];

	texturePath = texturePaths[idTexturePaths::skelet];
	name = "Skelet";

	width = WIDTH_SKELET;
	height = HEIGHT_SKELET;

	int* minAmountForSkelet = new int[1];
	int* maxAmountForSkelet = new int[1];
	int* idItemsForSkelet = new int[1];

	health = 50;
	stamina = 50;
	mana = 0;

	protectCut = 0.f;
	protectCrush = 1.f;

	*minAmountForSkelet = { 1 };
	*maxAmountForSkelet = { 2 };
	*idItemsForSkelet = { idItem::dirtItem };// ИСПРАВЬ

	typeEnemy->Init(texturePath, name, databaseSound, width, height, AMOUNT_SKELET_SLOTS,
									health, stamina, mana, protectCut, protectCrush,
									idItemsForSkelet, minAmountForSkelet, maxAmountForSkelet, 1);

	delete minAmountForSkelet;
	delete maxAmountForSkelet;
	delete idItemsForSkelet;
	////////////////////////////////////////////////////////////////
}

void TypeEnemy::Init(sf::String texturePath, sf::String nameEnemy, dataSound &databaseSound,
										 int widthEnemy, int heightEnemy, int amountEnemySlots,
										 int health, int stamina, int mana, float protectCut, float protectCrush,
										 int * idItems, int * minAmountItems, int * maxAmountItems, int count)
{
	textureEntity = new Texture;

	name = nameEnemy;

	// Задание размера
	height = widthEnemy;
	width = heightEnemy;

	// Дальность подбора предметов
	radiusUse = 1;

	// Скорость ходьбы
	stepFirst = speedEntity;
	stepCurrent = speedEntity;
	timeAnimation = 0.f;

	// Текстура
	textureEntity->loadFromFile(texturePath);

	// Звуки 
	soundsEntity[idSoundEntity::stepGrass] = &databaseSound.sounds[idSoundEntity::stepGrass];
	soundsEntity[idSoundEntity::stepStone] = &databaseSound.sounds[idSoundEntity::stepStone];

	// Показатели
	maxHealth = health;
	maxStamina = stamina;
	maxMana = mana;

	protectionCut = protectCut;
	protectionCrash = protectCrush;

	// Выпадающие предметы
	dropItems = new int[count];
	minCountItems = new int[count];
	maxCountItems = new int[count];

	for (size_t i = 0; i < count; i++) {
		dropItems[i] = idItems[i];
		minCountItems[i] = minAmountItems[i];
		maxCountItems[i] = maxAmountItems[i];
	}

}
