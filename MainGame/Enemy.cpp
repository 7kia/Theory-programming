#include "Enemy.h"
#include "Items.h"
#include "UnlifeObject.h"
#include "EntityVar.h"

void initializeEntitys(TypeEnemy *typesEnemy, std::vector<Enemy> &enemy, int countEnemy,
											 Item &emptyItem, UnlifeObject &emptyObject, Enemy &emptyEnemy)// ���������� �������� 
{

	srand(time(0)); // �������������� �����������
									//////////////////////////////////////////////////////////////
									// �����
	Enemy* addEnemy = new Enemy();

	TypeEnemy* typeEnemy = &typesEnemy[idEnemy::wolfEnemy];
	
	int xPos;
	int yPos;
	int levelFloor;

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
	// �������
	typeEnemy = &typesEnemy[idEnemy::skeletEnemy];

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
	typeEnemy = &typesEnemy[idEnemy::emptyEnemy];
	emptyEnemy.EnemyInit(*typeEnemy, emptyItem, emptyObject, -1, -1, -1);//TODO

	delete addEnemy;

}


void Enemy::initStepSounds()
{
	soundsEntity.push_back(type->soundsEntity[idSoundEntity::stepGrass]);
	soundsEntity.push_back(type->soundsEntity[idSoundEntity::stepStone]);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
void Enemy::EnemyInit(TypeEnemy &typesEnemy, Item &emptyItem, UnlifeObject &emptyObject,
											int xPos, int yPos, int level)
{
	spriteEntity = new Sprite;

	type = &typesEnemy;

	size.width = type->featuresSprite.size.width;
	size.height = type->featuresSprite.size.height;

	// ��������� ������� ���������
	radiusUse = 1;

	currenMode = idEntityMode::walk;

	// �������� ������
	step.init(SPEED_ENTITY);

	// ��������
	spriteEntity->setTexture(*type->textureEntity);
	spriteEntity->setTextureRect(IntRect(0, 0, size.width, size.height));


	initStepSounds();

	founds.init(&emptyItem, &emptyObject);

	// ������� � �����������
	currentLevelFloor = level;
	currenMode = idEntityMode::walk;

	spriteEntity->setOrigin(size.width / 2, size.height / 2);
	spriteEntity->setPosition(xPos * SIZE_BLOCK - SIZE_BLOCK / 2, yPos * SIZE_BLOCK - SIZE_BLOCK / 2);

	directions.directionWalk = NONE_DIRECTION;
	directions.directionLook = DOWN;

	////////////////////////////////////////////////////////////////////////
	// ��� ���������� ����������� �� �����
	step.timeWalk = minTimeWalk + rand() % (int(maxTimeWalk - minTimeWalk));

	step.currentTime = 0;

	int randomDirection = 1 + rand() % Direction::AMOUNT_DIRECTION;
	directions.directionWalk = Direction(randomDirection);
	////////////////////////////////////////////////////////////////////////

	// ����������
	health.maxHealth = type->features.maxHealth;
	health.currentHealth = health.maxHealth;

	stamina.maxStamina = type->features.maxStamina;
	stamina.currentStamina = stamina.maxStamina;

	mana.maxMana = type->features.maxMana;
	mana.currentMana = mana.maxMana;

	thirst.currentThirst = thirst.maxThirst;
	hungry.currentHungry = hungry.maxHungry;

	protection.init(type->protection.protectionCut,
									type->protection.protectionCrash);

	float timeAtack = 1.f;
	animation.init(type->damage.timeOutputDamage, timeAtack);
	damage.init(type->damage.cuttingDamage, type->damage.crushingDamage, timeAtack, 1.f);
}

Enemy::~Enemy()
{
}

void Enemy::randomWalk(const Time &deltaTime) {

	if (currenMode == idEntityMode::walk) {
		if (step.currentTime < step.timeWalk && directions.directionWalk != Direction::NONE_DIRECTION) {

			step.currentTime += deltaTime.asSeconds();

		} else {

			step.currentTime = 0;
			step.timeWalk = minTimeWalk + rand() % (int(maxTimeWalk - minTimeWalk));

			int randomDirection = 1 + rand() % Direction::AMOUNT_DIRECTION;
			directions.directionWalk = Direction(randomDirection);
		}
	}
	

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Enemy::takeDamage(DamageInputAndOutput damage, Item &currentItem)
{
	bool isDestroy = currentItem.typeItem->features.isDestroy;
	if (isDestroy) {
		currentItem.currentToughness -= 1;
	}

	int cuttingDamage = currentItem.typeItem->damageItem.cuttingDamage;
	int crushingDamage = currentItem.typeItem->damageItem.crushingDamage;

	float cutDamage = damage.damageMultiplirer * currentItem.typeItem->damageItem.cuttingDamage;
	float crashDamage = damage.damageMultiplirer * currentItem.typeItem->damageItem.crushingDamage;

	cutDamage *= protection.protectionCut;
	crashDamage *= protection.protectionCrash;

	damage.inputDamage = cutDamage + crashDamage;
	health.currentHealth -= damage.inputDamage;
}

void Enemy::choiceDirections(Vector2f movemoment)
{
	float zero = SIZE_BLOCK / 2;

	bool xAboutZero = movemoment.x >= -zero && movemoment.x <= zero;
	bool yAboutZero = movemoment.y >= -zero && movemoment.y <= zero;

	if (movemoment.x > zero && movemoment.y > zero) {
		directions.directionWalk = DOWN_RIGHT;
		directions.directionLook = DOWN_RIGHT;
	} else if (movemoment.x < -zero && movemoment.y > zero) {
		directions.directionWalk = DOWN_LEFT;
		directions.directionLook = DOWN_LEFT;
	} else if (movemoment.x < -zero && movemoment.y < -zero) {
		directions.directionWalk = UP_LEFT;
		directions.directionLook = UP_LEFT;
	} else if (movemoment.x > zero && movemoment.y < zero) {
		directions.directionWalk = UP_RIGHT;
		directions.directionLook = UP_RIGHT;
	} else if (movemoment.y >= zero && xAboutZero) {
		directions.directionWalk = DOWN;
		directions.directionLook = DOWN;
	} else if (movemoment.y <= -zero && xAboutZero) {
		directions.directionWalk = UP;
		directions.directionLook = UP;
	} else if (movemoment.x >= zero && yAboutZero) {
		directions.directionWalk = RIGHT;
		directions.directionLook = RIGHT;
	} else if (movemoment.x <= -zero && yAboutZero) {
		directions.directionWalk = LEFT;
		directions.directionLook = LEFT;
	} else {
		directions.directionWalk = NONE_DIRECTION;
	}
}
