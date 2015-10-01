#include "MainPerson.h"

////////////////////////////////////////////////////////////////////
// Объявление персонажа
void initializeMainPerson(MainPerson & mainPerson)
{
	mainPerson.spritePerson = new Sprite;
	mainPerson.textureMainPerson = new Texture;

	// Задание размера
	mainPerson.height = 48;
	mainPerson.width = 32;

	// Скорость ходьбы
	mainPerson.stepFirst = 150.f;
	mainPerson.stepCurrent = 150.f;
	mainPerson.timeAnimation = 0.f;

	// View
	int posX(100), posY(100);
	mainPerson.view = new View;
	mainPerson.view->setSize(640, 480);
	mainPerson.view->setCenter(posX, posY);

	// Текстура
	mainPerson.textureMainPerson->loadFromFile("recourses\\images\\mainPerson.png");
	mainPerson.spritePerson->setTexture(*mainPerson.textureMainPerson);
	mainPerson.spritePerson->setTextureRect(IntRect(0, 0, mainPerson.width, mainPerson.height));

	// Звуки
	mainPerson.soundBuffer[0].loadFromFile("recourses\\sounds\\step\\grass1.ogg");
	mainPerson.startSounds[idSoundPerson::stepGrass] = 0;
	mainPerson.sounds[0].setBuffer(mainPerson.soundBuffer[0]);

	mainPerson.soundBuffer[1].loadFromFile("recourses\\sounds\\step\\stone1.ogg");
	mainPerson.startSounds[idSoundPerson::stepStone] = 0;
	mainPerson.sounds[1].setBuffer(mainPerson.soundBuffer[1]);

	// Текущий выбранный тип блока
	mainPerson.idSelectItem = 0;

	// Позиция и направление
	mainPerson.currentLevel = 1;
	mainPerson.currentLevelFloor = 0;
	mainPerson.currenMode = idModeMainPerson::build;
	mainPerson.spritePerson->setPosition(posX, posY);
	mainPerson.direction = NONE;
}
////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
// View
void MainPerson::getCoordinateForView(float x, float y)//функция для считывания координат игрока
{ 
	view->setCenter(x, y);//следим за игроком, передавая его координаты. 
}

// Возможно пригодится (не ВКЛЮЧЕНА)
void MainPerson::viewmap(float time)
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
void MainPerson::changeview()
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
// Вспомагательные функции
float MainPerson::getXPos()
{
	return spritePerson->getPosition().x;
}

float MainPerson::getYPos()
{
	return spritePerson->getPosition().y;
}

// Использую потом (не ВКЛЮЧЕНА)
void MainPerson::computeAngle(RenderWindow &window)
{
	Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
	Vector2f pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)

	float dX = pos.x - spritePerson->getPosition().x - width / 2;//вектор , колинеарный прямой, которая пересекает спрайт и курсор
	float dY = pos.y - spritePerson->getPosition().y - height / 2;//он же, координата y
	rotation = (atan2(dY, dX)) * 180 / 3.14159265;//получаем угол в радианах и переводим его в градусы
}
////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
// Взаимодейтсвие с миром
void MainPerson::interactionWithMap(wchar_t(*map)[LongMap][WidthMap], const Time & deltaTime)
{
	float x(getXPos());
	float y(getYPos());
	float dx(movement.x);
	float dy(movement.y);

	/////////////////////////////////////////////
	// Проверяем окружающие объекты
	for (int i = y / 32; i < (y + height) / 32; i++)//проходимся по всей карте, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
	{
		for (int j = x / 32; j < (x + width) / 32; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
		{
			if (map[currentLevel][i][j] != u' ')
				//|| map[currentLevel][i][j] != 'w')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
			{
				if (dy > 0)//если мы шли вниз,
				{

					y = i * 32 - height;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
				}
				if (dy < 0)
				{
					y = i * 32 + 32;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
				}
				if (dx > 0)
				{
					x = j * 32 - width;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
				}
				if (dx < 0)
				{
					x = j * 32 + 32;//аналогично идем влево
				}
			}

		}
	}
	/////////////////////////////////////////////

	/////////////////////////////////////////////
	// Проверяем пол
	for (int i = y / 32; i < (y + height) / 32; i++)//проходимся по всей карте, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
	{
		for (int j = x / 32; j < (x + width) / 32; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
		{
			if (map[currentLevelFloor][i][j] == u' '
				|| map[currentLevelFloor][i][j] == u'\x013')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
			{
				if (dy > 0)//если мы шли вниз,
				{

					y = i * 32 - height;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
				}
				if (dy < 0)
				{
					y = i * 32 + 32;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
				}
				if (dx > 0)
				{
					x = j * 32 - width;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
				}
				if (dx < 0)
				{
					x = j * 32 + 32;//аналогично идем влево
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
	// Строительный режим
	case idModeMainPerson::build:
		///////////////////////////////////////////////////
		// Установка стены
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
		// Установка пола
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
	// Боевой режим
	case idModeMainPerson::fight:
		break;
	////////////////////////////////////////////////////////
	default:
		break;
	}
}
////////////////////////////////////////////////////////////////////