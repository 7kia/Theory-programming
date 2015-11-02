#include "Entity.h"
#include <list>
#include "Items.h"
#include "Map.h"
#include "ListObjectsAndBlocks.h"
#include "EntityVar.h"

using namespace sf;
using namespace std;

////////////////////////////////////////////////////////////////////
// Передвижение. Его анимация и озвучка
void Entity::update(const Time & deltaTime, dataSound &databaseSound)
{

	////////////////////////////////////////////////////////////////////
	// Обновление показателей 
	if (inputDamage) {
		timeInputDamage += deltaTime.asSeconds();
		printf("damage %d time %f\n", inputDamage, timeInputDamage);

		if (timeInputDamage > TIME_ATTENTION_SHOW_DAMAGE) {
			timeInputDamage = 0;
			inputDamage = 0;
		}

	}

	///////////////////////////////////////
	// Маны
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
	///////////////////////////////////////
	// Выносливости
	timeForStamina += deltaTime.asSeconds();

	if (timeForStamina > timeUpdateStamina) {
		timeForStamina = 0;

		if (needMinusStamina && direction != Direction::NONE) {
			currentStamina -= delStamina;
		} else {
			currentStamina += addStamina;
		}
	}

	if (currentStamina < 1) {
		currentStamina = 0;
		needMinusStamina = false;
		stepCurrent = stepFirst;// Персонаж не может бегать
	}
	else if (currentStamina > maxStamina){
		currentStamina = maxStamina;
	}
	///////////////////////////////////////////////////
	// Здоровья
	timeForHealth += deltaTime.asSeconds();

	if (timeForHealth > timeUpdateHealth) {
		timeForHealth = 0;

		if (needMinusHealth) {
			currentHealth -= delHealth;
		}
		else {
			currentHealth += addHealth;
		}
	}

	if (currentHealth < 1) {
		isDeath = true;
	} else if (currentHealth > maxHealth) {
		currentHealth = maxHealth;
	}
	///////////////////////////////////////
	// жажды
	timeForHungry += deltaTime.asSeconds();
	
	if (timeForHungry > timeUpdateThirst) {
		timeForHungry = 0;
		currentThirst--;
		//printf("%d\n", currentThirst);// ИСПРАВЬ
	}

	if (currentThirst > maxThirst) {
		currentThirst = maxThirst;
	}
	///////////////////////////////////////
	// голода
	timeForThirst += deltaTime.asSeconds();
	if (timeForThirst > timeUpdateHungry) {
		timeForThirst = 0;
		currentHungry--;
		//printf("%d\n", currentHungry);// ИСПРАВЬ
	}

	if (currentHungry > maxHungry) {
		currentHungry = maxHungry;
	}
	// Персонаж умирает от голода или жажды
	if (currentHungry > 0 && currentThirst > 0) {
		needMinusHealth = false;
	}
	else {
		needMinusHealth = true;
	}
	///////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////

	float pauseStep = 5, resetAnimation = 4;

	if (currenMode == idEntityMode::walk) {
		switch (direction) {
		case UP_LEFT:
			directionLook = UP_LEFT;
			movement.y = -stepCurrent;
			movement.x = -stepCurrent;

			playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

			timeAnimation += deltaTime.asSeconds() * pauseStep;
			resetTimeAnimation(timeAnimation, resetAnimation);


			spriteEntity->setTextureRect(IntRect(2 * width, height * int(timeAnimation), -width, height));
			break;
		case UP_RIGHT:
			directionLook = UP_RIGHT;
			movement.y = -stepCurrent;
			movement.x = stepCurrent;

			playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

			timeAnimation += deltaTime.asSeconds() * pauseStep;
			resetTimeAnimation(timeAnimation, resetAnimation);

			spriteEntity->setTextureRect(IntRect(width, height * int(timeAnimation), width, height));
			break;
		case UP:
			directionLook = UP;
			movement.y = -stepCurrent;

			playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

			timeAnimation += deltaTime.asSeconds() * pauseStep;
			resetTimeAnimation(timeAnimation, resetAnimation);

			spriteEntity->setTextureRect(IntRect(0, height * int(timeAnimation), width, height));
			break;
		case DOWN_LEFT:
			directionLook = DOWN_LEFT;
			movement.y = stepCurrent;
			movement.x = -stepCurrent;

			playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

			timeAnimation += deltaTime.asSeconds() * pauseStep;
			resetTimeAnimation(timeAnimation, resetAnimation);



			spriteEntity->setTextureRect(IntRect(4 * width, height * int(timeAnimation), -width, height));
			break;
		case DOWN_RIGHT:
			directionLook = DOWN_RIGHT;
			movement.y = stepCurrent;
			movement.x = stepCurrent;

			playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

			timeAnimation += deltaTime.asSeconds() * pauseStep;
			resetTimeAnimation(timeAnimation, resetAnimation);

			spriteEntity->setTextureRect(IntRect(3 * width, height * int(timeAnimation), width, height));
			break;
		case DOWN:
			directionLook = DOWN;
			movement.y = stepCurrent;

			playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

			timeAnimation += deltaTime.asSeconds() * pauseStep;
			resetTimeAnimation(timeAnimation, resetAnimation);

			spriteEntity->setTextureRect(IntRect(4 * width, height * int(timeAnimation), width, height));
			break;
		case LEFT:
			directionLook = LEFT;
			movement.x = -stepCurrent;

			playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

			timeAnimation += deltaTime.asSeconds() * pauseStep;
			resetTimeAnimation(timeAnimation, resetAnimation);

			spriteEntity->setTextureRect(IntRect(3 * width, height * int(timeAnimation), -width, height));
			break;
		case RIGHT:
			directionLook = RIGHT;
			movement.x = stepCurrent;

			playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

			timeAnimation += deltaTime.asSeconds() * pauseStep;
			resetTimeAnimation(timeAnimation, resetAnimation);

			spriteEntity->setTextureRect(IntRect(2 * width, height * int(timeAnimation), width, height));
			break;
		case NONE:
			movement.x = 0;
			movement.y = 0;
			break;
		default:
			break;
		}
	}


	if(currentTimeOutputDamage > 0)
	{
		resetAnimation = 3;
		int shiftAnimation = 4;
		switch (directionLook) {
		case UP_LEFT:
			// TODO
			//playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

			//currentTimeOutputDamage += deltaTime.asSeconds() * pauseStep;
			//resetTimeAnimation(currentTimeOutputDamage, resetAnimation);

			spriteEntity->setTextureRect(IntRect(2 * width, height * (int(currentTimeOutputDamage * resetAnimation) + shiftAnimation), -width, height));
			break;
		case UP_RIGHT:
			//playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

			//currentTimeOutputDamage += deltaTime.asSeconds() * pauseStep;
			//resetTimeAnimation(currentTimeOutputDamage, resetAnimation);

			spriteEntity->setTextureRect(IntRect(width, height * (int(currentTimeOutputDamage * resetAnimation) + shiftAnimation), width, height));
			break;
		case UP:
			//playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

			//currentTimeOutputDamage += deltaTime.asSeconds() * pauseStep;
			//resetTimeAnimation(currentTimeOutputDamage, resetAnimation);

			spriteEntity->setTextureRect(IntRect(0, height * (int(currentTimeOutputDamage * resetAnimation) + shiftAnimation), width, height));
			break;
		case DOWN_LEFT:
			//playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

			//currentTimeOutputDamage += deltaTime.asSeconds() * pauseStep;
			//resetTimeAnimation(currentTimeOutputDamage, resetAnimation);

			spriteEntity->setTextureRect(IntRect(4 * width, height * (int(currentTimeOutputDamage * resetAnimation) + shiftAnimation), -width, height));
			break;
		case DOWN_RIGHT:
			//playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

			//currentTimeOutputDamage += deltaTime.asSeconds() * pauseStep;
			resetTimeAnimation(currentTimeOutputDamage, resetAnimation);

			spriteEntity->setTextureRect(IntRect(3 * width, height * (int(currentTimeOutputDamage * resetAnimation) + shiftAnimation), width, height));
			break;
		case DOWN:
			//playSound(currentTimeOutputDamage, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

			//currentTimeOutputDamage += deltaTime.asSeconds() * pauseStep;
			//resetTimeAnimation(currentTimeOutputDamage, resetAnimation);

			spriteEntity->setTextureRect(IntRect(4 * width, height * (int(currentTimeOutputDamage * resetAnimation) + shiftAnimation), width, height));
			break;
		case LEFT:
			//playSound(currentTimeOutputDamage, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

			//currentTimeOutputDamage += deltaTime.asSeconds() * pauseStep;
			//resetTimeAnimation(currentTimeOutputDamage, resetAnimation);

			spriteEntity->setTextureRect(IntRect(3 * width, height * (int(currentTimeOutputDamage * resetAnimation) + shiftAnimation), -width, height));
			break;
		case RIGHT:
			//playSound(currentTimeOutputDamage, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

			//currentTimeOutputDamage += deltaTime.asSeconds() * pauseStep;
			//resetTimeAnimation(currentTimeOutputDamage, resetAnimation);

			spriteEntity->setTextureRect(IntRect(2 * width, height * (int(currentTimeOutputDamage * resetAnimation) + shiftAnimation), width, height));
			break;
		default:
			break;
		}
	}
}

void Entity::playSound(float time, float &start, const int idSound)
{
	if (time == start)
	{
		soundsEntity[idSound]->play();
	}
}

void Entity::resetTimeAnimation(float &time, float &reset)
{
	if (time > reset)
	{
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

	if (direction >= Direction::UP_LEFT)
	{
		// Чтобы скорость по диагонали была равной скорости по вертикали и горизонтали
		x = getXPos() + DIAGONAL_SCALE_SPEED * dx * deltaTime.asSeconds();
		y = getYPos() + DIAGONAL_SCALE_SPEED * dy * deltaTime.asSeconds();
	}
	else
	{
		x = getXPos() + dx * deltaTime.asSeconds();
		y = getYPos() + dy * deltaTime.asSeconds();
	}

	// Проверка на выход за карту
	if ( ((x < (SIZE_BLOCK * WIDTH_MAP)) && (x > 0))
		&& (y < (SIZE_BLOCK * (LONG_MAP - 1)) && (y > 0)) )
	{
		wchar_t *charBlocks = field.charBlocks;
		wchar_t(*map)[LONG_MAP][WIDTH_MAP] = field.dataMap;

		bool isSlowingBlock = false;
		/////////////////////////////////////////////
		// Проверяем окружающие объекты
		for (int i = y / SIZE_BLOCK; i < (y + height) / SIZE_BLOCK; i++) {
			for (int j = x / SIZE_BLOCK; j < (x + width) / SIZE_BLOCK; j++) {
				// Замедляющие блоки
				if (wcschr(listDestroy.slowingBlocks, map[currentLevelFloor + 1][i][j])) {// ИСПРАВЬ
					stepCurrent = stepFirst / slowingStep;
					isSlowingBlock = true;
					needMinusStamina = false;
					break;
				} else if (stepCurrent == stepFirst / slowingStep) {
					stepCurrent = stepFirst;
				}



				// Проверяем по списку проходимых блоков
				if (wcschr(listDestroy.passableBlocks, map[currentLevelFloor + 1][i][j]) == NULL) {
					x = getXPos();
					y = getYPos();
					direction = Direction::NONE;
					break;
				}

			}
		}
		/////////////////////////////////////////////

		/////////////////////////////////////////////
		// Проверяем пол
		
			for (int i = y / SIZE_BLOCK; i < (y + height) / SIZE_BLOCK; i++) {
				for (int j = x / SIZE_BLOCK; j < (x + width) / SIZE_BLOCK; j++) {

					
					// Замедляющие блоки
					if (wcschr(listDestroy.slowingBlocks, map[currentLevelFloor][i][j])) {// ИСПРАВЬ
						stepCurrent = stepFirst / slowingStep;
						needMinusStamina = false;
						break;
					} else if (stepCurrent == stepFirst / slowingStep && !isSlowingBlock) {
						stepCurrent = stepFirst;
					}
					
					// Является непроходимым
					if (wcschr(listDestroy.notPassableFloor, map[currentLevelFloor][i][j]) != NULL) {
						x = getXPos();
						y = getYPos();
						direction = Direction::NONE;
						break;
					}

				}
			}
		
		/////////////////////////////////////////////
	}
	else
	{
		x = getXPos();
		y = getYPos();
		direction = Direction::NONE;
	}

	spriteEntity->setPosition(x, y);
}

bool Entity::isEmptySlot()
{
	for (int i = 0; i < AMOUNT_ACTIVE_SLOTS; i++) {
		if (itemFromPanelQuickAccess[i].typeItem == emptyItem->typeItem) {
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

	bool checkX = (((getXPos() + width / 2) / SIZE_BLOCK) + radiusUse > xPosBlock)
		&& (((getXPos() + width / 2) / SIZE_BLOCK) - (radiusUse + 1) <= xPosBlock);

	bool checkY = (((getYPos() + height / 2) / SIZE_BLOCK) + radiusUse > yPosBlock)
		&& (((getYPos() + height / 2) / SIZE_BLOCK) - (radiusUse + 1) <= yPosBlock);

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

	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			// Если над лестницей стена не переходим
			if (i == 0 && j == 0)
			{// Если спускаемся блок лестницы не проверяем
				if (isExitFromBorder(x, y) == false && Level != currentLevelFloor)
				{
					if (map[Level][y][x] != charBlocks[idBlocks::air])
					{
						return{ -1, -1 };
					}
				}
			}
			else
			{
				if (isExitFromBorder(x + i, y + j) == false)
				{
					// Проверка стены
					if (Level != currentLevelFloor)
					{
						// Проверяем пол и стену над ним
						if (map[Level][y + j][x + i] != charBlocks[idBlocks::air]
							&& (map[Level + 1][y + j][x + i] == charBlocks[idBlocks::air]
							||	map[Level + 1][y + j][x + i] == charBlocks[idBlocks::woodLadder]))// ИСПРАВЬ
						{
							return{ x + i, y + j };
						}
					}
					else
					{// Проверяем пол
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
		&& (y < (SIZE_BLOCK * (LONG_MAP - 1)) && (y > 0)))
	{
		return false;
	}
	return true;
}
////////////////////////////////////////////////////////////////////