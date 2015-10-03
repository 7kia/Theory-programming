#include "Entity.h"

////////////////////////////////////////////////////////////////////
// Объявление персонажа
void initializeEntity(Entity & Entity, dataSound &databaseSound)
{
	Entity.spriteObject = new Sprite;
	Entity.textureEntity = new Texture;

	// Задание размера

	Entity.height = 42;
	Entity.width = 22;

	// Скорость ходьбы
	Entity.stepFirst = 150.f;
	Entity.stepCurrent = 150.f;
	Entity.timeAnimation = 0.f;

	// Камера
	int posX(70), posY(70);
	Entity.view = new View;
	Entity.view->setSize(640, 480);
	Entity.view->setCenter(posX, posY);

	// Текстура
	Entity.textureEntity->loadFromFile("recourses\\images\\mainPerson.png");
	Entity.spriteObject->setTexture(*Entity.textureEntity);
	Entity.spriteObject->setTextureRect(IntRect(0, 0, Entity.width, Entity.height));

	// Звуки 
	Entity.soundsEntity[idSoundEntity::stepGrass] = &databaseSound.sounds[idSoundEntity::stepGrass];
	Entity.soundsEntity[idSoundEntity::stepStone] = &databaseSound.sounds[idSoundEntity::stepStone];

	// Текущий выбранный тип блока
	Entity.idSelectItem = 0;

	// Позиция и направление
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
void Entity::getCoordinateForView(float x, float y)//функция для считывания координат игрока
{ 
	view->setCenter(x, y);//следим за игроком, передавая его координаты. 
}

// Возможно пригодится (не ВКЛЮЧЕНА)
void Entity::viewmap(float time)
{
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		view->move(0.1*time, 0);//скроллим карту вправо (см урок, когда мы двигали героя - всё тоже самое)
	}

	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		view->move(0, 0.1*time);//скроллим карту вниз (см урок, когда мы двигали героя - всё тоже самое)
	}

	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		view->move(-0.1*time, 0);//скроллим карту влево (см урок, когда мы двигали героя - всё тоже самое)
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		view->move(0, -0.1*time);//скроллим карту вправо (см урок, когда мы двигали героя - всё тоже самое)
	}

}
// Возможно пригодится (не ВКЛЮЧЕНА)
void Entity::changeview()
{
	if (Keyboard::isKeyPressed(Keyboard::U)) {
		view->zoom(1.0100f); //масштабируем, уменьшение
							//view.zoom(1.0006f); //тоже самое помедленнее соответственно
	}

	if (Keyboard::isKeyPressed(Keyboard::R)) {
		//view.setRotation(90);//сразу же задает поворот камере
		view->rotate(1);//постепенно поворачивает камеру (отрицательное значение - в обратную сторону)
	}


	if (Keyboard::isKeyPressed(Keyboard::I)) {
		view->setSize(640, 480);//устанавливает размер камеры (наш исходный)
	}

	if (Keyboard::isKeyPressed(Keyboard::P)) {
		view->setSize(540, 380);//например другой размер
	}

}
////////////////////////////////////////////////////////////////////

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
// Вспомагательные функции
float Entity::getXPos()
{
	return spriteObject->getPosition().x;
}

float Entity::getYPos()
{
	return spriteObject->getPosition().y;
}

// Использую потом (не ВКЛЮЧЕНА)
void Entity::computeAngle(RenderWindow &window)
{
	Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
	Vector2f pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)

	float dX = pos.x - spriteObject->getPosition().x - width / 2;//вектор , колинеарный прямой, которая пересекает спрайт и курсор
	float dY = pos.y - spriteObject->getPosition().y - height / 2;//он же, координата y
	rotation = (atan2(dY, dX)) * 180 / 3.14159265;//получаем угол в радианах и переводим его в градусы
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
			// Строительный режим
		case idModeEntity::build:
			///////////////////////////////////////////////////
			// Установка стены
			if (pressKey == Mouse::Left)
			{
				isFloor = 1;
			}
			// Установка пола
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
			// Боевой режим
		case idModeEntity::fight:
			break;
			////////////////////////////////////////////////////////
		default:
			break;
		}
	}
	
}

// Взаимодействие с лестницами
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