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
	mainPerson.findEnemy = mainPerson.emptyEnemy;
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

	world.deleteUnlifeObjects = new vector<int>;
	world.deleteItems = new vector<int>;
	world.deleteEnemys = new vector<int>;;


	window.create(VideoMode(widthMainWindow, heightMainWindow), TITLE_PROGRAM);


	initializeField(world.field);

	::sounds = &world.databaseSound;

	typesObjectsInWorld &types = world.typesObjects;

	initializeTypeUnlifeObjects(types.typesUnlifeObject, world.databaseSound);
	initializeUnlifeObjects(*world.unlifeObjects, types.typesUnlifeObject, world.emptyObjects.emptyObject);

	initializeCategorysBreakingObject();

	initializeTypesItem(types.typesItem, *world.listDestroy);
	initializeItems(*world.items, types.typesItem, world.emptyObjects.emptyItem);

	createListAward();

	// TODO
	loadConfig("Configs\\EnemeWaves.conf", world.enemyWaveVariables);
	difficult = world.enemyWaveVariables[CURRENT_DIFFICULT];

	initializeTypeEnemy(types);
	initializeEntitys(world);

	initializeMainPerson(mainPerson, world);
	initializeHotKeys();

	createTextsAndFonts(textGame);
	initializeTexts(textGame);

	initializeGUI(gui, textGame);

	playDayMusic();
}

void Game::loadConfig(char *nameConfig, int *variables)
{

	FILE *pConfigFile;
	errno_t eMapFile = fopen_s(&pConfigFile, nameConfig, "r");

	if (eMapFile == 0) {
		
		bool passString = false;
		bool searchSymbolSpace = false;
		bool recordValue = false;
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
					std::cout << "value = %s " << value << std::endl;
					stringToInt(variables[id], value);

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
		}
		
	}
	else {
		printf("File not find!\n");
	}
}

void Game::initializeCategorysBreakingObject() 
{
	listDestroyObjectsAndBlocks &listDestroy = *world.listDestroy;
	typesObjectsInWorld &types = world.typesObjects;
	TypeUnlifeObject* typesUnlifeObject = types.typesUnlifeObject;
	wchar_t* charBlocks = world.field.charBlocks;

	//////////////////////////////////////
	// Блоки уничтожаемые лопатой
	listDestroy.backhoe = new vector<int>;
	vector<int> *listIds = listDestroy.backhoe;

	listIds->push_back(idNatureObject::groundNature);
	listIds->push_back(idNatureObject::sandNature);
	//////////////////////////////////////
	// Блоки уничтожаемые топором
	listDestroy.axe = new vector<int>;
	listIds = listDestroy.axe;

	listIds->push_back(idNatureObject::woodNature);
	//////////////////////////////////////
	// Блоки уничтожаемые киркой
	listDestroy.pickax = new vector<int>;
	listIds = listDestroy.pickax;

	listIds->push_back(idNatureObject::stoneNature);
	//////////////////////////////////////
	// Блоки уничтожаемые каменным ножом
	listDestroy.stoneKnife = new vector<int>;
	listIds = listDestroy.stoneKnife;

	listIds->push_back(idNatureObject::stoneNature);
	listIds->push_back(idNatureObject::woodNature);
	listIds->push_back(idNatureObject::groundNature);
	listIds->push_back(idNatureObject::sandNature);

	listDestroy.none = new vector<int>;
	listIds = listDestroy.none;
	listIds->push_back(idNatureObject::NoneNature);
	/////////////////////////////////////////////////////////////////////////
	// Проходимые блоки
	listDestroy.passableBlocks = new vector<wchar_t>;
	vector<wchar_t> *listBlocks = listDestroy.passableBlocks;

	listBlocks->push_back(charBlocks[idBlocks::air]);
	listBlocks->push_back(charBlocks[idBlocks::water]);
	listBlocks->push_back(charBlocks[idBlocks::woodLadder]);

	/////////////////////////////////////////////////////////////////////////
	// Проходим по полу
	listDestroy.notPassableFloor = new vector<wchar_t>;
	listBlocks = listDestroy.notPassableFloor;

	listBlocks->push_back(charBlocks[idBlocks::air]);
	/////////////////////////////////////////////////////////////////////////
	// Замедляющие блоки
	listDestroy.slowingBlocks = new vector<wchar_t>;
	listBlocks = listDestroy.slowingBlocks;

	listBlocks->push_back(charBlocks[idBlocks::water]);
	/////////////////////////////////////////////////////////////////////////
	// Лестницы
	listDestroy.ladder = new vector<wchar_t>;
	listBlocks = listDestroy.ladder;

	listBlocks->push_back(charBlocks[idBlocks::woodLadder]);
	/////////////////////////////////////////////////////////////////////////
	listDestroy.harvestObjects = new vector<int>;
	vector<int> *listObjects = listDestroy.harvestObjects;

	listObjects->push_back(typesUnlifeObject[idUnlifeObject::appleGrowTree].id);
	/////////////////////////////////////////////////////////////////////////

}

void Game::initializeHotKeys()
{
	for (int i = 0; i < hotKeys::amountKeys; i++)
	{
		keys[i] = hotKeys::defaultValue[i];
	}
}

void destroyGame(Game & game)
{
	// TODO
	delete game.world.items;
	delete game.world.unlifeObjects;
	delete game.world.Enemys;
	delete game.world.listDestroy;

	delete &game;
}
