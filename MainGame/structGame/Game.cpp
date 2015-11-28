#include "Game.h"
#include "updateGame.h"
#include "renderGame.h"
#include "../worldCircle/worldCircle.h"

using namespace std;


void Game::informationAboutSelect(float x, float y)
{

	Field &field = world.field;

	int xPosBlock = int(x / SIZE_BLOCK);
	int yPosBlock = int(y / SIZE_BLOCK);

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

Game::Game()
{
	
	world.unlifeObjects = new vector<UnlifeObject>;
	world.items = new vector<Item>;
	world.listDestroy = new listDestroyObjectsAndBlocks;

	window.create(VideoMode(widthMainWindow, heightMainWindow), TITLE_PROGRAM);

	initializeField(world.field);

	typesObjectsInWorld &types = world.typesObjects;
	initializeTypesItem(types.typesItem, *world.listDestroy, databaseSound);
	initializeItems(*world.items, types.typesItem, world.emptyObjects.emptyItem);

	initializeTypeUnlifeObjects(types.typesUnlifeObject, databaseSound);
	initializeUnlifeObjects(*world.unlifeObjects, types.typesUnlifeObject, world.emptyObjects.emptyObject);

	// TODO
	initializeCategorysBreakingObject();

	loadConfig();

	world.Enemys = new vector<Enemy>;

	initializeTypeEnemy(types, databaseSound);
	initializeEntitys(world);

	initializeMainPerson(mainPerson, databaseSound, world.emptyObjects);
	initializeHotKeys();

	createTextsAndFonts(textGame);
	initializeTexts(textGame);

	initializeGUI(gui, textGame);

	initializeClock(clock);
}

void Game::loadConfig()
{

	FILE *pConfigFile;
	errno_t eMapFile = fopen_s(&pConfigFile, "config.txt", "r");

	const int amountHelpSymblos = 4;
	wchar_t buff[amountHelpSymblos];

	// Если файл открыт
	if (pConfigFile) {
		
		bool passString = false;
		bool searchSymbolEqually = false;
		bool searchSymbolSpace = false;
		bool recordValue = false;
		bool searchName = false;
		char currentSymbol;
		string value = "";

		size_t id = 0;

		while (!feof(pConfigFile)) {
			currentSymbol = fgetc(pConfigFile);
			if (currentSymbol == '#')
			{
				passString = true;
				recordValue = false;
			}
			else if(currentSymbol == '\n')
			{
				passString = false;
				searchSymbolSpace = false;
			}

			if (recordValue) {
				if (currentSymbol != '\n') {
					value += currentSymbol;
				}
				else {
					//std::cout << "value = %s " << value << std::endl;
					stringToInt(world.configVariable[id], value);

					id++;
					value.clear();

					recordValue = false;
					searchSymbolSpace = false;
				}
			}

			if(passString == false)
			{
				if (searchSymbolSpace == false) {
					if (currentSymbol == ' ') {
						recordValue = true;
					}
				}
			}

				//fgetws(buff, amountHelpSymblos, pMapFile);//Пропускаем остальную часть строки

		}
		
	}
	else {
		printf("File not find!\n");
	}
}

///*
void Game::initializeCategorysBreakingObject() 
{
	listDestroyObjectsAndBlocks &listDestroy = *world.listDestroy;
	typesObjectsInWorld &types = world.typesObjects;
	TypeUnlifeObject* typesUnlifeObject = types.typesUnlifeObject;
	wchar_t* charBlocks = world.field.charBlocks;

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

void Game::initializeHotKeys()
{
	for (int i = 0; i < hotKeys::amountKeys; i++)
	{
		keys[i] = hotKeys::defaultValue[i];
	}
}

//*/

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