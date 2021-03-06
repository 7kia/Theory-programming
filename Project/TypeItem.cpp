#include "TypeItems.h"
#include "ItemsVar.h"
#include "UnlifeObjectVar.h"
#include "Recourses.h"
#include <iostream>


using namespace sf;
using namespace std;

void initializeTypesItem(TypeItem *typesItem, dataSound &databaseSound)
{

	////////////////////////////////////////////////v
	// ���������� ��� ����������� ������
	TypeItem addType;

	featuresItem featuresAddItem;
	sizeMainSprite sizeMain;
	idCreateObjects idCreated;
	typeDamageItem damage;

	int numberItem = idItem::stoneItem;

	String* pathTexture = new String;
	*pathTexture = texturePaths[idTexturePaths::items];

	featuresAddItem.init("Stone block", numberItem, idCategoryItem::block);
	featuresAddItem.defineToughness(false, 1);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_SMALL_STONE, PIXEL_Y_SMALL_STONE);

	damage.init(0, 10);

	idCreated.init(idBlocks::stone, idUnlifeObject::NONE_OBJECT);

	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);
	
	typesItem[numberItem] = addType;
	/////////////////////////////
	// �����
	numberItem = idItem::planksBlockItem;

	featuresAddItem.init("Planks", numberItem, idCategoryItem::block);
	featuresAddItem.defineToughness(false, 1);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_PLANKS, PIXEL_Y_PLANKS);

	damage.init(0, 5);

	idCreated.init(idBlocks::planksBlock, idUnlifeObject::NONE_OBJECT);

	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////
	// �����
	numberItem = idItem::dirtItem;

	featuresAddItem.init("Dirt block", numberItem, idCategoryItem::block);
	featuresAddItem.defineToughness(false, 1);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_DIRT, PIXEL_Y_DIRT);

	damage.init(0, 1);

	idCreated.init(idBlocks::planksBlock, idUnlifeObject::NONE_OBJECT);

	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////
	// ����� � ������
	numberItem = idItem::grassItem;

	featuresAddItem.init("Grass", numberItem, idCategoryItem::block);
	featuresAddItem.defineToughness(false, 1);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_GRASS_BRICK, PIXEL_Y_GRASS_BRICK);

	damage.init(0, 1);

	idCreated.init(idBlocks::grass, idUnlifeObject::NONE_OBJECT);

	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////
	// �����
	numberItem = idItem::sandItem;

	featuresAddItem.init("Sand block", numberItem, idCategoryItem::block);
	featuresAddItem.defineToughness(false, 1);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_SAND, PIXEL_Y_SAND);

	damage.init(0, 1);

	idCreated.init(idBlocks::sand, idUnlifeObject::NONE_OBJECT);

	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////
	// ���������� ��������
	numberItem = idItem::woodLadderItem;

	featuresAddItem.init("Wood ladder", numberItem, idCategoryItem::block);
	featuresAddItem.defineToughness(false, 1);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_WOOD_LADDER, PIXEL_Y_WOOD_LADDER);

	damage.init(0, 4);

	idCreated.init(idBlocks::woodLadder, idUnlifeObject::NONE_OBJECT);

	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////
	// �������� �������
	numberItem = idItem::stoneBrickItem;

	featuresAddItem.init("Stone brick", numberItem, idCategoryItem::block);
	featuresAddItem.defineToughness(false, 1);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_STONE_BRICK, PIXEL_Y_STONE_BRICK);

	damage.init(0, 10);

	idCreated.init(idBlocks::woodLadder, idUnlifeObject::NONE_OBJECT);

	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////
	// ������� ������
	numberItem = idItem::logOakItem;

	featuresAddItem.init("Log oak", numberItem, idCategoryItem::block);
	featuresAddItem.defineToughness(false, 1);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_LOG_OAK, PIXEL_Y_LOG_OAK);

	damage.init(1, 5);

	idCreated.init(idBlocks::logOak, idUnlifeObject::NONE_OBJECT);

	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////////////////////////////////
	// �������

	/////////////////////////////
	// ������� ����
	numberItem = idItem::seadlingOakItem;

	featuresAddItem.init("Seadling oak", numberItem, idCategoryItem::unlifeObject);
	featuresAddItem.defineToughness(false, 1);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_SEADLING_OAK_ITEM, PIXEL_Y_SEADLING_OAK_ITEM);

	damage.init(1, 1);

	idCreated.init(idBlocks::NONE_BLOCK, idUnlifeObject::oakSeadling);

	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////////////////////////////////
	// ������� � ������

	/////////////////////////////
	// ���������� �����
	numberItem = idItem::woodBukketItem;

	featuresAddItem.init("Wood bukket", numberItem, idCategoryItem::bukketEmpty);
	featuresAddItem.defineToughness(false, 1);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_WOOD_BUKKET, PIXEL_Y_WOOD_BUKKET);

	damage.init(0, 3);

	idCreated.init(idBlocks::water, idUnlifeObject::NONE_OBJECT);

	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////
	// ���������� ����� � �����
	numberItem = idItem::woodBukketWithWaterItem;

	featuresAddItem.init("Wood bukket with water", numberItem, idCategoryItem::bukketWithWater);
	featuresAddItem.defineToughness(false, 20);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_WOOD_BUKKET_WITH_WATER, PIXEL_Y_WOOD_BUKKET_WITH_WATER);

	damage.init(0, 4);

	idCreated.init(idBlocks::water, idUnlifeObject::NONE_OBJECT);

	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////
	// ���������� �������
	numberItem = idItem::glassBottleItem;

	featuresAddItem.init("Glass bottle", numberItem, idCategoryItem::bottleEmpty);
	featuresAddItem.defineToughness(false, 1);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_GLASS_BOTTLE, PIXEL_Y_GLASS_BOTTLE);

	damage.init(0, 2);

	idCreated.init(idBlocks::water, idUnlifeObject::NONE_OBJECT);

	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////
	// ���������� ������� � �����
	numberItem = idItem::glassbukketWithWater;

	featuresAddItem.init("Glass bottle with water", numberItem, idCategoryItem::bottleWithWater);
	featuresAddItem.defineToughness(false, 5);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_GLASS_BOTTLE_WITH_WATER, PIXEL_Y_GLASS_BOTTLE_WITH_WATER);

	damage.init(0, 2);

	idCreated.init(idBlocks::NONE_BLOCK, idUnlifeObject::NONE_OBJECT);

	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////////////////////////////////
	// ���

	/////////////////////////////////////
	// ����
	numberItem = idItem::mushroomItem;

	featuresAddItem.init("Mushroom", numberItem, idCategoryItem::food);
	featuresAddItem.defineToughness(false, 4);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_MUSHROOM, PIXEL_Y_MUSHROOM);

	damage.init(0, 1);

	idCreated.init(idBlocks::NONE_BLOCK, idUnlifeObject::NONE_OBJECT);

	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////////////
	// ���� �����
	numberItem = idItem::rawMeatWolfItem;

	featuresAddItem.init("Raw meat wolf", numberItem, idCategoryItem::other);
	featuresAddItem.defineToughness(false, 4);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_RAW_MEAT_WOLF, PIXEL_Y_RAW_MEAT_WOLF);

	damage.init(0, 1);

	idCreated.init(idBlocks::NONE_BLOCK, idUnlifeObject::NONE_OBJECT);

	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////////////
	// �������� ���� �����
	numberItem = idItem::roastMeatWolfItem;

	featuresAddItem.init("Roast meat wolf", numberItem, idCategoryItem::food);
	featuresAddItem.defineToughness(false, 10);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_ROAST_MEAT_WOLF, PIXEL_Y_ROAST_MEAT_WOLF);

	damage.init(0, 1);

	idCreated.init(idBlocks::NONE_BLOCK, idUnlifeObject::NONE_OBJECT);

	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////////////
	// ������
	numberItem = idItem::appleItem;

	featuresAddItem.init("Apple", numberItem, idCategoryItem::food);
	featuresAddItem.defineToughness(false, 4);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_APPLE, PIXEL_Y_APPLE);

	damage.init(0, 1);

	idCreated.init(idBlocks::NONE_BLOCK, idUnlifeObject::NONE_OBJECT);

	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////////////////////////////////
	// ����

	/////////////////////////////
	// �������� ���
	numberItem = idItem::stoneKnifeItem;

	featuresAddItem.init("Stone knife", numberItem, idCategoryItem::weapon);
	featuresAddItem.defineToughness(true, 128);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_STONE_KNIFE, PIXEL_Y_STONE_KNIFE);

	damage.init(18, 1);

	idCreated.init(idBlocks::NONE_BLOCK, idUnlifeObject::NONE_OBJECT);

	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////////////////////////////////
	// ������

	/////////////////////////////
	// ���������� ������
	numberItem = idItem::woodClubItem;

	featuresAddItem.init("Wood club", numberItem, idCategoryItem::weapon);
	featuresAddItem.defineToughness(true, 128);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_WOOD_CLUB, PIXEL_Y_WOOD_CLUB);

	damage.init(0, 18);

	idCreated.init(idBlocks::NONE_BLOCK, idUnlifeObject::NONE_OBJECT);

	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////////////////////////////////
	// ������

	/////////////////////////////
	// �������� ������
	numberItem = idItem::ironBackHoerIte;

	featuresAddItem.init("Iron backhoe", numberItem, idCategoryItem::backhoe);
	featuresAddItem.defineToughness(true, 512);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_IRON_BACKHOE, PIXEL_Y_IRON_BACKHOE);

	damage.init(1, 10);

	idCreated.init(idBlocks::air, idUnlifeObject::NONE_OBJECT);

	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////////////////////////////////
	// �����

	/////////////////////////////
	// �������� �����
	numberItem = idItem::stonePickaxItem;

	featuresAddItem.init("Stone pickax", numberItem, idCategoryItem::pickax);
	featuresAddItem.defineToughness(true, 128);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_IRON_BACKHOE, PIXEL_Y_IRON_BACKHOE);

	damage.init(10, 6);

	idCreated.init(idBlocks::air, idUnlifeObject::NONE_OBJECT);

	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////////////////////////////////
	// ������

	/////////////////////////////
	// �������� �����
	numberItem = idItem::stoneAxeItem;

	featuresAddItem.init("Stone axe", numberItem, idCategoryItem::axe);
	featuresAddItem.defineToughness(true, 128);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_STONE_AXE, PIXEL_Y_STONE_AXE);

	damage.init(8, 8);

	idCreated.init(idBlocks::air, idUnlifeObject::NONE_OBJECT);

	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////////////////////////////////
	// ���������� ��������
	/////////////////////////////
	// ������ �������( ����� ��� ������ � ���������
	numberItem = idItem::emptyItem;

	featuresAddItem.init("Empty", numberItem, idCategoryItem::other);
	featuresAddItem.defineToughness(false, 1);

	sizeMain.init(0, 0, 0, 0);

	damage.init(0, 1);

	idCreated.init(idBlocks::NONE_BLOCK, idUnlifeObject::NONE_OBJECT);

	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////
	delete pathTexture;
}

void sizeMainSprite::init(int w, int h, int xPixPos, int yPixPos)
{
	width = w;
	height = h;
	pixelPosX = xPixPos;
	pixelPosY = yPixPos;
}

void sizeAlternativeSprite::init(int w, int h, int xPixPos, int yPixPos)
{
	widthForUse = w;
	heightForUse = h;
	pixelXForUse = xPixPos;
	pixelYForUse = yPixPos;
}

void typeDamageItem::init(int cut, int crush)
{
	cuttingDamage = cut;
	crushingDamage = crush;
}

void idCreateObjects::init(int idBlock, int idObject)
{
	idBlockForUse = idBlock;
	idUnlideOnjectForUse = idObject;
}

void featuresItem::init(String nameItem, int idItem, int idCategory)
{
	name = nameItem;
	id = idItem;
	category = idCategory;

}

void featuresItem::defineToughness(bool destroy, int toughnessItem)
{
	isDestroy = destroy;
	toughness = toughnessItem;
}
////////////////////////////////////////////////////////////////////
// ���� ��������
void TypeItem::Init(String filenameTexture, featuresItem featuresAddItem,
										sizeMainSprite sizeMainSprite, idCreateObjects idCreated, typeDamageItem damage)
{
	textureItem = new Texture;
	if (textureItem->loadFromFile(filenameTexture))
	{
		std::cout << string(filenameTexture) << std::endl;
	}
	else
	{
		std::cout << "error " << string(filenameTexture) << std::endl;
	}

	sizeMain.height = sizeMainSprite.height;
	sizeMain.width = sizeMainSprite.width;
	sizeMain.pixelPosX = sizeMainSprite.pixelPosX;
	sizeMain.pixelPosY = sizeMainSprite.pixelPosY;

	features.isDestroy = featuresAddItem.isDestroy;
	features.category = featuresAddItem.category;
	features.toughness = featuresAddItem.toughness;
	features.name = featuresAddItem.name;
	features.id = featuresAddItem.id;

	damageItem.cuttingDamage = damage.cuttingDamage;// �������
	damageItem.crushingDamage = damage.crushingDamage;// ��������

	switch (features.category) {
	case idCategoryItem::block:
	case idCategoryItem::bukketEmpty:
	case idCategoryItem::bottleEmpty:
	case idCategoryItem::bottleWithWater:
	case idCategoryItem::bukketWithWater:
		idAdd.idBlockForUse = idCreated.idBlockForUse;
		idAdd.idUnlideOnjectForUse = -1;
		break;
	case idCategoryItem::unlifeObject:
		idAdd.idUnlideOnjectForUse = idCreated.idUnlideOnjectForUse;
		idAdd.idBlockForUse = -1;
	default:
		break;
	}

	// ����� 
	//mainPerson.soundsEntity[idSoundEntity::stepGrass] = &databaseSound.sounds[idSoundEntity::stepGrass];// �������
	//mainPerson.soundsEntity[idSoundEntity::stepStone] = &databaseSound.sounds[idSoundEntity::stepStone];
};

void TypeItem::InitForUse(String filenameTextureForUse, sizeAlternativeSprite size)
{
	textureItemForUse = new Texture;
	textureItemForUse->loadFromFile(filenameTextureForUse);
	// ������� �������
	sizeAlternative.heightForUse = size.heightForUse;
	sizeAlternative.widthForUse = size.widthForUse;

	sizeAlternative.pixelXForUse = size.pixelXForUse;
	sizeAlternative.pixelYForUse = size.pixelYForUse;
}
////////////////////////////////////////////////////////////////////