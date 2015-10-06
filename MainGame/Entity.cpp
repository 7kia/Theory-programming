#include "Entity.h"

using namespace sf;

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
		x = getXPos() + 0.6 * dx * deltaTime.asSeconds();
		y = getYPos() + 0.6 * dy * deltaTime.asSeconds();
	}
	else
	{
		x = getXPos() + dx * deltaTime.asSeconds();
		y = getYPos() + dy * deltaTime.asSeconds();
	}

	// �������� �� ����� �� �����
	if ( ((x < (sizeTile * WidthMap)) && (x > 0))
		&& (y < (sizeTile * (LongMap - 1)) && (y > 0)) )
	{
		wchar_t *charBlocks = field.charBlocks;
		wchar_t(*map)[LongMap][WidthMap] = field.dataMap;

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
		for (int i = y / sizeTile; i < (y + height) / sizeTile; i++)
		{
			for (int j = x / sizeTile; j < (x + width) / sizeTile; j++)
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
		for (int i = y / sizeTile; i < (y + height) / sizeTile; i++)
		{
			for (int j = x / sizeTile; j < (x + width) / sizeTile; j++)
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

void Entity::interactionWitnUnlifeObject(UnlifeObjects &unlifeObjects, const Time & deltaTime)
{
	float dx(movement.x);
	float dy(movement.y);

	float x;
	float y;
	x = getXPos();// +dx * deltaTime.asSeconds();
	y = getYPos();// +dy * deltaTime.asSeconds();

	// �������� �� ����� �� �����
	if (((x < (sizeTile * WidthMap)) && (x >  0))
		&& (y < (sizeTile * (LongMap - 1)) && (y >  0)))
	{
		for (size_t i = 0; i < unlifeObjects.countObject; i++)
		{
			

			int levelUnlifeObject = unlifeObjects.unlifeObject[i].currentLevel;

			Sprite *spriteObject = unlifeObjects.unlifeObject[i].spriteObject;
			FloatRect objectBound = spriteObject->getGlobalBounds();
			FloatRect entityBound = spriteEntity->getGlobalBounds();

			if (entityBound.intersects(objectBound) && (levelUnlifeObject == currentLevelFloor + 1) )
			{
				/*
				switch (direction)
				{
				///*
				case UP_LEFT:
					y += objectBound.top + objectBound.height - entityBound.top;
					x += objectBound.left + objectBound.width - entityBound.left;
					break;
				case UP_RIGHT:
					y += objectBound.top + objectBound.height - entityBound.top;
					x -= objectBound.left + objectBound.width - entityBound.left;
					break;
				case DOWN_LEFT:
					y -= objectBound.top + objectBound.height - entityBound.top;
					x += objectBound.left + objectBound.width - entityBound.left;
					break;
				case DOWN_RIGHT:
					y -= objectBound.top + objectBound.height - entityBound.top;
					x -= objectBound.left + objectBound.width - entityBound.left;
					break;

				case UP:
					y += objectBound.top + objectBound.height - entityBound.top;
					break;
				case DOWN:
					y -= entityBound.top + entityBound.height - objectBound.top;
					break;
				case LEFT:
					x += objectBound.left + objectBound.width - entityBound.left;
					break;
				case RIGHT:
					x -= entityBound.left + entityBound.width - objectBound.left;
					break;

				///

				}
				//*/
				if (direction >= Direction::UP_LEFT)
				{
					// ����� �������� �� ��������� ���� ������ �������� �� ��������� � �����������
					x -=  0.6 * dx * deltaTime.asSeconds();
					y -=  0.6 * dy * deltaTime.asSeconds();
				}
				else
				{
					x -=  dx * deltaTime.asSeconds();
					y -=  dy * deltaTime.asSeconds();
				}
				direction = Direction::NONE;
				break;
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

Vector2i  Entity::isEmptyFloor(Field &field, int Level)
{
	int x = getXPos() / sizeTile;
	int y = getYPos() / sizeTile;

	wchar_t *charBlocks = field.charBlocks;
	wchar_t(*map)[LongMap][WidthMap] = field.dataMap;

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
							&& map[Level + 1][y + j][x + i] == charBlocks[idBlocks::air])
						{
							return{ x + i, y + j };
						}
					}
					else
					{// ��������� ���
						if (map[Level][y + j][x + i] == charBlocks[idBlocks::air])
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

	if (((x < (sizeTile * WidthMap)) && (x > 0))
		&& (y < (sizeTile * (LongMap - 1)) && (y > 0)))
	{
		return false;
	}
	return true;
}
////////////////////////////////////////////////////////////////////