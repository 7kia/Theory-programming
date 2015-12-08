#include "TypeUnlifeObject.h"
#include "../ListObjectsAndBlocks.h"


using namespace sf;
using namespace std;

void initializeTypeUnlifeObjects(TypeUnlifeObject *typesUnlifeObjects) {
	
	initTree(typesUnlifeObjects);
	initStones(typesUnlifeObjects);
	initEmpty(typesUnlifeObjects);

	initEffects(typesUnlifeObjects);
}

void initTree(TypeUnlifeObject *typesUnlifeObjects)
{
	int id = idUnlifeObject::oakGrow;
	int idNature = idNatureObject::woodNature;

	TypeUnlifeObject *typesObject = &typesUnlifeObjects[id];

	String texturePath = texturePaths[idTexturePaths::Trees];
	String name = "Oak";
	bool canDestroy = true;
	int toughness = 100;

	typesObject->mainSize.init(WIDTH_OAK_STUMP, HEIGHT_OAK_STUMP, PIXEL_X_OAK_STUMP, PIXEL_Y_OAK_STUMP);
	typesObject->Init(texturePath, name, id, idNature);
	typesObject->defineToughness(canDestroy, toughness);
	typesObject->transparentSize.init(WIDTH_OAK, HEIGHT_OAK, PIXEL_X_OAK, PIXEL_Y_OAK);

	// ��������
	objectDropItems drop;
	drop.addItem(3, 6, idItem::logOakItem);
	drop.addItem(2, 4, idItem::seadlingOakItem);

	typesObject->redefine.init(idUnlifeObject::oakGrow, 0);
	typesObject->drop.init(drop);
	drop.clear();
	////////////////////////////////////////////////////////////////////////////////////////
	id = idUnlifeObject::oakSmall;
	typesObject = &typesUnlifeObjects[id];

	texturePath = texturePaths[idTexturePaths::Trees];
	name = "Small oak";
	canDestroy = true;
	toughness = 50;

	typesObject->mainSize.init(0, 0, 0, 0);
	typesObject->Init(texturePath, name, id, idNature);
	typesObject->defineToughness(canDestroy, toughness);
	typesObject->transparentSize.init(WIDTH_SMALL_OAK, HEIGHT_SMALL_OAK, PIXEL_X_SMALL_OAK, PIXEL_Y_SMALL_OAK);

	// ��������
	drop.addItem(1, 3, idItem::logOakItem);
	drop.addItem(1, 2, idItem::seadlingOakItem);

	typesObject->redefine.init(idUnlifeObject::oakGrow, 3);
	typesObject->drop.init(drop);
	drop.clear();
	////////////////////////////////////////////////////////////////////////////////////////
	id = idUnlifeObject::appleGrowTree;
	typesObject = &typesUnlifeObjects[id];

	texturePath = texturePaths[idTexturePaths::Trees];
	name = "Apple tree with apple's";
	canDestroy = true;
	toughness = 50;

	typesObject->mainSize.init(0, 0, 0, 0);
	typesObject->Init(texturePath, name, id, idNature);
	typesObject->defineToughness(canDestroy, toughness);
	typesObject->transparentSize.init(WIDTH_APPLE_TREE, HEIGHT_APPLE_TREE, PIXEL_X_GROW_APPLE_TREE, PIXEL_Y_GROW_APPLE_TREE);

	// ��������
	drop.addItem(1, 2, idItem::logOakItem);
	drop.addItem(3, 6, idItem::appleItem);

	typesObject->redefine.init(idUnlifeObject::appleTree, 0);
	typesObject->drop.init(drop);
	drop.clear();
	////////////////////////////////////////////////////////////////////////////////////////
	id = idUnlifeObject::appleTree;
	typesObject = &typesUnlifeObjects[id];

	texturePath = texturePaths[idTexturePaths::Trees];
	name = "Apple tree";
	canDestroy = true;
	toughness = 50;

	typesObject->mainSize.init(0, 0, 0, 0);
	typesObject->Init(texturePath, name, id, idNature);
	typesObject->defineToughness(canDestroy, toughness);
	typesObject->transparentSize.init(WIDTH_APPLE_TREE, HEIGHT_APPLE_TREE, PIXEL_X_APPLE_TREE, PIXEL_Y_APPLE_TREE);

	// ��������
	drop.addItem(1, 2, idItem::logOakItem);

	typesObject->redefine.init(idUnlifeObject::appleGrowTree, 3);
	typesObject->drop.init(drop);
	drop.clear();
	////////////////////////////////////////////////////////////////////////////////////////
	id = idUnlifeObject::oakSeadling;
	typesObject = &typesUnlifeObjects[id];

	texturePath = texturePaths[idTexturePaths::Trees];
	name = "Seadling oak";
	canDestroy = true;
	toughness = 30;

	typesObject->mainSize.init(0, 0, 0, 0);
	typesObject->Init(texturePath, name, id, idNature);
	typesObject->defineToughness(canDestroy, toughness);
	typesObject->transparentSize.init(WIDTH_SEADLING_OAK, HEIGHT_SEADLING_OAK, PIXEL_X_SEADLING_OAK, PIXEL_Y_SEADLING_OAK);

	// ��������
	drop.addItem(1, 1, idItem::seadlingOakItem);

	typesObject->redefine.init(idUnlifeObject::oakSmall, 3);
	typesObject->drop.init(drop);
	drop.clear();
	////////////////////////////////////////////////////////////////////////////////////////
	// ������� ������
	id = idUnlifeObject::appleSeadling;
	typesObject = &typesUnlifeObjects[id];

	texturePath = texturePaths[idTexturePaths::Trees];
	name = "Apple seadling";
	canDestroy = true;
	toughness = 30;

	typesObject->mainSize.init(0, 0, 0, 0);
	typesObject->Init(texturePath, name, id, idNature);
	typesObject->defineToughness(canDestroy, toughness);
	typesObject->transparentSize.init(WIDTH_SEADLING_APPLE, HEIGHT_SEADLING_APPLE, PIXEL_X_SEADLING_APPLE, PIXEL_Y_SEADLING_APPLE);

	// ��������
	drop.addItem(1, 1, idItem::seadlingApple);

	typesObject->redefine.init(idUnlifeObject::appleTree, 3);
	typesObject->drop.init(drop);
	drop.clear();
}

void initStones(TypeUnlifeObject *typesUnlifeObjects)
{
	int id = idUnlifeObject::smallStone;
	int idNature = idNatureObject::stoneNature;
	TypeUnlifeObject *typesObject = &typesUnlifeObjects[id];
	String texturePath = texturePaths[idTexturePaths::items];
	String name = "Small stone";
	bool canDestroy = true;
	int toughness = 2;

	typesObject->mainSize.init(0, 0, 0, 0);
	typesObject->Init(texturePath, name, id, idNature);
	typesObject->defineToughness(canDestroy, toughness);
	typesObject->transparentSize.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_SMALL_STONE, PIXEL_Y_SMALL_STONE);

	objectDropItems drop;
	drop.addItem(1, 1, idItem::stoneItem);

	typesObject->redefine.init(idUnlifeObject::smallStone, 0);
	typesObject->drop.init(drop);
	drop.clear();
}

void initEmpty(TypeUnlifeObject *typesUnlifeObjects)
{
	int id = idUnlifeObject::empty;
	TypeUnlifeObject *typesObject = &typesUnlifeObjects[id];
	typesObject->Init(texturePaths[idTexturePaths::items], "Empty", id, 0);
	typesObject->defineToughness(false, 0);
}

void initEffects(TypeUnlifeObject* typesUnlifeObjects)
{
	int id = idUnlifeObject::skeletDeathEffect;
	int idNature = idNatureObject::NoneNature;
	TypeUnlifeObject *typesObject = &typesUnlifeObjects[id];
	String texturePath = texturePaths[idTexturePaths::skelet];
	String name = "Skelet Death";
	bool canDestroy = false;
	int toughness = 1;

	typesObject->mainSize.init(0, 0, 0, 0);
	typesObject->Init(texturePath, name, id, idNature);
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

	texturePath = texturePaths[idTexturePaths::wolf];
	name = "Wolf death";
	canDestroy = false;
	toughness = 0;

	typesObject->mainSize.init(0, 0, 0, 0);
	typesObject->Init(texturePath, name, id, idNature);
	typesObject->defineToughness(canDestroy, toughness);
	typesObject->transparentSize.init(WIDTH_WOLF, HEIGHT_WOLF, 0, HEIGHT_WOLF * 7);

	// ��������
	drop.addItem(0, 0, idItem::stoneItem);

	//typesObject->redefine.init(idUnlifeObject::appleTree, 0);
	typesObject->drop.init(drop);
	drop.clear();
	////////////////////////////////////////////////////////////////////////////////////////
	id = idUnlifeObject::destroyBlockEffect;
	typesObject = &typesUnlifeObjects[id];

	texturePath = texturePaths[idTexturePaths::destroyBlock];
	name = "Destroy block";
	canDestroy = true;
	toughness = 50;

	typesObject->mainSize.init(WIDTH_DESTROY_BLOCK_EFFECT, HEIGHT_DESTROY_BLOCK_EFFECT, 0, 0);
	typesObject->Init(texturePath, name, id, idNature);
	typesObject->defineToughness(canDestroy, toughness);
	typesObject->transparentSize.init(0, 0, 0, 0);

	// ��������
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

void TypeUnlifeObject::Init(String filenameTexture, String typeName, int idType, int numberNature) {
	textureObject = new Texture;
	textureObject->loadFromFile(filenameTexture);

	name = typeName;
	id = idType;
	idNature = numberNature;

};