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
		Vector2i mousePos = Mouse::getPosition(window);
		Vector2f pos = window.mapPixelToCoords(mousePos);

		int numberY(pos.y / sizeTile);
		int numberX(pos.x / sizeTile);

		/////////////////////////////////////////////////////////////////////////////////////////
		// ��������� ������ ������� ���������� �������

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
		// ��������� ���� �������
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
		// ������������ �������
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
		// ������ "�������" � "������ ��������"
		else if (Keyboard::isKeyPressed(Keyboard::Q))
		{
			game.mainPerson->actionAlternative(*game.field, numberX, numberY);
			printf("Alternative action\n");
		}
		else if (Keyboard::isKeyPressed(Keyboard::E))
		{
			game.mainPerson->actionMain(*game.field, numberX, numberY);
			printf("Main action\n");
		}
		/////////////////////////////////////////////////////////////////////////////////////////
		else if (Keyboard::isKeyPressed(Keyboard::LShift))
		{
			if (game.mainPerson->stepCurrent > game.mainPerson->stepFirst)
			{
				game.mainPerson->stepCurrent -= 350.f;
			}
			else
			{
				game.mainPerson->stepCurrent += 350.f;
			}
			
		}
		/////////////////////////////////////////////////////////////////////////////////////////
		// ��������� 0 - 9
		else if (Keyboard::isKeyPressed(Keyboard::Num0))
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
		// ��������� ������ ����
		if (event.type == Event::MouseButtonPressed)//���� ������ ������� ����
		{
			game.mainPerson->modeProcess(*game.field, event, numberX, numberY);
		}
		//////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////
		// ��� ����������� �������
		game.mainPerson->computeAngle(window);
		/////////////////////////////////////////////////////////////////////////////////////////

		// ���� �������
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
	// ��������� �����
	//int BLOCK_SIZE = game.field.BLOCK_SIZE;
	Field &field = *game.field;
	bool isEmpty(false);

	window.clear();
	
	int l = 0;
	while (l < HeightMap)
	{
		//printf("%f %f\n", game.mainPerson->currentLevelFloor,
		//	game.mainPerson->currentLevelFloor );
		// ������ ������ ������� �������
		if (l == game.mainPerson->currentLevelFloor
			|| l == game.mainPerson->currentLevelFloor + 1)
		{
			for (int i = 0; i < LongMap; i++)
			{
				for (int j = 0; j < WidthMap - border1; j++)
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
	window.draw(*game.mainPerson->spriteEntity);

	////////////////////////////////////////////////////////
	// ������ ������� �������
	for (int i = 0; i < game.unlifeObjects->countObject; i++)
	{
		//UnlifeObject &unlifeObject = *game.unlifeObjects->unlifeObject[i];
		//window.draw(unlifeObjects[i].spriteObject);
		if (game.unlifeObjects->unlifeObject[i].currentLevel == game.mainPerson->currentLevelFloor + 1)
		{
			window.draw(*game.unlifeObjects->unlifeObject[i].spriteObject);
		}
		
	}
	////////////////////////////////////////////////////////

	window.display();
}

void startGame()
{
	Game *game = new Game();
	initializeGame(*game);

	RenderWindow window(VideoMode(game->widthMainWindow, game->heightMainWindow), "MainGame v1.0.6");

	Time timeSinceLastUpdate = Time::Zero;


	MainPerson &mainPerson = *game->mainPerson;
	while (window.isOpen())
	{
		timeSinceLastUpdate += game->clock->restart();
		//printf("FPS: %f\n", 1.f / timeSinceLastUpdate.asSeconds());
		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{

			timeSinceLastUpdate -= TIME_PER_FRAME;
			processEvents(window, *game);

			mainPerson.update(TIME_PER_FRAME, *game->databaseSound);
			mainPerson.interactionWithMap(*game->field, TIME_PER_FRAME);
			mainPerson.interactionWitnUnlifeObject(*game->unlifeObjects, TIME_PER_FRAME);
			mainPerson.getCoordinateForView(mainPerson.getXPos(), mainPerson.getYPos());

			window.setView(*mainPerson.view);

			//printf("Angle %f \n", game.Entity.rotation);//������� �� ������� � ���������	
		}
		render(window, *game);
	}
	destroyGame(*game);
}

int main()
{
	startGame();
	return 0;
}

