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

	renderMap();
	renderItems();


	mainPerson.renderCurrentItem(window);
	window.draw(*mainPerson.spriteEntity);

	renderEntitys();
	renderUnlifeObjects();

	gui.setPositionGui(window, mainPerson, *world.Enemys, textGame);
	window.display();
}

void Game::renderMap()
{
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
}

void Game::renderItems()
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

			window.draw(*items[i].mainSprite);
			//window.draw(*game.items->item[i].spriteForUse);// ÈÑÏÐÀÂÜ
		}

	}
}

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
			if (personLevel) currentColor = NORMAL_COLOR;
			else if (personLevel - 1) currentColor = DOWN_VIEW;
			else if (personLevel + 1) currentColor = UP_VIEW;
			Enemys[i].spriteEntity->setColor(NORMAL_COLOR);
			window.draw(*Enemys[i].spriteEntity);
			//window.draw(*game.items->item[i].spriteForUse);// ÈÑÏÐÀÂÜ
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
