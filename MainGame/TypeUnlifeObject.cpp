#include "TypeUnlifeObject.h"
#include "Recourses.h"
#include "UnlifeObjectVar.h"
#include "ItemsVar.h"

using namespace sf;
using namespace std;

void initializeTypeUnlifeObjects(TypeUnlifeObject *typesUnlifeObjects, dataSound &databaseSound) {
	////////////////////////////////////////////////////////////////////////////////////////
	TypeUnlifeObject *typesObject = &typesUnlifeObjects[idUnlifeObject::oakGrow];

	String texturePath = texturePaths[idTexturePaths::Trees];
	String name = "Oak";
	bool canDestroy = true;
	int toughness = 2;

	typesObject->mainSize.init(WIDTH_OAK_STUMP, HEIGHT_OAK_STUMP, PIXEL_X_OAK_STUMP, PIXEL_Y_OAK_STUMP);
	typesObject->Init(texturePath, name, canDestroy, toughness);
	typesObject->transparentSize.init(WIDTH_OAK, HEIGHT_OAK, PIXEL_X_OAK, PIXEL_Y_OAK);

	// Предметы
	objectDropItems drop;
	drop.addItem(3, 6, idItem::logOakItem);
	drop.addItem(2, 4, idItem::seadlingOakItem);

	typesObject->drop.init(drop);
	drop.clear();
	////////////////////////////////////////////////////////////////////////////////////////
	typesObject = &typesUnlifeObjects[idUnlifeObject::oakSmall];

	texturePath = texturePaths[idTexturePaths::Trees];
	name = "Small oak";
	canDestroy = true;
	toughness = 2;

	typesObject->mainSize.init(0, 0, 0, 0);
	typesObject->Init(texturePath, name, canDestroy, toughness);

	typesObject->transparentSize.init(WIDTH_SMALL_OAK, HEIGHT_SMALL_OAK, PIXEL_X_SMALL_OAK, PIXEL_Y_SMALL_OAK);

	// Предметы
	drop.addItem(1, 3, idItem::logOakItem);
	drop.addItem(1, 2, idItem::seadlingOakItem);

	typesObject->drop.init(drop);
	////////////////////////////////////////////////////////////////////////////////////////
	// Саженец дуба
	typesObject = &typesUnlifeObjects[idUnlifeObject::oakSeadling];

	texturePath = texturePaths[idTexturePaths::Trees];
	name = "Seadling oak";
	canDestroy = true;
	toughness = 2;

	typesObject->mainSize.init(0, 0, 0, 0);
	typesObject->Init(texturePath, name, canDestroy, toughness);

	typesObject->transparentSize.init(WIDTH_SEADLING_OAK, HEIGHT_SEADLING_OAK, PIXEL_X_SEADLING_OAK, PIXEL_Y_SEADLING_OAK);

	// Предметы
	drop.addItem(1, 1, idItem::seadlingOakItem);

	typesObject->drop.init(drop);
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

	typesObject->drop.init(drop);
	////////////////////////////////////////////////////////////////////////////////////////
	// Пустой предмет
	typesObject = &typesUnlifeObjects[idUnlifeObject::empty];
	typesObject->Init(texturePaths[idTexturePaths::items], "Empty", false, 0);
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