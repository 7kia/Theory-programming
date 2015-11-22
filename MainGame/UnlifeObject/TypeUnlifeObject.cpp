#include "TypeUnlifeObject.h"



using namespace sf;
using namespace std;

void initializeTypeUnlifeObjects(TypeUnlifeObject *typesUnlifeObjects, dataSound &databaseSound) {
	////////////////////////////////////////////////////////////////////////////////////////
	TypeUnlifeObject *typesObject = &typesUnlifeObjects[idUnlifeObject::oakGrow];

	String texturePath = texturePaths[idTexturePaths::Trees];
	String name = "Oak";
	bool canDestroy = true;
	int toughness = 100;

	typesObject->mainSize.init(WIDTH_OAK_STUMP, HEIGHT_OAK_STUMP, PIXEL_X_OAK_STUMP, PIXEL_Y_OAK_STUMP);
	typesObject->Init(texturePath, name, canDestroy, toughness);
	typesObject->transparentSize.init(WIDTH_OAK, HEIGHT_OAK, PIXEL_X_OAK, PIXEL_Y_OAK);

	// Предметы
	objectDropItems drop;
	drop.addItem(3, 6, idItem::logOakItem);
	drop.addItem(2, 4, idItem::seadlingOakItem);

	typesObject->redefine.init(idUnlifeObject::oakGrow, 0);
	typesObject->drop.init(drop);
	drop.clear();
	////////////////////////////////////////////////////////////////////////////////////////
	typesObject = &typesUnlifeObjects[idUnlifeObject::oakSmall];

	texturePath = texturePaths[idTexturePaths::Trees];
	name = "Small oak";
	canDestroy = true;
	toughness = 50;

	typesObject->mainSize.init(0, 0, 0, 0);
	typesObject->Init(texturePath, name, canDestroy, toughness);

	typesObject->transparentSize.init(WIDTH_SMALL_OAK, HEIGHT_SMALL_OAK, PIXEL_X_SMALL_OAK, PIXEL_Y_SMALL_OAK);

	// Предметы
	drop.addItem(1, 3, idItem::logOakItem);
	drop.addItem(1, 2, idItem::seadlingOakItem);

	typesObject->redefine.init(idUnlifeObject::oakGrow, 3);
	typesObject->drop.init(drop);
	drop.clear();
	////////////////////////////////////////////////////////////////////////////////////////
	typesObject = &typesUnlifeObjects[idUnlifeObject::appleGrowTree];

	texturePath = texturePaths[idTexturePaths::Trees];
	name = "Apple tree with apple's";
	canDestroy = true;
	toughness = 50;

	typesObject->mainSize.init(0, 0, 0, 0);
	typesObject->Init(texturePath, name, canDestroy, toughness);

	typesObject->transparentSize.init(WIDTH_APPLE_TREE, HEIGHT_APPLE_TREE, PIXEL_X_GROW_APPLE_TREE, PIXEL_Y_GROW_APPLE_TREE);

	// Предметы
	drop.addItem(1, 2, idItem::logOakItem);
	drop.addItem(3, 6, idItem::appleItem);

	typesObject->redefine.init(idUnlifeObject::appleGrowTree, 0);
	typesObject->drop.init(drop);
	drop.clear();
	////////////////////////////////////////////////////////////////////////////////////////
	typesObject = &typesUnlifeObjects[idUnlifeObject::appleTree];

	texturePath = texturePaths[idTexturePaths::Trees];
	name = "Apple tree";
	canDestroy = true;
	toughness = 50;

	typesObject->mainSize.init(0, 0, 0, 0);
	typesObject->Init(texturePath, name, canDestroy, toughness);

	typesObject->transparentSize.init(WIDTH_APPLE_TREE, HEIGHT_APPLE_TREE, PIXEL_X_APPLE_TREE, PIXEL_Y_APPLE_TREE);

	// Предметы
	drop.addItem(1, 2, idItem::logOakItem);

	typesObject->redefine.init(idUnlifeObject::appleGrowTree, 3);
	typesObject->drop.init(drop);
	drop.clear();
	////////////////////////////////////////////////////////////////////////////////////////
	// Саженец дуба
	typesObject = &typesUnlifeObjects[idUnlifeObject::oakSeadling];

	texturePath = texturePaths[idTexturePaths::Trees];
	name = "Seadling oak";
	canDestroy = true;
	toughness = 30;

	typesObject->mainSize.init(0, 0, 0, 0);
	typesObject->Init(texturePath, name, canDestroy, toughness);

	typesObject->transparentSize.init(WIDTH_SEADLING_OAK, HEIGHT_SEADLING_OAK, PIXEL_X_SEADLING_OAK, PIXEL_Y_SEADLING_OAK);

	// Предметы
	drop.addItem(1, 1, idItem::seadlingOakItem);

	typesObject->redefine.init(idUnlifeObject::oakSmall, 3);
	typesObject->drop.init(drop);
	drop.clear();
	////////////////////////////////////////////////////////////////////////////////////////
	// Саженец яблони
	typesObject = &typesUnlifeObjects[idUnlifeObject::appleSeadling];

	texturePath = texturePaths[idTexturePaths::Trees];
	name = "Apple seadling";
	canDestroy = true;
	toughness = 30;

	typesObject->mainSize.init(0, 0, 0, 0);
	typesObject->Init(texturePath, name, canDestroy, toughness);

	typesObject->transparentSize.init(WIDTH_SEADLING_APPLE, HEIGHT_SEADLING_APPLE, PIXEL_X_SEADLING_APPLE, PIXEL_Y_SEADLING_APPLE);

	// Предметы
	drop.addItem(1, 1, idItem::seadlingApple);

	typesObject->redefine.init(idUnlifeObject::appleTree, 3);
	typesObject->drop.init(drop);
	drop.clear();
	////////////////////////////////////////////////////////////////////////////////////////
	typesObject = &typesUnlifeObjects[idUnlifeObject::smallStone];
	texturePath = texturePaths[idTexturePaths::items];
	name = "Small stone";
	canDestroy = true;
	toughness = 2;

	typesObject->mainSize.init(0, 0, 0, 0);
	typesObject->Init(texturePath, name, canDestroy, toughness);

	typesObject->transparentSize.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_SMALL_STONE, PIXEL_Y_SMALL_STONE);

	// Предметы
	drop.addItem(1, 1, idItem::stoneItem);

	typesObject->redefine.init(idUnlifeObject::smallStone, 0);
	typesObject->drop.init(drop);
	drop.clear();
	////////////////////////////////////////////////////////////////////////////////////////
	// Пустой предмет
	typesObject = &typesUnlifeObjects[idUnlifeObject::empty];
	typesObject->Init(texturePaths[idTexturePaths::items], "Empty", false, 0);
}

void redefineObject::init(int idType, float time)
{
	id = idType;
	timeUpdate = time;
}

////////////////////////////////////////////////////////////////////
// Виды объектов
void TypeUnlifeObject::Init(String filenameTexture, String typeName, bool canDestroy, int toughness) {
	textureObject = new Texture;
	textureObject->loadFromFile(filenameTexture);

	name = typeName;

	isDestroy = canDestroy;
	toughnessObject = toughness;
	if (isDestroy == false) {
		toughness = 0;
	}

	// TODO
	// Звуки 
	//mainPerson.soundsEntity[idSoundEntity::stepGrass] = &databaseSound.sounds[idSoundEntity::stepGrass];
	//mainPerson.soundsEntity[idSoundEntity::stepStone] = &databaseSound.sounds[idSoundEntity::stepStone];
};
////////////////////////////////////////////////////////////////////