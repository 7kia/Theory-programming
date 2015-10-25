#include "TypeItems.h"

using namespace sf;

void initializeTypesItem(TypesItem &typesItem, dataSound &databaseSound)
{
	typesItem.typesItem = new TypeItem[AMOUNT_TYPES_ITEM];

	////////////////////////////////////////////////v
	// Переменные для записывания данных
	int numberItem = idItem::stoneItem;

	String* pathTexture = new String;
	*pathTexture =	texturePaths[idTexturePaths::items];

	String* nameItem = new String;
	*nameItem = "Stone block";

	int categoryItem = idCategoryItem::block;

	bool canDestroy = false;

	int toughness = 0;

	int pixelX = PIXEL_X_SMALL_STONE;
	int pixelY = PIXEL_Y_SMALL_STONE;

	int cuttingDamage = 0;
	int crushingDamage = 1;

	int block = idBlocks::stone;
	int unlifeObject = 0;//idUnlifeObject::
	////////////////////////////////////////////////

	/////////////////////////////////////
	// Камень
	typesItem.typesItem[numberItem].Init(*pathTexture, *nameItem, numberItem, categoryItem, canDestroy, toughness, SIZE_ITEM, SIZE_ITEM, pixelX, pixelY, block, unlifeObject, cuttingDamage, crushingDamage);
	typesItem.countTypeItem += 1;
	/////////////////////////////////////
	// Гриб
	numberItem = idItem::mushroomItem;
	*nameItem = "Mushroom";

	categoryItem = idCategoryItem::food;

	canDestroy = true;

	toughness = 4;

	pixelX = PIXEL_X_MUSHROOM;
	pixelY = PIXEL_Y_MUSHROOM;

	cuttingDamage = 0;
	crushingDamage = 1;

	block = 0;
	unlifeObject = 0;

	typesItem.typesItem[numberItem].Init(*pathTexture, *nameItem, numberItem, categoryItem, canDestroy, toughness, SIZE_ITEM, SIZE_ITEM, pixelX, pixelY, block, unlifeObject, cuttingDamage, crushingDamage);
	typesItem.countTypeItem += 1;
	/////////////////////////////
	// Доски
	numberItem = idItem::planksBlockItem;
	*nameItem = "Planks";

	categoryItem = idCategoryItem::block;

	canDestroy = false;

	toughness = 0;

	pixelX = PIXEL_X_PLANKS;
	pixelY = PIXEL_Y_PLANKS;

	cuttingDamage = 0;
	crushingDamage = 1;

	block = idBlocks::planksBlock;
	unlifeObject = 0;

	typesItem.typesItem[numberItem].Init(*pathTexture, *nameItem, numberItem, categoryItem, canDestroy, toughness, SIZE_ITEM, SIZE_ITEM, pixelX, pixelY, block, unlifeObject, cuttingDamage, crushingDamage);
	typesItem.countTypeItem += 1;
	/////////////////////////////
	// Земля
	numberItem = idItem::dirtItem;
	*nameItem = "Dirt block";

	categoryItem = idCategoryItem::block;

	canDestroy = false;

	toughness = 0;

	pixelX = PIXEL_X_DIRT;
	pixelY = PIXEL_Y_DIRT;

	cuttingDamage = 0;
	crushingDamage = 1;

	block = idBlocks::dirt;
	unlifeObject = 0;

	typesItem.typesItem[numberItem].Init(*pathTexture, *nameItem, numberItem, categoryItem, canDestroy, toughness, SIZE_ITEM, SIZE_ITEM, pixelX, pixelY, block, unlifeObject, cuttingDamage, crushingDamage);
	typesItem.countTypeItem += 1;
	/////////////////////////////
	// Земля с травой
	numberItem = idItem::grassItem;
	*nameItem = "Grass brick";

	categoryItem = idCategoryItem::block;

	canDestroy = false;

	toughness = 0;

	pixelX = PIXEL_X_GRASS_BRICK;
	pixelY = PIXEL_Y_GRASS_BRICK;

	cuttingDamage = 0;
	crushingDamage = 1;

	block = idBlocks::grass;
	unlifeObject = 0;

	typesItem.typesItem[numberItem].Init(*pathTexture, *nameItem, numberItem, categoryItem, canDestroy, toughness, SIZE_ITEM, SIZE_ITEM, pixelX, pixelY, block, unlifeObject, cuttingDamage, crushingDamage);
	typesItem.countTypeItem += 1;
	/////////////////////////////
	// Песок
	numberItem = idItem::sandItem;
	*nameItem = "Sand block";

	categoryItem = idCategoryItem::block;

	canDestroy = false;

	toughness = 0;

	pixelX = PIXEL_X_SAND;
	pixelY = PIXEL_Y_SAND;

	cuttingDamage = 0;
	crushingDamage = 1;

	block = idBlocks::sand;
	unlifeObject = 0;

	typesItem.typesItem[numberItem].Init(*pathTexture, *nameItem, numberItem, categoryItem, canDestroy, toughness, SIZE_ITEM, SIZE_ITEM, pixelX, pixelY, block, unlifeObject, cuttingDamage, crushingDamage);
	typesItem.countTypeItem += 1;
	/////////////////////////////
	// Деревянная лестница
	numberItem = idItem::woodLadderItem;
	*nameItem = "Wood ladder";

	categoryItem = idCategoryItem::block;

	canDestroy = false;

	toughness = 0;

	pixelX = PIXEL_X_WOOD_LADDER;
	pixelY = PIXEL_Y_WOOD_LADDER;

	cuttingDamage = 0;
	crushingDamage = 1;

	block = idBlocks::woodLadder;
	unlifeObject = 0;

	typesItem.typesItem[numberItem].Init(*pathTexture, *nameItem, numberItem, categoryItem, canDestroy, toughness, SIZE_ITEM, SIZE_ITEM, pixelX, pixelY, block, unlifeObject, cuttingDamage, crushingDamage);
	typesItem.countTypeItem += 1;
	/////////////////////////////
	// Каменные кирпичи
	numberItem = idItem::stoneBrickItem;
	*nameItem = "Stone brick";

	categoryItem = idCategoryItem::block;

	canDestroy = false;

	toughness = 0;

	pixelX = PIXEL_X_STONE_BRICK;
	pixelY = PIXEL_Y_STONE_BRICK;

	cuttingDamage = 0;
	crushingDamage = 1;

	block = idBlocks::stoneBrick;
	unlifeObject = 0;

	typesItem.typesItem[numberItem].Init(*pathTexture, *nameItem, numberItem, categoryItem, canDestroy, toughness, SIZE_ITEM, SIZE_ITEM, pixelX, pixelY, block, unlifeObject, cuttingDamage, crushingDamage);
	typesItem.countTypeItem += 1;
	/////////////////////////////
	// Дубовое бревно
	numberItem = idItem::logOakItem;
	*nameItem = "Log oak";

	categoryItem = idCategoryItem::block;

	canDestroy = false;

	toughness = 0;

	pixelX = PIXEL_X_LOG_OAK;
	pixelY = PIXEL_Y_LOG_OAK;
	
	cuttingDamage = 0;
	crushingDamage = 1;

	block = idBlocks::logOak;
	unlifeObject = 0;

	typesItem.typesItem[numberItem].Init(*pathTexture, *nameItem, numberItem, categoryItem, canDestroy, toughness, SIZE_ITEM, SIZE_ITEM, pixelX, pixelY, block, unlifeObject, cuttingDamage, crushingDamage);
	typesItem.countTypeItem += 1;
	/////////////////////////////////////////////////////////
	// Напитки


	/////////////////////////////
	// Деревянное ведро
	numberItem = idItem::woodBukketItem;
	*nameItem = "Wood bukket";

	categoryItem = idCategoryItem::bukketEmpty;

	canDestroy = false;

	toughness = 0;

	pixelX = PIXEL_X_WOOD_BUKKET;
	pixelY = PIXEL_Y_WOOD_BUKKET;

	cuttingDamage = 0;
	crushingDamage = 1;

	block = idBlocks::water;
	unlifeObject = 0;

	typesItem.typesItem[numberItem].Init(*pathTexture, *nameItem, numberItem, categoryItem, canDestroy, toughness, SIZE_ITEM, SIZE_ITEM, pixelX, pixelY, block, unlifeObject, cuttingDamage, crushingDamage);
	typesItem.countTypeItem += 1;
	/////////////////////////////
	// Деревянное ведро
	numberItem = idItem::woodBukketWithWaterItem;
	*nameItem = "Wood bukket with water";

	categoryItem = idCategoryItem::bukketWithWater;

	canDestroy = true;

	toughness = 20;

	pixelX = PIXEL_X_WOOD_BUKKET_WITH_WATER;
	pixelY = PIXEL_Y_WOOD_BUKKET_WITH_WATER;

	cuttingDamage = 0;
	crushingDamage = 1;

	block = idBlocks::water;
	unlifeObject = 0;

	typesItem.typesItem[numberItem].Init(*pathTexture, *nameItem, numberItem, categoryItem, canDestroy, toughness, SIZE_ITEM, SIZE_ITEM, pixelX, pixelY, block, unlifeObject, cuttingDamage, crushingDamage);
	typesItem.countTypeItem += 1;
	/////////////////////////////
	// Стеклянная бытылка
	numberItem = idItem::glassBottleItem;
	*nameItem = "Glass bottle";

	categoryItem = idCategoryItem::bottleEmpty;

	canDestroy = false;

	toughness = 0;

	pixelX = PIXEL_X_GLASS_BOTTLE;
	pixelY = PIXEL_Y_GLASS_BOTTLE;

	cuttingDamage = 0;
	crushingDamage = 1;

	block = idBlocks::water;
	unlifeObject = 0;

	typesItem.typesItem[numberItem].Init(*pathTexture, *nameItem, numberItem, categoryItem, canDestroy, toughness, SIZE_ITEM, SIZE_ITEM, pixelX, pixelY, block, unlifeObject, cuttingDamage, crushingDamage);
	typesItem.countTypeItem += 1;
	/////////////////////////////
	// Стеклянная бытылка с водой
	numberItem = idItem::glassbukketWithWater;
	*nameItem = "Glass bottle with water";

	categoryItem = idCategoryItem::bottleWithWater;

	canDestroy = true;

	toughness = 5;

	pixelX = PIXEL_X_GLASS_BOTTLE_WITH_WATER;
	pixelY = PIXEL_Y_GLASS_BOTTLE_WITH_WATER;

	cuttingDamage = 0;
	crushingDamage = 1;

	block = 0;
	unlifeObject = 0;

	typesItem.typesItem[numberItem].Init(*pathTexture, *nameItem, numberItem, categoryItem, canDestroy, toughness, SIZE_ITEM, SIZE_ITEM, pixelX, pixelY, block, unlifeObject, cuttingDamage, crushingDamage);
	typesItem.countTypeItem += 1;
	/////////////////////////////////////////////////////////
	// Мечи

	/////////////////////////////
	// Каменный нож
	numberItem = idItem::stoneKnifeItem;
	*nameItem = "Stone knife";

	categoryItem = idCategoryItem::weapon;

	canDestroy = true;

	toughness = 5;

	pixelX = PIXEL_X_STONE_KNIFE;
	pixelY = PIXEL_Y_STONE_KNIFE;

	cuttingDamage = 18;
	crushingDamage = 0;

	block = 0;
	unlifeObject = 0;

	typesItem.typesItem[numberItem].Init(*pathTexture, *nameItem, numberItem, categoryItem, canDestroy, toughness, SIZE_ITEM, SIZE_ITEM, pixelX, pixelY, block, unlifeObject, cuttingDamage, crushingDamage);
	typesItem.countTypeItem += 1;
	/////////////////////////////////////////////////////////
	// Дубины

	/////////////////////////////
	// Деревянная дубина
	numberItem = idItem::woodClubItem;
	*nameItem = "Wood club";

	categoryItem = idCategoryItem::weapon;

	canDestroy = true;

	toughness = 5;

	pixelX = PIXEL_X_WOOD_CLUB;
	pixelY = PIXEL_Y_WOOD_CLUB;

	cuttingDamage = 0;
	crushingDamage = 18;

	block = 0;
	unlifeObject = 0;

	typesItem.typesItem[numberItem].Init(*pathTexture, *nameItem, numberItem, categoryItem, canDestroy, toughness, SIZE_ITEM, SIZE_ITEM, pixelX, pixelY, block, unlifeObject, cuttingDamage, crushingDamage);
	typesItem.countTypeItem += 1;
	/////////////////////////////////////////////////////////
	// Кирки

	/////////////////////////////
	// Каменная кирка
	numberItem = idItem::stonePickaxItem;
	*nameItem = "Stone pickax";

	categoryItem = idCategoryItem::pickax;

	canDestroy = true;

	toughness = 5;

	pixelX = PIXEL_X_STONE_PICKAX;
	pixelY = PIXEL_Y_STONE_PICKAX;

	cuttingDamage = 10;
	crushingDamage = 6;

	block = idBlocks::air;
	unlifeObject = 0;

	typesItem.typesItem[numberItem].Init(*pathTexture, *nameItem, numberItem, categoryItem, canDestroy, toughness, SIZE_ITEM, SIZE_ITEM, pixelX, pixelY, block, unlifeObject, cuttingDamage, crushingDamage);
	typesItem.countTypeItem += 1;
	/////////////////////////////////////////////////////////
	// Топоры

	/////////////////////////////
	// Каменный топор
	numberItem = idItem::stoneAxeItem;
	*nameItem = "Stone axe";

	categoryItem = idCategoryItem::axe;

	canDestroy = true;

	toughness = 5;

	pixelX = PIXEL_X_STONE_AXE;
	pixelY = PIXEL_Y_STONE_AXE;

	cuttingDamage = 8;
	crushingDamage = 8;

	block = idBlocks::air;
	unlifeObject = 0;

	typesItem.typesItem[numberItem].Init(*pathTexture, *nameItem, numberItem, categoryItem, canDestroy, toughness, SIZE_ITEM, SIZE_ITEM, pixelX, pixelY, block, unlifeObject, cuttingDamage, crushingDamage);
	typesItem.countTypeItem += 1;
	/////////////////////////////////////////////////////////
	// ДОБАВЛЕНИЕ ПРЕДМЕТА
	/////////////////////////////
	// Пустой предмет( нужен для работы с инвентарём
	numberItem = idItem::emptyItem;
	*nameItem = "Empty";

	categoryItem = idCategoryItem::other;

	canDestroy = false;

	toughness = 0;

	int width = 0;
	int height = 0;

	pixelX = 0;
	pixelY = 0;

	cuttingDamage = 0;
	crushingDamage = 0;

	block = 0;
	unlifeObject = 0;

	typesItem.typesItem[numberItem].Init(*pathTexture, *nameItem, numberItem, categoryItem, canDestroy, toughness, SIZE_ITEM, SIZE_ITEM, pixelX, pixelY, block, unlifeObject, cuttingDamage, crushingDamage);
	typesItem.countTypeItem += 1;
	/////////////////////////////
	delete pathTexture;
}

////////////////////////////////////////////////////////////////////
// Виды объектов
void TypeItem::Init(String filenameTexture, String typeName, int id, int idCategory, bool canDestroy, int toughness, int w, int h, int pixelX, int pixelY, int idBlock, int idUnlifeObject, int damCut, int damCrash)
{
	textureItem = new Texture;

	name = typeName;
	idItem = id;

	// Задание размера
	height = h;
	width = w;

	pixelPosX = pixelX;
	pixelPosY = pixelY;

	// Разрушаемый или перетаскиваемый
	isDestroy = canDestroy;

	// Категория
	category = idCategory;

	// Урон
	cuttingDamage = damCut;// Режущий
	crushingDamage = damCrash;// Дробящий

	// Прочность 
	toughnessObject = toughness;

	// У разрушаемых предметов недолжно быть прочности
	if (isDestroy == false) {
		toughness = 0;
	}

	switch (idCategory) {
	case idCategoryItem::block:
	case idCategoryItem::bukketEmpty:
	case idCategoryItem::bottleEmpty:
	case idCategoryItem::bottleWithWater:
	case idCategoryItem::bukketWithWater:
		idBlockForUse = idBlock;
		break;
	default:
		break;
	}

	// Текстура
	textureItem->loadFromFile(filenameTexture);

	// Звуки 
	//mainPerson.soundsEntity[idSoundEntity::stepGrass] = &databaseSound.sounds[idSoundEntity::stepGrass];// ИСПРАВЬ
	//mainPerson.soundsEntity[idSoundEntity::stepStone] = &databaseSound.sounds[idSoundEntity::stepStone];
};

void TypeItem::InitForUse(String filenameTextureForUse, int w, int h, int pixelX, int pixelY)
{
	textureItemForUse = new Texture;

	// Задание размера
	heightUse = h;
	widthForUse = w;

	pixelXUse = pixelX;
	pixelYUse = pixelY;
}
////////////////////////////////////////////////////////////////////