#include "Enemy.h"
#include "Items.h"
#include "UnlifeObject.h"
#include "EntityVar.h"

void initializeEntitys(TypesEnemy *typesEnemy, std::vector<Enemy> &enemy, int countEnemy,
											 Item &emptyItem, UnlifeObject &emptyObject)// ДОБАВЛЕНИЕ СУЩНОСТИ 
{

	srand(time(0)); // автоматическая случайность
									//////////////////////////////////////////////////////////////
									// Волки
	Enemy* addEnemy = new Enemy();

	TypeEnemy* typeEnemy = &typesEnemy->typesEnemy[idEnemy::wolfEnemy];
	
	int xPos;
	int yPos;
	int levelFloor;

	for (size_t i = 0; i < 4; i++) {
		countEnemy++;
		if (countEnemy > AMOUNT_ENTITY) {
			break;
		}

		int xPos = 9 + rand() % 5;
		int yPos = 9 + rand() % 5;
		int levelFloor = 0;

		addEnemy->EnemyInit(*typeEnemy, emptyItem, emptyObject, xPos, yPos, levelFloor);

		enemy.push_back(*addEnemy);

	}
	//////////////////////////////////////////////////////////////
	// Скелеты
	typeEnemy = &typesEnemy->typesEnemy[idEnemy::skeletEnemy];

	for (size_t i = 0; i < 4; i++) {
		countEnemy++;
		if (countEnemy > AMOUNT_ENTITY) {
			break;
		}

		xPos = 9 + rand() % 5;
		yPos = 9 + rand() % 5;
		levelFloor = 0;

		addEnemy->EnemyInit(*typeEnemy, emptyItem, emptyObject, xPos, yPos, levelFloor);

		enemy.push_back(*addEnemy);

	}
	//////////////////////////////////////////////////////////////
	delete addEnemy;

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Сущности
void Enemy::EnemyInit(TypeEnemy &typesEnemy, Item &emptyItem, UnlifeObject &emptyObject,
											int xPos, int yPos, int level)
{
	spriteEntity = new Sprite;

	type = &typesEnemy;

	width = type->width;
	height = type->height;

	// Дальность подбора предметов
	radiusUse = 1;

	mode = idEntityMode::walk;

	// Скорость ходьбы
	stepFirst = SPEED_ENTITY;
	stepCurrent = SPEED_ENTITY;
	timeAnimation = 0.f;

	// Текстура
	spriteEntity->setTexture(*type->textureEntity);
	spriteEntity->setTextureRect(IntRect(0, 0, type->width, type->height));

	// Звуки 
	soundsEntity[idSoundEntity::stepGrass] = type->soundsEntity[idSoundEntity::stepGrass];
	soundsEntity[idSoundEntity::stepStone] = type->soundsEntity[idSoundEntity::stepStone];

	findItem = new Item;
	findObject = new UnlifeObject;

	// Текущий выбранный тип блока
	this->emptyObject = &emptyObject;
	this->emptyItem = &emptyItem;
	idSelectItem = 0;

	// Позиция и направление
	currentLevelFloor = level;
	currenMode = idEntityMode::fight;

	spriteEntity->setOrigin(type->width / 2, type->height / 2);
	spriteEntity->setPosition(xPos * SIZE_BLOCK - SIZE_BLOCK / 2, yPos * SIZE_BLOCK - SIZE_BLOCK / 2);
	direction = NONE;

	////////////////////////////////////////////////////////////////////////
	// Для случайного перемещения по карте
	timeWalk = minTimeWalk + rand() % (int(maxTimeWalk - minTimeWalk));

	currentTime = 0;

	int randomDirection = 1 + rand() % Direction::AMOUNT_DIRECTION;
	direction = (Direction)randomDirection;
	////////////////////////////////////////////////////////////////////////

	// Показатели
	maxHealth = type->maxHealth;
	currentHealth = maxHealth;

	maxStamina = type->maxStamina;
	currentStamina = maxStamina;

	maxMana = type->maxMana;
	currentMana = maxMana;

	currentThirst = maxThirst;
	currentHungry = maxHungry;

	protectionCut = type->protectionCut;
	protectionCrash = type->protectionCrash;

	timeOutputDamage = type->timeOutputDamage;
	currentTimeOutputDamage = 0.f;

	timeInputDamage = 0.f;

	cuttingDamage = type->cuttingDamage;
	crushingDamage = type->crushingDamage;
	damageMultiplirer = 1.f;

}

Enemy::~Enemy()
{
}

void Enemy::randomWalk(const Time &deltaTime) {

	if (mode == idEntityMode::walk) {
		if (currentTime < timeWalk && direction != Direction::NONE) {

			currentTime += deltaTime.asSeconds();

		} else {

			currentTime = 0;
			timeWalk = minTimeWalk + rand() % (int(maxTimeWalk - minTimeWalk));

			int randomDirection = 1 + rand() % Direction::AMOUNT_DIRECTION;
			direction = (Direction)randomDirection;
		}
	}
	

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////