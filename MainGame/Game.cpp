#include "Game.h"
#include "EntityVar.h"

using namespace std;

void initializeGame(Game & game)
{
	// Карта и звуки
//game.field = new Field;
//game.databaseSound = new dataSound;

//game.clock = new Clock;
//game.mainPerson = new MainPerson;

	// Неживые объекты
//game.typesUnlifeObject = new TypesUnlifeObject;
	game.unlifeObjects = new vector<UnlifeObject>;
//game.emptyObject = new UnlifeObject;

	// Предметы
//game.typesItem = new TypeItem[AMOUNT_TYPES_ITEM];
	game.items = new vector<Item>;
//game.emptyItem = new Item;// Нужно для корректной работы инвентаря

	// Список уничтожаемых объектов и блоков
	game.listDestroy = new destroyObjectsAndBlocks;

	// GUI
//game.gui = new GUI;
//game.textGame = new TextGame;

	game.window.create(VideoMode(game.widthMainWindow, game.heightMainWindow), TITLE_PROGRAM);

	// Карта и звуки
	initializeSound(game.databaseSound);// На будущее
	initializeField(game.field);

	// Предметы
	initializeTypesItem(game.typesItem, game.databaseSound);
	initializeItems(*game.items, game.typesItem, game.emptyItem);


	// Неживые объекты
	initializeTypeUnlifeObjects(*game.typesUnlifeObject, game.databaseSound);
	initializeUnlifeObjects(*game.unlifeObjects, game.typesUnlifeObject, game.emptyObject);


	// TODO
	// Категории ломаемых предметов
	initializeCategorysBreakingObject(game);

	game.Enemys = new vector<Enemy>;

	initializeTypeEnemy(game.typesEnemy, game.databaseSound);
	initializeEntitys(game.typesEnemy, *game.Enemys, game.countEntity, game.emptyItem, game.emptyObject);
	////////////////////////////////////

	// Основной персонаж
	initializeMainPerson(game.mainPerson, game.databaseSound, game.emptyItem, game.emptyObject, game.emptyEnemy);

	createTextsAndFonts(game.textGame);
	initializeTexts(game.textGame);

	// GUI
	initializeGUI(game.gui, game.textGame);



	// Часы
	initializeClock(game.clock);
}

///*
void initializeCategorysBreakingObject(Game &game) 
{
	destroyObjectsAndBlocks& listDestroy = *game.listDestroy;
	TypeUnlifeObject* typesUnlifeObject = game.typesUnlifeObject->typeUnlifeObject;
	wchar_t* charBlocks = game.field.charBlocks;

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
}
//*/


void renderEntitys(Game &game)// ДОБАВЛЕНИЕ СУЩНОСТИ
{
	RenderWindow& window = game.window;

	vector<Enemy>& Enemys = *game.Enemys;

	for (int i = 0; i != Enemys.size(); ++i) {


		if (Enemys[i].currentLevelFloor == game.mainPerson.currentLevelFloor - 1) {
			Enemys[i].spriteEntity->setColor(DOWN_VIEW);
			window.draw(*Enemys[i].spriteEntity);
			//window.draw(*game.items->item[i].spriteForUse);// ИСПРАВЬ
		}
		else if (Enemys[i].currentLevelFloor == game.mainPerson.currentLevelFloor) {
			Enemys[i].spriteEntity->setColor(NORMAL_VIEW);
			window.draw(*Enemys[i].spriteEntity);
			//window.draw(*game.items->item[i].spriteForUse);// ИСПРАВЬ
		}
		else if (Enemys[i].currentLevelFloor == game.mainPerson.currentLevelFloor + 1) {
			Enemys[i].spriteEntity->setColor(UP_VIEW);
			window.draw(*Enemys[i].spriteEntity);
			//window.draw(*game.items->item[i].spriteForUse);// ИСПРАВЬ
		}
	}

}

void destroyGame(Game & game)
{
	delete &game;
}

void informationAboutSelect(Game &game, float x, float y)
{
	///////////////////////////////////////////////////////////////////
	// Осмотр блоков
	Field &field = game.field;
	TextGame &textGame = game.textGame;
	MainPerson &mainPerson = game.mainPerson;


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


				if ( (xPosBlock == j) && (yPosBlock == i) ) {
					if (l == mainPerson.currentLevelFloor) {
						infoFloor.setString("Floor : " + field.findCharBlocks(field.dataMap[l][i][j]));
					}
					else {
						infoBlock.setString("Block : " + field.findCharBlocks(field.dataMap[l][i][j]));
					}
				}
					

				}
			}
		}
	}
	///////////////////////////////////////////////////////////////////
	// Осмотр неживых объектов
	vector<UnlifeObject> &unlifeObjects = *game.unlifeObjects;
	Text& infoUnlifeObject = textGame.texts[idText::infoWindowUnlifeObject];


	mainPerson.founds.init(&game.emptyItem,  &game.emptyObject);
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
	///////////////////////////////////////////////////////////////////
	// Осмотр предметов
	vector<Item> &items = *game.items;
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
		if (itemBound.contains(x, y) ) {
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
	///////////////////////////////////////////////////////////////////
	// Осмотр сущностей
	vector<Enemy>& Enemys = *game.Enemys;
	Text& infoEnemys = textGame.texts[idText::infoEntity];

	mainPerson.findEnemy = &game.emptyEnemy;
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
	///////////////////////////////////////////////////////////////////
}

void initializeClock(Clock &clock)// ИСПРАВЬ
{

}