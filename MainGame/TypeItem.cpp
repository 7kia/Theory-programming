#include "TypeItems.h"

using namespace sf;

void initializeTypesItem(TypesItem &typesItem, dataSound &databaseSound)
{
	typesItem.typesItem = new TypeItem[AMOUNT_TYPES_ITEM];

	////////////////////////////////////////////////v
	// ���������� ��� ����������� ������
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
	////////////////////////////////////////////////

	/////////////////////////////////////
	// ������
	typesItem.typesItem[numberItem].Init(*pathTexture, *nameItem, categoryItem, canDestroy, toughness, SIZE_ITEM, SIZE_ITEM, pixelX, pixelY, idBlocks::stone, 0);
	typesItem.countTypeItem += 1;
	/////////////////////////////////////
	// ����
	numberItem = idItem::mushroom;
	*nameItem = "Mushroom";

	categoryItem = idCategoryItem::food;

	canDestroy = true;

	toughness = 4;

	pixelX = PIXEL_X_MUSHROOM;
	pixelY = PIXEL_Y_MUSHROOM;

	typesItem.typesItem[numberItem].Init(*pathTexture, *nameItem, categoryItem, canDestroy, toughness, SIZE_ITEM, SIZE_ITEM, pixelX, pixelY, 0, 0);
	typesItem.countTypeItem += 1;
	/////////////////////////////
	// �����
	numberItem = idItem::planksBlockItem;
	*nameItem = "Planks";

	categoryItem = idCategoryItem::block;

	canDestroy = false;

	toughness = 0;


	pixelX = PIXEL_X_PLANKS;
	pixelY = PIXEL_Y_PLANKS;

	typesItem.typesItem[numberItem].Init(*pathTexture, *nameItem, categoryItem, canDestroy, toughness, SIZE_ITEM, SIZE_ITEM, pixelX, pixelY, idBlocks::planksBlock, 0);
	typesItem.countTypeItem += 1;
	/////////////////////////////
	// �����
	numberItem = idItem::dirtItem;
	*nameItem = "Dirt block";

	categoryItem = idCategoryItem::block;

	canDestroy = false;

	toughness = 0;


	pixelX = PIXEL_X_DIRT;
	pixelY = PIXEL_Y_DIRT;

	typesItem.typesItem[numberItem].Init(*pathTexture, *nameItem, categoryItem, canDestroy, toughness, SIZE_ITEM, SIZE_ITEM, pixelX, pixelY, idBlocks::dirt, 0);
	typesItem.countTypeItem += 1;
	/////////////////////////////
	// ����� � ������
	numberItem = idItem::grassItem;
	*nameItem = "Grass brick";

	categoryItem = idCategoryItem::block;

	canDestroy = false;

	toughness = 0;

	pixelX = PIXEL_X_GRASS_BRICK;
	pixelY = PIXEL_Y_GRASS_BRICK;

	typesItem.typesItem[numberItem].Init(*pathTexture, *nameItem, categoryItem, canDestroy, toughness, SIZE_ITEM, SIZE_ITEM, pixelX, pixelY, idBlocks::grass, 0);
	typesItem.countTypeItem += 1;
	/////////////////////////////
	// �����
	numberItem = idItem::sandItem;
	*nameItem = "Sand block";

	categoryItem = idCategoryItem::block;

	canDestroy = false;

	toughness = 0;


	pixelX = PIXEL_X_SAND;
	pixelY = PIXEL_Y_SAND;

	typesItem.typesItem[numberItem].Init(*pathTexture, *nameItem, categoryItem, canDestroy, toughness, SIZE_ITEM, SIZE_ITEM, pixelX, pixelY, idBlocks::sand, 0);
	typesItem.countTypeItem += 1;
	/////////////////////////////
	// ���������� ��������
	numberItem = idItem::woodLadderItem;
	*nameItem = "logOak ladder";

	categoryItem = idCategoryItem::block;

	canDestroy = false;

	toughness = 0;


	pixelX = PIXEL_X_WOOD_LADDER;
	pixelY = PIXEL_Y_WOOD_LADDER;

	typesItem.typesItem[numberItem].Init(*pathTexture, *nameItem, categoryItem, canDestroy, toughness, SIZE_ITEM, SIZE_ITEM, pixelX, pixelY, idBlocks::woodLadder, 0);
	typesItem.countTypeItem += 1;
	/////////////////////////////
	// �������� �������
	numberItem = idItem::stoneBrickItem;
	*nameItem = "Stone brick";

	categoryItem = idCategoryItem::block;

	canDestroy = false;

	toughness = 0;

	pixelX = PIXEL_X_STONE_BRICK;
	pixelY = PIXEL_Y_STONE_BRICK;

	typesItem.typesItem[numberItem].Init(*pathTexture, *nameItem, categoryItem, canDestroy, toughness, SIZE_ITEM, SIZE_ITEM, pixelX, pixelY, idBlocks::stoneBrick, 0);
	typesItem.countTypeItem += 1;
	/////////////////////////////
	// ������� ������
	numberItem = idItem::logOakItem;
	*nameItem = "Log oak";

	categoryItem = idCategoryItem::other;

	canDestroy = false;

	toughness = 0;

	pixelX = PIXEL_X_LOG_OAK;
	pixelY = PIXEL_Y_LOG_OAK;

	typesItem.typesItem[numberItem].Init(*pathTexture, *nameItem, categoryItem, canDestroy, toughness, SIZE_ITEM, SIZE_ITEM, pixelX, pixelY, 0, 0);// �������
	typesItem.countTypeItem += 1;
	/////////////////////////////
	// ������ �������( ����� ��� ������ � ���������
	numberItem = idItem::emptyItem;
	*nameItem = "Empty";

	categoryItem = idCategoryItem::other;

	canDestroy = false;

	toughness = 0;

	int width = 0;
	int height = 0;
	pixelX = 0;
	pixelY = 0;

	typesItem.typesItem[numberItem].Init(*pathTexture, *nameItem, categoryItem, canDestroy, toughness, width, height, pixelX, pixelY, 0, 0);
	typesItem.countTypeItem += 1;
	/////////////////////////////
	delete pathTexture;
}

////////////////////////////////////////////////////////////////////
// ���� ��������
void TypeItem::Init(String filenameTexture, String typeName, int idCategory, bool canDestroy, int toughness, int w, int h, int pixelX, int pixelY, int idBlock, int idUnlifeObject)
{
	textureItem = new Texture;

	name = typeName;

	// ������� �������
	height = h;
	width = w;

	pixelPosX = pixelX;
	pixelPosY = pixelY;

	// ����������� ��� ���������������
	isDestroy = canDestroy;

	// ���������
	category = idCategory;

	// ��������� 
	toughnessObject = toughness;

	// � ����������� ��������� �������� ���� ���������
	if (isDestroy == false) {
		toughness = 0;
	}

	switch (idCategory) {
	case idCategoryItem::block:
		idBlockForUse = idBlock;
		break;

	default:
		break;
	}

	// ��������
	textureItem->loadFromFile(filenameTexture);

	// ����� 
	//mainPerson.soundsEntity[idSoundEntity::stepGrass] = &databaseSound.sounds[idSoundEntity::stepGrass];// �������
	//mainPerson.soundsEntity[idSoundEntity::stepStone] = &databaseSound.sounds[idSoundEntity::stepStone];
};

void TypeItem::InitForUse(String filenameTextureForUse, int w, int h, int pixelX, int pixelY)
{
	textureItemForUse = new Texture;

	// ������� �������
	heightUse = h;
	widthForUse = w;

	pixelXUse = pixelX;
	pixelYUse = pixelY;
}
////////////////////////////////////////////////////////////////////