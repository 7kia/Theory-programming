#include  "renderGame.h"

using namespace sf;
using namespace std;


void Game::showFPS(const Time timeSinceLastUpdate)
{
	float currentWorldTime = world.worldTime.getElapsedTime().asSeconds();

	if (currentWorldTime - int(currentWorldTime) <= faultWorldTime) {
		world.lastSecond += 1.f;
		printf("FPS: %f\n", 1.f / timeSinceLastUpdate.asSeconds());
	}
}

void Game::render()
{
	window.clear();

	Vector2f centerWindow = window.getView().getCenter();
	Vector2f sizeWindow = Vector2f(window.getSize());
	FloatRect rectWindow = FloatRect(centerWindow - sizeWindow, sizeWindow + centerWindow);

	//if(rectWindow.left )

	renderMap(rectWindow);
	renderItems(rectWindow);


	mainPerson.renderCurrentItem(window);
	window.draw(*mainPerson.spriteEntity);

	renderEntitys(rectWindow);
	renderUnlifeObjects(rectWindow);

	gui.setPositionGui(window, mainPerson, *world.Enemys, textGame);
	window.display();
}

void Game::renderMap(FloatRect const& rectWindow)
{
	Field &field = world.field;

	int l = mainPerson.currentLevelFloor;
	int lowBorder = l - 1;
	if (lowBorder < 0)
		lowBorder = 0;
	int topBorder = l + 2;
	if (topBorder > HEIGHT_MAP - 1)
		topBorder = HEIGHT_MAP - 1;

	l = lowBorder;
	FloatRect rectWallSprite;
	FloatRect rectFloorSprite;
	while (l <= topBorder) {

		for (int i = 0; i < LONG_MAP; i++) {
			for (int j = 0; j < WIDTH_MAP - BORDER1; j++) {
				field.setTypeSprite(mainPerson.currentLevelFloor, l, i, j);

				/*
								rectWallSprite = field.wallSprite->getGlobalBounds();
				rectFloorSprite = field.floorSprite->getGlobalBounds();
				// TODO
				if(rectWallSprite != NULL_RECT)
				{
					if (isExitFromWindow(rectWindow, rectWallSprite)) {
						window.draw(*field.wallSprite);
					}	
				}
				if (rectFloorSprite != NULL_RECT) {
					if (isExitFromWindow(rectWindow, rectFloorSprite)) {
						window.draw(*field.floorSprite);
					}
				}

				*/
				drawInWindow(*field.floorSprite, rectWindow);
				drawInWindow(*field.wallSprite, rectWindow);
			}
		}

		l++;
	}
}

void Game::renderItems(FloatRect const& rectWindow)
{
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

			drawInWindow(*items[i].mainSprite, rectWindow);

			//window.draw(*items[i].mainSprite);
			//window.draw(*game.items->item[i].spriteForUse);// ÈÑÏÐÀÂÜ
		}

	}
}

void Game::renderEntitys(FloatRect const& rectWindow)
{
	vector<Enemy>& Enemys = *world.Enemys;

	int enemyLevel;
	const int personLevel = mainPerson.currentLevelFloor;
	for (int i = 0; i < Enemys.size(); ++i) {
		enemyLevel = Enemys[i].currentLevelFloor;
		if (enemyLevel >= personLevel - 1 && enemyLevel <= personLevel + 1) {

			
			Enemys[i].renderCurrentItem(window);

			Color currentColor;
			if (personLevel) currentColor = NORMAL_COLOR;
			else if (personLevel - 1) currentColor = DOWN_VIEW;
			else if (personLevel + 1) currentColor = UP_VIEW;
			Enemys[i].spriteEntity->setColor(currentColor);

			drawInWindow(*Enemys[i].spriteEntity, rectWindow);

			//window.draw(*Enemys[i].spriteEntity);
			//window.draw(*game.items->item[i].spriteForUse);// ÈÑÏÐÀÂÜ
		}

	}

}

void Game::renderUnlifeObjects(FloatRect const& rectWindow)
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

			drawInWindow(*unlifeObjects[i].spriteObject, rectWindow);
			drawInWindow(*unlifeObjects[i].transparentSpiteObject, rectWindow);
		}

	}
}

bool isExitFromWindow(FloatRect const& rectWindow, FloatRect &rectObject)
{
	if (rectObject.intersects(rectWindow))
	{
		return true;
	}
	return false;
}

void Game::drawInWindow(sf::Sprite &sprite, sf::FloatRect const& rectWindow)
{
	FloatRect rectSprite = sprite.getGlobalBounds();
	//if (rectSprite != NULL_RECT) {
		if (isExitFromWindow(rectWindow, rectSprite)) {
			window.draw(sprite);
		}
//	}
}