#include "Game.h"

void initializeGame(Game & game)
{
	game.databaseSound = new dataSound;
	game.clock = new Clock;
	game.field = new Field;
	game.mainPerson = new MainPerson;
	game.unlifeObjects = new UnlifeObjects;
	game.typesUnlifeObject = new TypesUnlifeObject;

	game.gui = new GUI;
	game.textGame = new TextGame;

	game.window = new RenderWindow(VideoMode(game.widthMainWindow, game.heightMainWindow), titleGame);


	initializeSound(game.databaseSound);// На будущее
	initializeField(*game.field);

	initializeMainPerson(*game.mainPerson, *game.databaseSound);

	initializeTypeUnlifeObjects(game.typesUnlifeObject, *game.databaseSound);
	initializeUnlifeObjects(game.unlifeObjects, game.typesUnlifeObject);

	initializeGUI(*game.gui, *game.textGame);
	initializeTexts(*game.textGame);
	//initializeEntity(*game.mainPerson, *game.databaseSound);
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
	UnlifeObjects &unlifeObjects = *game.unlifeObjects;

	textGame.texts[idText::infoWindowUnlifeObject].setString("UnlifeObject : not select");
	for (int i = 0; i < unlifeObjects.countObject; i++) {

		int level = unlifeObjects.unlifeObject[i].currentLevel;

		Sprite *spriteObject = unlifeObjects.unlifeObject[i].spriteObject;
		FloatRect objectBound = spriteObject->getGlobalBounds();

		Sprite *transparentSpiteObject = unlifeObjects.unlifeObject[i].transparentSpiteObject;
		FloatRect objectAltBound = transparentSpiteObject->getGlobalBounds();

		if (objectBound.contains(x, y) || objectAltBound.contains(x, y)) {
			if (level == game.mainPerson->currentLevelFloor + 1) {
				String nameType = unlifeObjects.unlifeObject[i].typeObject->nameType;
				if (nameType != "") {
					textGame.texts[idText::infoWindowUnlifeObject].setString("UnlifeObject : " + nameType);
				}
			}
		}

	}
	///////////////////////////////////////////////////////////////////
}


void initializeClock(Clock &clock)
{

}