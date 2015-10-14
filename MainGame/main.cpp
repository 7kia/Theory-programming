#include <SFML/Graphics.hpp>

#include "Game.h"

const Time TIME_PER_FRAME = seconds(1.f / 60.f);

using namespace sf;
using namespace std;

void processEvents(Game &game)
{
	Event event;
	RenderWindow &window = *game.window;
	while (window.pollEvent(event))
	{

		MainPerson &mainPerson = *game.mainPerson;

		Vector2i mousePos = Mouse::getPosition(window);
		Vector2f pos = window.mapPixelToCoords(mousePos);

		informationAboutSelect(game, pos.x, pos.y);

		/////////////////////////////////////////////////////////////////////////////////////////
		// Проверяем случаи нажатия нескольких стрелок

		if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::A))
		{
			mainPerson.direction = Direction::UP_LEFT;
		}
		else if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::D))
		{
			mainPerson.direction = Direction::UP_RIGHT;
		}
		else if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::A))
		{
			mainPerson.direction = Direction::DOWN_LEFT;
		}
		else if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::D))
		{
			mainPerson.direction = Direction::DOWN_RIGHT;
		}

		/////////////////////////////////////////////////////////////////////////////////////////
		// Проверяем одну стрелку
		else if (Keyboard::isKeyPressed(Keyboard::W))
		{
			mainPerson.direction = UP;
		}
		else if (Keyboard::isKeyPressed(Keyboard::S))
		{
			mainPerson.direction = DOWN;
		}
		else if (Keyboard::isKeyPressed(Keyboard::A))
		{
			mainPerson.direction = LEFT;
		}
		else if (Keyboard::isKeyPressed(Keyboard::D))
		{
			mainPerson.direction = RIGHT;
		}
		else
		{
			mainPerson.direction = NONE;
		}
		/////////////////////////////////////////////////////////////////////////////////////////
		// Переключение режимов
		if (Keyboard::isKeyPressed(Keyboard::G))
		{
			mainPerson.currenMode = idModeEntity::build;
			printf("build mode\n");
		}
		else if (Keyboard::isKeyPressed(Keyboard::F))
		{
			mainPerson.currenMode = idModeEntity::fight;
			printf("fight mode\n");
		}
		/////////////////////////////////////////////////////////////////////////////////////////
		// кнопка "Дествие" и "Другое действие"
		int numberY(pos.y / SIZE_BLOCK);
		int numberX(pos.x / SIZE_BLOCK);

		if (Keyboard::isKeyPressed(Keyboard::Q))
		{
			mainPerson.actionAlternate(*game.field, numberX, numberY);
			printf("Alternative action\n");
		}
		else if (Keyboard::isKeyPressed(Keyboard::E))
		{
			mainPerson.actionMain(*game.field, numberX, numberY);
			printf("Main action\n");
		}
		/////////////////////////////////////////////////////////////////////////////////////////
		else if (Keyboard::isKeyPressed(Keyboard::LShift))
		{
			if (mainPerson.stepCurrent > mainPerson.stepFirst)
			{
				mainPerson.stepCurrent -= 350.f;
			}
			else
			{
				mainPerson.stepCurrent += 350.f;
			}	
		}
		/////////////////////////////////////////////////////////////////////////////////////////
		// Обработка 0 - 9
		else if (Keyboard::isKeyPressed(Keyboard::Num0))
		{
			mainPerson.idSelectItem = 10;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num1))
		{
			mainPerson.idSelectItem = 1;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num2))
		{
			mainPerson.idSelectItem = 2;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num3))
		{
			mainPerson.idSelectItem = 3;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num4))
		{
			mainPerson.idSelectItem = 4;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num5))
		{
			mainPerson.idSelectItem = 5;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num6))
		{
			mainPerson.idSelectItem = 6;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num7))
		{
			mainPerson.idSelectItem = 7;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num8))
		{
			mainPerson.idSelectItem = 8;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num9))
		{
			mainPerson.idSelectItem = 9;
		}
		/////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////
		// Оюработка щелчка мыши
		UnlifeObject* emptyObject = NULL;
		Item* emptyItem = NULL;
		if (event.type == Event::MouseButtonPressed)
		{
			mainPerson.findObject = emptyObject;
			mainPerson.findItem = emptyItem;
			mainPerson.modeProcess(*game.field, game.unlifeObjects , game.items, event, pos.x, pos.y);
		}
		else if (event.type == Event::MouseMoved) {
			// Передвижение предмета
			if (mainPerson.isMoveItem) {
				
				
				if (mainPerson.isInUseField(pos.x, pos.y)) {
					Vector2f position = { pos.x - mainPerson.dMoveItemX, pos.y - mainPerson.dMoveItemY };
					if (mainPerson.findObject != emptyObject) {
						Sprite &spriteObject = *mainPerson.findObject->spriteObject;
						spriteObject.setPosition(position);
					}
					else if (mainPerson.findItem != emptyItem) {
						Sprite &spriteItem = *mainPerson.findItem->mainSprite;
						spriteItem.setPosition(position);
					}


					// Объект должен находиться в центре клетки
					// position = { (float)( (int)position.x/ SIZE_BLOCK) * SIZE_BLOCK - SIZE_BLOCK / 2,
					//	(float)( (int)position.y/ SIZE_BLOCK)* SIZE_BLOCK - SIZE_BLOCK / 2 };

					
					
				}
			}
		}
		else if (event.type == Event::MouseButtonReleased) {
			mainPerson.isMoveItem = false;
		}
		//////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////
		// Для направление взгляда
		mainPerson.computeAngle(window);
		/////////////////////////////////////////////////////////////////////////////////////////

		// Окно закрыли
		if (event.type == Event::Closed)
		{
			window.close();
		}
	}
}

void render(Game & game)
{
	RenderWindow &window = *game.window;

	/////////////////////////////////////////////////////////////
	// Для обновления окна
	Vector2u currentSizeWindow = { game.widthMainWindow, game.heightMainWindow };

	if ( window.getSize() != currentSizeWindow) {

		int width = window.getSize().x;
		int height = window.getSize().y;

		window.create(VideoMode(width, height), titleGame );
		game.widthMainWindow = width;
		game.heightMainWindow = height;
	};
	/////////////////////////////////////////////////////////////
	window.clear();

	//////////////////////////////////////////////
	// Отрисовка карты
	MainPerson &mainPerson = *game.mainPerson;
	Field &field = *game.field;
	bool isEmpty(false);
	
	int l = 0;
	while (l < HEIGHT_MAP)
	{
		// Рисуем только текущий уровень
		if (l == mainPerson.currentLevelFloor
			|| l == mainPerson.currentLevelFloor + 1)
		{
			for (int i = 0; i < LONG_MAP; i++)
			{
				for (int j = 0; j < WIDTH_MAP - BORDER1; j++)
				{
					field.setTypeSprite(mainPerson.currentLevelFloor, l, i, j);

					window.draw(*field.floorSprite);
					window.draw(*field.wallSprite);
				}
			}
		}
		
		l++;
	}

	//////////////////////////////////////////////
	// Отрислвка предметов
	for (std::list<Item>::iterator it = game.items->begin(); it != game.items->end(); ++it) {
		if (it->currentLevel == game.mainPerson->currentLevelFloor + 1) {

			window.draw(*it->mainSprite);
			//window.draw(*game.items->item[i].spriteForUse);// ИСПРАВЬ
		}

	}

	//////////////////////////////////////////////
	// Отрисовка главного персонажа
	window.draw(*mainPerson.spriteEntity);

	////////////////////////////////////////////////////////
	// Рисуем неживые объекты
	for (std::list<UnlifeObject>::iterator it = game.unlifeObjects->begin(); it != game.unlifeObjects->end(); ++it)
	{
		if (it->currentLevel == game.mainPerson->currentLevelFloor + 1)
		{

			window.draw(*it->spriteObject);
			window.draw(*it->transparentSpiteObject);
		}
		
	}
	////////////////////////////////////////////////////////

	//////////////////////////////////////////////
	// GUI
	game.gui->setPositionGui(window, *game.mainPerson, *game.textGame);
	window.draw(*game.gui->infoSelectBlockSprite);
	window.draw(*game.gui->panelQuickAccess);
	window.draw(*game.gui->selectInPanelQuickAccess);
	//////////////////////////////////////////////
	// Текст GUI
	for (size_t i = 0; i < idTextGui::amountTextsGui; i++) {
		window.draw(game.textGame->texts[i]);
	}

	window.display();
}

void startGame()
{
	Game *game = new Game();
	initializeGame(*game);

	RenderWindow &window = *game->window;

	Time timeSinceLastUpdate = Time::Zero;

	MainPerson &mainPerson = *game->mainPerson;
	while (window.isOpen())
	{
		timeSinceLastUpdate += game->clock->restart();
		//printf("FPS: %f\n", 1.f / timeSinceLastUpdate.asSeconds());
		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{

			timeSinceLastUpdate -= TIME_PER_FRAME;
			processEvents(*game);

			mainPerson.update(TIME_PER_FRAME, *game->databaseSound);
			mainPerson.interactionWithMap(*game->field, TIME_PER_FRAME);
			mainPerson.interactionWitnUnlifeObject(game->unlifeObjects, TIME_PER_FRAME);
			mainPerson.getCoordinateForView(mainPerson.getXPos(), mainPerson.getYPos());

			window.setView(*mainPerson.view);

			//printf("Angle %f \n", game->mainPerson->rotation);//смотрим на градусы в консоли	
		}
		render(*game);
	}
	destroyGame(*game);
}

int main()
{
	startGame();
	return 0;
}

