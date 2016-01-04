#include "Game.h"

using namespace std;

void Game::informationAboutSelect(float x , float y)
{
	int xPosBlock = int(x / SIZE_BLOCK);
	int yPosBlock = int(y / SIZE_BLOCK);

	inforAboutBlocks(xPosBlock , yPosBlock);
	inforAboutUnlifeObject(x , y);
	inforAboutItem(x , y);
	inforAboutEntity(x , y);
}

void Game::inforAboutBlocks(int x , int y)
{
	Entity &mainPerson = world.Enemys[ID_PLAYER_IN_LIST];
	Field &field = world.field;

	Text& infoBlock = textGame.texts[idText::infoWindowBlock];
	Text& infoFloor = textGame.texts[idText::infoWindowFloor];

	infoBlock.setString("Block : not select");
	infoFloor.setString("Floor : not select");
	for (int l = 0; l < HEIGHT_MAP; l++) {
		if (l >= mainPerson.currentLevelFloor - 1
				&& l <= mainPerson.currentLevelFloor + 2) {
			for (int i = 0; i < LONG_MAP; i++) {
				for (int j = 0; j < WIDTH_MAP - BORDER1; j++) {


					if ((x == j) && (y == i)) {
						if (l == mainPerson.currentLevelFloor) {
							infoFloor.setString("Floor : " + field.findCharBlocks(field.dataMap[l][i][j]));
						}
						else if (l == mainPerson.currentLevelFloor + 1) {
							infoBlock.setString("Block : " + field.findCharBlocks(field.dataMap[l][i][j]));
						}
					}


				}
			}
		}
	}
}

void Game::inforAboutUnlifeObject(float x , float y)
{
	Entity &mainPerson = world.Enemys[ID_PLAYER_IN_LIST];

	vector<UnlifeObject> &unlifeObjects = world.unlifeObjects;
	Text& infoUnlifeObject = textGame.texts[idText::infoWindowUnlifeObject];

	emptyObjects &emptyObjects = world.emptyObjects;
	mainPerson.founds.init(emptyObjects);

	mainPerson.founds.findObject = mainPerson.founds.emptyObject;
	mainPerson.founds.findObjectFromList = -1;
	infoUnlifeObject.setString("UnlifeObject : not select");
	for (int i = 0; i != unlifeObjects.size(); ++i) {

		int level = unlifeObjects[i].currentLevel;

		Sprite *spriteObject = unlifeObjects[i].spriteObject;
		FloatRect objectBound = spriteObject->getGlobalBounds();

		Sprite *transparentSpiteObject = unlifeObjects[i].transparentSpiteObject;
		FloatRect objectAltBound = transparentSpiteObject->getGlobalBounds();

		if (objectBound.contains(x , y) || objectAltBound.contains(x , y)) {
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
}

void Game::inforAboutItem(float x , float y)
{
	Entity &mainPerson = world.Enemys[ID_PLAYER_IN_LIST];

	vector<Item> &items = world.items;
	Text& infoItem = textGame.texts[idText::infoWindowItem];

	mainPerson.founds.findItemFromList = -1;
	infoItem.setString("Item : not select");
	for (int i = 0; i != items.size(); ++i) {

		int level = items[i].getLevelOnMap();


		if (items[i].getGlobalBounds().contains(x , y)) {
			if (level >= mainPerson.currentLevelFloor
					&& level <= mainPerson.currentLevelFloor + 2) {
				String name = items[i].getName();
				if (name != "") {
					mainPerson.setIdFindItem(i);
					mainPerson.setFindItem(items[i]);
					infoItem.setString("Item : " + name);
				}
			}
		}

	}

}

void Game::inforAboutEntity(float x , float y)
{
	Entity &mainPerson = world.Enemys[ID_PLAYER_IN_LIST];

	vector<Entity>& Enemys = world.Enemys;
	Text& infoEnemys = textGame.texts[idText::infoEntity];
	emptyObjects &emptyObjects = world.emptyObjects;

	mainPerson.founds.findEnemy = &emptyObjects.emptyEnemy;
	mainPerson.founds.findEnemyFromList = -1;
	infoEnemys.setString("Entity : not select");
	for (int i = 1; i != Enemys.size(); ++i) {

		int level = Enemys[i].currentLevelFloor;

		Sprite *spriteObject = Enemys[i].spriteEntity;
		FloatRect objectBound = spriteObject->getGlobalBounds();

		if (objectBound.contains(x , y)) {
			if (level >= mainPerson.currentLevelFloor - 1
					&& level <= mainPerson.currentLevelFloor + 1) {
				String name = Enemys[i].getName();
				if (name != "") {

					mainPerson.founds.findEnemyFromList = i;
					mainPerson.founds.findEnemy = &Enemys[i];
					infoEnemys.setString("Entity : " + name);
				}
			}
		}

	}

}
