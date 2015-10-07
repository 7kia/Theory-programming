#include "MainPerson.h"

using namespace sf;

////////////////////////////////////////////////////////////////////
// Объявление персонажа
void initializeMainPerson(MainPerson & mainPerson, dataSound &databaseSound)
{
	mainPerson.spriteEntity = new Sprite;
	mainPerson.textureEntity = new Texture;

	// Задание размера

	mainPerson.height = 22;
	mainPerson.width = 22;

	// Скорость ходьбы
	mainPerson.stepFirst = 150.f;
	mainPerson.stepCurrent = 150.f;
	mainPerson.timeAnimation = 0.f;

	// Камера
	int posX(70), posY(70);
	mainPerson.view = new View;
	mainPerson.view->setSize(640, 480);
	mainPerson.view->setCenter(posX, posY);

	// Текстура
	mainPerson.textureEntity->loadFromFile(texturePaths[idTexturePaths::mainPerson]);
	mainPerson.spriteEntity->setTexture(*mainPerson.textureEntity);
	mainPerson.spriteEntity->setTextureRect(IntRect(0, 0, mainPerson.width, mainPerson.height));

	// Звуки 
	mainPerson.soundsEntity[idSoundEntity::stepGrass] = &databaseSound.sounds[idSoundEntity::stepGrass];
	mainPerson.soundsEntity[idSoundEntity::stepStone] = &databaseSound.sounds[idSoundEntity::stepStone];

	// Текущий выбранный тип блока
	mainPerson.idSelectItem = 0;

	// Позиция и направление
	mainPerson.currentLevelFloor = 0;
	mainPerson.currenMode = idModeEntity::build;
	mainPerson.spriteEntity->setPosition(posX, posY);
	mainPerson.direction = NONE;
}
////////////////////////////////////////////////////////////////////



void MainPerson::modeProcess(Field &field, Event &eventPerson, int x, int y)
{
	Keyboard::Key pressKey = eventPerson.key.code;

	int isFloor;

	printf("%f %f\n", getXPos(), getYPos());

	int radiusUse = 1;

	bool checkX = (( (getXPos() + width / 2) / sizeTile) + radiusUse > x) && (( (getXPos() + width / 2) / sizeTile) - (radiusUse + 1) <= x);
	bool checkY = (( (getYPos() + height / 2) / sizeTile) + radiusUse > y) && (((getYPos() + height / 2) / sizeTile) - (radiusUse + 1) <= y);

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
					currentBlock = field.charBlocks[idBlocks::stoneBrick];
					break;
				case 3:
					currentBlock = field.charBlocks[idBlocks::sand];
					break;
				case 4:
					currentBlock = field.charBlocks[idBlocks::dirt];
					break;
				case 5:
					currentBlock = field.charBlocks[idBlocks::woodBoard];
					break;
				case 6:
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
void MainPerson::actionMain(Field &field, int x, int y)
{
	if ((currentLevelFloor >= 0 && currentLevelFloor < HeightMap - 1)
		&& (currentLevelFloor + 1 >= 1 && currentLevelFloor + 1 <= HeightMap - 1))
	{

		if (field.dataMap[currentLevelFloor + 1][y][x] == field.charBlocks[idBlocks::woodLadder])
		{
			Vector2i noPos = { -1, -1 };
			Vector2i emptyPos = isEmptyFloor(field, currentLevelFloor + 1);
			printf("%d %d\n", emptyPos.x, emptyPos.y);
			if (emptyPos != noPos)
			{
				currentLevelFloor += 1;
				spriteEntity->setPosition(emptyPos.x * sizeTile, emptyPos.y * sizeTile);
			}
		}

	}
}

void MainPerson::actionAlternative(Field &field, int x, int y)
{
	if ((currentLevelFloor > 0 && currentLevelFloor <= HeightMap - 1)
		&& (currentLevelFloor + 1 > 1 && currentLevelFloor + 1 <= HeightMap - 1))
	{

		if (field.dataMap[currentLevelFloor][y][x] == field.charBlocks[idBlocks::woodLadder])
		{
			Vector2i noPos = { -1, -1 };
			Vector2i emptyPos = isEmptyFloor(field, currentLevelFloor);
			//printf("%d %d\n", emptyPos.x, emptyPos.y);
			if (emptyPos != noPos)
			{
				currentLevelFloor -= 1;
				spriteEntity->setPosition(emptyPos.x * sizeTile, emptyPos.y * sizeTile);
			}
		}

	}
}
////////////////////////////////////////////////////////////////////

// Использую потом (не ВКЛЮЧЕНА)
void MainPerson::computeAngle(RenderWindow &window)
{
	Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
	Vector2f pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)

	float dX = pos.x - spriteEntity->getPosition().x - width / 2;//вектор , колинеарный прямой, которая пересекает спрайт и курсор
	float dY = pos.y - spriteEntity->getPosition().y - height / 2;//он же, координата y
	rotation = (atan2(dY, dX)) * 180 / 3.14159265;//получаем угол в радианах и переводим его в градусы
}

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