#include "TypeUnlifeObject.h"
#include "Recourses.h"
#include "UnlifeObjectVar.h"
#include "ItemsVar.h"

using namespace sf;

void initializeTypeUnlifeObjects(TypesUnlifeObject &typesUnlifeObjects, dataSound &databaseSound) {
	typesUnlifeObjects.typeUnlifeObject = new TypeUnlifeObject[AMOUNT_TYPES_UNLIFE_OBJECT];

	////////////////////////////////////////////////////////////////////////////////////////
	// Дуб выросший
	TypeUnlifeObject *typesObject = &typesUnlifeObjects.typeUnlifeObject[idUnlifeObject::oakGrow];

	String texturePath = texturePaths[idTexturePaths::Trees];
	String name = "Oak";
	bool canDestroy = true;

	int toughness = 2;

	int width = WIDTH_OAK_STUMP;
	int height = HEIGHT_OAK_STUMP;
	int pixelX = PIXEL_X_OAK_STUMP;
	int pixelY = PIXEL_Y_OAK_STUMP;
	typesObject->Init(texturePath, name, canDestroy, toughness,
									 width, height, pixelX, pixelY);


	int widthTransparent = WIDTH_OAK;
	int heightTransparent = HEIGHT_OAK;
	int pixelXTransparent = PIXEL_X_OAK;
	int pixelYTransparent = PIXEL_Y_OAK;
	typesObject->InitTransparent(widthTransparent, heightTransparent, pixelXTransparent, pixelYTransparent);

	// Предметы
	int* minAmountForOak = new int[2];
	int* maxAmountForOak = new int[2];
	int* idItemsForOak = new int[2];

	minAmountForOak[0] = 3;
	minAmountForOak[1] = 1;
	maxAmountForOak[0] = 6;
	maxAmountForOak[1] = 3;
	idItemsForOak[0] = idItem::logOakItem;
	idItemsForOak[1] = idItem::seadlingOakItem;

	typesObject->InitItem(idItemsForOak, minAmountForOak, maxAmountForOak, 2);

	delete minAmountForOak;
	delete maxAmountForOak;
	delete idItemsForOak;
	//
	typesUnlifeObjects.countTypeObjects += 1;
	////////////////////////////////////////////////////////////////////////////////////////
	// Дуб маленький
	typesObject = &typesUnlifeObjects.typeUnlifeObject[idUnlifeObject::oakSmall];

	texturePath = texturePaths[idTexturePaths::Trees];
	name = "Small oak";
	canDestroy = true;
	toughness = 2;

	width = 0;// Его можно обойти
	height = 0;
	pixelX = 0;
	pixelY = 0;
	typesObject->Init(texturePath, name, canDestroy, toughness,
										width, height, pixelX, pixelY);

	widthTransparent = WIDTH_SMALL_OAK;
	heightTransparent = HEIGHT_SMALL_OAK;
	pixelXTransparent = PIXEL_X_SMALL_OAK;
	pixelYTransparent = PIXEL_Y_SMALL_OAK;
	typesObject->InitTransparent(widthTransparent, heightTransparent, pixelXTransparent, pixelYTransparent);

	// Предметы
	int* minAmountForSmallOak = new int[2];
	int* maxAmountForSmallOak = new int[2];
	int* idItemsForSmallOak = new int[2];

	minAmountForSmallOak[0] = 1;
	minAmountForSmallOak[1] = 1;
	maxAmountForSmallOak[0] = 2;
	maxAmountForSmallOak[1] = 2;
	idItemsForSmallOak[0] = idItem::logOakItem;
	idItemsForSmallOak[1] = idItem::seadlingOakItem;

	typesObject->InitItem(idItemsForSmallOak, minAmountForSmallOak, maxAmountForSmallOak, 2);

	delete minAmountForSmallOak;
	delete maxAmountForSmallOak;
	delete idItemsForSmallOak;
	//
	typesUnlifeObjects.countTypeObjects += 1;
	////////////////////////////////////////////////////////////////////////////////////////
	// Саженец дуба
	typesObject = &typesUnlifeObjects.typeUnlifeObject[idUnlifeObject::oakSeadling];

	texturePath = texturePaths[idTexturePaths::Trees];
	name = "Seadling oak";
	canDestroy = true;
	toughness = 2;

	width = 0;
	height = 0;
	pixelX = 0;
	pixelY = 0;
	typesObject->Init(texturePath, name, canDestroy, toughness,
										width, height, pixelX, pixelY);

	widthTransparent = WIDTH_SEADLING_OAK;
	heightTransparent = HEIGHT_SEADLING_OAK;
	pixelXTransparent = PIXEL_X_SEADLING_OAK;
	pixelYTransparent = PIXEL_Y_SEADLING_OAK;
	typesObject->InitTransparent(widthTransparent, heightTransparent, pixelXTransparent, pixelYTransparent);

	// Предметы
	int* minAmountForSeadlingOak = new int[1];
	int* maxAmountForSeadlingOak = new int[1];
	int* idItemsForSeadlingOak = new int[1];

	minAmountForSeadlingOak[0] = 1;
	maxAmountForSeadlingOak[0] = 1;
	idItemsForSeadlingOak[0] = idItem::seadlingOakItem;

	typesObject->InitItem(idItemsForSeadlingOak, minAmountForSeadlingOak, maxAmountForSeadlingOak, 1);

	delete minAmountForSeadlingOak;
	delete maxAmountForSeadlingOak;
	delete idItemsForSeadlingOak;
	//
	typesUnlifeObjects.countTypeObjects += 1;
	////////////////////////////////////////////////////////////////////////////////////////
	// Камень
	int* minAmountForSmallStone = new int[1];
	int* maxAmountForSmallStone = new int[1];
	int* idItemsForSmallStone = new int[1];

	*minAmountForSmallStone = { 1 };
	*maxAmountForSmallStone = { 1 };
	*idItemsForSmallStone = { idItem::stoneItem };


	typesObject = &typesUnlifeObjects.typeUnlifeObject[idUnlifeObject::smallStone];
	typesObject->Init(texturePaths[idTexturePaths::items], "SmallStone", false, 0,
										SIZE_ITEM, SIZE_ITEM, 
										PIXEL_X_SMALL_STONE, PIXEL_Y_SMALL_STONE);
	typesObject->InitItem(idItemsForSmallStone, minAmountForSmallStone, maxAmountForSmallStone, 1);
	typesUnlifeObjects.countTypeObjects += 1;

	delete minAmountForSmallStone;
	delete maxAmountForSmallStone;
	delete idItemsForSmallStone;
	////////////////////////////////////////////////////////////////////////////////////////
	// Пустой предмет
	typesObject = &typesUnlifeObjects.typeUnlifeObject[idUnlifeObject::empty];
	typesObject->Init(texturePaths[idTexturePaths::items], "Empty", false, 0, 0, 0, 0, 0);
	typesUnlifeObjects.countTypeObjects += 1;
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

void TypeUnlifeObject::InitTransparent(int width, int height, int pixelX, int pixelY) {
	// Задание размера
	widthTransparent = width;
	heightTransparent = height;

	pixelXTransparent = pixelX;
	pixelYTransparent = pixelY;

	printf("%d %d %d %d\n", width, height, pixelX, pixelY);
}
////////////////////////////////////////////////////////////////////