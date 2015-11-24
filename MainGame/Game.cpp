#include "Game.h"

using namespace std;


void Game::informationAboutSelect(float x, float y)
{

	Field &field = world.field;

	int xPosBlock = x / SIZE_BLOCK;
	int yPosBlock = y / SIZE_BLOCK;

	Text& infoBlock = textGame.texts[idText::infoWindowBlock];
	Text& infoFloor = textGame.texts[idText::infoWindowFloor];

	infoBlock.setString("Block : not select");
	infoFloor.setString("Floor : not select");
	for (int l = 0; l < HEIGHT_MAP; l++) {
		// Рисуем только текущий уровень
		if (l >= mainPerson.currentLevelFloor - 1
				&& l <= mainPerson.currentLevelFloor + 2) {
			for (int i = 0; i < LONG_MAP; i++) {
				for (int j = 0; j < WIDTH_MAP - BORDER1; j++) {


					if ((xPosBlock == j) && (yPosBlock == i)) {
						if (l == mainPerson.currentLevelFloor) {
							infoFloor.setString("Floor : " + field.findCharBlocks(field.dataMap[l][i][j]));
						} else if (l == mainPerson.currentLevelFloor + 1) {
							infoBlock.setString("Block : " + field.findCharBlocks(field.dataMap[l][i][j]));
						}
					}


				}
			}
		}
	}

	vector<UnlifeObject> &unlifeObjects = *world.unlifeObjects;
	Text& infoUnlifeObject = textGame.texts[idText::infoWindowUnlifeObject];

	emptyObjects &emptyObjects = world.emptyObjects;
	mainPerson.founds.init(&emptyObjects.emptyItem, &emptyObjects.emptyObject);
	mainPerson.founds.findObjectFromList = -1;
	infoUnlifeObject.setString("UnlifeObject : not select");
	for (int i = 0; i != unlifeObjects.size(); ++i) {

		int level = unlifeObjects[i].currentLevel;

		Sprite *spriteObject = unlifeObjects[i].spriteObject;
		FloatRect objectBound = spriteObject->getGlobalBounds();

		Sprite *transparentSpiteObject = unlifeObjects[i].transparentSpiteObject;
		FloatRect objectAltBound = transparentSpiteObject->getGlobalBounds();

		if (objectBound.contains(x, y) || objectAltBound.contains(x, y)) {
			if (level >= mainPerson.currentLevelFloor
					&& level <= mainPerson.currentLevelFloor + 1) {
				String name = unlifeObjects[i].typeObject->name;
				if (name != "") {

					mainPerson.founds.findObjectFromList = i;
					mainPerson.founds.findObject = &unlifeObjects[i];
					infoUnlifeObject.setString("UnlifeObject : " + name);
				}
			}
		}

	}

	vector<Item> &items = *world.items;
	Text& infoItem = textGame.texts[idText::infoWindowItem];

	mainPerson.founds.findItemFromList = -1;
	infoItem.setString("Item : not select");
	for (int i = 0; i != items.size(); ++i) {

		int level = items[i].currentLevel;

		Sprite *mainSprite = items[i].mainSprite;
		FloatRect itemBound = mainSprite->getGlobalBounds();

		// TODO
		//Sprite *useSpiteObject = items[i].spriteForUse;// ИСПРАВЬ
		//FloatRect itemUseBound = useSpiteObject->getGlobalBounds();
		//|| itemUseBound.contains(x, y)
		if (itemBound.contains(x, y)) {
			if (level >= mainPerson.currentLevelFloor
					&& level <= mainPerson.currentLevelFloor + 2) {
				String name = items[i].typeItem->features.name;
				if (name != "") {
					mainPerson.founds.findItemFromList = i;
					mainPerson.founds.findItem = &items[i];
					infoItem.setString("Item : " + name);
				}
			}
		}

	}

	vector<Enemy>& Enemys = *world.Enemys;
	Text& infoEnemys = textGame.texts[idText::infoEntity];

	mainPerson.findEnemy = &emptyObjects.emptyEnemy;
	mainPerson.findEnemyFromList = -1;
	infoEnemys.setString("Entity : not select");
	for (int i = 0; i != Enemys.size(); ++i) {

		int level = Enemys[i].currentLevelFloor;

		Sprite *spriteObject = Enemys[i].spriteEntity;
		FloatRect objectBound = spriteObject->getGlobalBounds();

		if (objectBound.contains(x, y)) {
			if (level >= mainPerson.currentLevelFloor - 1
					&& level <= mainPerson.currentLevelFloor + 1) {
				String name = Enemys[i].type->name;
				if (name != "") {

					mainPerson.findEnemyFromList = i;
					mainPerson.findEnemy = &Enemys[i];
					infoEnemys.setString("Entity : " + name);
				}
			}
		}

	}

}


void Game::processEvents(const float deltaTime)
{
	Event event;
	while (window.pollEvent(event)) {


		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Если персонаж жив
		if (mainPerson.isDeath == false) {
			Vector2i mousePos = Mouse::getPosition(window);
			Vector2f pos = window.mapPixelToCoords(mousePos);

			UnlifeObject* emptyObject = nullptr;
			Item* emptyItem = nullptr;

			informationAboutSelect(pos.x, pos.y);

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

				} else if (Keyboard::isKeyPressed(Keyboard::F)) {
					//mainPerson.currenMode = idModeEntity::fight;// ИСПРАВЬ

				}
			}
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
		// То что в любом случае обрабатываестя

		/////////////////////////////////////////////////////////////
		// Для обновления окна
		// получение размера окна
		if (event.type == sf::Event::Resized) {
			unsigned int width = window.getSize().x;
			unsigned int height = window.getSize().y;
			widthMainWindow = width;
			heightMainWindow = height;

			window.create(VideoMode(width, height), TITLE_PROGRAM);
		}
		/////////////////////////////////////////////////////////////


		// Окно закрыли
		if (event.type == Event::Closed) {
			window.close();
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
}


void Game::updatePlayer(const float &deltaTime)
{
	mainPerson.update(deltaTime, databaseSound);
	mainPerson.updateAtack(world, deltaTime);
	mainPerson.interactionWithMap(world.field, *world.listDestroy, deltaTime);
	mainPerson.interactionWitnUnlifeObject(world.unlifeObjects, deltaTime);
	mainPerson.getCoordinateForView(mainPerson.getXPos(), mainPerson.getYPos());

	mainPerson.updateView(window);
	window.setView(*mainPerson.view);

	//printf("Angle %f \n", mainPerson.rotation);
}

void Game::updateEntity(const float deltaTime)
{
	vector<Enemy>& Enemys = *world.Enemys;
	Field &field = world.field;
	for (int i = 0; i < Enemys.size(); ++i) {
		Enemys[i].update(deltaTime, databaseSound);
		Enemys[i].interactionWithMap(field, *world.listDestroy, deltaTime);
		Enemys[i].interactionWithEntity(world.Enemys, i, deltaTime);
		Enemys[i].interactionWitnUnlifeObject(world.unlifeObjects, deltaTime);

		mainPerson.attractionEnemy(Enemys[i], world, deltaTime);
		Enemys[i].randomWalk(deltaTime);
	}
}


void Game::updateUnlifeObjects(const float &deltaTime)
{
	vector<UnlifeObject> &objects = *world.unlifeObjects;
	for (int i = 0; i < objects.size(); ++i) {
		objects[i].timeLife += deltaTime;

		redefineObject &redefine = objects[i].typeObject->redefine;
		float timeUpdate = redefine.timeUpdate;
		if (timeUpdate) {
			if (objects[i].timeLife > timeUpdate) {
				upgradeObject(objects[i]);
			}
		}

	}
}


void Game::render()
{
	window.clear();

	//////////////////////////////////////////////
	// Отрисовка карты
	Field &field = world.field;
	bool isEmpty(false);

	int l = mainPerson.currentLevelFloor;
	int lowBorder = l - 1;
	if (lowBorder < 0)
		lowBorder = 0;
	int topBorder = l + 2;
	if (topBorder > HEIGHT_MAP - 1)
		topBorder = HEIGHT_MAP - 1;

	l = lowBorder;
	while (l <= topBorder) {

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
	// Отрисовка предметов
	vector<Item> &items = *world.items;
	for (int i = 0; i != items.size(); ++i) {
		if (items[i].currentLevel >= mainPerson.currentLevelFloor
				&& items[i].currentLevel <= mainPerson.currentLevelFloor + 2) {


			if (items[i].currentLevel == mainPerson.currentLevelFloor) {
				items[i].mainSprite->setColor(DOWN_VIEW);
			} else if (items[i].currentLevel == mainPerson.currentLevelFloor + 1) {
				items[i].mainSprite->setColor(NORMAL_VIEW);
			} else if (items[i].currentLevel == mainPerson.currentLevelFloor + 2) {
				items[i].mainSprite->setColor(UP_VIEW);
			}

			window.draw(*items[i].mainSprite);
			//window.draw(*game.items->item[i].spriteForUse);// ИСПРАВЬ
		}

	}


	mainPerson.renderCurrentItem(window);
	window.draw(*mainPerson.spriteEntity);

	renderEntitys();
	renderUnlifeObjects();

	gui.setPositionGui(window, mainPerson, *world.Enemys, textGame);
	window.display();
}

void Game::upgradeObject(UnlifeObject &object)
{
	redefineObject &redefine = object.typeObject->redefine;
	Sprite &spriteObject = *object.spriteObject;
	Vector2f currentPos = spriteObject.getPosition();
	Vector2i posOnMap = { int((currentPos.x + SIZE_BLOCK / 2) / SIZE_BLOCK),
		int((currentPos.y + SIZE_BLOCK / 2) / SIZE_BLOCK) };

	TypeUnlifeObject &nextType = world.typesObjects.typesUnlifeObject[redefine.id];


	object.setType(nextType);
	object.setPosition(posOnMap.x, posOnMap.y, object.currentLevel);
}

void Game::showFPS(const Time timeSinceLastUpdate)
{
	float currentWorldTime = world.worldTime.getElapsedTime().asSeconds();

	if (currentWorldTime - int(currentWorldTime) <= faultWorldTime) {
		world.lastSecond += 1.f;
		printf("FPS: %f\n", 1.f / timeSinceLastUpdate.asSeconds());
	}
}

void Game::createGroups(float time)
{
	Vector3i pos = { 3, 10, 0 };
	//createSmallGroupSkelets(world, pos);

	pos = { 5, 5, 2 };
	createSmallGroupSkelets(world, pos);

	bool updateDifficult = int(time) % TIME_UPDATE_DIFFICULT == 0;
	if (updateDifficult)
		world.difficult++;

	if (world.difficult > 0) {
		pos = { 10, 10, 1 };
		createMiddleGroupSkelets(world, pos);
	}
	if (world.difficult > 1) {
		pos = { 20, 20, 1 };
		createBigGroupSkelets(world, pos);
	}
}

void Game::generateGroups()
{
	bool &needGenerateWave = world.waveEnemysCreated;
	float currentWorldTime = world.worldTime.getElapsedTime().asSeconds();

	bool condition = int(currentWorldTime) % TIME_GENERATE_WAVE_ENEMYS == 0;
	if (condition && needGenerateWave == false) {
		createGroups(currentWorldTime);
	}
}

void Game::updateWorldTimeCircles()
{
	float currentWorldTime = world.worldTime.getElapsedTime().asSeconds();

	if (currentWorldTime - int(currentWorldTime) <= faultWorldTime) {
		generateGroups();

		printf("World time: %f\n", currentWorldTime);
	}
}


void Game::update(const float &deltaTime)
{
	processEvents(deltaTime);

	if (mainPerson.isDeath == false) {
		updatePlayer(deltaTime);
		updateEntity(deltaTime);
		updateUnlifeObjects(deltaTime);
		updateWorldTimeCircles();
	}
}

void initializeGame(Game & game)
{
	
	game.world.unlifeObjects = new vector<UnlifeObject>;
	game.world.items = new vector<Item>;
	game.world.listDestroy = new listDestroyObjectsAndBlocks;

	game.window.create(VideoMode(game.widthMainWindow, game.heightMainWindow), TITLE_PROGRAM);

	world &world = game.world;

	initializeSound(game.databaseSound);
	initializeField(game.world.field);

	typesObjectsInWorld &types = game.world.typesObjects;
	initializeTypesItem(types.typesItem, *game.world.listDestroy, game.databaseSound);
	initializeItems(*world.items, types.typesItem, world.emptyObjects.emptyItem);

	initializeTypeUnlifeObjects(types.typesUnlifeObject, game.databaseSound);
	initializeUnlifeObjects(*game.world.unlifeObjects, types.typesUnlifeObject, world.emptyObjects.emptyObject);

	// TODO
	initializeCategorysBreakingObject(game);

	world.Enemys = new vector<Enemy>;

	initializeTypeEnemy(types, game.databaseSound);
	initializeEntitys(game.world);

	initializeMainPerson(game.mainPerson, game.databaseSound, world.emptyObjects);

	createTextsAndFonts(game.textGame);
	initializeTexts(game.textGame);

	initializeGUI(game.gui, game.textGame);

	initializeClock(game.clock);
}

///*
void initializeCategorysBreakingObject(Game &game) 
{
	listDestroyObjectsAndBlocks &listDestroy = *game.world.listDestroy;
	typesObjectsInWorld &types = game.world.typesObjects;
	TypeUnlifeObject* typesUnlifeObject = types.typesUnlifeObject;
	wchar_t* charBlocks = game.world.field.charBlocks;

	//////////////////////////////////////
	// Блоки уничтожаемые лопатой
	listDestroy.backoeBreakingBlock[SIZE_STRING - 1] = u'\0';

	listDestroy.backoeBreakingBlock[0] = charBlocks[idBlocks::grass];
	listDestroy.backoeBreakingBlock[1] = charBlocks[idBlocks::dirt];
	listDestroy.backoeBreakingBlock[2] = charBlocks[idBlocks::sand];
	//////////////////////////////////////
	// Объекты уничтожаемые лопатой TODO
	listDestroy.backoeBreakingObject[0] = typesUnlifeObject[idUnlifeObject::oakSeadling].name;
	//////////////////////////////////////
	// Блоки уничтожаемые топором
	listDestroy.axeBreakingBlock[SIZE_STRING - 1] = u'\0';

	listDestroy.axeBreakingBlock[0] = charBlocks[idBlocks::logOak];
	listDestroy.axeBreakingBlock[1] = charBlocks[idBlocks::planksBlock];
	listDestroy.axeBreakingBlock[2] = charBlocks[idBlocks::woodLadder];
	//////////////////////////////////////
	// Объекты уничтожаемые топором
	listDestroy.axeBreakingObject[0] = typesUnlifeObject[idUnlifeObject::oakGrow].name;
	listDestroy.axeBreakingObject[1] = typesUnlifeObject[idUnlifeObject::oakSmall].name;
	listDestroy.axeBreakingObject[2] = typesUnlifeObject[idUnlifeObject::appleTree].name;
	listDestroy.axeBreakingObject[3] = typesUnlifeObject[idUnlifeObject::appleGrowTree].name;
	/////////////////////////////////////////////////////////////////////////
	// Блоки уничтожаемые киркой
	listDestroy.pickaxBreakingBlock[SIZE_STRING - 1] = u'\0';

	listDestroy.pickaxBreakingBlock[0] = charBlocks[idBlocks::stone];
	listDestroy.pickaxBreakingBlock[1] = charBlocks[idBlocks::stoneBrick];
	//////////////////////////////////////
	// Киркой уничтожаемые киркой
	listDestroy.pickaxBreakingObject[0] = typesUnlifeObject[idUnlifeObject::smallStone].name;
	/////////////////////////////////////////////////////////////////////////
	// Проходимые блоки
	listDestroy.passableBlocks[SIZE_STRING - 1] = u'\0';

	listDestroy.passableBlocks[0] = charBlocks[idBlocks::air];
	listDestroy.passableBlocks[1] = charBlocks[idBlocks::water];
	listDestroy.passableBlocks[2] = charBlocks[idBlocks::woodLadder];
	/////////////////////////////////////////////////////////////////////////
	// Проходим по полу
	listDestroy.notPassableFloor[SIZE_STRING - 1] = u'\0';

	listDestroy.notPassableFloor[0] = charBlocks[idBlocks::air]; 
	/////////////////////////////////////////////////////////////////////////
	// Замедляющие блоки
	listDestroy.slowingBlocks[SIZE_STRING - 1] = u'\0';

	listDestroy.slowingBlocks[0] = charBlocks[idBlocks::water];
	/////////////////////////////////////////////////////////////////////////
	// Лестницы
	listDestroy.ladder[SIZE_STRING - 1] = u'\0';

	listDestroy.ladder[0] = charBlocks[idBlocks::woodLadder];
	/////////////////////////////////////////////////////////////////////////
	listDestroy.harvestObjects[0] = typesUnlifeObject[idUnlifeObject::appleGrowTree].name;

}

//*/


void Game::renderEntitys()
{
	vector<Enemy>& Enemys = *world.Enemys;

	int enemyLevel;
	const int personLevel = mainPerson.currentLevelFloor;
	for (int i = 0; i < Enemys.size(); ++i) {
		enemyLevel = Enemys[i].currentLevelFloor;
		if (enemyLevel >= personLevel - 1 && enemyLevel <= personLevel + 1) {
			Enemys[i].renderCurrentItem(window);

			Color currentColor;
			if(personLevel) currentColor = NORMAL_COLOR;
			else if(personLevel - 1) currentColor = DOWN_VIEW;
			else if(personLevel + 1) currentColor = UP_VIEW;
			Enemys[i].spriteEntity->setColor(NORMAL_COLOR);
			window.draw(*Enemys[i].spriteEntity);
			//window.draw(*game.items->item[i].spriteForUse);// ИСПРАВЬ
		}

	}

}

void Game::renderUnlifeObjects()
{

	int currentLevel = mainPerson.currentLevelFloor;
	vector<UnlifeObject> &unlifeObjects = *world.unlifeObjects;
	bool inView;
	for (int i = 0; i != unlifeObjects.size(); ++i) {
		inView = unlifeObjects[i].currentLevel >= currentLevel
			&& unlifeObjects[i].currentLevel <= currentLevel + 2;

		if (inView) {
			if (unlifeObjects[i].currentLevel == currentLevel) {
				unlifeObjects[i].spriteObject->setColor(DOWN_VIEW);
				unlifeObjects[i].transparentSpiteObject->setColor(DOWN_VIEW);
			} else if (unlifeObjects[i].currentLevel == currentLevel + 2) {
				unlifeObjects[i].spriteObject->setColor(UP_VIEW);
				unlifeObjects[i].transparentSpiteObject->setColor(UP_VIEW);
			}

			window.draw(*unlifeObjects[i].spriteObject);
			window.draw(*unlifeObjects[i].transparentSpiteObject);
		}

	}
}

void destroyGame(Game & game)
{
	// TODO
	delete game.world.items;
	delete game.world.unlifeObjects;
	delete game.world.Enemys;
	delete game.world.listDestroy;

	delete &game;
}

void initializeClock(Clock &clock)// ИСПРАВЬ
{

}