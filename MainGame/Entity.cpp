#include "Entity.h"

////////////////////////////////////////////////////////////////////
// Передвижение. Его анимация и озвучка
void Entity::update(const Time & deltaTime, dataSound &databaseSound)
{
	float pauseStep = 5, resetAnimation = 2;
	switch (direction)
	{
	/*
	case UP_LEFT:
		movement.y = -stepCurrent;
		movement.x = -stepCurrent;

		playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

		timeAnimation += deltaTime.asSeconds() * pauseStep;
		resetTimeAnimation(timeAnimation, resetAnimation);

		getCoordinateForView(getXPos(), getYPos());

		spriteObject->setTextureRect(IntRect((int)timeAnimation *  width, height * 3, width, height));
		break;
	case UP_RIGHT:
		movement.y = -stepCurrent;
		movement.x = stepCurrent;

		playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

		timeAnimation += deltaTime.asSeconds() * pauseStep;
		resetTimeAnimation(timeAnimation, resetAnimation);

		//getCoordinateForView(spriteObject->getPosition().x, spriteObject->getPosition().y);
		getCoordinateForView(getXPos(), getYPos());

		spriteObject->setTextureRect(IntRect((int)timeAnimation *  width, height * 3, width, height));
		break;
		*/
	case UP:
		movement.y = -stepCurrent;

		this->playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

		timeAnimation += deltaTime.asSeconds() * pauseStep;
		resetTimeAnimation(timeAnimation, resetAnimation);

		

		spriteObject->setTextureRect(IntRect((int)timeAnimation *  width, height * 3, width, height));
		break;
		/*
	case DOWN_LEFT:
		movement.y = stepCurrent;
		movement.x = -stepCurrent;

		playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

		timeAnimation += deltaTime.asSeconds() * pauseStep;
		resetTimeAnimation(timeAnimation, resetAnimation);



		spriteObject->setTextureRect(IntRect((int)timeAnimation *   width, 0, width, height));
		break;
	case DOWN_RIGHT:
		movement.y = stepCurrent;
		movement.x = stepCurrent;

		playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

		timeAnimation += deltaTime.asSeconds() * pauseStep;
		resetTimeAnimation(timeAnimation, resetAnimation);



		spriteObject->setTextureRect(IntRect((int)timeAnimation *   width, 0, width, height));
		break;
		*/
	case DOWN:
		movement.y = stepCurrent;

		playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

		timeAnimation += deltaTime.asSeconds() * pauseStep;
		resetTimeAnimation(timeAnimation, resetAnimation);



		spriteObject->setTextureRect(IntRect((int)timeAnimation * width, 0, width, height));
		break;
	case LEFT:
		movement.x = -stepCurrent;
		
		playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

		timeAnimation += deltaTime.asSeconds() * pauseStep;
		resetTimeAnimation(timeAnimation, resetAnimation);



		spriteObject->setTextureRect(IntRect((int)timeAnimation *   width, height, width, height));
		break;
	case RIGHT:
		movement.x = stepCurrent;

		playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

		timeAnimation += deltaTime.asSeconds() * pauseStep;
		resetTimeAnimation(timeAnimation, resetAnimation);



		spriteObject->setTextureRect(IntRect(((int)timeAnimation + 1) *   width, height, -width, height));
		break;
	default:
		break;
	}

	//spriteObject->move(movement * deltaTime.asSeconds());

	//movement = { 0.f, 0.f };
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
	return spriteObject->getPosition().x;
}

float Entity::getYPos()
{
	return spriteObject->getPosition().y;
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
	x = getXPos() + dx * deltaTime.asSeconds();
	y = getYPos() + dy * deltaTime.asSeconds();
	// Проверка на выход за карту
	if ( ((x < sizeTile * LongMap) && (x > 0))
		&& ((y < sizeTile * (WidthMap - 1)) && (y > 0)) )
	{
		wchar_t *charBlocks = field.charBlocks;
		wchar_t(*map)[LongMap][WidthMap] = field.dataMap;

		/*
		//////////////////////////////////////////////
		// проходимся по всей карте, то есть по всем квадратикам размера
		// икс делим на 32, тем самым получаем левый квадратик, с которым
		// персонаж соприкасается. (он ведь больше размера 32*32, поэтому может
		//	одновременно стоять на нескольких квадратах). А j<(x + w) / 32
		//	- условие ограничения координат по иксу. то есть координата самого 
		//	правого квадрата, который соприкасается с персонажем. таким образом
		//	идем в цикле слева направо по иксу, проходя по от левого квадрата 
		//	(соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
		//
		///
		// то стопорим координату игрек персонажа. сначала получаем координату 
		//нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
		//////////////////////////////////////////////
		*/


		/////////////////////////////////////////////
		// Проверяем окружающие объекты
		for (int i = y / sizeTile; i < (y + height / 2) / sizeTile; i++)
		{
			for (int j = x / sizeTile; j < (x + width / 2) / sizeTile; j++)
			{
				if (map[currentLevelFloor + 1][i][j] != charBlocks[idBlocks::air])
				{
					if (dy > 0)//если мы шли вниз,
					{

						y = i * sizeTile - height / 2;
					}
					if (dy < 0)
					{
						y = i * sizeTile + sizeTile;
					}
					if (dx > 0)
					{
						x = j * sizeTile - width / 2;
					}
					if (dx < 0)
					{
						x = j * sizeTile + sizeTile;//аналогично идем влево
					}
				}

			}
		}
		/////////////////////////////////////////////

		/////////////////////////////////////////////
		// Проверяем пол
		for (int i = y / sizeTile; i < (y + height / 2) / sizeTile; i++)
		{
			for (int j = x / sizeTile; j < (x + width / 2) / sizeTile; j++)
			{
				if (map[currentLevelFloor][i][j] == charBlocks[idBlocks::air])
				{
					if (dy > 0)//если мы шли вниз,
					{

						y = i * sizeTile - height / 2;
					}
					if (dy < 0)
					{
						y = i * sizeTile + sizeTile;
					}
					if (dx > 0)
					{
						x = j * sizeTile - width / 2;
					}
					if (dx < 0)
					{
						x = j * sizeTile + sizeTile;//аналогично идем влево
					}
				}

			}
		}
		/////////////////////////////////////////////
	}
	else
	{
		x = (int)getXPos();
		y = (int)getYPos();
	}

	spriteObject->setPosition(x, y);
	movement = { 0.f, 0.f };
}