#include "Game.h"

using namespace hotKeys;

void Game::processEvents(const float deltaTime)
{
	Entity *mainPerson = world.mainPerson;


	Event event;
	while (window.pollEvent(event)) {

		Vector2i mousePos = Mouse::getPosition(window);
		Vector2f pos = window.mapPixelToCoords(mousePos);

		if (!mainPerson->isDeath) {


			informationAboutSelect(pos.x, pos.y);


			processArrows();


			processPanelQuickAccess();


			mainPerson->computeAngle(window);


		}
		processOtherAction(event, pos);

	}

}

void Game::processArrows()
{
	Entity &mainPerson = world.Enemys[0];

	if (Keyboard::isKeyPressed(keys[Up]) && Keyboard::isKeyPressed(keys[Left])) {
		mainPerson.directions.directionWalk = Direction::UP_LEFT;
	} else if (Keyboard::isKeyPressed(keys[Up]) && Keyboard::isKeyPressed(keys[Right])) {
		mainPerson.directions.directionWalk = Direction::UP_RIGHT;
	} else if (Keyboard::isKeyPressed(keys[Down]) && Keyboard::isKeyPressed(keys[Left])) {
		mainPerson.directions.directionWalk = Direction::DOWN_LEFT;
	} else if (Keyboard::isKeyPressed(keys[Down]) && Keyboard::isKeyPressed(keys[Right])) {
		mainPerson.directions.directionWalk = Direction::DOWN_RIGHT;
	}
	else if (Keyboard::isKeyPressed(keys[Up])) {
		mainPerson.directions.directionWalk = UP;
	} else if (Keyboard::isKeyPressed(keys[Down])) {
		mainPerson.directions.directionWalk = DOWN;
	} else if (Keyboard::isKeyPressed(keys[Left])) {
		mainPerson.directions.directionWalk = LEFT;
	} else if (Keyboard::isKeyPressed(keys[Right])) {
		mainPerson.directions.directionWalk = RIGHT;
	} else {
		mainPerson.directions.directionWalk = NONE_DIRECTION;
	}
}

void Game::processInterface()
{

	if (Keyboard::isKeyPressed(keys[pauseGame])) {
		if (stateGame == gameState) {
			stateGame = pauseState;
			music.pause();
		}
		else if (stateGame == pauseState) {
			stateGame = gameState;
			music.play();

			panels &panels = gui.panels;
			panel &panel = panels.awardPanel;
			Sprite &sprite = panel.sprite;

			panel.draw = false;
		}
		else if(stateGame == endGameState)
		{
			window.close();
		}
	}
}

void Game::processPersonAction(Vector2f pos)
{
	Entity *mainPerson = world.mainPerson;

	if (Keyboard::isKeyPressed(keys[actionAlternate])) {
		if (mainPerson->isInUseField(pos, true)) {
			mainPerson->actionAlternate(world, pos);
		}
	}
	else if (Keyboard::isKeyPressed(keys[throwItem])) {
		mainPerson->throwItem(world.field, world.items);
	}
	else if (Keyboard::isKeyPressed(keys[actionMain])) {
		if (mainPerson->isInUseField(pos, true)) {
			mainPerson->actionMain(world, pos);
		}
	}
	else if (Keyboard::isKeyPressed(keys[takeItem])) {

		mainPerson->takeItem(world, pos);

	}
	else if (Keyboard::isKeyPressed(keys[run])) {
		mainPerson->run();
	}

}

void Game::processOtherAction(Event &event, Vector2f pos)
{
	Entity *mainPerson = world.mainPerson;

	if (!mainPerson->isDeath) {
		switch (event.type) {
		case Event::KeyPressed:
			processInterface();
			processPersonAction(pos);
			break;
		case Event::MouseButtonPressed:
			if (mainPerson->currenMode != idEntityMode::atack) {
				mainPerson->useItem(world , event , pos);
			}
			break;
		default:
			break;
		}
	}

	switch (event.type) {
	case Event::Resized:
		resizeWindow();
		break;
	case Event::Closed:
		window.close();
		break;
	default:
		break;
	}

}

void Game::processPanelQuickAccess()
{
	Entity &mainPerson = world.Enemys[0];

	if (Keyboard::isKeyPressed(Keyboard::Num0)) {

		if (mainPerson.idSelectItem != 9) {
			mainPerson.playSoundChoiseItem();
		}
		mainPerson.idSelectItem = 9;

	}
	else {
		for (int i = 0; i < mainPerson.type->amountSlots - 1; i++) {
			if (Keyboard::isKeyPressed(Keyboard::Key(Keyboard::Num1 + i))) {

				if (mainPerson.idSelectItem != i) {
					mainPerson.playSoundChoiseItem();
				}
				mainPerson.idSelectItem = i;

			}
		}

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