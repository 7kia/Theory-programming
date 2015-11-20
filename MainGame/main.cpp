#include <SFML/Graphics.hpp>

#include "Game.h"

const Time TIME_PER_FRAME = seconds(1.f / 60.f);
const float faultWorldTime = 0.03f;

using namespace sf;
using namespace std;

void processEvents(Game &game, const Time &deltaTime)
{
	Event event;
	RenderWindow &window = game.window;
	while (window.pollEvent(event)) {

	
		MainPerson &mainPerson = game.mainPerson;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// ���� �������� ���
		if (mainPerson.isDeath == false) {
			Vector2i mousePos = Mouse::getPosition(window);
			Vector2f pos = window.mapPixelToCoords(mousePos);

			UnlifeObject* emptyObject = nullptr;
			Item* emptyItem = nullptr;

			informationAboutSelect(game, pos.x, pos.y);

			/////////////////////////////////////////////////////////////////////////////////////////
			// ��������� ������ ������� ���������� �������
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
			// ��������� ���� �������
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
			// ������������ �������
			if (event.type == Event::KeyPressed) {
				if (Keyboard::isKeyPressed(Keyboard::G)) {
					//mainPerson.currenMode = idEntityMode::build;// �������

				} else if (Keyboard::isKeyPressed(Keyboard::F)) {
					//mainPerson.currenMode = idModeEntity::fight;// �������

				}
			}
			/////////////////////////////////////////////////////////////////////////////////////////
			// ������ "�������" � "������ ��������"
			int numberY(pos.y / SIZE_BLOCK);
			int numberX(pos.x / SIZE_BLOCK);

			if (event.type == Event::KeyPressed) {
				if (Keyboard::isKeyPressed(Keyboard::C)) 
				{
					if (mainPerson.isInUseField(pos.x, pos.y, true)) {
						mainPerson.actionAlternate(game.world, pos);// �������
					}
				} 
				else if (Keyboard::isKeyPressed(Keyboard::Q)) 
				{
					mainPerson.throwItem(game.world.field, *game.world.items);
				} 
				else if (Keyboard::isKeyPressed(Keyboard::E)) 
				{
					if (mainPerson.isInUseField(pos.x, pos.y, true)) {
						mainPerson.actionMain(game.world, pos);// �������
					}
				} 
				else if (Keyboard::isKeyPressed(Keyboard::R)) 
				{
					mainPerson.takeItem(game.world, pos);
				}
				/////////////////////////////////////////////////////////////////////////////////////////
				// ���
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
				// ��������� 0 - 9. ������ �������� �������
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
			// ��������� ������ ����
			if (event.type == Event::MouseButtonPressed) {
				// ������������� ��������
				mainPerson.useItem(game.world, deltaTime, event, pos);// �������
				//mainPerson.modeProcess(*game.field, game.unlifeObjects , game.items, event, pos.x, pos.y);// �������
			}
			//////////////////////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////////////////////////////
			// ��� ����������� �������
			mainPerson.computeAngle(window);// �������
			/////////////////////////////////////////////////////////////////////////////////////////

		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// �� ��� � ����� ������ ��������������

		/////////////////////////////////////////////////////////////
		// ��� ���������� ����
		// ��������� ������� ����
		if (event.type == sf::Event::Resized) {
			unsigned int width = window.getSize().x;
			unsigned int height = window.getSize().y;
			game.widthMainWindow = width;
			game.heightMainWindow = height;

			window.create(VideoMode(width, height), TITLE_PROGRAM);
		}
		/////////////////////////////////////////////////////////////


		// ���� �������
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
	// ��������� �����
	MainPerson &mainPerson = game.mainPerson;
	Field &field = game.world.field;
	bool isEmpty(false);
	
	int l = mainPerson.currentLevelFloor;
	int lowBorder = l - 1;
	if (lowBorder < 0)
		lowBorder = 0;
	int topBorder = l + 2;
	if (topBorder > HEIGHT_MAP - 1)
		topBorder = HEIGHT_MAP - 1;

	l = lowBorder;
	while (l <= topBorder)
	{

		for (int i = 0; i < LONG_MAP; i++) {
			for (int j = 0; j < WIDTH_MAP - BORDER1; j++) {
				field.setTypeSprite(mainPerson.currentLevelFloor, l, i, j);

				window.draw(*field.wallSprite);
				window.draw(*field.floorSprite);

			}
		}
		
		l++;
	}

	//////////////////////////////////////////////
	// ��������� ���������
	vector<Item> &items = *game.world.items;
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
			//window.draw(*game.items->item[i].spriteForUse);// �������
		}

	}

	//////////////////////////////////////////////
	// ��������� �������� ���������
	mainPerson.renderCurrentItem(window);
	window.draw(*mainPerson.spriteEntity);

	////////////////////////////////////////////////////////
	// ��������


	renderEntitys(game);

	////////////////////////////////////////////////////////
	// ������ ������� �������
	renderUnlifeObjects(game);

	game.gui.setPositionGui(window, game.mainPerson, *game.world.Enemys, game.textGame);
	window.display();
}

void updatePlayer(Game &game, MainPerson& mainPerson)
{
	mainPerson.update(TIME_PER_FRAME, game.databaseSound);
	mainPerson.updateAtack(game.world, TIME_PER_FRAME);
	mainPerson.interactionWithMap(game.world.field, *game.world.listDestroy, TIME_PER_FRAME);
	mainPerson.interactionWitnUnlifeObject(game.world.unlifeObjects, TIME_PER_FRAME);
	mainPerson.getCoordinateForView(mainPerson.getXPos(), mainPerson.getYPos());

	mainPerson.updateView(game.window);
	game.window.setView(*mainPerson.view);

	//printf("Angle %f \n", mainPerson.rotation);// �������
}

void generateGroups(Game &game)
{
	world &world = game.world;
	bool &needGenerateWave = world.waveEnemysCreated;
	float currentWorldTime = world.worldTime.getElapsedTime().asSeconds();

	bool condition = int(currentWorldTime) % TIME_GENERATE_WAVE_ENEMYS == 0;
	if(condition && needGenerateWave == false)
	{
		Vector3i pos = { 10, 10, 1 };
		createSmallGroupSkelets(game.world, pos);
	}

}

void updateWorldTimeCircles(Game &game)
{
	world &world = game.world;
	float currentWorldTime = world.worldTime.getElapsedTime().asSeconds();

	if (currentWorldTime - int(currentWorldTime) <= faultWorldTime) {
		generateGroups(game);

		printf("World time: %f\n", currentWorldTime);
	}
}

void showFPS(Game &game, const Time timeSinceLastUpdate)
{
	world &world = game.world;
	float currentWorldTime = world.worldTime.getElapsedTime().asSeconds();

	if (currentWorldTime - int(currentWorldTime) <= faultWorldTime) {
		world.lastSecond += 1.f;
		printf("FPS: %f\n", 1.f / timeSinceLastUpdate.asSeconds());
	}
}

void startGame()
{
	// ���������� ����
	Game *game = new Game();
	initializeGame(*game);

	RenderWindow &window = game->window;
	MainPerson &mainPerson = game->mainPerson;

	Time timeSinceLastUpdate = Time::Zero;

	while (window.isOpen())
	{
		timeSinceLastUpdate += game->clock.restart();
		while (timeSinceLastUpdate > TIME_PER_FRAME) {
			timeSinceLastUpdate -= TIME_PER_FRAME;
			processEvents(*game, TIME_PER_FRAME);

			if (mainPerson.isDeath == false) {
				updatePlayer(*game, mainPerson);
				updateEntity(*game, TIME_PER_FRAME);
				updateWorldTimeCircles(*game);
			}
			////////////////////////////////////////////////////////////
		}
		render(*game);
		
		showFPS(*game, timeSinceLastUpdate);
		//writeMap(game->field->dataMap);
	}
	destroyGame(*game);
}

int main()
{
	startGame();
	return 0;
}

