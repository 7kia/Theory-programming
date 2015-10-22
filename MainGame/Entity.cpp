#include "Entity.h"

using namespace sf;
using namespace std;

////////////////////////////////////////////////////////////////////
// Передвижение. Его анимация и озвучка
void Entity::update(const Time & deltaTime, dataSound &databaseSound)
{
	///////////////////////////////////////
	// Оьновление показателей (голода)
	timeForBars += deltaTime.asSeconds();

	if (timeForBars > minusHungry) {
		timeForBars = 0;
		currentHungry--;
		printf("%d\n", currentHungry);
	}

	if (currentHungry < 1) {
		isDeath = true;
	}
	///////////////////////////////////////



	float pauseStep = 5, resetAnimation = 2;
	switch (direction)
	{
	case UP_LEFT:
		movement.y = -stepCurrent;
		movement.x = -stepCurrent;

		playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

		timeAnimation += deltaTime.asSeconds() * pauseStep;
		resetTimeAnimation(timeAnimation, resetAnimation);


		spriteEntity->setTextureRect(IntRect((int)timeAnimation *  width, height * 3, width, height));
		break;
	case UP_RIGHT:
		movement.y = -stepCurrent;
		movement.x = stepCurrent;

		playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

		timeAnimation += deltaTime.asSeconds() * pauseStep;
		resetTimeAnimation(timeAnimation, resetAnimation);

		spriteEntity->setTextureRect(IntRect((int)timeAnimation *  width, height * 3, width, height));
		break;
	case UP:
		movement.y = -stepCurrent;

		playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

		timeAnimation += deltaTime.asSeconds() * pauseStep;
		resetTimeAnimation(timeAnimation, resetAnimation);

		spriteEntity->setTextureRect(IntRect((int)timeAnimation *  width, height * 3, width, height));
		break;
	case DOWN_LEFT:
		movement.y = stepCurrent;
		movement.x = -stepCurrent;

		playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

		timeAnimation += deltaTime.asSeconds() * pauseStep;
		resetTimeAnimation(timeAnimation, resetAnimation);



		spriteEntity->setTextureRect(IntRect((int)timeAnimation *   width, 0, width, height));
		break;
	case DOWN_RIGHT:
		movement.y = stepCurrent;
		movement.x = stepCurrent;

		playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

		timeAnimation += deltaTime.asSeconds() * pauseStep;
		resetTimeAnimation(timeAnimation, resetAnimation);

		spriteEntity->setTextureRect(IntRect((int)timeAnimation *   width, 0, width, height));
		break;
	case DOWN:
		movement.y = stepCurrent;

		playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

		timeAnimation += deltaTime.asSeconds() * pauseStep;
		resetTimeAnimation(timeAnimation, resetAnimation);

		spriteEntity->setTextureRect(IntRect((int)timeAnimation * width, 0, width, height));
		break;
	case LEFT:
		movement.x = -stepCurrent;
		
		playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

		timeAnimation += deltaTime.asSeconds() * pauseStep;
		resetTimeAnimation(timeAnimation, resetAnimation);

		spriteEntity->setTextureRect(IntRect((int)timeAnimation *   width, height, width, height));
		break;
	case RIGHT:
		movement.x = stepCurrent;

		playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

		timeAnimation += deltaTime.asSeconds() * pauseStep;
		resetTimeAnimation(timeAnimation, resetAnimation);

		spriteEntity->setTextureRect(IntRect(((int)timeAnimation + 1) *   width, height, -width, height));
		break;
	default:
		break;
	}
}

void Entity::playSound(float time, float start, const int idSound)
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
void Entity::interactionWithMap(Field &field, const Time & deltaTime)
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

		/////////////////////////////////////////////
		// Проверяем окружающие объекты
		for (int i = y / SIZE_BLOCK; i < (y + height) / SIZE_BLOCK; i++)
		{
			for (int j = x / SIZE_BLOCK; j < (x + width) / SIZE_BLOCK; j++)
			{
				if (map[currentLevelFloor + 1][i][j] != charBlocks[idBlocks::air])
				{
					x = getXPos();
					y = getYPos();
					break;
				}

			}
		}
		/////////////////////////////////////////////

		/////////////////////////////////////////////
		// Проверяем пол
		for (int i = y / SIZE_BLOCK; i < (y + height) / SIZE_BLOCK; i++)
		{
			for (int j = x / SIZE_BLOCK; j < (x + width) / SIZE_BLOCK; j++)
			{
				if (map[currentLevelFloor][i][j] == charBlocks[idBlocks::air])
				{
					x = getXPos();
					y = getYPos();
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
	}

	spriteEntity->setPosition(x, y);
}

void Entity::interactionWitnUnlifeObject(list<UnlifeObject> *unlifeObjects, const Time & deltaTime)// ИСПРАВЬ for enity and mainPerson
{
	float dx(movement.x);
	float dy(movement.y);

	float x;
	float y;
	x = getXPos();
	y = getYPos();

	// Проверка на выход за карту
	if (((x < (SIZE_BLOCK * WIDTH_MAP)) && (x >  0))
		&& (y < (SIZE_BLOCK * (LONG_MAP - 1)) && (y >  0)))
	{
		for (std::list<UnlifeObject>::iterator it = unlifeObjects->begin(); it != unlifeObjects->end(); ++it)
		{
			int levelUnlifeObject = it->currentLevel;

			Sprite *spriteObject = it->spriteObject;
			FloatRect objectBound = spriteObject->getGlobalBounds();

			Sprite *transparentSpiteObject = it->transparentSpiteObject;
			FloatRect objectAltBound = transparentSpiteObject->getGlobalBounds();
			FloatRect entityBound = spriteEntity->getGlobalBounds();

			if (entityBound.intersects(objectBound) && (levelUnlifeObject == currentLevelFloor + 1) )
			{
				if (direction >= Direction::UP_LEFT)
				{
					// Чтобы скорость по диагонали была равной скорости по вертикали и горизонтали
					x -= DIAGONAL_SCALE_SPEED * dx * deltaTime.asSeconds();
					y -= DIAGONAL_SCALE_SPEED * dy * deltaTime.asSeconds();
				}
				else
				{
					x -=  dx * deltaTime.asSeconds();
					y -=  dy * deltaTime.asSeconds();
				}
				direction = Direction::NONE;
				break;
			}
			else if(entityBound.intersects(objectAltBound) && (levelUnlifeObject == currentLevelFloor + 1))
			{
				transparentSpiteObject->setColor(TRANSPARENT_COLOR);
			}
			else
			{
				transparentSpiteObject->setColor(NORMAL_COLOR);
			}

		}
	}
	else
	{
		x = (int)getXPos();
		y = (int)getYPos();
	}

	spriteEntity->setPosition(x, y);
	movement = { 0.f, 0.f };
}


//////////////////////////////////////////////////////
// Поиск неживого объекта
bool isObject(float x, float y, list<UnlifeObject> *unlifeObjects, UnlifeObject *&findObject, list<UnlifeObject>::iterator &findObjectFromList, list<UnlifeObject>::iterator &current, int currentLevel)
{
	int levelObject = current->currentLevel;

	Sprite *spriteObject = current->spriteObject;
	FloatRect objectBound = spriteObject->getGlobalBounds();

	if (objectBound.contains(x, y) && levelObject == currentLevel) {
		findObject = &*current;
		findObjectFromList = current;
		return true;
	}
	return false;
}
//////////////////////////////////////////////////////
// Поиск предмета
bool isItem(float x, float y, list<Item> &items, Item *&findItem, list<Item>::iterator &findItemFromList, list<Item>::iterator &current, int currentLevel)
{
	int levelItem = current->currentLevel;

	Sprite *spriteItem = current->mainSprite;
	FloatRect objectItem = spriteItem->getGlobalBounds();

	if (objectItem.contains(x, y) && levelItem == currentLevel) {
		findItem = &*current;
		findItemFromList = current;// ИСПРАВЬ
		return true;
	}
	return false;
}
//////////////////////////////////////////////////////

bool Entity::isInUseField(float x, float y)
{
	int xPosBlock = x / SIZE_BLOCK;
	int yPosBlock = y / SIZE_BLOCK;

	bool checkX = (((getXPos() + width / 2) / SIZE_BLOCK) + radiusUse > xPosBlock)
		&& (((getXPos() + width / 2) / SIZE_BLOCK) - (radiusUse + 1) <= xPosBlock);

	bool checkY = (((getYPos() + height / 2) / SIZE_BLOCK) + radiusUse > yPosBlock)
		&& (((getYPos() + height / 2) / SIZE_BLOCK) - (radiusUse + 1) <= yPosBlock);

	bool checkUnderPerson = xPosBlock != ( (int)getXPos() / SIZE_BLOCK)
		|| yPosBlock != ((int)getYPos() / SIZE_BLOCK);

	if (checkX && checkY && checkUnderPerson) return true;

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