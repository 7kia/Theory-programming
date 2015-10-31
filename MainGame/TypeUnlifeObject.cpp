#include "TypeUnlifeObject.h"

using namespace sf;

void initializeTypeUnlifeObjects(TypesUnlifeObject *typesUnlifeObjects, dataSound &databaseSound) {
	typesUnlifeObjects->typeUnlifeObject = new TypeUnlifeObject[AMOUNT_TYPES_UNLIFE_OBJECT];

	////////////////////////////////////////////////////////////////////////////////////////
	// Дуб
	TypeUnlifeObject* typeObject = &typesUnlifeObjects->typeUnlifeObject[idUnlifeObject::oak];

	int* minAmountForOak = new int[1];
	int* maxAmountForOak = new int[1];
	int* idItemsForOak = new int[1];

	*minAmountForOak = { 3 };
	*maxAmountForOak = { 6 };
	*idItemsForOak = { idItem::logOakItem };

	typeObject->Init(texturePaths[idTexturePaths::Trees], "Oak", true, 2,  47, 30, 0, 208);
	typeObject->InitTransparent(136, 208, 0, 0);
	typeObject->InitItem(idItemsForOak, minAmountForOak, maxAmountForOak, 1);
	typesUnlifeObjects->countTypeObjects += 1;

	delete minAmountForOak;
	delete maxAmountForOak;
	delete idItemsForOak;
	////////////////////////////////////////////////////////////////////////////////////////
	// Камень
	int* minAmountForSmallStone = new int[1];
	int* maxAmountForSmallStone = new int[1];
	int* idItemsForSmallStone = new int[1];

	*minAmountForSmallStone = { 1 };
	*maxAmountForSmallStone = { 1 };
	*idItemsForSmallStone = { idItem::stoneItem };


	typeObject = &typesUnlifeObjects->typeUnlifeObject[idUnlifeObject::smallStone];
	typeObject->Init(texturePaths[idTexturePaths::items], "SmallStone", false, 0, SIZE_ITEM, SIZE_ITEM, PIXEL_X_SMALL_STONE, PIXEL_Y_SMALL_STONE);
	typeObject->InitItem(idItemsForSmallStone, minAmountForSmallStone, maxAmountForSmallStone, 1);
	typesUnlifeObjects->countTypeObjects += 1;

	delete minAmountForSmallStone;
	delete maxAmountForSmallStone;
	delete idItemsForSmallStone;
	////////////////////////////////////////////////////////////////////////////////////////
	// Пустой предмет
	typeObject = &typesUnlifeObjects->typeUnlifeObject[idUnlifeObject::empty];
	typeObject->Init(texturePaths[idTexturePaths::items], "Empty", false, 0, 0, 0, 0, 0);
	typesUnlifeObjects->countTypeObjects += 1;
}

////////////////////////////////////////////////////////////////////
// Виды объектов
void TypeUnlifeObject::Init(String filenameTexture, String typeName, bool canDestroy, int toughness, int w, int h, int pixelX, int pixelY) {
	textureObject = new Texture;

	name = typeName;

	// Задание размера
	height = h;
	width = w;

	pixelPosX = pixelX;
	pixelPosY = pixelY;


	// Разрушаемый или перетаскиваемый
	isDestroy = canDestroy;

	// Прочность 
	toughnessObject = toughness;

	// У разрушаемых предметов недолжно быть прочности
	if (isDestroy == false) {
		toughness = 0;
	}


	// Текстура
	textureObject->loadFromFile(filenameTexture);

	// Звуки 
	//mainPerson.soundsEntity[idSoundEntity::stepGrass] = &databaseSound.sounds[idSoundEntity::stepGrass];
	//mainPerson.soundsEntity[idSoundEntity::stepStone] = &databaseSound.sounds[idSoundEntity::stepStone];
};

void TypeUnlifeObject::InitItem(int* idItems, int* minAmountItems, int* maxAmountItems, int count)
{
	dropItems = new int[count];
	minCountItems = new int[count];
	maxCountItems = new int[count];

	for (size_t i = 0; i < count; i++) {
		dropItems[i] = idItems[i];
		minCountItems[i] = minAmountItems[i];
		maxCountItems[i] = maxAmountItems[i];
	}
	
}

void TypeUnlifeObject::InitTransparent(int w, int h, int pixelX, int pixelY) {
	// Задание размера
	heightTransparent = h;
	widthTransparent = w;

	pixelXTransparent = pixelX;
	pixelYTransparent = pixelY;
}
////////////////////////////////////////////////////////////////////