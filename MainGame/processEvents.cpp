#include "processEvents.h"

void Game::processEvents(const float deltaTime)
{
	Event event;
	while (window.pollEvent(event)) {

		bool isClosed = event.type == Event::Closed;
		bool isResized = event.type == sf::Event::Resized;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Если персонаж жив
		if (mainPerson.isDeath == false) {
			Vector2i mousePos = Mouse::getPosition(window);
			Vector2f pos = window.mapPixelToCoords(mousePos);

			UnlifeObject* emptyObject = nullptr;
			Item* emptyItem = nullptr;

			informationAboutSelect(pos.x, pos.y);

			processArrows();
			/////////////////////////////////////////////////////////////////////////////////////////
			// кнопка "Дествие" и "Другое действие"
			int numberY(pos.y / SIZE_BLOCK);
			int numberX(pos.x / SIZE_BLOCK);

			if (event.type == Event::KeyPressed) {
				if (Keyboard::isKeyPressed(Keyboard::C)) {
					if (mainPerson.isInUseField(pos.x, pos.y, true)) {
						mainPerson.actionAlternate(world, pos);// ИСПРАВЬ
					}
				} else if (Keyboard::isKeyPressed(Keyboard::Q)) {
					mainPerson.throwItem(world.field, *world.items);
				} else if (Keyboard::isKeyPressed(Keyboard::E)) {
					if (mainPerson.isInUseField(pos.x, pos.y, true)) {
						mainPerson.actionMain(world, pos);// ИСПРАВЬ
					}
				} else if (Keyboard::isKeyPressed(Keyboard::R)) {
					mainPerson.takeItem(world, pos);
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
				mainPerson.useItem(world, event, pos);// ИСПРАВЬ
																							//mainPerson.modeProcess(*game.field, game.unlifeObjects , game.items, event, pos.x, pos.y);// ИСПРАВЬ
			}
			//////////////////////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////////////////////////////
			// Для направление взгляда
			mainPerson.computeAngle(window);// ИСПРАВЬ
																			/////////////////////////////////////////////////////////////////////////////////////////

		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		switch(event.type)
		{
		case Event::Closed:
			window.close();
			break;
		case Event::Resized:
			resizeWindow();
			break;
		default:
			break;
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
}

void Game::processArrows()
{
	if (Keyboard::isKeyPressed(keys.Up) && Keyboard::isKeyPressed(keys.Left)) {
		mainPerson.directions.directionWalk = Direction::UP_LEFT;
	} else if (Keyboard::isKeyPressed(keys.Up) && Keyboard::isKeyPressed(keys.Right)) {
		mainPerson.directions.directionWalk = Direction::UP_RIGHT;
	} else if (Keyboard::isKeyPressed(keys.Down) && Keyboard::isKeyPressed(keys.Left)) {
		mainPerson.directions.directionWalk = Direction::DOWN_LEFT;
	} else if (Keyboard::isKeyPressed(keys.Down) && Keyboard::isKeyPressed(keys.Right)) {
		mainPerson.directions.directionWalk = Direction::DOWN_RIGHT;
	}
	else if (Keyboard::isKeyPressed(keys.Up)) {
		mainPerson.directions.directionWalk = UP;
	} else if (Keyboard::isKeyPressed(keys.Down)) {
		mainPerson.directions.directionWalk = DOWN;
	} else if (Keyboard::isKeyPressed(keys.Left)) {
		mainPerson.directions.directionWalk = LEFT;
	} else if (Keyboard::isKeyPressed(keys.Right)) {
		mainPerson.directions.directionWalk = RIGHT;
	} else {
		mainPerson.directions.directionWalk = NONE_DIRECTION;
	}
}


void Game::resizeWindow()
{
	unsigned int width = window.getSize().x;
	unsigned int height = window.getSize().y;
	widthMainWindow = width;
	heightMainWindow = height;

	window.create(VideoMode(width, height), TITLE_PROGRAM);
}