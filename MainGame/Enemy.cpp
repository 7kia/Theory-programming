#include "Enemy.h"

void initializeEntitys(TypesEnemy *typesEnemy, std::list<Enemy> &enemy, int countEnemy,
											 Item &emptyItem, UnlifeObject &emptyObject)// ���������� �������� 
{

	srand(time(0)); // �������������� �����������
									//////////////////////////////////////////////////////////////
									// �����
	Enemy* addEnemy = new Enemy();

	TypeEnemy* typeEnemy = &typesEnemy->typesEnemy[idEnemy::wolfEnemy];
	
	int xPos;
	int yPos;
	int levelFloor;

	for (size_t i = 0; i < 3; i++) {
		countEnemy++;
		if (countEnemy > AMOUNT_ENTITY) {
			break;
		}

		int xPos = 5 + rand() % 5;
		int yPos = 5 + rand() % 5;
		int levelFloor = 0;

		addEnemy->EnemyInit(*typeEnemy, emptyItem, emptyObject, xPos, yPos, levelFloor);

		enemy.push_back(*addEnemy);

	}
	//////////////////////////////////////////////////////////////
	// �������
	typeEnemy = &typesEnemy->typesEnemy[idEnemy::skeletEnemy];

	for (size_t i = 0; i < 3; i++) {
		countEnemy++;
		if (countEnemy > AMOUNT_ENTITY) {
			break;
		}

		xPos = 7 + rand() % 5;
		yPos = 7 + rand() % 5;
		levelFloor = 0;

		addEnemy->EnemyInit(*typeEnemy, emptyItem, emptyObject, xPos, yPos, levelFloor);

		enemy.push_back(*addEnemy);

	}
	//////////////////////////////////////////////////////////////
	delete addEnemy;

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
void Enemy::EnemyInit(TypeEnemy &typesEnemy, Item &emptyItem, UnlifeObject &emptyObject,
											int xPos, int yPos, int level)
{
	spriteEntity = new Sprite;

	type = &typesEnemy;

	width = type->width;
	height = type->height;

	// ��������� ������� ���������
	radiusUse = 1;

	// �������� ������
	stepFirst = SPEED_ENTITY;
	stepCurrent = SPEED_ENTITY;
	timeAnimation = 0.f;

	// ��������
	spriteEntity->setTexture(*type->textureEntity);
	spriteEntity->setTextureRect(IntRect(0, 0, type->width, type->height));

	// ����� 
	soundsEntity[idSoundEntity::stepGrass] = type->soundsEntity[idSoundEntity::stepGrass];
	soundsEntity[idSoundEntity::stepStone] = type->soundsEntity[idSoundEntity::stepStone];

	findItem = new Item;
	findObject = new UnlifeObject;

	// ������� ��������� ��� �����
	this->emptyObject = &emptyObject;
	this->emptyItem = &emptyItem;
	idSelectItem = 0;

	// ������� � �����������
	currentLevelFloor = level;
	currenMode = idModeEntity::fight;

	spriteEntity->setOrigin(type->width / 2, type->height / 2);
	spriteEntity->setPosition(xPos * SIZE_BLOCK - SIZE_BLOCK / 2, yPos * SIZE_BLOCK - SIZE_BLOCK / 2);
	direction = NONE;

	////////////////////////////////////////////////////////////////////////
	// ��� ���������� ����������� �� �����
	timeWalk = minTimeWalk + rand() % (int(maxTimeWalk - minTimeWalk));

	currentTime = 0;

	int randomDirection = 1 + rand() % Direction::AMOUNT_DIRECTION;
	direction = (Direction)randomDirection;
	////////////////////////////////////////////////////////////////////////

	// ����������
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

}

Enemy::~Enemy()
{
}

void Enemy::randomWalk(const Time &deltaTime) {

	if (currentTime < timeWalk && direction != Direction::NONE){

		currentTime += deltaTime.asSeconds();

	} else {

		currentTime = 0;
		timeWalk = minTimeWalk + rand() % (int(maxTimeWalk - minTimeWalk));

		int randomDirection = 1 + rand() % Direction::AMOUNT_DIRECTION;
		direction = (Direction)randomDirection;
	}

	




}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////