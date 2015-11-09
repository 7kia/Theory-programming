#include "Enemy.h"
#include "Items.h"
#include "UnlifeObject.h"
#include "EntityVar.h"

void initializeEntitys(TypeEnemy *typesEnemy, std::vector<Enemy> &enemy, int countEnemy,
											 Item &emptyItem, UnlifeObject &emptyObject)// ���������� �������� 
{

	srand(time(0)); // �������������� �����������
									//////////////////////////////////////////////////////////////
									// �����
	Enemy* addEnemy = new Enemy();

	TypeEnemy* typeEnemy = &typesEnemy[idEnemy::wolfEnemy];
	
	int xPos;
	int yPos;
	int levelFloor;

	for (size_t i = 0; i < 1; i++) {
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

	for (size_t i = 0; i < 0; i++) {
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////