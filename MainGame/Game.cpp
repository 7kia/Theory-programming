#include "Game.h"

using namespace std;

void initializeGame(Game & game)
{
	// Карта и звуки
	game.field = new Field;
	game.databaseSound = new dataSound;

	game.clock = new Clock;
	game.mainPerson = new MainPerson;

	// Неживые объекты
	game.typesUnlifeObject = new TypesUnlifeObject;
	game.unlifeObjects = new list<UnlifeObject>;
	game.emptyObject = new UnlifeObject;

	// Предметы
	game.typesItem = new TypesItem;
	game.items = new list<Item>;
	game.emptyItem = new Item;// Нужно для корректной работы инвентаря

	// Список уничтожаемых объектов и блоков
	game.listDestroy = new destroyObjectsAndBlocks;

	// GUI
	game.gui = new GUI;
	game.textGame = new TextGame;

	game.window = new RenderWindow(VideoMode(game.widthMainWindow, game.heightMainWindow), TITLE_PROGRAM);

	// Карта и звуки
	initializeSound(game.databaseSound);// На будущее
	initializeField(*game.field);

	// Неживые объекты
	initializeTypeUnlifeObjects(game.typesUnlifeObject, *game.databaseSound);
	initializeUnlifeObjects(*game.unlifeObjects, game.typesUnlifeObject, *game.emptyObject);

	// Предметы
	initializeTypesItem(*game.typesItem, *game.databaseSound);
	initializeItems(*game.items, game.typesItem, *game.emptyItem);

	// Категории ломаемых предметов
	initializeCategorysBreakingObject(game);

	// Основной персонаж
	initializeMainPerson(*game.mainPerson, *game.databaseSound, *game.emptyItem, *game.emptyObject);

	// GUI
	initializeGUI(*game.gui, *game.textGame);
	initializeTexts(*game.textGame);

	// Часы
	initializeClock(*game.clock);
}

///*
void initializeCategorysBreakingObject(Game &game) 
{
	destroyObjectsAndBlocks& listDestroy = *game.listDestroy;
	TypeUnlifeObject* typesUnlifeObject = game.typesUnlifeObject->typeUnlifeObject;
	wchar_t* charBlocks = game.field->charBlocks;

	//////////////////////////////////////
	listDestroy.axeBreakingBlock[SIZE_STRING - 1] = u'\0';

	listDestroy.axeBreakingBlock[0] = charBlocks[idBlocks::logOak];
	listDestroy.axeBreakingBlock[1] = charBlocks[idBlocks::planksBlock];
	listDestroy.axeBreakingBlock[2] = charBlocks[idBlocks::woodLadder];
	//////////////////////////////////////

	listDestroy.axeBreakingObject[0] = typesUnlifeObject[idUnlifeObject::oak].name;
	/////////////////////////////////////////////////////////////////////////
	listDestroy.pickaxBreakingBlock[SIZE_STRING - 1] = u'\0';

	listDestroy.pickaxBreakingBlock[0] = charBlocks[idBlocks::stone];
	listDestroy.pickaxBreakingBlock[1] = charBlocks[idBlocks::stoneBrick];

	/////////////////////////

	listDestroy.pickaxBreakingObject[0] = typesUnlifeObject[idUnlifeObject::smallStone].name;
}
//*/


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
	Text& infoUnlifeObject = textGame.texts[idText::infoWindowUnlifeObject];

	infoUnlifeObject.setString("UnlifeObject : not select");
	for (std::list<UnlifeObject>::iterator it = unlifeObjects.begin(); it != unlifeObjects.end(); ++it) {

		int level = it->currentLevel;

		Sprite *spriteObject = it->spriteObject;
		FloatRect objectBound = spriteObject->getGlobalBounds();

		Sprite *transparentSpiteObject = it->transparentSpiteObject;
		FloatRect objectAltBound = transparentSpiteObject->getGlobalBounds();

		if (objectBound.contains(x, y) || objectAltBound.contains(x, y)) {
			if (level == game.mainPerson->currentLevelFloor + 1) {
				String name = it->typeObject->name;
				if (name != "") {

					game.mainPerson->findObjectFromList = it;
					game.mainPerson->findObject = &*it;
					infoUnlifeObject.setString("UnlifeObject : " + name);
				}
			}
		}

	}
	///////////////////////////////////////////////////////////////////
	// Осмотр предметов
	list<Item> &items = *game.items;
	Text& infoItem = textGame.texts[idText::infoWindowItem];

	infoItem.setString("Item : not select");
	for (std::list<Item>::iterator it = items.begin(); it != items.end(); ++it) {

		int level = it->currentLevel;

		Sprite *mainSprite = it->mainSprite;
		FloatRect itemBound = mainSprite->getGlobalBounds();

		Sprite *useSpiteObject = it->spriteForUse;// ИСПРАВЬ
		FloatRect itemUseBound = useSpiteObject->getGlobalBounds();

		if (itemBound.contains(x, y) || itemUseBound.contains(x, y)) {
			if (level == game.mainPerson->currentLevelFloor + 1) {
				String name = it->typeItem->name;
				if (name != "") {
					game.mainPerson->findItemFromList = it;
					game.mainPerson->findItem = &*it;
					infoItem.setString("Item : " + name);
				}
			}
		}

	}
	///////////////////////////////////////////////////////////////////
}

void initializeClock(Clock &clock)// ИСПРАВЬ
{

}