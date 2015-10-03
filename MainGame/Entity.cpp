#include "Entity.h"

////////////////////////////////////////////////////////////////////
// ���������� ���������
void initializeEntity(Entity & Entity, dataSound &databaseSound)
{
	Entity.spriteObject = new Sprite;
	Entity.textureEntity = new Texture;

	// ������� �������

	Entity.height = 42;
	Entity.width = 22;

	// �������� ������
	Entity.stepFirst = 150.f;
	Entity.stepCurrent = 150.f;
	Entity.timeAnimation = 0.f;

	// ������
	int posX(70), posY(70);
	Entity.view = new View;
	Entity.view->setSize(640, 480);
	Entity.view->setCenter(posX, posY);

	// ��������
	Entity.textureEntity->loadFromFile("recourses\\images\\mainPerson.png");
	Entity.spriteObject->setTexture(*Entity.textureEntity);
	Entity.spriteObject->setTextureRect(IntRect(0, 0, Entity.width, Entity.height));

	// ����� 
	Entity.soundsEntity[idSoundEntity::stepGrass] = &databaseSound.sounds[idSoundEntity::stepGrass];
	Entity.soundsEntity[idSoundEntity::stepStone] = &databaseSound.sounds[idSoundEntity::stepStone];

	// ������� ��������� ��� �����
	Entity.idSelectItem = 0;

	// ������� � �����������
	Entity.currentLevelFloor = 0;
	Entity.currentLevel = 1;
	Entity.currenMode = idModeEntity::build;
	Entity.spriteObject->setOrigin(Entity.width / 2, Entity.height / 2);
	Entity.spriteObject->setPosition(posX, posY);
	Entity.direction = NONE;
}
////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
// View
void Entity::getCoordinateForView(float x, float y)//������� ��� ���������� ��������� ������
{ 
	view->setCenter(x, y);//������ �� �������, ��������� ��� ����������. 
}

// �������� ���������� (�� ��������)
void Entity::viewmap(float time)
{
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		view->move(0.1*time, 0);//�������� ����� ������ (�� ����, ����� �� ������� ����� - �� ���� �����)
	}

	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		view->move(0, 0.1*time);//�������� ����� ���� (�� ����, ����� �� ������� ����� - �� ���� �����)
	}

	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		view->move(-0.1*time, 0);//�������� ����� ����� (�� ����, ����� �� ������� ����� - �� ���� �����)
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		view->move(0, -0.1*time);//�������� ����� ������ (�� ����, ����� �� ������� ����� - �� ���� �����)
	}

}
// �������� ���������� (�� ��������)
void Entity::changeview()
{
	if (Keyboard::isKeyPressed(Keyboard::U)) {
		view->zoom(1.0100f); //������������, ����������
							//view.zoom(1.0006f); //���� ����� ����������� ��������������
	}

	if (Keyboard::isKeyPressed(Keyboard::R)) {
		//view.setRotation(90);//����� �� ������ ������� ������
		view->rotate(1);//���������� ������������ ������ (������������� �������� - � �������� �������)
	}


	if (Keyboard::isKeyPressed(Keyboard::I)) {
		view->setSize(640, 480);//������������� ������ ������ (��� ��������)
	}

	if (Keyboard::isKeyPressed(Keyboard::P)) {
		view->setSize(540, 380);//�������� ������ ������
	}

}
////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
// ������������. ��� �������� � �������
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

		getCoordinateForView(getXPos(), getYPos());

		spriteObject->setTextureRect(IntRect((int)timeAnimation *  width, height * 3, width, height));
		break;
		/*
	case DOWN_LEFT:
		movement.y = stepCurrent;
		movement.x = -stepCurrent;

		playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

		timeAnimation += deltaTime.asSeconds() * pauseStep;
		resetTimeAnimation(timeAnimation, resetAnimation);

		getCoordinateForView(getXPos(), getYPos());

		spriteObject->setTextureRect(IntRect((int)timeAnimation *   width, 0, width, height));
		break;
	case DOWN_RIGHT:
		movement.y = stepCurrent;
		movement.x = stepCurrent;

		playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

		timeAnimation += deltaTime.asSeconds() * pauseStep;
		resetTimeAnimation(timeAnimation, resetAnimation);

		getCoordinateForView(getXPos(), getYPos());

		spriteObject->setTextureRect(IntRect((int)timeAnimation *   width, 0, width, height));
		break;
		*/
	case DOWN:
		movement.y = stepCurrent;

		playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

		timeAnimation += deltaTime.asSeconds() * pauseStep;
		resetTimeAnimation(timeAnimation, resetAnimation);

		getCoordinateForView(getXPos(), getYPos());

		spriteObject->setTextureRect(IntRect((int)timeAnimation * width, 0, width, height));
		break;
	case LEFT:
		movement.x = -stepCurrent;
		
		playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

		timeAnimation += deltaTime.asSeconds() * pauseStep;
		resetTimeAnimation(timeAnimation, resetAnimation);

		getCoordinateForView(getXPos(), getYPos());

		spriteObject->setTextureRect(IntRect((int)timeAnimation *   width, height, width, height));
		break;
	case RIGHT:
		movement.x = stepCurrent;

		playSound(timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

		timeAnimation += deltaTime.asSeconds() * pauseStep;
		resetTimeAnimation(timeAnimation, resetAnimation);

		getCoordinateForView(getXPos(), getYPos());

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
// ��������������� �������
float Entity::getXPos()
{
	return spriteObject->getPosition().x;
}

float Entity::getYPos()
{
	return spriteObject->getPosition().y;
}

// ��������� ����� (�� ��������)
void Entity::computeAngle(RenderWindow &window)
{
	Vector2i pixelPos = Mouse::getPosition(window);//�������� ����� �������
	Vector2f pos = window.mapPixelToCoords(pixelPos);//��������� �� � ������� (������ �� ����� ����)

	float dX = pos.x - spriteObject->getPosition().x - width / 2;//������ , ����������� ������, ������� ���������� ������ � ������
	float dY = pos.y - spriteObject->getPosition().y - height / 2;//�� ��, ���������� y
	rotation = (atan2(dY, dX)) * 180 / 3.14159265;//�������� ���� � �������� � ��������� ��� � �������
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
	x = getXPos() + dx * deltaTime.asSeconds();
	y = getYPos() + dy * deltaTime.asSeconds();
	// �������� �� ����� �� �����
	if ( ((x < sizeTile * LongMap) && (x > 0))
		&& ((y < sizeTile * (WidthMap - 1)) && (y > 0)) )
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
		for (int i = y / sizeTile; i < (y + height / 2) / sizeTile; i++)
		{
			for (int j = x / sizeTile; j < (x + width / 2) / sizeTile; j++)
			{
				if (map[currentLevelFloor + 1][i][j] != charBlocks[idBlocks::air])
				{
					if (dy > 0)//���� �� ��� ����,
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
						x = j * sizeTile + sizeTile;//���������� ���� �����
					}
				}

			}
		}
		/////////////////////////////////////////////

		/////////////////////////////////////////////
		// ��������� ���
		for (int i = y / sizeTile; i < (y + height / 2) / sizeTile; i++)
		{
			for (int j = x / sizeTile; j < (x + width / 2) / sizeTile; j++)
			{
				if (map[currentLevelFloor][i][j] == charBlocks[idBlocks::air])
				{
					if (dy > 0)//���� �� ��� ����,
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
						x = j * sizeTile + sizeTile;//���������� ���� �����
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

void Entity::modeProcess(Field &field, Event &eventPerson, int x, int y)
{
	Keyboard::Key pressKey = eventPerson.key.code;

	int isFloor;

	bool checkX = ((getXPos() / sizeTile) + 2 > x) && ((getXPos() / sizeTile) - 2 < x);
	bool checkY = ((getYPos() / sizeTile) + 2 > y) && ((getYPos() / sizeTile) - 2 < y);

	if (checkX && checkY)
	{
		switch (currenMode)
		{
			////////////////////////////////////////////////////////	
			// ������������ �����
		case idModeEntity::build:
			///////////////////////////////////////////////////
			// ��������� �����
			if (pressKey == Mouse::Left)
			{
				isFloor = 1;
			}
			// ��������� ����
			else if (pressKey == Mouse::Right)
			{
				isFloor = 0;
			}
			//
			else
			{
				isFloor = -1;
			}
			///////////////////////////////////////////////////

			if (isFloor >= 0)
			{
				printf("%d %d\n", x, y);
				wchar_t currentBlock(u'\x00');
				switch (idSelectItem)
				{
				case 0:
					currentBlock = field.charBlocks[idBlocks::air];
					break;
				case 1:
					currentBlock = field.charBlocks[idBlocks::stone];
					break;
				case 2:
					currentBlock = field.charBlocks[idBlocks::woodLadder];
					break;
				case 9:
					currentBlock = u'\x99';
					break;
				default:
					break;
				}
				if (currentBlock != u'\x00')
				{
					field.dataMap[currentLevelFloor + isFloor][y][x] = currentBlock;
				}
			}


			break;
			////////////////////////////////////////////////////////
			// ������ �����
		case idModeEntity::fight:
			break;
			////////////////////////////////////////////////////////
		default:
			break;
		}
	}
	
}

// �������������� � ����������
void Entity::actionMain(Field &field, int x, int y)
{
	if ( (currentLevelFloor >= 0 && currentLevelFloor < HeightMap - 1)
			&& (currentLevel >= 1 && currentLevel <= HeightMap - 1) )
	{

		if (field.dataMap[currentLevelFloor + 1][y][x] == field.charBlocks[idBlocks::woodLadder])
		{
			currentLevelFloor += 1;
			currentLevel += 1;
			spriteObject->setPosition(x * sizeTile, y * sizeTile);
		}

	}
}

void Entity::actionAlternative(Field &field, int x, int y)
{
	if ((currentLevelFloor > 0 && currentLevelFloor <= HeightMap - 1)
		&& (currentLevel > 1 && currentLevel <= HeightMap - 1))
	{

		if (field.dataMap[currentLevelFloor][y][x] == field.charBlocks[idBlocks::woodLadder])
		{
			currentLevelFloor -= 1;
			currentLevel -= 1;

			spriteObject->setPosition(x * sizeTile, (y + 1) * sizeTile);
		}

	}
}
////////////////////////////////////////////////////////////////////