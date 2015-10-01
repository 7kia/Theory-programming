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
		/////////////////////////////////////////////////////////////////////////////////////////
		// Проверяем случаи нажатия нескольких стрелок
		if (Keyboard::isKeyPressed(Keyboard::Up) && Keyboard::isKeyPressed(Keyboard::Left))
		{
			game.mainPerson.direction = Direction::UP_LEFT;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Up) && Keyboard::isKeyPressed(Keyboard::Right))
		{
			game.mainPerson.direction = Direction::UP_RIGHT;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down) && Keyboard::isKeyPressed(Keyboard::Left))
		{
			game.mainPerson.direction = Direction::DOWN_LEFT;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down) && Keyboard::isKeyPressed(Keyboard::Right))
		{
			game.mainPerson.direction = Direction::DOWN_RIGHT;
		}
		/////////////////////////////////////////////////////////////////////////////////////////
		// Проверяем одну стрелку
		else if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			game.mainPerson.direction = UP;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			game.mainPerson.direction = DOWN;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			game.mainPerson.direction = LEFT;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			game.mainPerson.direction = RIGHT;
		}
		else
		{
			game.mainPerson.direction = NONE;
		}
		/////////////////////////////////////////////////////////////////////////////////////////


		//////////////////////////////////////////////////////////////////////////////////
		// Оюработка щелчка мыши
		if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
		{
			Vector2i mousePos = Mouse::getPosition(window);//забираем коорд курсора
			Vector2f pos = window.mapPixelToCoords(mousePos);//переводим их в игровые (уходим от коорд окна)

			int numberY(pos.y / 32);
			int numberX(pos.x / 32);

			game.mainPerson.modeProcess(game.field.dataMap, event, numberX, numberY);
		}
		//////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////
		// Обработка 0 - 9
		if (Keyboard::isKeyPressed(Keyboard::Num0))
		{
			game.mainPerson.idSelectItem = 0;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num1))
		{
			game.mainPerson.idSelectItem = 1;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num2))
		{
			game.mainPerson.idSelectItem = 2;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num3))
		{
			game.mainPerson.idSelectItem = 3;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num4))
		{
			game.mainPerson.idSelectItem = 4;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num5))
		{
			game.mainPerson.idSelectItem = 5;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num6))
		{
			game.mainPerson.idSelectItem = 6;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num7))
		{
			game.mainPerson.idSelectItem = 7;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num8))
		{
			game.mainPerson.idSelectItem = 8;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num9))
		{
			game.mainPerson.idSelectItem = 9;
		}
		/////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////
		// Для направление взгляда
		game.mainPerson.computeAngle(window);
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
	Field & field = game.field;
	//int BLOCK_SIZE = game.field.BLOCK_SIZE;
	bool isEmpty(false);

	window.clear();

	for (int l = 0; l < HeightMap; l++)
	{
		for (int i = 0; i < LongMap; i++)
		{
			for (int j = 0; j < WidthMap; j++)
			{
				game.field.setTypeSprite(l, i, j);

				window.draw(*field.floorSprite);
				window.draw(*field.wallSprite);
			}
		}

	}
	//////////////////////////////////////////////

	window.draw(*game.mainPerson.spritePerson);
	window.display();
}

void startGame()
{
	RenderWindow window(VideoMode(800, 600), "mainPerson");

	Game game;
	initializeGame(game);

	Time timeSinceLastUpdate = Time::Zero;

	while (window.isOpen())
	{

		timeSinceLastUpdate += game.clock.restart();
		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;
			processEvents(window, game);
			game.mainPerson.update(TIME_PER_FRAME);
			game.mainPerson.interactionWithMap(game.field.dataMap, TIME_PER_FRAME);

			window.setView(*game.mainPerson.view);

			//printf("Angle %f \n", game.mainPerson.rotation);//смотрим на градусы в консольке	
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

