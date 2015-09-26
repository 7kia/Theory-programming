#include <SFML/Graphics.hpp>

#include "variables.h";
#include "generateMaps.h";
#include "enemyQueue.h";
#include "myQueue.h";

using namespace sf;


void processEvents(RenderWindow & window, Sprite *buttons, bool &myQueue, bool &gameNotFinish)
{

	Vector2i mousePos = Mouse::getPosition(window);//�������� ����� �������

	int x(mousePos.x), y(mousePos.y);
	int numberY(y / 32);
	int numberX((x - (sizeRectangleWeb - 1) * 32) / 32);

	Event event;
	while (window.pollEvent(event))
	{
		//Vector2i pixelPos = Mouse::getPosition(window);//�������� ����� �������

		//////////////////////////////////////////////////////////////////////////////////
		// ��������� ������ ����
		if (event.type == Event::MouseButtonPressed)//���� ������ ������� ����
			if (event.key.code == Mouse::Left)//� ������ �����
			{

				//////////////////////////////////////////////////////////////////////////////////
				// ������ ������
				if (buttons[0].getGlobalBounds().contains(mousePos.x, mousePos.y))
				{
					//////////////////////////////////////////////////////////////////////////////////
					// ������ ����� ����

					////////////////////////////////////////
					// ���������� ������ ����������
					countMyDestroyShips = countEnemyDestroyShips = 0;// ������� ���� � ��������� ��������
					lastTile[0] = lastTile[1] = 0;// ������ ������ ��������� � ���� ����
					direction = x = y = 0;// ����������� �������
					findDirection =false;
					directionNotRedefine = true;
					findShip = false;// ���� ������� ������� 2 ������ �� ���������� ��������� �����				
					for (int i = 0; i < 3; i++)
					{
						memberDirection[i] = 0;
					}
					/////////////////////////////////////////

					/////////////////////////////////////////
					// ��������� ����
					gameNotFinish = true;
					myQueue = true;
					/////////////////////////////////////////

					/////////////////////////////////////////
					// ��� ������ ��������� � ��������� ������� ��������
					isFindStart = false;
					isNotFindEnd = true;
					isNotDestroyShip = true;
					countTile = 0;
					/////////////////////////////////////////

					generateMaps(amountShips,
						amountEveryType, myPlace, enemyPlace,
						coordinatesMyShips, coordinatesEnemyShips);
					//////////////////////////////////////////////////////////////////////////////////
				}
				if (buttons[1].getGlobalBounds().contains(mousePos.x, mousePos.y))
				{
					// ������ �����
					window.close();
				}
				//////////////////////////////////////////////////////////////////////////////////

				if (gameNotFinish)
				{
					///////////////////////////////////////////////////////
					// ��� ������
					if (myQueue)
					{
						ifMyQueue(numberX, numberY, countEnemyDestroyShips, victoryNumber,
							enemyPlace, coordinatesEnemyShips,
							isNotFindEnd, isFindStart, gameNotFinish, myQueue);
					}
					///////////////////////////////////////////////////////
				}


			}
		//////////////////////////////////////////////////////////////////////////////////


		// ���� �������
		if (event.type == Event::Closed)
		{
			window.close();
		}
	}
}

void render(RenderWindow &window, Sprite &mapSprite, Sprite *buttons,
	char(*myPlace)[sizeRectangleWeb], char(*enemyPlace)[sizeRectangleWeb])
{
	window.clear();

	// ��������� �����
	for (int i = 1; i < sizeRectangleWeb - 1; i++)
		for (int j = 1; j < sizeRectangleWeb - 1; j++)
		{
			if (myPlace[i][j] == '_')  mapSprite.setTextureRect(IntRect(0, 0, 32, 32));
			if (myPlace[i][j] == '0') mapSprite.setTextureRect(IntRect(32, 0, 32, 32));
			if (myPlace[i][j] == '#') mapSprite.setTextureRect(IntRect(64, 0, 32, 32));
			if (myPlace[i][j] == 'X') mapSprite.setTextureRect(IntRect(96, 0, 32, 32));

			mapSprite.setPosition(j * 32, i * 32);
			window.draw(mapSprite);


			if (enemyPlace[i][j] == '_')  mapSprite.setTextureRect(IntRect(128, 0, 32, 32));
			if (enemyPlace[i][j] == '0') mapSprite.setTextureRect(IntRect(32, 0, 32, 32));
			if (enemyPlace[i][j] == '#') mapSprite.setTextureRect(IntRect(128, 0, 32, 32));
			if (enemyPlace[i][j] == 'X') mapSprite.setTextureRect(IntRect(96, 0, 32, 32));

			mapSprite.setPosition(j * 32 + (sizeRectangleWeb - 1) * 32, i * 32);
			window.draw(mapSprite);
		}

	// ��������� ������
	buttons[0].setTextureRect(IntRect(0, 0, 96, 32));
	buttons[1].setTextureRect(IntRect(0, 32, 96, 32));

	buttons[0].setPosition((sizeRectangleWeb - 2) * 32, (sizeRectangleWeb - 2) * 32 + 64);
	buttons[1].setPosition((sizeRectangleWeb - 2) * 32, (sizeRectangleWeb - 2) * 32 + 108);

	window.draw(buttons[0]);
	window.draw(buttons[1]);


	window.display();
}


void startGame()
{
	RenderWindow window(VideoMode((sizeRectangleWeb * 2 - 1) * 32, (sizeRectangleWeb + 3) * 32), "Sea war");

	///////////////////////////////////////////////////////
	// �������� �������
	sf::Sprite mapSprite, buttons[2];
	sf::Texture textureTile;
	sf::Texture textureButtons;

	textureButtons.loadFromFile("recourses\\images\\Buttons.png");
	textureTile.loadFromFile("recourses\\images\\map.png");
	mapSprite.setTexture(textureTile);

	buttons[0].setTexture(textureButtons);
	buttons[1].setTexture(textureButtons);
	///////////////////////////////////////////////////////
	//labelStartGame:


	generateMaps(amountShips,
		amountEveryType, myPlace, enemyPlace,
		coordinatesMyShips, coordinatesEnemyShips);

	// ����� �� ���� ������ ������ ����
	Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		processEvents(window, buttons, myQueue, gameNotFinish);

		if (gameNotFinish)
		{
			if (myQueue == false)
			{
				enemyQueue(myPlace, direction,
					countMyDestroyShips, victoryNumber, lastTile,
					coordinatesMyShips, memberDirection,
					findDirection, findShip, myQueue, gameNotFinish,
					x, y);
			}
		}
		render(window, mapSprite, buttons, myPlace, enemyPlace);
	}
}

int main()
{
	startGame();
	return 0;
}
