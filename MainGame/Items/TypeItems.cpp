#include <iostream>
#include "../UnlifeObject/UnlifeObjectVar.h"
#include "../Recourses.h"

#include "TypeItems.h"
#include "ItemsVar.h"

using namespace sf;
using namespace std;

void initializeTypesItem(TypeItem *typesItem, listDestroyObjectsAndBlocks &list)
{
	initStoneBlock(typesItem, list);
	initWoodBlock(typesItem, list);
	initSeadling(typesItem, list);
	initGroundBlock(typesItem, list);
	initWeapon(typesItem, list);
	initTools(typesItem, list);
	initFoods(typesItem, list);
	initHaveWater(typesItem, list);
	initEmptyItem(typesItem, list);
}

void initStoneBlock(TypeItem* typesItem, listDestroyObjectsAndBlocks& list)
{
	TypeItem addType;

	featuresItem featuresAddItem;
	featuresSprite sizeMain;
	idCreateObjects idCreated;
	typeDamageItem damage;

	int numberItem = idItem::stoneItem;

	String* pathTexture = new String;
	*pathTexture = texturePaths[idTexturePaths::items];

	featuresAddItem.init("Stone block", numberItem, idCategoryItem::block, false);
	featuresAddItem.defineToughness(false, 1);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_SMALL_STONE, PIXEL_Y_SMALL_STONE);

	damage.init(0, 10, 0);

	idCreated.init(idBlocks::stone, idUnlifeObject::NONE_OBJECT);

	addType.maxAmount = 4;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////
	// Каменные кирпичи
	numberItem = idItem::stoneBrickItem;

	featuresAddItem.init("Stone brick", numberItem, idCategoryItem::block, false);
	featuresAddItem.defineToughness(false, 1);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_STONE_BRICK, PIXEL_Y_STONE_BRICK);

	damage.init(0, 10, 0);

	idCreated.init(idBlocks::stoneBrick, idUnlifeObject::NONE_OBJECT);

	addType.maxAmount = 4;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;

	delete pathTexture;
}

void initWoodBlock(TypeItem* typesItem, listDestroyObjectsAndBlocks& list)
{
	TypeItem addType;

	featuresItem featuresAddItem;
	featuresSprite sizeMain;
	idCreateObjects idCreated;
	typeDamageItem damage;

	String* pathTexture = new String;
	*pathTexture = texturePaths[idTexturePaths::items];

	int numberItem = idItem::planksBlockItem;

	featuresAddItem.init("Planks", numberItem, idCategoryItem::block, false);
	featuresAddItem.defineToughness(false, 1);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_PLANKS, PIXEL_Y_PLANKS);

	damage.init(0, 5, 0);

	idCreated.init(idBlocks::planksBlock, idUnlifeObject::NONE_OBJECT);

	addType.maxAmount = 4;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////
	// Деревянная лестница
	numberItem = idItem::woodLadderItem;

	featuresAddItem.init("Wood ladder", numberItem, idCategoryItem::block, false);
	featuresAddItem.defineToughness(false, 1);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_WOOD_LADDER, PIXEL_Y_WOOD_LADDER);

	damage.init(0, 4, 0);

	idCreated.init(idBlocks::woodLadder, idUnlifeObject::NONE_OBJECT);

	addType.maxAmount = 4;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////
	// Дубовое бревно
	numberItem = idItem::logOakItem;

	featuresAddItem.init("Log", numberItem, idCategoryItem::block, false);
	featuresAddItem.defineToughness(false, 1);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_LOG_OAK, PIXEL_Y_LOG_OAK);

	damage.init(1, 5, 0);

	idCreated.init(idBlocks::logOak, idUnlifeObject::NONE_OBJECT);

	addType.maxAmount = 4;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;

	delete pathTexture;
}

void initSeadling(TypeItem* typesItem, listDestroyObjectsAndBlocks& list)
{
	TypeItem addType;

	featuresItem featuresAddItem;
	featuresSprite sizeMain;
	idCreateObjects idCreated;
	typeDamageItem damage;

	String* pathTexture = new String;
	*pathTexture = texturePaths[idTexturePaths::items];

	int numberItem = idItem::seadlingOakItem;

	featuresAddItem.init("Seadling oak", numberItem, idCategoryItem::unlifeObject, false);
	featuresAddItem.defineToughness(false, 1);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_SEADLING_OAK_ITEM, PIXEL_Y_SEADLING_OAK_ITEM);

	damage.init(1, 1, 0);

	idCreated.init(idBlocks::NONE_BLOCK, idUnlifeObject::oakSeadling);

	addType.maxAmount = 16;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////
	// Саженец дуба
	numberItem = idItem::seadlingApple;

	featuresAddItem.init("Seadling apple", numberItem, idCategoryItem::unlifeObject, false);
	featuresAddItem.defineToughness(false, 1);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_SEADLING_APPLE_ITEM, PIXEL_Y_SEADLING_APPLE_ITEM);

	damage.init(1, 1, 0);

	idCreated.init(idBlocks::NONE_BLOCK, idUnlifeObject::appleSeadling);

	addType.maxAmount = 16;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;

	delete pathTexture;
}

void initGroundBlock(TypeItem* typesItem, listDestroyObjectsAndBlocks& list)
{
	TypeItem addType;

	featuresItem featuresAddItem;
	featuresSprite sizeMain;
	idCreateObjects idCreated;
	typeDamageItem damage;

	String* pathTexture = new String;
	*pathTexture = texturePaths[idTexturePaths::items];

	int numberItem = idItem::dirtItem;

	featuresAddItem.init("Dirt block", numberItem, idCategoryItem::block, false);
	featuresAddItem.defineToughness(false, 1);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_DIRT, PIXEL_Y_DIRT);

	damage.init(0, 1, 0);

	addType.maxAmount = 4;
	idCreated.init(idBlocks::dirt, idUnlifeObject::NONE_OBJECT);

	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////
	// Земля с травой
	numberItem = idItem::grassItem;

	featuresAddItem.init("Grass", numberItem, idCategoryItem::block, false);
	featuresAddItem.defineToughness(false, 1);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_GRASS_BRICK, PIXEL_Y_GRASS_BRICK);

	damage.init(0, 1, 0);

	idCreated.init(idBlocks::grass, idUnlifeObject::NONE_OBJECT);

	addType.maxAmount = 4;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////
	// Песок
	numberItem = idItem::sandItem;

	featuresAddItem.init("Sand block", numberItem, idCategoryItem::block, false);
	featuresAddItem.defineToughness(false, 1);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_SAND, PIXEL_Y_SAND);

	damage.init(0, 1, 0);

	idCreated.init(idBlocks::sand, idUnlifeObject::NONE_OBJECT);

	addType.maxAmount = 4;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;

	delete pathTexture;
}

void initWeapon(TypeItem* typesItem, listDestroyObjectsAndBlocks& list)
{
	TypeItem addType;

	featuresItem featuresAddItem;
	featuresSprite sizeMain;
	idCreateObjects idCreated;
	typeDamageItem damage;

	String* pathTexture = new String;
	*pathTexture = texturePaths[idTexturePaths::items];

	int numberItem = idItem::stoneKnifeItem;

	featuresAddItem.init("Stone knife", numberItem, idCategoryItem::weapon, true);
	featuresAddItem.defineToughness(true, 128);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_STONE_KNIFE, PIXEL_Y_STONE_KNIFE);

	damage.init(18, 1, 0);

	idCreated.init(idBlocks::NONE_BLOCK, idUnlifeObject::NONE_OBJECT);

	addType.maxAmount = 1;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;

	// железный меч
	numberItem = idItem::ironSwordItem;

	featuresAddItem.init("Iron sword", numberItem, idCategoryItem::weapon, true);
	featuresAddItem.defineToughness(true, 512);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_IRON_SWORD, PIXEL_Y_IRON_SWORD);

	damage.init(32, 4, 0);

	idCreated.init(idBlocks::NONE_BLOCK, idUnlifeObject::NONE_OBJECT);

	addType.maxAmount = 1;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;

	// Серебрянный меч
	numberItem = idItem::silverSwordItem;

	featuresAddItem.init("Silver  sword", numberItem, idCategoryItem::weapon, true);
	featuresAddItem.defineToughness(true, 5000);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_SILVER_SWORD, PIXEL_Y_SILVER_SWORD);

	damage.init(45, 5, 75);

	idCreated.init(idBlocks::NONE_BLOCK, idUnlifeObject::NONE_OBJECT);

	addType.maxAmount = 1;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////
	// Деревянная дубина
	numberItem = idItem::woodClubItem;

	featuresAddItem.init("Wood club", numberItem, idCategoryItem::weapon, false);
	featuresAddItem.defineToughness(true, 128);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_WOOD_CLUB, PIXEL_Y_WOOD_CLUB);

	damage.init(0, 18, 0);

	idCreated.init(idBlocks::NONE_BLOCK, idUnlifeObject::NONE_OBJECT);

	addType.maxAmount = 1;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;

	// железная дубина
	numberItem = idItem::ironClubItem;

	featuresAddItem.init("Iron club", numberItem, idCategoryItem::weapon, false);
	featuresAddItem.defineToughness(true, 512);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_IRON_CLUB, PIXEL_Y_IRON_CLUB);

	damage.init(0, 32, 0);

	idCreated.init(idBlocks::NONE_BLOCK, idUnlifeObject::NONE_OBJECT);

	addType.maxAmount = 1;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;

	delete pathTexture;
}

void initTools(TypeItem* typesItem, listDestroyObjectsAndBlocks& list)
{
	TypeItem addType;

	featuresItem featuresAddItem;
	featuresSprite sizeMain;
	idCreateObjects idCreated;
	typeDamageItem damage;

	String* pathTexture = new String;
	*pathTexture = texturePaths[idTexturePaths::items];

	int numberItem = idItem::ironBackHoerItem;

	featuresAddItem.init("Iron backhoe", numberItem, idCategoryItem::backhoe, false);
	featuresAddItem.defineToughness(true, 512);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_IRON_BACKHOE, PIXEL_Y_IRON_BACKHOE);

	damage.init(1, 10, 0);

	addType.destroy.init(&list.backoeBreakingObject, &list.backoeBreakingBlock);

	idCreated.init(idBlocks::air, idUnlifeObject::NONE_OBJECT);

	addType.maxAmount = 1;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////////////////////////////////
	// Кирки
	// Каменная кирка
	numberItem = idItem::stonePickaxItem;

	featuresAddItem.init("Stone pickax", numberItem, idCategoryItem::pickax, false);
	featuresAddItem.defineToughness(true, 128);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_STONE_PICKAX, PIXEL_Y_STONE_PICKAX);

	damage.init(10, 6, 0);

	addType.destroy.init(&list.pickaxBreakingObject, &list.pickaxBreakingBlock);

	idCreated.init(idBlocks::air, idUnlifeObject::NONE_OBJECT);

	addType.maxAmount = 1;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;

	// Железная кирка
	numberItem = idItem::ironPickaxItem;

	featuresAddItem.init("Iron pickax", numberItem, idCategoryItem::pickax, false);
	featuresAddItem.defineToughness(true, 512);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_IRON_PICKAK, PIXEL_Y_IRON_PICKAK);

	damage.init(18, 12, 0);

	addType.destroy.init(&list.pickaxBreakingObject, &list.pickaxBreakingBlock);

	idCreated.init(idBlocks::air, idUnlifeObject::NONE_OBJECT);

	addType.maxAmount = 1;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////
	// Топоры

	/////////////////////////////
	// Каменный топор
	numberItem = idItem::stoneAxeItem;

	featuresAddItem.init("Stone axe", numberItem, idCategoryItem::axe, false);
	featuresAddItem.defineToughness(true, 128);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_STONE_AXE, PIXEL_Y_STONE_AXE);

	damage.init(8, 8, 0);

	addType.destroy.init(&list.axeBreakingObject, &list.axeBreakingBlock);

	idCreated.init(idBlocks::air, idUnlifeObject::NONE_OBJECT);

	addType.maxAmount = 1;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	// Железный топор
	numberItem = idItem::ironAxeItem;

	featuresAddItem.init("Iron axe", numberItem, idCategoryItem::axe, false);
	featuresAddItem.defineToughness(true, 512);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_IRON_AXE, PIXEL_Y_IRON_AXE);

	damage.init(18, 18, 0);

	addType.destroy.init(&list.axeBreakingObject, &list.axeBreakingBlock);

	idCreated.init(idBlocks::air, idUnlifeObject::NONE_OBJECT);

	addType.maxAmount = 1;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;


	delete pathTexture;
}

void initFoods(TypeItem* typesItem, listDestroyObjectsAndBlocks& list)
{
	TypeItem addType;

	featuresItem featuresAddItem;
	featuresSprite sizeMain;
	idCreateObjects idCreated;
	typeDamageItem damage;

	String* pathTexture = new String;
	*pathTexture = texturePaths[idTexturePaths::items];

	int numberItem = idItem::mushroomItem;

	featuresAddItem.init("Mushroom", numberItem, idCategoryItem::food, false);
	featuresAddItem.defineToughness(false, 4);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_MUSHROOM, PIXEL_Y_MUSHROOM);

	damage.init(0, 1, 0);

	idCreated.init(idBlocks::NONE_BLOCK, idUnlifeObject::NONE_OBJECT);

	addType.maxAmount = 16;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////////////
	// Мясо волка
	numberItem = idItem::rawMeatWolfItem;

	featuresAddItem.init("Raw meat wolf", numberItem, idCategoryItem::other, false);
	featuresAddItem.defineToughness(false, 4);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_RAW_MEAT_WOLF, PIXEL_Y_RAW_MEAT_WOLF);

	damage.init(0, 1, 0);

	idCreated.init(idBlocks::NONE_BLOCK, idUnlifeObject::NONE_OBJECT);

	addType.maxAmount = 16;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////////////
	// Жаренное мясо волка
	numberItem = idItem::roastMeatWolfItem;

	featuresAddItem.init("Roast meat wolf", numberItem, idCategoryItem::food, false);
	featuresAddItem.defineToughness(false, 10);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_ROAST_MEAT_WOLF, PIXEL_Y_ROAST_MEAT_WOLF);

	damage.init(0, 1, 0);

	idCreated.init(idBlocks::NONE_BLOCK, idUnlifeObject::NONE_OBJECT);

	addType.maxAmount = 16;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////////////
	// Яблоко
	numberItem = idItem::appleItem;

	featuresAddItem.init("Apple", numberItem, idCategoryItem::food, false);
	featuresAddItem.defineToughness(false, 4);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_APPLE, PIXEL_Y_APPLE);

	damage.init(0, 1, 0);

	idCreated.init(idBlocks::NONE_BLOCK, idUnlifeObject::NONE_OBJECT);

	addType.maxAmount = 16;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;

	delete pathTexture;
}

void initEmptyItem(TypeItem* typesItem, listDestroyObjectsAndBlocks& list)
{
	////////////////////////////////////////////////v
	// Переменные для записывания данных
	TypeItem addType;

	featuresItem featuresAddItem;
	featuresSprite sizeMain;
	idCreateObjects idCreated;
	typeDamageItem damage;

	int numberItem = idItem::emptyItem;

	String* pathTexture = new String;
	*pathTexture = texturePaths[idTexturePaths::items];

	featuresAddItem.init("Empty", numberItem, idCategoryItem::other, false);
	featuresAddItem.defineToughness(false, 1);

	sizeMain.init(0, 0, 0, 0);

	damage.init(0, 1, 0);

	idCreated.init(idBlocks::NONE_BLOCK, idUnlifeObject::NONE_OBJECT);

	addType.maxAmount = 1;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////
	delete pathTexture;
}

void initHaveWater(TypeItem* typesItem, listDestroyObjectsAndBlocks& list)
{
	TypeItem addType;

	featuresItem featuresAddItem;
	featuresSprite sizeMain;
	idCreateObjects idCreated;
	typeDamageItem damage;

	String* pathTexture = new String;
	*pathTexture = texturePaths[idTexturePaths::items];

	int numberItem = idItem::woodBukketItem;

	/////////////////////////////////////////////////////////
	// Напитки и сосуды

	/////////////////////////////
	// Деревянное ведро

	featuresAddItem.init("Wood bukket", numberItem, idCategoryItem::bukketEmpty, false);
	featuresAddItem.defineToughness(false, 1);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_WOOD_BUKKET, PIXEL_Y_WOOD_BUKKET);

	damage.init(0, 3, 0);

	idCreated.init(idBlocks::water, idUnlifeObject::NONE_OBJECT);

	addType.maxAmount = 4;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////
	// Деревянное ведро с водой
	numberItem = idItem::woodBukketWithWaterItem;

	featuresAddItem.init("Wood bukket with water", numberItem, idCategoryItem::bukketWithWater, false);
	featuresAddItem.defineToughness(false, 20);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_WOOD_BUKKET_WITH_WATER, PIXEL_Y_WOOD_BUKKET_WITH_WATER);

	damage.init(0, 4, 0);

	idCreated.init(idBlocks::water, idUnlifeObject::NONE_OBJECT);

	addType.maxAmount = 4;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////
	// Стеклянная бытылка
	numberItem = idItem::glassBottleItem;

	featuresAddItem.init("Glass bottle", numberItem, idCategoryItem::bottleEmpty, false);
	featuresAddItem.defineToughness(false, 1);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_GLASS_BOTTLE, PIXEL_Y_GLASS_BOTTLE);

	damage.init(0, 2, 0);

	idCreated.init(idBlocks::water, idUnlifeObject::NONE_OBJECT);

	addType.maxAmount = 16;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////
	// Стеклянная бытылка с водой
	numberItem = idItem::glassbukketWithWater;

	featuresAddItem.init("Glass bottle with water", numberItem, idCategoryItem::bottleWithWater, false);
	featuresAddItem.defineToughness(false, 5);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_GLASS_BOTTLE_WITH_WATER, PIXEL_Y_GLASS_BOTTLE_WITH_WATER);

	damage.init(0, 2, 0);

	idCreated.init(idBlocks::NONE_BLOCK, idUnlifeObject::NONE_OBJECT);

	addType.maxAmount = 16;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	/////////////////////////////
	// Стеклянная бытылка с водой
	numberItem = idItem::healthPotionItem;

	featuresAddItem.init("Health potion", numberItem, idCategoryItem::healthPotion, false);
	featuresAddItem.defineToughness(false, 100);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_HEALTH_POTION, PIXEL_Y_HEALTH_POTION);

	damage.init(0, 2, 0);

	idCreated.init(idBlocks::NONE_BLOCK, idUnlifeObject::NONE_OBJECT);

	addType.maxAmount = 16;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain, idCreated, damage);

	typesItem[numberItem] = addType;
	delete pathTexture;
}

void typeDamageItem::init(int cut, int crush, int unlife)
{
	cuttingDamage = cut;
	crushingDamage = crush;
	unlifeDamage = unlife;
}

void idCreateObjects::init(int idBlock, int idObject)
{
	idBlockForUse = idBlock;
	idUnlideOnjectForUse = idObject;
}

void featuresItem::init(String nameItem, int idItem, int idCategory, bool cutting)
{
	name = nameItem;
	id = idItem;
	category = idCategory;
	isCutting = cutting;
}

void featuresItem::defineToughness(bool destroy, int toughnessItem)
{
	isDestroy = destroy;
	toughness = toughnessItem;
}

void destroyObjectsAndBlocks::init(std::vector<sf::String> *namesObjects, std::vector<wchar_t> *charBlocks)
{
	objects = namesObjects;

	blocks = charBlocks;
}

////////////////////////////////////////////////////////////////////
// Виды объектов
void TypeItem::Init(String filenameTexture, featuresItem featuresAddItem,
										featuresSprite featuresSprite, idCreateObjects idCreated, typeDamageItem damage)
{
	textureItem = new Texture;
	if (textureItem->loadFromFile(filenameTexture)) {
		//std::cout << string(filenameTexture) << std::endl;
	} else {
		std::cout << "error " << string(filenameTexture) << std::endl;
	}

	sizeMain.size.height = featuresSprite.size.height;
	sizeMain.size.width = featuresSprite.size.width;
	sizeMain.pixPos.x = featuresSprite.pixPos.x;
	sizeMain.pixPos.y = featuresSprite.pixPos.y;

	features.isDestroy = featuresAddItem.isDestroy;
	features.category = featuresAddItem.category;
	features.toughness = featuresAddItem.toughness;
	features.name = featuresAddItem.name;
	features.id = featuresAddItem.id;
	features.isCutting = featuresAddItem.isCutting;

	damageItem.cuttingDamage = damage.cuttingDamage;// Режущий
	damageItem.crushingDamage = damage.crushingDamage;// Дробящий
	damageItem.unlifeDamage = damage.unlifeDamage;

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

};

void TypeItem::InitForUse(String filenameTextureForUse, featuresSprite features)
{
	textureItemForUse = new Texture;
	textureItemForUse->loadFromFile(filenameTextureForUse);
	// Задание размера
	sizeAlternative.size.height = features.size.height;
	sizeAlternative.size.width = features.size.width;

	sizeAlternative.pixPos.x = features.pixPos.x;
	sizeAlternative.pixPos.y = features.pixPos.y;
}
////////////////////////////////////////////////////////////////////