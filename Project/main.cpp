#include <SFML/Graphics.hpp>

#include "Game.h"

const Time TIME_PER_FRAME = seconds(1.f / 60.f);

using namespace sf;
using namespace std;

void processEvents(Game &game)
{
	Event event;
	RenderWindow &window = *game.window;
	while (window.pollEvent(event)) {

	
		MainPerson &mainPerson = *game.mainPerson;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// ���� �������� ���
		if (mainPerson.isDeath == false) {
			Vector2i mousePos = Mouse::getPosition(window);
			Vector2f pos = window.mapPixelToCoords(mousePos);

			UnlifeObject* emptyObject = NULL;
			Item* emptyItem = NULL;

			mainPerson.findObject = emptyObject;
			mainPerson.findItem = emptyItem;


			informationAboutSelect(game, pos.x, pos.y);

			/////////////////////////////////////////////////////////////////////////////////////////
			// ��������� ������ ������� ���������� �������
			if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::A)) {
				mainPerson.direction = Direction::UP_LEFT;
			} else if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::D)) {
				mainPerson.direction = Direction::UP_RIGHT;
			} else if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::A)) {
				mainPerson.direction = Direction::DOWN_LEFT;
			} else if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::D)) {
				mainPerson.direction = Direction::DOWN_RIGHT;
			}

			/////////////////////////////////////////////////////////////////////////////////////////
			// ��������� ���� �������
			else if (Keyboard::isKeyPressed(Keyboard::W)) {
				mainPerson.direction = UP;
			} else if (Keyboard::isKeyPressed(Keyboard::S)) {
				mainPerson.direction = DOWN;
			} else if (Keyboard::isKeyPressed(Keyboard::A)) {
				mainPerson.direction = LEFT;
			} else if (Keyboard::isKeyPressed(Keyboard::D)) {
				mainPerson.direction = RIGHT;
			} else {
				mainPerson.direction = NONE;
			}
			/////////////////////////////////////////////////////////////////////////////////////////
			// ������������ �������
			if (event.type == Event::KeyPressed) {
				if (Keyboard::isKeyPressed(Keyboard::G)) {
					//mainPerson.currenMode = idEntityMode::build;// �������
					printf("build mode\n");
				} else if (Keyboard::isKeyPressed(Keyboard::F)) {
					//mainPerson.currenMode = idModeEntity::fight;// �������
					printf("fight mode\n");
				}
			}
			/////////////////////////////////////////////////////////////////////////////////////////
			// ������ "�������" � "������ ��������"
			int numberY(pos.y / SIZE_BLOCK);
			int numberX(pos.x / SIZE_BLOCK);

			if (event.type == Event::KeyPressed) {
				if (Keyboard::isKeyPressed(Keyboard::C)) 
				{
					mainPerson.actionAlternate(*game.field, game.unlifeObjects, *game.listDestroy, game.items, pos.x, pos.y);
				} 
				else if (Keyboard::isKeyPressed(Keyboard::Q)) 
				{
					mainPerson.throwItem(*game.field, *game.items);
				} 
				else if (Keyboard::isKeyPressed(Keyboard::E)) 
				{
					mainPerson.actionMain(*game.field, game.unlifeObjects, *game.listDestroy, game.items, pos.x, pos.y);// �������
				} 
				else if (Keyboard::isKeyPressed(Keyboard::R)) 
				{
					mainPerson.takeItem(*game.field, *game.items, pos.x, pos.y);
				}
				/////////////////////////////////////////////////////////////////////////////////////////
				// ���
				else if (Keyboard::isKeyPressed(Keyboard::LShift)) {
					if (mainPerson.stepCurrent > mainPerson.stepFirst) {
						mainPerson.stepCurrent = mainPerson.stepFirst;
						mainPerson.needMinusStamina = false;
					} else {
						mainPerson.stepCurrent = mainPerson.stepFirst * 3;
						mainPerson.needMinusStamina = true;
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
				mainPerson.useItem(*game.field, *game.listDestroy, 
													 game.typesItem->typesItem, game.typesUnlifeObject->typeUnlifeObject, game.Enemys,
													 game.items, game.unlifeObjects, event, pos.x, pos.y);// �������
				//mainPerson.modeProcess(*game.field, game.unlifeObjects , game.items, event, pos.x, pos.y);// �������
			} else if (event.type == Event::MouseMoved) {// �������
				// ������������ ��������
				if (mainPerson.isMoveItem) {


					if (mainPerson.isInUseField(pos.x, pos.y)) {
						Vector2f position = { pos.x - mainPerson.dMoveItemX, pos.y - mainPerson.dMoveItemY };
						if (mainPerson.findObject != emptyObject) {
							Sprite &spriteObject = *mainPerson.findObject->spriteObject;
							spriteObject.setPosition(position);
						} else if (mainPerson.findItem != emptyItem) {
							Sprite &spriteItem = *mainPerson.findItem->mainSprite;
							spriteItem.setPosition(position);
						}
						// ������ ������ ���������� � ������ ������
						// position = { (float)( (int)position.x/ SIZE_BLOCK) * SIZE_BLOCK - SIZE_BLOCK / 2,
						//	(float)( (int)position.y/ SIZE_BLOCK)* SIZE_BLOCK - SIZE_BLOCK / 2 };

					}
				}
			} else if (event.type == Event::MouseButtonReleased) {
				mainPerson.isMoveItem = false;
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
	RenderWindow &window = *game.window;
	window.clear();

	//////////////////////////////////////////////
	// ��������� �����
	MainPerson &mainPerson = *game.mainPerson;
	Field &field = *game.field;
	bool isEmpty(false);
	
	int l = 0;
	while (l < HEIGHT_MAP)
	{
		// ������ ������ ������� �������
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
	// ��������� ���������
	vector<Item> &items = *game.items;
	for (int i = 0; i != items.size(); ++i) {
		if (items[i].currentLevel == game.mainPerson->currentLevelFloor + 1) {

			window.draw(*items[i].mainSprite);
			//window.draw(*game.items->item[i].spriteForUse);// �������
		}

	}

	//////////////////////////////////////////////
	// ��������� �������� ���������
	window.draw(*mainPerson.spriteEntity);

	////////////////////////////////////////////////////////
	// ��������
	renderEntitys(game);

	////////////////////////////////////////////////////////
	// ������ ������� �������
	vector<UnlifeObject> &unlifeObjects = *game.unlifeObjects;
	for (int i = 0; i != unlifeObjects.size(); ++i)
	{
		if (unlifeObjects[i].currentLevel == game.mainPerson->currentLevelFloor + 1)
		{

			window.draw(*unlifeObjects[i].spriteObject);
			window.draw(*unlifeObjects[i].transparentSpiteObject);
		}
		
	}

	//////////////////////////////////////////////
	// GUI
	game.gui->setPositionGui(window, *game.mainPerson, *game.Enemys, *game.textGame);
	//////////////////////////////////////////////
	window.display();
}

void startGame()
{
	// ���������� ����
	Game *game = new Game();
	initializeGame(*game);

	RenderWindow &window = *game->window;
	MainPerson &mainPerson = *game->mainPerson;

	Time timeSinceLastUpdate = Time::Zero;

	while (window.isOpen())
	{
		timeSinceLastUpdate += game->clock->restart();
		//printf("FPS: %f\n", 1.f / timeSinceLastUpdate.asSeconds());// �������
		while (timeSinceLastUpdate > TIME_PER_FRAME) {
			timeSinceLastUpdate -= TIME_PER_FRAME;
			processEvents(*game);
			////////////////////////////////////////////////////////////
			// ���� �������� ���
			if (mainPerson.isDeath == false) {
				mainPerson.update(TIME_PER_FRAME, *game->databaseSound);
				mainPerson.interactionWithMap(*game->field, *game->listDestroy, TIME_PER_FRAME);
				mainPerson.interactionWitnUnlifeObject(game->unlifeObjects, TIME_PER_FRAME);
				mainPerson.getCoordinateForView(mainPerson.getXPos(), mainPerson.getYPos());

				/////////////////////////////////////
				// �������������� ������� � �����
				vector<Enemy>& Enemys = *game->Enemys;
				for (int i = 0; i != Enemys.size(); ++i) {
					
					Enemys[i].update(TIME_PER_FRAME, *game->databaseSound);
					Enemys[i].interactionWithMap(*game->field, *game->listDestroy, TIME_PER_FRAME);
					Enemys[i].randomWalk(TIME_PER_FRAME);
					mainPerson.attractionEnemy(Enemys[i], TIME_PER_FRAME);

				}
				/////////////////////////////////////

				mainPerson.updateView(*game->window);
				window.setView(*mainPerson.view);

				//printf("Angle %f \n", game->mainPerson->rotation);// �������
			}
			////////////////////////////////////////////////////////////
		}
		render(*game);
		writeMap(game->field->dataMap);
	}
	destroyGame(*game);
}

int main()
{
	startGame();
	return 0;
}

