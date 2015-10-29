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

	float timeGivenDamage = 1.f;
	int damCut = 5;
	int damCrash = 0;

	float protectCut = 1.5f;
	float protectCrush = 1.f;

	float view = RADIUSE_VIEW;

	*minAmountForWolf = { 1 };
	*maxAmountForWolf = { 2 };
	*idItemsForWolf = { idItem::dirtItem };// ИСПРАВЬ

	typeEnemy->Init(texturePath, name, databaseSound, width, height, AMOUNT_WOLF_SLOTS, 
									health, stamina, mana, protectCut, protectCrush,
									view, damCut, damCrash, timeGivenDamage,
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

	timeGivenDamage = 1.f;
	damCut = 0;
	damCrash = 5;

	protectCut = 0.f;
	protectCrush = 1.f;

	view = RADIUSE_VIEW;

	*minAmountForSkelet = { 1 };
	*maxAmountForSkelet = { 2 };
	*idItemsForSkelet = { idItem::dirtItem };// ИСПРАВЬ

	typeEnemy->Init(texturePath, name, databaseSound, width, height, AMOUNT_SKELET_SLOTS,
									health, stamina, mana, protectCut, protectCrush,
									view, damCut, damCrash, timeGivenDamage,
									idItemsForSkelet, minAmountForSkelet, maxAmountForSkelet, 1);

	delete minAmountForSkelet;
	delete maxAmountForSkelet;
	delete idItemsForSkelet;
	////////////////////////////////////////////////////////////////
}

void TypeEnemy::Init(sf::String texturePath, sf::String nameEnemy, dataSound &databaseSound,
										 int widthEnemy, int heightEnemy, int amountEnemySlots,
										 int health, int stamina, int mana, float protectCut, float protectCrush,
										 float view, int damCut, int damCrash, float timeDam,
										 int * idItems, int * minAmountItems, int * maxAmountItems, int count)
{
	textureEntity = new Texture;

	name = nameEnemy;

	// Задание размера
	height = widthEnemy;
	width = heightEnemy;

	// Дальность подбора предметов
	radiusUse = 1;
	radiuseView = view;

	// Скорость ходьбы
	stepFirst = SPEED_ENTITY;
	stepCurrent = SPEED_ENTITY;
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

	timeGivenDamage = timeDam;
	cuttingDamage = damCut;
	crushingDamage = damCrash;

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
