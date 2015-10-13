#include "MainPerson.h"

using namespace sf;
using namespace std;

////////////////////////////////////////////////////////////////////
// Объявление персонажа
void initializeMainPerson(MainPerson & mainPerson, dataSound &databaseSound)
{
	mainPerson.spriteEntity = new Sprite;
	mainPerson.textureEntity = new Texture;

	// Задание размера
	mainPerson.height = 22;
	mainPerson.width = 22;

	mainPerson.radiusUse = 1;

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



void MainPerson::modeProcess(Field &field, list<UnlifeObject> *unlifeObjects, list<Item> *items, Event &eventPerson, float x, float y)
{
	Keyboard::Key pressKey = eventPerson.key.code;

	int isFloor;

	//printf("%f %f\n", getXPos(), getYPos());

	int xPosBlock = x / SIZE_BLOCK;
	int yPosBlock = y / SIZE_BLOCK;

	if (isInUseField(x, y)) {

		switch (currenMode) {
			////////////////////////////////////////////////////////////////////////////////////////////////
			// Строительный режим
		case idModeEntity::build:
			///////////////////////////////////////////////////
			// Установка стены
			if (pressKey == Mouse::Left) {
				isFloor = 1;
			}
			// Установка пола
			else if (pressKey == Mouse::Right) {
				isFloor = 0;
			}
			//
			else {
				isFloor = -1;
			}
			///////////////////////////////////////////////////
			if (isFloor >= 0) {
				//printf("%d %d\n", numberX, numberY);
				wchar_t currentBlock(u'\x00');
				switch (idSelectItem) {
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
				if (currentBlock != u'\x00') {
					field.dataMap[currentLevelFloor + isFloor][yPosBlock][xPosBlock] = currentBlock;
				}
			}
			break;
			////////////////////////////////////////////////////////////////////////////////////////////////
			// Боевой режим
		case idModeEntity::fight:
			// Основное действие - атака, разрушение блока или объекта
			if (pressKey == Mouse::Left) {
				for (int l = 0; l < HEIGHT_MAP; l++) {
					////////////////////////////////////////////////////////////////////////
					// Ищем только на текущем уровне
					// Находим объект или предмет
					if (l == currentLevelFloor + 1) {
						//////////////////////////////////////////////
						// Предмет
						if (field.isItem(x, y, items, findItem, findItemFromList, l)) {
							//////////////////////////////////
							// Если предмет уничтожаемый то ...
							if (findItem->isDestroy) {
							}
							//////////////////////////////////
							// иначе просто перетаскиваем
							else {
								Sprite &mainSprite = *findItem->mainSprite;
								if (mainSprite.getGlobalBounds().contains(x, y))//и при этом координата курсора попадает в спрайт
								{
									printf("isClicked!\n");//выводим в консоль сообщение об этом

																				 //spriteObject.setPosition(x, y);
									dMoveItemX = x - mainSprite.getPosition().x;//делаем разность между позицией курсора и спрайта.для корректировки нажатия
									dMoveItemY = y - mainSprite.getPosition().y;//тоже самое по игреку
									isMoveItem = true;//можем двигать спрайт							
								}
							}
							//////////////////////////////////
						}
						//////////////////////////////////////////////
						// Объект
						else if (field.isObject(x, y, unlifeObjects, findObject, findObjectFromList, l)) {
							

							//////////////////////////////////
							// Если объект уничтожаемый то ...
							if (findObject->isDestroy) {

								printf("currentToughness %d and now %d\n", findObject->currentToughness, findObject->currentToughness - 1);

								// уменьшаем прочность
								if (findObject->currentToughness > 0) {
									findObject->currentToughness -= 1;
								}

								// уничтожаем если прочность = 0
								if (findObject->currentToughness == 0) 
								{
									//printf("%s destroy \n", findObject->typeObject->nameType);
									//////////////////////////////////////////
									// Удаление
									for (std::list<UnlifeObject>::iterator it = unlifeObjects->begin(); it != unlifeObjects->end(); ++it) {

										//if (&findElement != NULL) {
										if (it == findObjectFromList) {// ИСПРАВЬ
											unlifeObjects->erase(it);
											break;
										}

									}

								}
							//////////////////////////////////
							}
							//////////////////////////////////
							// иначе просто перетаскиваем
							else {
								Sprite &spriteObject = *findObject->spriteObject;
								if (spriteObject.getGlobalBounds().contains(x, y))//и при этом координата курсора попадает в спрайт
								{
									printf("isClicked!\n");//выводим в консоль сообщение об этом

																				 //spriteObject.setPosition(x, y);
									dMoveItemX = x - spriteObject.getPosition().x;//делаем разность между позицией курсора и спрайта.для корректировки нажатия
									dMoveItemY = y - spriteObject.getPosition().y;//тоже самое по игреку
									isMoveItem = true;//можем двигать спрайт							
								}
							}
						///////////////////////////////////////////////////////////
						}
						///////////////////////////////////////////////////////////
					}
					////////////////////////////////////////////////////////////////////////		
				}
				//////////////////////////////////////////////////////////////
			}
			// 
			else if (pressKey == Mouse::Right) {
			}
			else {
			};
			break;
			////////////////////////////////////////////////////////////////////////////////////////////////
		default:
			break;
		}

	}
}



// Взаимодействие с лестницами
void MainPerson::actionMain(Field &field, int x, int y)
{
	if ((currentLevelFloor >= 0 && currentLevelFloor < HEIGHT_MAP - 1)
		&& (currentLevelFloor + 1 >= 1 && currentLevelFloor + 1 <= HEIGHT_MAP - 1))
	{

		if (field.dataMap[currentLevelFloor + 1][y][x] == field.charBlocks[idBlocks::woodLadder])
		{
			Vector2i noPos = { -1, -1 };
			Vector2i emptyPos = isEmptyFloor(field, currentLevelFloor + 1);
			//printf("%d %d\n", emptyPos.x, emptyPos.y);
			if (emptyPos != noPos)
			{
				currentLevelFloor += 1;
				spriteEntity->setPosition(emptyPos.x * SIZE_BLOCK, emptyPos.y * SIZE_BLOCK);
			}
		}

	}
}

void MainPerson::actionAlternate(Field &field, int x, int y)
{


	if ((currentLevelFloor > 0 && currentLevelFloor <= HEIGHT_MAP - 1)
		&& (currentLevelFloor + 1 > 1 && currentLevelFloor + 1 <= HEIGHT_MAP - 1))
	{

		if (field.dataMap[currentLevelFloor][y][x] == field.charBlocks[idBlocks::woodLadder])
		{
			Vector2i noPos = { -1, -1 };
			Vector2i emptyPos = isEmptyFloor(field, currentLevelFloor);
			//printf("%d %d\n", emptyPos.x, emptyPos.y);
			if (emptyPos != noPos)
			{
				currentLevelFloor -= 1;
				spriteEntity->setPosition(emptyPos.x * SIZE_BLOCK, emptyPos.y * SIZE_BLOCK);
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
	rotation = (atan2(dY, dX)) * 180 / PI;//получаем угол в радианах и переводим его в градусы
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