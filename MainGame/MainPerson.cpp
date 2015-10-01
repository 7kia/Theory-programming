#include "MainPerson.h"

////////////////////////////////////////////////////////////////////
// ���������� ���������
void initializeMainPerson(MainPerson & mainPerson)
{
	mainPerson.spritePerson = new Sprite;
	mainPerson.textureMainPerson = new Texture;

	// ������� �������
	mainPerson.height = 48;
	mainPerson.width = 32;

	// �������� ������
	mainPerson.stepFirst = 150.f;
	mainPerson.stepCurrent = 150.f;
	mainPerson.timeAnimation = 0.f;

	// View
	int posX(100), posY(100);
	mainPerson.view = new View;
	mainPerson.view->setSize(640, 480);
	mainPerson.view->setCenter(posX, posY);

	// ��������
	mainPerson.textureMainPerson->loadFromFile("recourses\\images\\mainPerson.png");
	mainPerson.spritePerson->setTexture(*mainPerson.textureMainPerson);
	mainPerson.spritePerson->setTextureRect(IntRect(0, 0, mainPerson.width, mainPerson.height));

	// �����
	mainPerson.soundBuffer[0].loadFromFile("recourses\\sounds\\step\\grass1.ogg");
	mainPerson.startSounds[idSoundPerson::stepGrass] = 0;
	mainPerson.sounds[0].setBuffer(mainPerson.soundBuffer[0]);

	mainPerson.soundBuffer[1].loadFromFile("recourses\\sounds\\step\\stone1.ogg");
	mainPerson.startSounds[idSoundPerson::stepStone] = 0;
	mainPerson.sounds[1].setBuffer(mainPerson.soundBuffer[1]);

	// ������� ��������� ��� �����
	mainPerson.idSelectItem = 0;

	// ������� � �����������
	mainPerson.currentLevel = 1;
	mainPerson.currentLevelFloor = 0;
	mainPerson.currenMode = idModeMainPerson::build;
	mainPerson.spritePerson->setPosition(posX, posY);
	mainPerson.direction = NONE;
}
////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
// View
void MainPerson::getCoordinateForView(float x, float y)//������� ��� ���������� ��������� ������
{ 
	view->setCenter(x, y);//������ �� �������, ��������� ��� ����������. 
}

// �������� ���������� (�� ��������)
void MainPerson::viewmap(float time)
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
void MainPerson::changeview()
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
void MainPerson::update(const Time & deltaTime)
{
	float pauseStep = 5, resetAnimation = 2;
	switch (direction)
	{
	/*
	case UP_LEFT:
		movement.y = -stepCurrent;
		movement.x = -stepCurrent;

		playSound(timeAnimation, startSounds[idSoundPerson::stepGrass], idSoundPerson::stepGrass);

		timeAnimation += deltaTime.asSeconds() * pauseStep;
		resetTimeAnimation(timeAnimation, resetAnimation);

		getCoordinateForView(getXPos(), getYPos());

		spritePerson->setTextureRect(IntRect((int)timeAnimation *  width, height * 3, width, height));
		break;
	case UP_RIGHT:
		movement.y = -stepCurrent;
		movement.x = stepCurrent;

		playSound(timeAnimation, startSounds[idSoundPerson::stepGrass], idSoundPerson::stepGrass);

		timeAnimation += deltaTime.asSeconds() * pauseStep;
		resetTimeAnimation(timeAnimation, resetAnimation);

		//getCoordinateForView(spritePerson->getPosition().x, spritePerson->getPosition().y);
		getCoordinateForView(getXPos(), getYPos());

		spritePerson->setTextureRect(IntRect((int)timeAnimation *  width, height * 3, width, height));
		break;
		*/
	case UP:
		movement.y = -stepCurrent;

		playSound(timeAnimation, startSounds[idSoundPerson::stepGrass], idSoundPerson::stepGrass);

		timeAnimation += deltaTime.asSeconds() * pauseStep;
		resetTimeAnimation(timeAnimation, resetAnimation);

		getCoordinateForView(getXPos(), getYPos());

		spritePerson->setTextureRect(IntRect((int)timeAnimation *  width, height * 3, width, height));
		break;
		/*
	case DOWN_LEFT:
		movement.y = stepCurrent;
		movement.x = -stepCurrent;

		playSound(timeAnimation, startSounds[idSoundPerson::stepGrass], idSoundPerson::stepGrass);

		timeAnimation += deltaTime.asSeconds() * pauseStep;
		resetTimeAnimation(timeAnimation, resetAnimation);

		getCoordinateForView(getXPos(), getYPos());

		spritePerson->setTextureRect(IntRect((int)timeAnimation *   width, 0, width, height));
		break;
	case DOWN_RIGHT:
		movement.y = stepCurrent;
		movement.x = stepCurrent;

		playSound(timeAnimation, startSounds[idSoundPerson::stepGrass], idSoundPerson::stepGrass);

		timeAnimation += deltaTime.asSeconds() * pauseStep;
		resetTimeAnimation(timeAnimation, resetAnimation);

		getCoordinateForView(getXPos(), getYPos());

		spritePerson->setTextureRect(IntRect((int)timeAnimation *   width, 0, width, height));
		break;
		*/
	case DOWN:
		movement.y = stepCurrent;

		playSound(timeAnimation, startSounds[idSoundPerson::stepGrass], idSoundPerson::stepGrass);

		timeAnimation += deltaTime.asSeconds() * pauseStep;
		resetTimeAnimation(timeAnimation, resetAnimation);

		getCoordinateForView(getXPos(), getYPos());

		spritePerson->setTextureRect(IntRect((int)timeAnimation * width, 0, width, height));
		break;
	case LEFT:
		movement.x = -stepCurrent;
		
		playSound(timeAnimation, startSounds[idSoundPerson::stepGrass], idSoundPerson::stepGrass);

		timeAnimation += deltaTime.asSeconds() * pauseStep;
		resetTimeAnimation(timeAnimation, resetAnimation);

		getCoordinateForView(getXPos(), getYPos());

		spritePerson->setTextureRect(IntRect((int)timeAnimation *   width, height, width, height));
		break;
	case RIGHT:
		movement.x = stepCurrent;

		playSound(timeAnimation, startSounds[idSoundPerson::stepGrass], idSoundPerson::stepGrass);

		timeAnimation += deltaTime.asSeconds() * pauseStep;
		resetTimeAnimation(timeAnimation, resetAnimation);

		getCoordinateForView(getXPos(), getYPos());

		spritePerson->setTextureRect(IntRect(((int)timeAnimation + 1) *   width, height, -width, height));
		break;
	default:
		break;
	}
	spritePerson->move(movement * deltaTime.asSeconds());

	//movement = { 0.f, 0.f };
}

void MainPerson::playSound(float &time, float &start, const int &idSound)
{
	if (time == start)
	{
		sounds[idSound].play();
	}
}

void MainPerson::resetTimeAnimation(float &time, float &reset)
{
	if (time > reset)
	{
		time = 0;
	}
}
////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
// ��������������� �������
float MainPerson::getXPos()
{
	return spritePerson->getPosition().x;
}

float MainPerson::getYPos()
{
	return spritePerson->getPosition().y;
}

// ��������� ����� (�� ��������)
void MainPerson::computeAngle(RenderWindow &window)
{
	Vector2i pixelPos = Mouse::getPosition(window);//�������� ����� �������
	Vector2f pos = window.mapPixelToCoords(pixelPos);//��������� �� � ������� (������ �� ����� ����)

	float dX = pos.x - spritePerson->getPosition().x - width / 2;//������ , ����������� ������, ������� ���������� ������ � ������
	float dY = pos.y - spritePerson->getPosition().y - height / 2;//�� ��, ���������� y
	rotation = (atan2(dY, dX)) * 180 / 3.14159265;//�������� ���� � �������� � ��������� ��� � �������
}
////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
// �������������� � �����
void MainPerson::interactionWithMap(wchar_t(*map)[LongMap][WidthMap], const Time & deltaTime)
{
	float x(getXPos());
	float y(getYPos());
	float dx(movement.x);
	float dy(movement.y);

	/////////////////////////////////////////////
	// ��������� ���������� �������
	for (int i = y / 32; i < (y + height) / 32; i++)//���������� �� ���� �����, �� ���� �� ���� ����������� ������� 32*32, ������� �� ���������� � 9 �����. ��� ������� ������� ����.
	{
		for (int j = x / 32; j < (x + width) / 32; j++)//��� ����� �� 32, ��� ����� �������� ����� ���������, � ������� �������� �������������. (�� ���� ������ ������� 32*32, ������� ����� ������������ ������ �� ���������� ���������). � j<(x + w) / 32 - ������� ����������� ��������� �� ����. �� ���� ���������� ������ ������� ��������, ������� ������������� � ����������. ����� ������� ���� � ����� ����� ������� �� ����, ������� �� �� ������ �������� (���������������� � ������), �� ������� �������� (���������������� � ������)
		{
			if (map[currentLevel][i][j] != u' ')
				//|| map[currentLevel][i][j] != 'w')//���� ��� ��������� ������������� ������� 0 (�����), �� ��������� "����������� ��������" ���������:
			{
				if (dy > 0)//���� �� ��� ����,
				{

					y = i * 32 - height;//�� �������� ���������� ����� ���������. ������� �������� ���������� ������ ���������� �� �����(�����) � ����� �������� �� ������ ������� ���������.
				}
				if (dy < 0)
				{
					y = i * 32 + 32;//���������� � ������� �����. dy<0, ������ �� ���� ����� (���������� ���������� ������)
				}
				if (dx > 0)
				{
					x = j * 32 - width;//���� ���� ������, �� ���������� � ����� ����� (������ 0) ����� ������ ���������
				}
				if (dx < 0)
				{
					x = j * 32 + 32;//���������� ���� �����
				}
			}

		}
	}
	/////////////////////////////////////////////

	/////////////////////////////////////////////
	// ��������� ���
	for (int i = y / 32; i < (y + height) / 32; i++)//���������� �� ���� �����, �� ���� �� ���� ����������� ������� 32*32, ������� �� ���������� � 9 �����. ��� ������� ������� ����.
	{
		for (int j = x / 32; j < (x + width) / 32; j++)//��� ����� �� 32, ��� ����� �������� ����� ���������, � ������� �������� �������������. (�� ���� ������ ������� 32*32, ������� ����� ������������ ������ �� ���������� ���������). � j<(x + w) / 32 - ������� ����������� ��������� �� ����. �� ���� ���������� ������ ������� ��������, ������� ������������� � ����������. ����� ������� ���� � ����� ����� ������� �� ����, ������� �� �� ������ �������� (���������������� � ������), �� ������� �������� (���������������� � ������)
		{
			if (map[currentLevelFloor][i][j] == u' '
				|| map[currentLevelFloor][i][j] == u'\x013')//���� ��� ��������� ������������� ������� 0 (�����), �� ��������� "����������� ��������" ���������:
			{
				if (dy > 0)//���� �� ��� ����,
				{

					y = i * 32 - height;//�� �������� ���������� ����� ���������. ������� �������� ���������� ������ ���������� �� �����(�����) � ����� �������� �� ������ ������� ���������.
				}
				if (dy < 0)
				{
					y = i * 32 + 32;//���������� � ������� �����. dy<0, ������ �� ���� ����� (���������� ���������� ������)
				}
				if (dx > 0)
				{
					x = j * 32 - width;//���� ���� ������, �� ���������� � ����� ����� (������ 0) ����� ������ ���������
				}
				if (dx < 0)
				{
					x = j * 32 + 32;//���������� ���� �����
				}
			}

		}
	}
	/////////////////////////////////////////////
	spritePerson->setPosition(x, y);
	movement = { 0.f, 0.f };
}

void MainPerson::modeProcess(wchar_t(*map)[LongMap][WidthMap], Event &eventPerson, int x, int y)
{
	switch (currenMode)
	{
	////////////////////////////////////////////////////////	
	// ������������ �����
	case idModeMainPerson::build:
		///////////////////////////////////////////////////
		// ��������� �����
		if (eventPerson.key.code == Mouse::Left)
		{
			printf("%d %d\n", x, y);
			wchar_t currentBlock(u'\x00');
			switch (idSelectItem)
			{
			case 0:
				currentBlock = u'\x014';
				break;
			case 1:
				currentBlock = u'\x020';
				break;
			case 9:
				currentBlock = u'\x012';
				break;
			default:
				break;
			}
			if (currentBlock != u'\x00')
			{
				map[currentLevel][y][x] = currentBlock;
			}
			
		}
		///////////////////////////////////////////////////
		// ��������� ����
		else if (eventPerson.key.code == Mouse::Right)
		{
			printf("%d %d\n", x, y);
			wchar_t currentBlock(u'\x00');
			switch (idSelectItem)
			{
			case 0:
				currentBlock = u'\x014';
				break;
			case 1:
				currentBlock = u'\x020';
				break;
			case 9:
				currentBlock = u'\x012';
				break;
			default:
				break;
			}
			if (currentBlock != u'\x00')
			{
				map[currentLevelFloor][y][x] = currentBlock;
			}
		}
		///////////////////////////////////////////////////
		break;
	////////////////////////////////////////////////////////
	// ������ �����
	case idModeMainPerson::fight:
		break;
	////////////////////////////////////////////////////////
	default:
		break;
	}
}
////////////////////////////////////////////////////////////////////