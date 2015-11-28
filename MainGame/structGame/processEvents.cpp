#include "processEvents.h"

using namespace hotKeys;

void Game::processEvents(const float deltaTime)
{
	Event event;
	while (window.pollEvent(event)) {

		if (mainPerson.isDeath == false) {
			Vector2i mousePos = Mouse::getPosition(window);
			Vector2f pos = window.mapPixelToCoords(mousePos);

			informationAboutSelect(pos.x, pos.y);

			processArrows();
			processOtherAction(event, pos);
			processPanelQuickAccess();

			mainPerson.computeAngle(window);// �������
		}

	}

}

void Game::processArrows()
{
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

void Game::processPersonAction(Vector2f pos)
{
	if (Keyboard::isKeyPressed(keys[actionAlternate])) {
		if (mainPerson.isInUseField(pos.x, pos.y, true)) {
			mainPerson.actionAlternate(world, pos);// �������
		}
	}
	else if (Keyboard::isKeyPressed(keys[throwItem])) {
		mainPerson.throwItem(world.field, *world.items);
	}
	else if (Keyboard::isKeyPressed(keys[actionMain])) {
		if (mainPerson.isInUseField(pos.x, pos.y, true)) {
			mainPerson.actionMain(world, pos);// �������
		}
	}
	else if (Keyboard::isKeyPressed(keys[takeItem])) {
		mainPerson.takeItem(world, pos);
	}
	else if (Keyboard::isKeyPressed(keys[run])) {
		mainPerson.run();
	}
}

void Game::processOtherAction(Event &event, Vector2f pos)
{

	

		switch (event.type) {
		case Event::KeyPressed:
			processPersonAction(pos);
			break;
		case Event::MouseButtonPressed:
			mainPerson.useItem(world, event, pos);
			break;
		case Event::Closed:
			window.close();
			break;
		case Event::Resized:
			resizeWindow();
			break;
		default:
			break;
		}
}

	void Game::processPanelQuickAccess()
	{
		if (Keyboard::isKeyPressed(Keyboard::Num0)) {
			mainPerson.idSelectItem = 9;
		}
		else {
			for (int i = 0; i < mainPerson.amountSlots - 1; i++) {
				if (Keyboard::isKeyPressed(Keyboard::Key(Keyboard::Num1 + i))) {
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