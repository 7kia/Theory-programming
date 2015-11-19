#include "Game.h"
#include "EntityVar.h"

using namespace std;

void initializeGame(Game & game)
{
	
	game.world.unlifeObjects = new vector<UnlifeObject>;
	game.world.items = new vector<Item>;
	game.world.listDestroy = new listDestroyObjectsAndBlocks;

	game.window.create(VideoMode(game.widthMainWindow, game.heightMainWindow), TITLE_PROGRAM);

	initializeSound(game.databaseSound);
	initializeField(game.world.field);

	typesObjectsInWorld &types = game.world.typesObjects;
	initializeTypesItem(types.typesItem, *game.world.listDestroy, game.databaseSound);
	initializeItems(*game.world.items, types.typesItem, game.emptyItem);

	initializeTypeUnlifeObjects(types.typesUnlifeObject, game.databaseSound);
	initializeUnlifeObjects(*game.world.unlifeObjects, types.typesUnlifeObject, game.emptyObject);

	// TODO
	initializeCategorysBreakingObject(game);

	game.world.Enemys = new vector<Enemy>;

	initializeTypeEnemy(types, game.databaseSound);
	initializeEntitys(types.typesEnemy, game.world, game.countEntity, game.emptyItem, game.emptyObject, game.emptyEnemy);

	initializeMainPerson(game.mainPerson, game.databaseSound, game.emptyItem, game.emptyObject, game.emptyEnemy);

	createTextsAndFonts(game.textGame);
	initializeTexts(game.textGame);

	initializeGUI(game.gui, game.textGame);

	initializeClock(game.clock);
}

///*
void initializeCategorysBreakingObject(Game &game) 
{
	listDestroyObjectsAndBlocks &listDestroy = *game.world.listDestroy;
	typesObjectsInWorld &types = game.world.typesObjects;
	TypeUnlifeObject* typesUnlifeObject = types.typesUnlifeObject;
	wchar_t* charBlocks = game.world.field.charBlocks;

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

void updateEntity(Game& game, const Time deltaTime)
{
	vector<Enemy>& Enemys = *game.world.Enemys;
	Field &field = game.world.field;
	for (int i = 0; i < Enemys.size(); ++i) {
		Enemys[i].update(deltaTime, game.databaseSound);
		Enemys[i].interactionWithMap(field, *game.world.listDestroy, deltaTime);
		game.mainPerson.attractionEnemy(Enemys[i], game.world, deltaTime);
		Enemys[i].randomWalk(deltaTime);
	}
}

//*/


void renderEntitys(Game &game)
{
	RenderWindow& window = game.window;

	vector<Enemy>& Enemys = *game.world.Enemys;

	int enemyLevel;
	const int personLevel = game.mainPerson.currentLevelFloor;
	for (int i = 0; i < Enemys.size(); ++i) {
		enemyLevel = Enemys[i].currentLevelFloor;
		if (enemyLevel >= personLevel - 1 && enemyLevel <= personLevel + 1) {
			printf("ID  %d\n", Enemys[i].idSelectItem);
			Enemys[i].renderCurrentItem(window);

			Color currentColor;
			if(personLevel) currentColor = NORMAL_COLOR;
			else if(personLevel - 1) currentColor = DOWN_VIEW;
			else if(personLevel + 1) currentColor = UP_VIEW;
			Enemys[i].spriteEntity->setColor(NORMAL_COLOR);
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

	Field &field = game.world.field;
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
					else if(l == mainPerson.currentLevelFloor + 1){
						infoBlock.setString("Block : " + field.findCharBlocks(field.dataMap[l][i][j]));
					}
				}
					

				}
			}
		}
	}

	vector<UnlifeObject> &unlifeObjects = *game.world.unlifeObjects;
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

	vector<Item> &items = *game.world.items;
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

	vector<Enemy>& Enemys = *game.world.Enemys;
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
	
}

void initializeClock(Clock &clock)// ИСПРАВЬ
{

}