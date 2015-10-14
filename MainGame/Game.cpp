#include "Game.h"

using namespace std;

void initializeGame(Game & game)
{
	game.databaseSound = new dataSound;
	game.clock = new Clock;
	game.field = new Field;
	game.mainPerson = new MainPerson;

	game.typesUnlifeObject = new TypesUnlifeObject;
	game.unlifeObjects = new list<UnlifeObject>;

	game.typesItem = new TypesItem;
	game.items = new list<Item>;
	game.emptyItem = new Item;
	//game.items = new list<Item>;
	//game.ite


	game.gui = new GUI;
	game.textGame = new TextGame;

	game.window = new RenderWindow(VideoMode(game.widthMainWindow, game.heightMainWindow), titleGame);


	initializeSound(game.databaseSound);// На будущее
	initializeField(*game.field);

	// Предметы
	initializeTypesItem(*game.typesItem, *game.databaseSound);
	initializeItems(*game.items, game.typesItem, *game.emptyItem);

	// Основной персонаж
	initializeMainPerson(*game.mainPerson, *game.databaseSound, *game.emptyItem);

	// Неживые объекты
	initializeTypeUnlifeObjects(game.typesUnlifeObject, *game.databaseSound);
	initializeUnlifeObjects(*game.unlifeObjects, game.typesUnlifeObject);

	// GUI
	initializeGUI(*game.gui, *game.textGame);
	initializeTexts(*game.textGame);
	//initializeEntity(*game.mainPerson, *game.databaseSound);

	// Часы
	initializeClock(*game.clock);
}

void destroyGame(Game & game)
{
	delete &game;
}

void informationAboutSelect(Game &game, float x, float y)
{
	///////////////////////////////////////////////////////////////////
	// Осмотр блоков
	Field &field = *game.field;
	TextGame &textGame = *game.textGame;

	int xPosBlock = x / SIZE_BLOCK;
	int yPosBlock = y / SIZE_BLOCK;

	textGame.texts[idText::infoWindowBlock].setString("Block : not select");
	textGame.texts[idText::infoWindowFloor].setString("Floor : not select");
	for (int l = 0; l < HEIGHT_MAP; l++) {
	// Рисуем только текущий уровень
	if (l == game.mainPerson->currentLevelFloor
		|| l == game.mainPerson->currentLevelFloor + 1) {
		for (int i = 0; i < LONG_MAP; i++) {
			for (int j = 0; j < WIDTH_MAP - BORDER1; j++) {


				if ( (xPosBlock == j) && (yPosBlock == i) ) {
					if (l == game.mainPerson->currentLevelFloor) {
						textGame.texts[idText::infoWindowFloor].setString("Floor : " + field.findCharBlocks(field.dataMap[l][i][j]));
					}
					else {
						textGame.texts[idText::infoWindowBlock].setString("Block : " + field.findCharBlocks(field.dataMap[l][i][j]));
					}
				}
					

				}
			}
		}
	}
	///////////////////////////////////////////////////////////////////
	// Осмотр неживых объектов
	list<UnlifeObject> &unlifeObjects = *game.unlifeObjects;

	textGame.texts[idText::infoWindowUnlifeObject].setString("UnlifeObject : not select");
	for (std::list<UnlifeObject>::iterator it = unlifeObjects.begin(); it != unlifeObjects.end(); ++it) {

		int level = it->currentLevel;

		Sprite *spriteObject = it->spriteObject;
		FloatRect objectBound = spriteObject->getGlobalBounds();

		Sprite *transparentSpiteObject = it->transparentSpiteObject;
		FloatRect objectAltBound = transparentSpiteObject->getGlobalBounds();

		if (objectBound.contains(x, y) || objectAltBound.contains(x, y)) {
			if (level == game.mainPerson->currentLevelFloor + 1) {
				String nameType = it->typeObject->nameType;
				if (nameType != "") {

					game.mainPerson->findObjectFromList = it;
					textGame.texts[idText::infoWindowUnlifeObject].setString("UnlifeObject : " + nameType);
				}
			}
		}

	}
	///////////////////////////////////////////////////////////////////
	// Осмотр предметов
	list<Item> &items = *game.items;

	textGame.texts[idText::infoWindowItem].setString("Item : not select");
	for (std::list<Item>::iterator it = items.begin(); it != items.end(); ++it) {

		int level = it->currentLevel;

		Sprite *mainSprite = it->mainSprite;
		FloatRect itemBound = mainSprite->getGlobalBounds();

		Sprite *useSpiteObject = it->spriteForUse;// ИСПРАВЬ
		FloatRect itemUseBound = useSpiteObject->getGlobalBounds();

		if (itemBound.contains(x, y) || itemUseBound.contains(x, y)) {
			if (level == game.mainPerson->currentLevelFloor + 1) {
				String nameType = it->typeItem->nameType;
				if (nameType != "") {
					game.mainPerson->findItemFromList = it;
					textGame.texts[idText::infoWindowItem].setString("Item : " + nameType);
				}
			}
		}

	}
	///////////////////////////////////////////////////////////////////
}

void initializeClock(Clock &clock)
{

}