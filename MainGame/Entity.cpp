
#include <list>
#include "Items.h"
#include "Map.h"
#include "ListObjectsAndBlocks.h"
#include "EntityVar.h"
#include "Entity.h"
#include "Font.h"

using namespace sf;
using namespace std;


void entityProtection::init(float cut, float crash)
{
	protectionCut = cut;
	protectionCrash = crash;
}

void foundObjects::init(Item *item, UnlifeObject *object)
{
	emptyItem = item;
	emptyObject = object;
	findItem = emptyItem;
	findObject = emptyObject;
}

void entityMana::update(const sf::Time deltaTime)
{
	timeForMana += deltaTime.asSeconds();

	if (timeForMana > timeUpdateMana) {
		timeForMana = 0;

		if (needMinusMana) {
			currentMana -= delMana;
		} else {
			currentMana += addMana;
		}
	}

	if (currentMana < 1) {
		currentMana = 0;
	} else if (currentMana > maxMana) {
		currentMana = maxMana;
	}
}

void Step::init(float first)
{
	stepFirst = first;
	stepCurrent = stepFirst;
}

void DamageInputAndOutput::init(int cut, int crush, float time, float mult)
{
	cuttingDamage = cut;
	crushingDamage = crush;
	timeOutputDamage = time;
	damageMultiplirer = mult;

	timeInputDamage = 0.f;
}

void entityAnimation::init(float input, float output)
{
	timeAnimation = 0.f;
	timeFightAnimation = 0.f;

	timeOutputDamage = input;
	currentTimeFightAnimation = output;
}

void entityAnimation::updateFight(const sf::Time deltaTime)
{
	if (currentTimeFightAnimation) {
		currentTimeFightAnimation += deltaTime.asSeconds();

		if (currentTimeFightAnimation > timeOutputDamage) {
			currentTimeFightAnimation = 0;
		}

	}
};

void DamageInputAndOutput::updateInputDamage(const sf::Time deltaTime)
{
	if (inputDamage) {
		timeInputDamage += deltaTime.asSeconds();
		printf("damage %d time %f\n", inputDamage, timeInputDamage);

		if (timeInputDamage > TIME_ATTENTION_SHOW_DAMAGE) {
			timeInputDamage = 0;
			inputDamage = 0;
		}

	}
};

void entityStamina::update(const sf::Time deltaTime, Direction directionWalk, Step &step)
{
	timeForStamina += deltaTime.asSeconds();

	if (timeForStamina > timeUpdateStamina) {
		timeForStamina = 0;

		if (needMinusStamina && directionWalk != NONE_DIRECTION) {
			currentStamina -= delStamina;
		} else {
			currentStamina += addStamina;
		}
	}

	if (currentStamina < 1) {
		currentStamina = 0;
		needMinusStamina = false;
		step.stepCurrent = step.stepFirst;// Персонаж не может бегать
	} else if (currentStamina > maxStamina) {
		currentStamina = maxStamina;
	}

};

void entityHealth::update(const sf::Time deltaTime, bool &isDeath)
{
	timeForHealth += deltaTime.asSeconds();

	if (timeForHealth > timeUpdateHealth) {
		timeForHealth = 0;

		if (needMinusHealth) {
			currentHealth -= delHealth;
		} else {
			currentHealth += addHealth;
		}
	}

	if (currentHealth < 1) {
		isDeath = true;
	} else if (currentHealth > maxHealth) {
		currentHealth = maxHealth;
	}

};

void entityHungry::update(const sf::Time deltaTime, bool &needMinusHealth)
{
	timeForHungry += deltaTime.asSeconds();

	if (timeForHungry > timeUpdateHungry) {
		timeForHungry = 0;
		currentHungry--;
		//printf("%d\n", currentThirst);// ИСПРАВЬ
	}

	if (currentHungry > maxHungry) {
		currentHungry = maxHungry;
	}

	if (currentHungry > 0) {
		needMinusHealth = false;
	} else {
		needMinusHealth = true;
	}
};

void entityThirst::update(const sf::Time deltaTime, bool &needMinusHealth)
{
	timeForThirst += deltaTime.asSeconds();

	if (timeForThirst > timeUpdateThirst) {
		timeForThirst = 0;
		currentThirst--;
		//printf("%d\n", currentThirst);// ИСПРАВЬ
	}

	if (currentThirst > maxThirst) {
		currentThirst = maxThirst;
	}

	if (currentThirst > 0) {
		needMinusHealth = false;
	} else {
		needMinusHealth = true;
	}
};

////////////////////////////////////////////////////////////////////
// Передвижение. Его анимация и озвучка
void Entity::update(const Time & deltaTime, dataSound &databaseSound)
{

	/*
	if (outputDamage) {
	currentTimeFightAnimation += deltaTime.asSeconds();
	if (currentTimeFightAnimation > timeOutputDamage) {
	currentTimeFightAnimation = 0;

	outputDamage = 0;
	}
	}
	*/
	animation.updateFight(deltaTime);
	damage.updateInputDamage(deltaTime);
	mana.update(deltaTime);
	stamina.update(deltaTime, directions.directionWalk, step);
	health.update(deltaTime, isDeath);
	hungry.update(deltaTime, health.needMinusHealth);
	thirst.update(deltaTime, health.needMinusHealth);

	///////////////////////////////////////
	if (currenMode == idEntityMode::walk) {
		switch (directions.directionWalk) {
		case UP_LEFT:
			directions.directionLook = UP_LEFT;
			movement.y = -step.stepCurrent;
			movement.x = -step.stepCurrent;
			break;
		case UP_RIGHT:
			directions.directionLook = UP_RIGHT;
			movement.y = -step.stepCurrent;
			movement.x = step.stepCurrent;
			break;
		case UP:
			directions.directionLook = UP;
			movement.y = -step.stepCurrent;
			break;
		case DOWN_LEFT:
			directions.directionLook = DOWN_LEFT;
			movement.y = step.stepCurrent;
			movement.x = -step.stepCurrent;
			break;
		case DOWN_RIGHT:
			directions.directionLook = DOWN_RIGHT;
			movement.y = step.stepCurrent;
			movement.x = step.stepCurrent;
			break;
		case DOWN:
			directions.directionLook = DOWN;
			movement.y = step.stepCurrent;
			break;
		case LEFT:
			directions.directionLook = LEFT;
			movement.x = -step.stepCurrent;
			break;
		case RIGHT:
			directions.directionLook = RIGHT;
			movement.x = step.stepCurrent;
			break;
		case NONE_DIRECTION:
			movement.x = 0;
			movement.y = 0;
			break;
		default:
			break;
		}

		if (directions.directionWalk) {
			playAnimationWalk(deltaTime, databaseSound);
		}

	}


	if (animation.currentTimeFightAnimation > 0) {
		playAnimationAtack(deltaTime, databaseSound);

	}
}

void Entity::playAnimationWalk(const Time& deltaTime, dataSound& databaseSound)
{
	float pauseStep = 5, resetAnimation = 4;

	//playSound(animation.timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

	animation.timeAnimation += deltaTime.asSeconds() * pauseStep;
	resetTimeAnimation(animation.timeAnimation, resetAnimation);
	playSound(animation.timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

	int shiftWidth = directions.directionLook / 6;// TODO

	int currentWidth = size.width;
	int xPos = currentWidth * (directions.directionLook - 1 - shiftWidth * 3);//

	if (shiftWidth) {
		currentWidth *= -1;
	}

	spriteEntity->setTextureRect(IntRect(xPos, size.height * int(animation.timeAnimation), currentWidth, size.height));
}

void Entity::playAnimationAtack(const Time& deltaTime, dataSound& databaseSound)
{
	float pauseStep = 5, resetAnimation = 3;
	int shiftAnimation = 4;


	animation.timeAnimation += deltaTime.asSeconds() * pauseStep;
	resetTimeAnimation(animation.timeAnimation, resetAnimation);

	int shiftWidth = directions.directionLook / 6;// TODO

	int currentWidth = size.width;
	int xPos = currentWidth * (directions.directionLook - 1 - shiftWidth * 3);//

	if (shiftWidth) {
		currentWidth *= -1;
	}

	spriteEntity->setTextureRect(IntRect(xPos, size.height * (int(animation.currentTimeFightAnimation * resetAnimation) + shiftAnimation),
															 currentWidth, size.height));
}

void Entity::playSound(float time, float &start, const int idSound)
{
	if (time == start) {
		soundsEntity[idSound]->play();
		soundsEntity[idSound]->setPosition(getXPos(), getYPos(), 0);
	}
}

void Entity::resetTimeAnimation(float &time, float &reset)
{
	if (time > reset) {
		time = 0;
	}
}
////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
// Вспомагательные функции
float Entity::getXPos()
{
	return spriteEntity->getPosition().x;
}

float Entity::getYPos()
{
	return spriteEntity->getPosition().y;
}
////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
// Взаимодейтсвие с миром
void Entity::interactionWithMap(Field &field, destroyObjectsAndBlocks& listDestroy, const Time & deltaTime)
{

	float dx(movement.x);
	float dy(movement.y);

	float x;
	float y;

	bool isCollision(false);

	if (directions.directionWalk >= Direction::UP_LEFT) {
		// Чтобы скорость по диагонали была равной скорости по вертикали и горизонтали
		x = getXPos() + DIAGONAL_SCALE_SPEED * dx * deltaTime.asSeconds();
		y = getYPos() + DIAGONAL_SCALE_SPEED * dy * deltaTime.asSeconds();
	} else {
		x = getXPos() + dx * deltaTime.asSeconds();
		y = getYPos() + dy * deltaTime.asSeconds();
	}

	// Проверка на выход за карту
	if (((x < (SIZE_BLOCK * WIDTH_MAP)) && (x > 0))
			&& (y < (SIZE_BLOCK * (LONG_MAP - 1)) && (y > 0))) {
		wchar_t *charBlocks = field.charBlocks;
		wchar_t(*map)[LONG_MAP][WIDTH_MAP] = field.dataMap;

		bool isSlowingBlock = false;
		/////////////////////////////////////////////
		// Проверяем окружающие объекты
		for (int i = y / SIZE_BLOCK; i < (y + size.height) / SIZE_BLOCK; i++) {
			for (int j = x / SIZE_BLOCK; j < (x + size.width) / SIZE_BLOCK; j++) {
				// Замедляющие блоки
				if (wcschr(listDestroy.slowingBlocks, map[currentLevelFloor + 1][i][j])) {// ИСПРАВЬ
					step.stepCurrent = step.stepFirst / slowingStep;
					isSlowingBlock = true;
					stamina.needMinusStamina = false;
					break;
				} else if (step.stepCurrent == step.stepFirst / slowingStep) {
					step.stepCurrent = step.stepFirst;
				}



				// Проверяем по списку проходимых блоков
				if (wcschr(listDestroy.passableBlocks, map[currentLevelFloor + 1][i][j]) == NULL) {
					x = getXPos();
					y = getYPos();
					directions.directionWalk = NONE_DIRECTION;
					break;
				}

			}
		}
		/////////////////////////////////////////////

		/////////////////////////////////////////////
		// Проверяем пол

		for (int i = y / SIZE_BLOCK; i < (y + size.height) / SIZE_BLOCK; i++) {
			for (int j = x / SIZE_BLOCK; j < (x + size.width) / SIZE_BLOCK; j++) {


				// Замедляющие блоки
				if (wcschr(listDestroy.slowingBlocks, map[currentLevelFloor][i][j])) {// ИСПРАВЬ
					step.stepCurrent = step.stepFirst / slowingStep;
					stamina.needMinusStamina = false;
					break;
				} else if (step.stepCurrent == step.stepFirst / slowingStep && !isSlowingBlock) {
					step.stepCurrent = step.stepFirst;
				}

				// Является непроходимым
				if (wcschr(listDestroy.notPassableFloor, map[currentLevelFloor][i][j]) != NULL) {
					x = getXPos();
					y = getYPos();
					directions.directionWalk = NONE_DIRECTION;
					break;
				}

			}
		}

		/////////////////////////////////////////////
	} else {
		x = getXPos();
		y = getYPos();
		directions.directionWalk = NONE_DIRECTION;
	}

	spriteEntity->setPosition(x, y);
}

bool Entity::isEmptySlot()
{
	for (int i = 0; i < AMOUNT_ACTIVE_SLOTS; i++) {
		if (itemFromPanelQuickAccess[i].typeItem == founds.emptyItem->typeItem) {
			emptySlot = i;
			return true;
		}
	}
	return false;
}


//////////////////////////////////////////////////////
// Поиск неживого объекта
bool isObject(float x, float y, std::vector<UnlifeObject> &unlifeObjects, UnlifeObject &findObject,
							int &findObjectFromList, int &current, int currentLevel)
{
	int levelObject = unlifeObjects[current].currentLevel;

	Sprite *spriteObject = unlifeObjects[current].spriteObject;
	FloatRect objectBound = spriteObject->getGlobalBounds();

	if (objectBound.contains(x, y) && levelObject == currentLevel) {
		findObject = unlifeObjects[current];
		findObjectFromList = current;
		return true;
	}
	return false;
}
//////////////////////////////////////////////////////
// Поиск предмета
bool isItem(float x, float y, vector<Item> &items, Item &findItem, int &findItemFromList, int currentLevel)
{
	int levelItem = items[findItemFromList].currentLevel;

	Sprite *spriteItem = items[findItemFromList].mainSprite;
	FloatRect objectItem = spriteItem->getGlobalBounds();

	if (objectItem.contains(x, y) && levelItem == currentLevel) {
		return true;
	}
	return false;
}
//////////////////////////////////////////////////////

bool Entity::isInUseField(float x, float y, bool under)
{
	int xPosBlock = x / SIZE_BLOCK;
	int yPosBlock = y / SIZE_BLOCK;

	bool checkX = (((getXPos() + size.width / 2) / SIZE_BLOCK) + radiusUse > xPosBlock)
		&& (((getXPos() + size.width / 2) / SIZE_BLOCK) - (radiusUse + 1) <= xPosBlock);

	bool checkY = (((getYPos() + size.height / 2) / SIZE_BLOCK) + radiusUse > yPosBlock)
		&& (((getYPos() + size.height / 2) / SIZE_BLOCK) - (radiusUse + 1) <= yPosBlock);

	bool checkUnderPerson = xPosBlock == (((int)getXPos() + SIZE_BLOCK / 2) / SIZE_BLOCK)
		&& yPosBlock == (((int)getYPos() + SIZE_BLOCK / 2) / SIZE_BLOCK);

	if (checkX && checkY) {
		{
			if (checkUnderPerson && !under) return false;
			return true;
		}
	}

	return false;
}

Vector2i  Entity::isEmptyFloor(Field &field, int Level)
{
	int x = getXPos() / SIZE_BLOCK;
	int y = getYPos() / SIZE_BLOCK;

	wchar_t *charBlocks = field.charBlocks;
	wchar_t(*map)[LONG_MAP][WIDTH_MAP] = field.dataMap;

	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			// Если над лестницей стена не переходим
			if (i == 0 && j == 0) {// Если спускаемся блок лестницы не проверяем
				if (isExitFromBorder(x, y) == false && Level != currentLevelFloor) {
					if (map[Level][y][x] != charBlocks[idBlocks::air]) {
						return{ -1, -1 };
					}
				}
			} else {
				if (isExitFromBorder(x + i, y + j) == false) {
					// Проверка стены
					if (Level != currentLevelFloor) {
						// Проверяем пол и стену над ним
						if (map[Level][y + j][x + i] != charBlocks[idBlocks::air]
								&& (map[Level + 1][y + j][x + i] == charBlocks[idBlocks::air]
								|| map[Level + 1][y + j][x + i] == charBlocks[idBlocks::woodLadder]))// ИСПРАВЬ
						{
							return{ x + i, y + j };
						}
					} else {// Проверяем пол
						if (map[Level][y + j][x + i] == charBlocks[idBlocks::air]
								|| map[Level + 1][y + j][x + i] == charBlocks[idBlocks::woodLadder])// ИСПРАВЬ
						{
							return{ x + i, y + j };
						}
					}
				}
			}
		}

	}
	return{ -1, -1 };
}

bool Entity::isExitFromBorder(int x, int y)
{

	if (((x < (SIZE_BLOCK * WIDTH_MAP)) && (x > 0))
			&& (y < (SIZE_BLOCK * (LONG_MAP - 1)) && (y > 0))) {
		return false;
	}
	return true;
}
////////////////////////////////////////////////////////////////////
