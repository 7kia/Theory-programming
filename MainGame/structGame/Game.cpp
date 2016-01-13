//#include "../Entity/Entity.h"
#include "Game.h"

using namespace std;

Game::Game()
{
	window.create(VideoMode(widthMainWindow, heightMainWindow), TITLE_PROGRAM);

	playMusic = false;
	::sounds = &world.databaseSound;

	typesObjectsInWorld &types = world.typesObjects;

	initializeTypeUnlifeObjects(types.typesUnlifeObject, world.databaseSound);
	initializeUnlifeObjects(world.unlifeObjects, types.typesUnlifeObject, world.emptyObjects.emptyObject);

	world.initializeCategorysBreakingObject();

	initializeTypesItem(types.typesItem, world.listDestroy);
	initializeItems(world.items, types.typesItem, world.emptyObjects.emptyItem);

	initTypeShoots(world.typesObjects.typesShoot);
	createListAward();

	// TODO : create configs for different category variables
	loadConfig("Configs\\EnemeWaves.conf", world.enemyWaveVariables);
	difficult = world.enemyWaveVariables[CURRENT_DIFFICULT];

	initializeTypeEnemy(types.typesEnemy, types.typesItem);
	initializeEntitys(world);


	world.initializePlayer(world.view, world.listener);
	initializeHotKeys();

	createTextsAndFonts(textGame);
	initializeTexts(textGame);

	initializeGUI(gui, textGame);

	if(playMusic)
	{
		playDayMusic();
	}

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
					variables[id] = Math::stringToInt(value);

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

void world::initializeCategorysBreakingObject() 
{
	TypeUnlifeObject *typesUnlifeObject = typesObjects.typesUnlifeObject;
	wchar_t* charBlocks = field.charBlocks;

	listDestroy.backhoe.push_back(idNatureObject::groundNature);
	listDestroy.backhoe.push_back(idNatureObject::sandNature);

	listDestroy.axe.push_back(idNatureObject::woodNature);

	listDestroy.pickax.push_back(idNatureObject::stoneNature);

	listDestroy.stoneKnife.push_back(idNatureObject::stoneNature);
	listDestroy.stoneKnife.push_back(idNatureObject::woodNature);
	listDestroy.stoneKnife.push_back(idNatureObject::groundNature);
	listDestroy.stoneKnife.push_back(idNatureObject::sandNature);

	listDestroy.none.push_back(idNatureObject::Unbreaking);

	listDestroy.passableBlocks.push_back(charBlocks[idBlocks::air]);
	listDestroy.passableBlocks.push_back(charBlocks[idBlocks::woodLadder]);

	listDestroy.notPassableFloor.push_back(charBlocks[idBlocks::air]);

	listDestroy.ladder.push_back(charBlocks[idBlocks::woodLadder]);

	listDestroy.harvestObjects.push_back(typesUnlifeObject[idUnlifeObject::appleGrowTree].id);

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

//	delete &game;
}
