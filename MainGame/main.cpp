#include <SFML/Graphics.hpp>

#include "Game.h"

const Time TIME_PER_FRAME = seconds(1.f / 60.f);

using namespace sf;
using namespace std;

void processEvents(RenderWindow & window, Game &game)
{
	Event event;
	while (window.pollEvent(event))
	{
		Vector2i mousePos = Mouse::getPosition(window);//забираем коорд курсора
		Vector2f pos = window.mapPixelToCoords(mousePos);//переводим их в игровые (уходим от коорд окна)

		int numberY(pos.y / sizeTile);
		int numberX(pos.x / sizeTile);

		/////////////////////////////////////////////////////////////////////////////////////////
		// Проверяем случаи нажатия нескольких стрелок
		if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::A))
		{
			game.mainPerson->direction = Direction::UP_LEFT;
		}
		else if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::D))
		{
			game.mainPerson->direction = Direction::UP_RIGHT;
		}
		else if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::A))
		{
			game.mainPerson->direction = Direction::DOWN_LEFT;
		}
		else if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::D))
		{
			game.mainPerson->direction = Direction::DOWN_RIGHT;
		}
		/////////////////////////////////////////////////////////////////////////////////////////
		// Проверяем одну стрелку
		else if (Keyboard::isKeyPressed(Keyboard::W))
		{
			game.mainPerson->direction = UP;
		}
		else if (Keyboard::isKeyPressed(Keyboard::S))
		{
			game.mainPerson->direction = DOWN;
		}
		else if (Keyboard::isKeyPressed(Keyboard::A))
		{
			game.mainPerson->direction = LEFT;
		}
		else if (Keyboard::isKeyPressed(Keyboard::D))
		{
			game.mainPerson->direction = RIGHT;
		}
		else
		{
			game.mainPerson->direction = NONE;
		}
		/////////////////////////////////////////////////////////////////////////////////////////
		// Переключение режимов
		if (Keyboard::isKeyPressed(Keyboard::G))
		{
			game.mainPerson->currenMode = idModeEntity::build;
			printf("build mode\n");
		}
		else if (Keyboard::isKeyPressed(Keyboard::F))
		{
			game.mainPerson->currenMode = idModeEntity::fight;
			printf("fight mode\n");
		}
		/////////////////////////////////////////////////////////////////////////////////////////
		// кнопка "Дествие" и "Другое действие"
		else if (Keyboard::isKeyPressed(Keyboard::Q))
		{
			game.mainPerson->actionAlternative(*game.field, numberX, numberY);
			//game.mainPerson->currenMode = idModeEntity::fight;
			printf("Alternative action\n");
		}
		else if (Keyboard::isKeyPressed(Keyboard::E))
		{
			game.mainPerson->actionMain(*game.field, numberX, numberY);
			//game.mainPerson->currenMode = idModeEntity::fight;
			printf("Main action\n");
		}
		/////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////
		// Обработка 0 - 9
		if (Keyboard::isKeyPressed(Keyboard::Num0))
		{
			game.mainPerson->idSelectItem = 0;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num1))
		{
			game.mainPerson->idSelectItem = 1;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num2))
		{
			game.mainPerson->idSelectItem = 2;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num3))
		{
			game.mainPerson->idSelectItem = 3;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num4))
		{
			game.mainPerson->idSelectItem = 4;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num5))
		{
			game.mainPerson->idSelectItem = 5;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num6))
		{
			game.mainPerson->idSelectItem = 6;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num7))
		{
			game.mainPerson->idSelectItem = 7;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num8))
		{
			game.mainPerson->idSelectItem = 8;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num9))
		{
			game.mainPerson->idSelectItem = 9;
		}
		/////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////
		// Оюработка щелчка мыши
		if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
		{
			game.mainPerson->modeProcess(*game.field, event, numberX, numberY);
		}
		//////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////
		// Для направление взгляда
		game.mainPerson->computeAngle(window);
		/////////////////////////////////////////////////////////////////////////////////////////

		// Окно закрыли
		if (event.type == Event::Closed)
		{
			window.close();
		}
	}
}

void render(RenderWindow & window, Game & game)
{
	window.clear();

	//////////////////////////////////////////////
	// Отрисовка карты
	//int BLOCK_SIZE = game.field.BLOCK_SIZE;
	Field &field = *game.field;
	bool isEmpty(false);

	window.clear();
	
	int l = 0;
	while (l < HeightMap)
	{
		//printf("%f %f\n", game.mainPerson->currentLevelFloor,
		//	game.mainPerson->currentLevelFloor );
		// Рисуем только текущий уровень
		if (l == game.mainPerson->currentLevelFloor
			|| l == game.mainPerson->currentLevel)
		{
			for (int i = 0; i < LongMap; i++)
			{
				for (int j = 0; j < WidthMap; j++)
				{
					field.setTypeSprite(game.mainPerson->currentLevelFloor, l, i, j);

					window.draw(*field.floorSprite);
					window.draw(*field.wallSprite);

					//field.resetSprites();
				}
			}
		}
		
		l++;
	}
	//////////////////////////////////////////////
	window.draw(*game.mainPerson->spriteObject);
	window.display();
}

void startGame()
{
	Game game;
	initializeGame(game);

	RenderWindow window(VideoMode(game.widthMainWindow, game.heightMainWindow), "MainGame v1.0.3");

	Time timeSinceLastUpdate = Time::Zero;

	while (window.isOpen())
	{
		timeSinceLastUpdate += game.clock->restart();
		printf("FPS: %f\n", 1.f / timeSinceLastUpdate.asSeconds());
		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{

			timeSinceLastUpdate -= TIME_PER_FRAME;
			processEvents(window, game);

			game.mainPerson->update(TIME_PER_FRAME, *game.databaseSound);
			game.mainPerson->interactionWithMap(*game.field, TIME_PER_FRAME);

			window.setView(*game.mainPerson->view);

			//printf("Angle %f \n", game.Entity.rotation);//смотрим на градусы в консольке	
		}
		render(window, game);
	}
	destroyGame(game);
}

int main()
{
	startGame();
	return 0;
}

