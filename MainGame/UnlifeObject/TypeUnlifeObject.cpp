#include "TypeUnlifeObject.h"


using namespace sf;
using namespace std;

void initializeTypeUnlifeObjects(TypeUnlifeObject *typesUnlifeObjects, dataSound &storage) {
	
	initTree(typesUnlifeObjects, storage);
	initStones(typesUnlifeObjects, storage);
	initEmpty(typesUnlifeObjects, storage);
	initTraps(typesUnlifeObjects , storage);

	initEffects(typesUnlifeObjects, storage);
}

void initTree(TypeUnlifeObject *typesUnlifeObjects, dataSound &storage)
{
	int id = idUnlifeObject::oakGrow;
	int idNature = idNatureObject::woodNature;

	TypeUnlifeObject *typesObject = &typesUnlifeObjects[id];

	String texturePath = texturePaths[idTexturePaths::TreesPath];
	String name = "Oak";
	bool canDestroy = true;
	int toughness = 100;

	typesObject->mainSize.init(WIDTH_OAK_STUMP, HEIGHT_OAK_STUMP, PIXEL_X_OAK_STUMP, PIXEL_Y_OAK_STUMP);
	typesObject->Init(texturePath, name, storage, id, idNature);
	typesObject->defineToughness(canDestroy, toughness);
	typesObject->transparentSize.init(WIDTH_OAK, HEIGHT_OAK, PIXEL_X_OAK, PIXEL_Y_OAK);

	// Предметы
	objectDropItems drop;
	drop.addItem(3, 6, idItem::logOakItem);
	drop.addItem(2, 4, idItem::seadlingOakItem);

	typesObject->redefine.init(idUnlifeObject::oakGrow, 0);
	typesObject->drop.init(drop);
	drop.clear();
	////////////////////////////////////////////////////////////////////////////////////////
	id = idUnlifeObject::oakSmall;
	typesObject = &typesUnlifeObjects[id];

	texturePath = texturePaths[idTexturePaths::TreesPath];
	name = "Small oak";
	canDestroy = true;
	toughness = 50;

	typesObject->mainSize.init(0, 0, 0, 0);
 typesObject->Init(texturePath, name, storage, id, idNature);
	typesObject->defineToughness(canDestroy, toughness);
	typesObject->transparentSize.init(WIDTH_SMALL_OAK, HEIGHT_SMALL_OAK, PIXEL_X_SMALL_OAK, PIXEL_Y_SMALL_OAK);

	// Предметы
	drop.addItem(1, 3, idItem::logOakItem);
	drop.addItem(1, 2, idItem::seadlingOakItem);

	typesObject->redefine.init(idUnlifeObject::oakGrow, 3);
	typesObject->drop.init(drop);
	drop.clear();
	////////////////////////////////////////////////////////////////////////////////////////
	id = idUnlifeObject::appleGrowTree;
	typesObject = &typesUnlifeObjects[id];

	texturePath = texturePaths[idTexturePaths::TreesPath];
	name = "Apple tree with apple's";
	canDestroy = true;
	toughness = 50;

	typesObject->mainSize.init(0, 0, 0, 0);
 typesObject->Init(texturePath, name, storage, id, idNature);
	typesObject->defineToughness(canDestroy, toughness);
	typesObject->transparentSize.init(WIDTH_APPLE_TREE, HEIGHT_APPLE_TREE, PIXEL_X_GROW_APPLE_TREE, PIXEL_Y_GROW_APPLE_TREE);

	// Предметы
	drop.addItem(1, 2, idItem::logOakItem);
	drop.addItem(3, 6, idItem::appleItem);

	typesObject->redefine.init(idUnlifeObject::appleTree, 0);
	typesObject->drop.init(drop);
	drop.clear();
	////////////////////////////////////////////////////////////////////////////////////////
	id = idUnlifeObject::appleTree;
	typesObject = &typesUnlifeObjects[id];

	texturePath = texturePaths[idTexturePaths::TreesPath];
	name = "Apple tree";
	canDestroy = true;
	toughness = 50;

	typesObject->mainSize.init(0, 0, 0, 0);
 typesObject->Init(texturePath, name, storage, id, idNature);
	typesObject->defineToughness(canDestroy, toughness);
	typesObject->transparentSize.init(WIDTH_APPLE_TREE, HEIGHT_APPLE_TREE, PIXEL_X_APPLE_TREE, PIXEL_Y_APPLE_TREE);

	// Предметы
	drop.addItem(1, 2, idItem::logOakItem);

	typesObject->redefine.init(idUnlifeObject::appleGrowTree, 3);
	typesObject->drop.init(drop);
	drop.clear();
	////////////////////////////////////////////////////////////////////////////////////////
	id = idUnlifeObject::oakSeadling;
	typesObject = &typesUnlifeObjects[id];

	texturePath = texturePaths[idTexturePaths::TreesPath];
	name = "Seadling oak";
	canDestroy = true;
	toughness = 30;

	typesObject->mainSize.init(0, 0, 0, 0);
 typesObject->Init(texturePath, name, storage, id, idNature);
	typesObject->defineToughness(canDestroy, toughness);
	typesObject->transparentSize.init(WIDTH_SEADLING_OAK, HEIGHT_SEADLING_OAK, PIXEL_X_SEADLING_OAK, PIXEL_Y_SEADLING_OAK);

	// Предметы
	drop.addItem(1, 1, idItem::seadlingOakItem);

	typesObject->redefine.init(idUnlifeObject::oakSmall, 3);
	typesObject->drop.init(drop);
	drop.clear();
	////////////////////////////////////////////////////////////////////////////////////////
	// Саженец яблони
	id = idUnlifeObject::appleSeadling;
	typesObject = &typesUnlifeObjects[id];

	texturePath = texturePaths[idTexturePaths::TreesPath];
	name = "Apple seadling";
	canDestroy = true;
	toughness = 30;

	typesObject->mainSize.init(0, 0, 0, 0);
 typesObject->Init(texturePath, name, storage, id, idNature);
	typesObject->defineToughness(canDestroy, toughness);
	typesObject->transparentSize.init(WIDTH_SEADLING_APPLE, HEIGHT_SEADLING_APPLE, PIXEL_X_SEADLING_APPLE, PIXEL_Y_SEADLING_APPLE);

	// Предметы
	drop.addItem(1, 1, idItem::seadlingApple);

	typesObject->redefine.init(idUnlifeObject::appleTree, 3);
	typesObject->drop.init(drop);
	drop.clear();
}

void initStones(TypeUnlifeObject *typesUnlifeObjects, dataSound &storage)
{
	int id = idUnlifeObject::smallStone;
	int idNature = idNatureObject::stoneNature;
	TypeUnlifeObject *typesObject = &typesUnlifeObjects[id];
	String texturePath = texturePaths[idTexturePaths::itemsPath];
	String name = "Small stone";
	bool canDestroy = true;
	int toughness = 2;

	typesObject->mainSize.init(0, 0, 0, 0);
 typesObject->Init(texturePath, name, storage, id, idNature);
	typesObject->defineToughness(canDestroy, toughness);
	typesObject->transparentSize.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_SMALL_STONE, PIXEL_Y_SMALL_STONE);

	objectDropItems drop;
	drop.addItem(1, 1, idItem::stoneItem);

	typesObject->redefine.init(idUnlifeObject::smallStone, 0);
	typesObject->drop.init(drop);
	drop.clear();
}

void initEmpty(TypeUnlifeObject *typesUnlifeObjects, dataSound &storage)
{
	int id = idUnlifeObject::empty;
	int idNature = idNatureObject::Unbreaking;

	TypeUnlifeObject *typesObject = &typesUnlifeObjects[id];
	typesObject->Init(texturePaths[idTexturePaths::itemsPath], "Empty", storage, id, idNature);
	typesObject->defineToughness(false, 0);

	typesObject->mainSize.init(0, 0, 0, 0);
	typesObject->defineToughness(false, 0);
	typesObject->transparentSize.init(0, 0, 0, 0);

}

void initTraps(TypeUnlifeObject * typesUnlifeObjects , dataSound & storage)
{
	int id = idUnlifeObject::mineObject;
	int idNature = idNatureObject::stoneNature;
	TypeUnlifeObject *typesObject = &typesUnlifeObjects[id];
	String texturePath = texturePaths[idTexturePaths::minePath];
	String name = "Mine";
	bool canDestroy = true;
	int toughness = 20;

	typesObject->mainSize.init(0 , 0 , 0 , 0);
	typesObject->Init(texturePath , name , storage , id , idNature);
	typesObject->defineToughness(canDestroy , toughness);
	typesObject->transparentSize.init(WIDTH_MINE , HEIGHT_MINE , PIXEL_X_MINE , PIXEL_Y_MINE);

	objectDropItems drop;
	drop.addItem(0 , 0 , idItem::grassItem);

	typesObject->redefine.init(idUnlifeObject::smallStone , 0);
	typesObject->drop.init(drop);
	drop.clear();
}

void initEffects(TypeUnlifeObject* typesUnlifeObjects, dataSound &storage)
{
	int id = idUnlifeObject::skeletDeathEffect;
	int idNature = idNatureObject::Unbreaking;
	TypeUnlifeObject *typesObject = &typesUnlifeObjects[id];
	String texturePath = texturePaths[idTexturePaths::skeletPath];
	String name = "Skelet Death";
	bool canDestroy = false;
	int toughness = 1;

	typesObject->mainSize.init(0, 0, 0, 0);
 typesObject->Init(texturePath, name, storage, id, idNature);
	typesObject->defineToughness(canDestroy, toughness);
	typesObject->transparentSize.init(WIDTH_SKELET, HEIGHT_SKELET, 0, HEIGHT_SKELET * 7);

	objectDropItems drop;
	drop.addItem(0, 0, idItem::stoneItem);

	//typesObject->redefine.init(idUnlifeObject::smallStone, 0);
	typesObject->drop.init(drop);
	drop.clear();
	///////////////////////////////////////////
	id = idUnlifeObject::wolfDeathEffect;
	typesObject = &typesUnlifeObjects[id];

	texturePath = texturePaths[idTexturePaths::wolfPath];
	name = "Wolf death";
	canDestroy = false;
	toughness = 0;

	typesObject->mainSize.init(0, 0, 0, 0);
 typesObject->Init(texturePath, name, storage, id, idNature);
	typesObject->defineToughness(canDestroy, toughness);
	typesObject->transparentSize.init(WIDTH_WOLF, HEIGHT_WOLF, 0, HEIGHT_WOLF * 7);

	// Предметы
	drop.addItem(0, 0, idItem::stoneItem);

	//typesObject->redefine.init(idUnlifeObject::appleTree, 0);
	typesObject->drop.init(drop);
	drop.clear();
	////////////////////////////////////////////////////////////////////////////////////////
	id = idUnlifeObject::destroyBlockEffect;
	typesObject = &typesUnlifeObjects[id];

	texturePath = texturePaths[idTexturePaths::destroyBlockPath];
	name = "Destroy block";
	canDestroy = true;
	toughness = 50;

	typesObject->mainSize.init(WIDTH_DESTROY_BLOCK_EFFECT, HEIGHT_DESTROY_BLOCK_EFFECT, 0, 0);
	typesObject->Init(texturePath, name, storage, id, idNature);
	typesObject->defineToughness(canDestroy, toughness);
	typesObject->transparentSize.init(WIDTH_DESTROY_BLOCK_EFFECT , HEIGHT_DESTROY_BLOCK_EFFECT , 0 , 0);

	// Предметы
	drop.addItem(1, 3, idItem::logOakItem);
	drop.addItem(1, 2, idItem::seadlingOakItem);

	typesObject->redefine.init(idUnlifeObject::destroyBlockEffect, 0);
	typesObject->drop.init(drop);
	drop.clear();
	////////////////////////////////////////////////////////////////////////////////////////
}

void redefineObject::init(int idType, float time)
{
	id = idType;
	timeUpdate = time;
}

void TypeUnlifeObject::defineToughness(bool canDestroy, int toughness)
{
	isDestroy = canDestroy;
	toughnessObject = toughness;
	if (isDestroy == false) {
		toughnessObject = 0;
	}

}

void TypeUnlifeObject::Init(String filenameTexture, String typeName, dataSound &storage, int idType, int numberNature) {
	textureObject = new Texture;
	textureObject->loadFromFile(filenameTexture);

	name = typeName;
	id = idType;
	idNature = numberNature;
	soundBase = &storage;
};