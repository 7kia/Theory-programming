#include "Entity.h"

using namespace sf;
using namespace std;

////////////////////////////////////////////////////////////////////
// ������������. ��� �������� � �������
void Entity::update(const Time & deltaTime, dataSound &databaseSound)
{
	float pauseStep = 5, resetAnimation = 2;
	switch (direction)
	{
	///*
	case UP_LEFT:
		movement.y = -stepCurrent;
		movement.x = -stepCurrent;

		playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

		timeAnimation += deltaTime.asSeconds() * pauseStep;
		resetTimeAnimation(timeAnimation, resetAnimation);

		//getCoordinateForView(getXPos(), getYPos());

		spriteEntity->setTextureRect(IntRect((int)timeAnimation *  width, height * 3, width, height));
		break;
	case UP_RIGHT:
		movement.y = -stepCurrent;
		movement.x = stepCurrent;

		playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

		timeAnimation += deltaTime.asSeconds() * pauseStep;
		resetTimeAnimation(timeAnimation, resetAnimation);

		//getCoordinateForView(spriteObject->getPosition().x, spriteObject->getPosition().y);
		//getCoordinateForView(getXPos(), getYPos());

		spriteEntity->setTextureRect(IntRect((int)timeAnimation *  width, height * 3, width, height));
		break;
		//*/
	case UP:
		movement.y = -stepCurrent;

		playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

		timeAnimation += deltaTime.asSeconds() * pauseStep;
		resetTimeAnimation(timeAnimation, resetAnimation);

		

		spriteEntity->setTextureRect(IntRect((int)timeAnimation *  width, height * 3, width, height));
		break;
		///*
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
		//*/
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
// ��������������� �������
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
// �������������� � �����
void Entity::interactionWithMap(Field &field, const Time & deltaTime)
{
	
	float dx(movement.x);
	float dy(movement.y);

	float x;
	float y;

	bool isCollision(false);

	if (direction >= Direction::UP_LEFT)
	{
		// ����� �������� �� ��������� ���� ������ �������� �� ��������� � �����������
		x = getXPos() + diagonalScaleSpeed * dx * deltaTime.asSeconds();
		y = getYPos() + diagonalScaleSpeed * dy * deltaTime.asSeconds();
	}
	else
	{
		x = getXPos() + dx * deltaTime.asSeconds();
		y = getYPos() + dy * deltaTime.asSeconds();
	}

	// �������� �� ����� �� �����
	if ( ((x < (SIZE_BLOCK * WIDTH_MAP)) && (x > 0))
		&& (y < (SIZE_BLOCK * (LONG_MAP - 1)) && (y > 0)) )
	{
		wchar_t *charBlocks = field.charBlocks;
		wchar_t(*map)[LONG_MAP][WIDTH_MAP] = field.dataMap;

		/*
		//////////////////////////////////////////////
		// ���������� �� ���� �����, �� ���� �� ���� ����������� �������
		// ��� ����� �� 32, ��� ����� �������� ����� ���������, � �������
		// �������� �������������. (�� ���� ������ ������� 32*32, ������� �����
		//	������������ ������ �� ���������� ���������). � j<(x + w) / 32
		//	- ������� ����������� ��������� �� ����. �� ���� ���������� ������ 
		//	������� ��������, ������� ������������� � ����������. ����� �������
		//	���� � ����� ����� ������� �� ����, ������� �� �� ������ �������� 
		//	(���������������� � ������), �� ������� �������� (���������������� � ������)
		//
		///
		// �� �������� ���������� ����� ���������. ������� �������� ���������� 
		//������ ���������� �� �����(�����) � ����� �������� �� ������ ������� ���������.
		//////////////////////////////////////////////
		*/


		/////////////////////////////////////////////
		// ��������� ���������� �������
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
		// ��������� ���
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
	//movement = { 0.f, 0.f };
}

void Entity::interactionWitnUnlifeObject(list<UnlifeObject> *unlifeObjects, const Time & deltaTime)
{
	float dx(movement.x);
	float dy(movement.y);

	float x;
	float y;
	x = getXPos();// +dx * deltaTime.asSeconds();
	y = getYPos();// +dy * deltaTime.asSeconds();

	// �������� �� ����� �� �����
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
					// ����� �������� �� ��������� ���� ������ �������� �� ��������� � �����������
					x -= diagonalScaleSpeed * dx * deltaTime.asSeconds();
					y -= diagonalScaleSpeed * dy * deltaTime.asSeconds();
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
				transparentSpiteObject->setColor(Color(255, 255, 255, 127) );
			}
			else
			{
				transparentSpiteObject->setColor(Color(255, 255, 255, 255));
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
			// ���� ��� ��������� ����� �� ���������
			if (i == 0 && j == 0)
			{// ���� ���������� ���� �������� �� ���������
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
					// �������� �����
					if (Level != currentLevelFloor)
					{
						// ��������� ��� � ����� ��� ���
						if (map[Level][y + j][x + i] != charBlocks[idBlocks::air]
							&& (map[Level + 1][y + j][x + i] == charBlocks[idBlocks::air]
							||	map[Level + 1][y + j][x + i] == charBlocks[idBlocks::woodLadder]))// �������
						{
							return{ x + i, y + j };
						}
					}
					else
					{// ��������� ���
						if (map[Level][y + j][x + i] == charBlocks[idBlocks::air]
								|| map[Level + 1][y + j][x + i] == charBlocks[idBlocks::woodLadder])// �������
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