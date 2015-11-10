#include <SFML/Graphics.hpp>

#include "Game.h"

const Time TIME_PER_FRAME = seconds(1.f / 60.f);

using namespace sf;
using namespace std;

void processEvents(Game &game, const Time &deltaTime)
{
	Event event;
	RenderWindow &window = game.window;
	while (window.pollEvent(event)) {

	
		MainPerson &mainPerson = game.mainPerson;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Если персонаж жив
		if (mainPerson.isDeath == false) {
			Vector2i mousePos = Mouse::getPosition(window);
			Vector2f pos = window.mapPixelToCoords(mousePos);

			UnlifeObject* emptyObject = nullptr;
			Item* emptyItem = nullptr;

			informationAboutSelect(game, pos.x, pos.y);

			/////////////////////////////////////////////////////////////////////////////////////////
			// Проверяем случаи нажатия нескольких стрелок
			if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::A)) {
				mainPerson.directions.directionWalk = Direction::UP_LEFT;
			} else if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::D)) {
				mainPerson.directions.directionWalk = Direction::UP_RIGHT;
			} else if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::A)) {
				mainPerson.directions.directionWalk = Direction::DOWN_LEFT;
			} else if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::D)) {
				mainPerson.directions.directionWalk = Direction::DOWN_RIGHT;
			}

			/////////////////////////////////////////////////////////////////////////////////////////
			// Проверяем одну стрелку
			else if (Keyboard::isKeyPressed(Keyboard::W)) {
				mainPerson.directions.directionWalk = UP;
			} else if (Keyboard::isKeyPressed(Keyboard::S)) {
				mainPerson.directions.directionWalk = DOWN;
			} else if (Keyboard::isKeyPressed(Keyboard::A)) {
				mainPerson.directions.directionWalk = LEFT;
			} else if (Keyboard::isKeyPressed(Keyboard::D)) {
				mainPerson.directions.directionWalk = RIGHT;
			} else {
				mainPerson.directions.directionWalk = NONE_DIRECTION;
			}
			/////////////////////////////////////////////////////////////////////////////////////////
			// Переключение режимов
			if (event.type == Event::KeyPressed) {
				if (Keyboard::isKeyPressed(Keyboard::G)) {
					//mainPerson.currenMode = idEntityMode::build;// ИСПРАВЬ
					printf("build mode\n");
				} else if (Keyboard::isKeyPressed(Keyboard::F)) {
					//mainPerson.currenMode = idModeEntity::fight;// ИСПРАВЬ
					printf("fight mode\n");
				}
			}
			/////////////////////////////////////////////////////////////////////////////////////////
			// кнопка "Дествие" и "Другое действие"
			int numberY(pos.y / SIZE_BLOCK);
			int numberX(pos.x / SIZE_BLOCK);

			if (event.type == Event::KeyPressed) {
				if (Keyboard::isKeyPressed(Keyboard::C)) 
				{
					mainPerson.actionAlternate(game.field, game.unlifeObjects, *game.listDestroy, game.items, pos.x, pos.y);
				} 
				else if (Keyboard::isKeyPressed(Keyboard::Q)) 
				{
					mainPerson.throwItem(game.field, *game.items);
				} 
				else if (Keyboard::isKeyPressed(Keyboard::E)) 
				{
					mainPerson.actionMain(game.field, game.unlifeObjects, *game.listDestroy, game.items, pos.x, pos.y);// ИСПРАВЬ
				} 
				else if (Keyboard::isKeyPressed(Keyboard::R)) 
				{
					mainPerson.takeItem(game.field, *game.items, pos.x, pos.y);
				}
				/////////////////////////////////////////////////////////////////////////////////////////
				// Бег
				else if (Keyboard::isKeyPressed(Keyboard::LShift)) {
					if (mainPerson.step.stepCurrent > mainPerson.step.stepFirst) {
						mainPerson.step.stepCurrent = mainPerson.step.stepFirst;
						mainPerson.stamina.needMinusStamina = false;
					} else {
						mainPerson.step.stepCurrent = mainPerson.step.stepFirst * 3;
						mainPerson.stamina.needMinusStamina = true;
					}
				}
				/////////////////////////////////////////////////////////////////////////////////////////
				// Обработка 0 - 9. Панель быстрого доступа
				else if (Keyboard::isKeyPressed(Keyboard::Num0)) {
					mainPerson.idSelectItem = 9;
				} else if (Keyboard::isKeyPressed(Keyboard::Num1)) {
					mainPerson.idSelectItem = 0;
				} else if (Keyboard::isKeyPressed(Keyboard::Num2)) {
					mainPerson.idSelectItem = 1;
				} else if (Keyboard::isKeyPressed(Keyboard::Num3)) {
					mainPerson.idSelectItem = 2;
				} else if (Keyboard::isKeyPressed(Keyboard::Num4)) {
					mainPerson.idSelectItem = 3;
				} else if (Keyboard::isKeyPressed(Keyboard::Num5)) {
					mainPerson.idSelectItem = 4;
				} else if (Keyboard::isKeyPressed(Keyboard::Num6)) {
					mainPerson.idSelectItem = 5;
				} else if (Keyboard::isKeyPressed(Keyboard::Num7)) {
					mainPerson.idSelectItem = 6;
				} else if (Keyboard::isKeyPressed(Keyboard::Num8)) {
					mainPerson.idSelectItem = 7;
				} else if (Keyboard::isKeyPressed(Keyboard::Num9)) {
					mainPerson.idSelectItem = 8;
				}

			}
			/////////////////////////////////////////////////////////////////////////////////////////

			//////////////////////////////////////////////////////////////////////////////////
			// Оюработка щелчка мыши
			if (event.type == Event::MouseButtonPressed) {
				// Использование предмета
				mainPerson.useItem(game.field, *game.listDestroy, deltaTime,
													 game.typesItem, game.typesUnlifeObject->typeUnlifeObject, game.Enemys,
													 game.items, game.unlifeObjects, event, pos.x, pos.y);// ИСПРАВЬ
				//mainPerson.modeProcess(*game.field, game.unlifeObjects , game.items, event, pos.x, pos.y);// ИСПРАВЬ
			}
			//////////////////////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////////////////////////////
			// Для направление взгляда
			mainPerson.computeAngle(window);// ИСПРАВЬ
			/////////////////////////////////////////////////////////////////////////////////////////

		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// То что в любом случае обрабатываестя

		/////////////////////////////////////////////////////////////
		// Для обновления окна
		// получение размера окна
		if (event.type == sf::Event::Resized) {
			unsigned int width = window.getSize().x;
			unsigned int height = window.getSize().y;
			game.widthMainWindow = width;
			game.heightMainWindow = height;

			window.create(VideoMode(width, height), TITLE_PROGRAM);
		}
		/////////////////////////////////////////////////////////////


		// Окно закрыли
		if (event.type == Event::Closed)
		{
			window.close();
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
}

void render(Game & game)
{
	RenderWindow &window = game.window;
	window.clear();

	//////////////////////////////////////////////
	// Отрисовка карты
	MainPerson &mainPerson = game.mainPerson;
	Field &field = game.field;
	bool isEmpty(false);
	
	int l = 0;
	while (l < HEIGHT_MAP)
	{
		// Рисуем только текущий уровень
		if (l >= mainPerson.currentLevelFloor - 1
			&& l <= mainPerson.currentLevelFloor + 2)
		{
			for (int i = 0; i < LONG_MAP; i++)
			{
				for (int j = 0; j < WIDTH_MAP - BORDER1; j++)
				{
					field.setTypeSprite(mainPerson.currentLevelFloor, l, i, j);

					window.draw(*field.wallSprite);
					window.draw(*field.floorSprite);

				}
			}
		}
		
		l++;
	}

	//////////////////////////////////////////////
	// Отрисовка предметов
	vector<Item> &items = *game.items;
	for (int i = 0; i != items.size(); ++i) {
		if (items[i].currentLevel >= game.mainPerson.currentLevelFloor
				&& items[i].currentLevel <= game.mainPerson.currentLevelFloor + 2) {


			if (items[i].currentLevel == game.mainPerson.currentLevelFloor)
			{
				items[i].mainSprite->setColor(DOWN_VIEW);
			}
			else if (items[i].currentLevel == game.mainPerson.currentLevelFloor + 1) {
				items[i].mainSprite->setColor(NORMAL_VIEW);
			}
			else if (items[i].currentLevel == game.mainPerson.currentLevelFloor + 2) {
				items[i].mainSprite->setColor(UP_VIEW);
			}

			window.draw(*items[i].mainSprite);
			//window.draw(*game.items->item[i].spriteForUse);// ИСПРАВЬ
		}

	}

	//////////////////////////////////////////////
	// Отрисовка главного персонажа
	window.draw(*mainPerson.spriteEntity);

	////////////////////////////////////////////////////////
	// Сущности
	renderEntitys(game);

	////////////////////////////////////////////////////////
	// Рисуем неживые объекты
	int currentLevel = game.mainPerson.currentLevelFloor;
	vector<UnlifeObject> &unlifeObjects = *game.unlifeObjects;
	for (int i = 0; i != unlifeObjects.size(); ++i)
	{
		if (unlifeObjects[i].currentLevel >= currentLevel
				&& unlifeObjects[i].currentLevel <= currentLevel + 2)
		{
			if (unlifeObjects[i].currentLevel == currentLevel)
			{
				unlifeObjects[i].spriteObject->setColor(DOWN_VIEW);
				unlifeObjects[i].transparentSpiteObject->setColor(DOWN_VIEW);
			}
			/*
			else if (unlifeObjects[i].currentLevel == currentLevel + 1)
			{
				unlifeObjects[i].spriteObject->setColor(NORMAL_VIEW);
				unlifeObjects[i].transparentSpiteObject->setColor(NORMAL_VIEW);
			}
			*/
			else if (unlifeObjects[i].currentLevel == currentLevel + 2) {
				unlifeObjects[i].spriteObject->setColor(UP_VIEW);
				unlifeObjects[i].transparentSpiteObject->setColor(UP_VIEW);
			}

			window.draw(*unlifeObjects[i].spriteObject);
			window.draw(*unlifeObjects[i].transparentSpiteObject);
		}
		
	}

	//////////////////////////////////////////////
	// GUI
	game.gui.setPositionGui(window, game.mainPerson, *game.Enemys, game.textGame);
	//////////////////////////////////////////////
	window.display();
}

void startGame()
{
	// Объявление игры
	Game *game = new Game();
	initializeGame(*game);

	RenderWindow &window = game->window;
	MainPerson &mainPerson = game->mainPerson;

	Time timeSinceLastUpdate = Time::Zero;

	while (window.isOpen())
	{
		timeSinceLastUpdate += game->clock.restart();
		//printf("FPS: %f\n", 1.f / timeSinceLastUpdate.asSeconds());// ИСПРАВЬ
		while (timeSinceLastUpdate > TIME_PER_FRAME) {
			timeSinceLastUpdate -= TIME_PER_FRAME;
			processEvents(*game, TIME_PER_FRAME);
			////////////////////////////////////////////////////////////
			// Если персонаж жив
			if (mainPerson.isDeath == false) {
				printf("TIMEPERSON %f\n", mainPerson.animation.currentTimeFightAnimation);
				mainPerson.update(TIME_PER_FRAME, game->databaseSound);
				mainPerson.updateAtack(game->Enemys, game->items, game->typesItem, TIME_PER_FRAME);
				mainPerson.interactionWithMap(game->field, *game->listDestroy, TIME_PER_FRAME);
				mainPerson.interactionWitnUnlifeObject(game->unlifeObjects, TIME_PER_FRAME);
				mainPerson.getCoordinateForView(mainPerson.getXPos(), mainPerson.getYPos());

				/////////////////////////////////////
				// Взаимодействие существ с миром
				updateEntity(*game, TIME_PER_FRAME);
				
				/////////////////////////////////////

				mainPerson.updateView(game->window);
				window.setView(*mainPerson.view);

				//printf("Angle %f \n", game->mainPerson->rotation);// ИСПРАВЬ
			}
			////////////////////////////////////////////////////////////
		}
		render(*game);
		//writeMap(game->field->dataMap);
	}
	destroyGame(*game);
}

int main()
{
	startGame();
	return 0;
}

