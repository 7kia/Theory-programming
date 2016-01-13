#include <iostream>
#include "../UnlifeObject/UnlifeObjectVar.h"
#include "../Recourses.h"

#include "TypeItems.h"
#include "ItemsVar.h"
#include "../Map/BlocksVar.h"
using namespace sf;
using namespace std;

void initializeTypesItem(TypeItem *typesItem , listDestroyObjectsAndBlocks &list)
{
	initStoneBlock(typesItem, list);
	initWoodBlock(typesItem, list);
	initSeadling(typesItem, list);
	initGroundBlock(typesItem, list);
	initWeapon(typesItem, list);
	initDistanseWeapon(typesItem,  list);
	initTools(typesItem, list);
	initFoods(typesItem, list);
	initEmptyItem(typesItem, list);
}

void initStoneBlock(TypeItem *typesItem, listDestroyObjectsAndBlocks &list)
{
	TypeItem addType;

	featuresItem featuresAddItem;
	featuresSprite sizeMain;
	std::vector<int> listDestroy;

	int numberItem = idItem::stoneItem;

	String* pathTexture = new String;
	*pathTexture = texturePaths[idTexturePaths::itemsPath];

	featuresAddItem.init("Stone block", numberItem, idCategoryItem::block, false);
	featuresAddItem.defineToughness(false, 1);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_SMALL_STONE, PIXEL_Y_SMALL_STONE);

	addType.damageItem[cuttingDamage] = 0;
	addType.damageItem[crushingDamage] = 10;
	addType.damageItem[unlifeDamage] = 0;

	addType.initListDestroy(list.none);

	addType.initIdsAddObject(stone, NONE_OBJECT , NONE_SHOOT);

	addType.maxAmount = 4;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain);

	typesItem[numberItem] = addType;
	/////////////////////////////
	// Каменные кирпичи
	numberItem = idItem::stoneBrickItem;

	featuresAddItem.init("Stone brick", numberItem, idCategoryItem::block, false);
	featuresAddItem.defineToughness(false, 1);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_STONE_BRICK, PIXEL_Y_STONE_BRICK);

	addType.damageItem[cuttingDamage] = 0;
	addType.damageItem[crushingDamage] = 10;
	addType.damageItem[unlifeDamage] = 0;

	addType.initListDestroy(list.none);

	addType.initIdsAddObject(stoneBrick, NONE_OBJECT , NONE_SHOOT);

	addType.maxAmount = 4;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain);

	typesItem[numberItem] = addType;

	delete pathTexture;
}

void initWoodBlock(TypeItem *typesItem,  listDestroyObjectsAndBlocks &list)
{
	TypeItem addType;

	featuresItem featuresAddItem;
	featuresSprite sizeMain;

	String* pathTexture = new String;
	*pathTexture = texturePaths[idTexturePaths::itemsPath];

	int numberItem = idItem::planksBlockItem;

	featuresAddItem.init("Planks", numberItem, idCategoryItem::block, false);
	featuresAddItem.defineToughness(false, 1);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_PLANKS, PIXEL_Y_PLANKS);

	addType.damageItem[cuttingDamage] = 0;
	addType.damageItem[crushingDamage] = 5;
	addType.damageItem[unlifeDamage] = 0;

	addType.initListDestroy(list.none);

	addType.initIdsAddObject(planksBlock, NONE_OBJECT , NONE_SHOOT);

	addType.maxAmount = 4;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain);

	typesItem[numberItem] = addType;
	/////////////////////////////
	// Деревянная лестница
	numberItem = idItem::woodLadderItem;

	featuresAddItem.init("Wood ladder", numberItem, idCategoryItem::block, false);
	featuresAddItem.defineToughness(false, 1);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_WOOD_LADDER, PIXEL_Y_WOOD_LADDER);

	addType.damageItem[cuttingDamage] = 0;
	addType.damageItem[crushingDamage] = 4;
	addType.damageItem[unlifeDamage] = 0;


	addType.initListDestroy(list.none);

	addType.initIdsAddObject(woodLadder, NONE_OBJECT , NONE_SHOOT);

	addType.maxAmount = 16;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain);

	typesItem[numberItem] = addType;
	/////////////////////////////
	// Дубовое бревно
	numberItem = idItem::logOakItem;

	featuresAddItem.init("Log", numberItem, idCategoryItem::block, false);
	featuresAddItem.defineToughness(false, 1);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_LOG_OAK, PIXEL_Y_LOG_OAK);

	addType.damageItem[cuttingDamage] = 1;
	addType.damageItem[crushingDamage] = 5;
	addType.damageItem[unlifeDamage] = 0;

	addType.initListDestroy(list.none);

	addType.initIdsAddObject(logOak, NONE_OBJECT , NONE_SHOOT);

	addType.maxAmount = 4;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain);

	typesItem[numberItem] = addType;

	delete pathTexture;
}

void initSeadling(TypeItem *typesItem,  listDestroyObjectsAndBlocks &list)
{
	TypeItem addType;

	featuresItem featuresAddItem;
	featuresSprite sizeMain;

	String* pathTexture = new String;
	*pathTexture = texturePaths[idTexturePaths::itemsPath];

	int numberItem = idItem::seadlingOakItem;

	featuresAddItem.init("Seadling oak", numberItem, idCategoryItem::unlifeObject, false);
	featuresAddItem.defineToughness(false, 1);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_SEADLING_OAK_ITEM, PIXEL_Y_SEADLING_OAK_ITEM);

	addType.damageItem[cuttingDamage] = 1;
	addType.damageItem[crushingDamage] = 1;
	addType.damageItem[unlifeDamage] = 0;

	addType.initListDestroy(list.none);

	addType.initIdsAddObject(NONE_BLOCK, oakSeadling , NONE_SHOOT);

	addType.maxAmount = 16;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain);

	typesItem[numberItem] = addType;
	/////////////////////////////
	// Саженец дуба
	numberItem = idItem::seadlingApple;

	featuresAddItem.init("Seadling apple", numberItem, idCategoryItem::unlifeObject, false);
	featuresAddItem.defineToughness(false, 1);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_SEADLING_APPLE_ITEM, PIXEL_Y_SEADLING_APPLE_ITEM);

	addType.damageItem[cuttingDamage] = 1;
	addType.damageItem[crushingDamage] = 1;
	addType.damageItem[unlifeDamage] = 0;

	addType.initListDestroy(list.none);

	addType.initIdsAddObject(NONE_BLOCK, appleSeadling , NONE_SHOOT);

	addType.maxAmount = 16;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain);

	typesItem[numberItem] = addType;

	delete pathTexture;
}

void initGroundBlock(TypeItem *typesItem,  listDestroyObjectsAndBlocks &list)
{
	TypeItem addType;

	featuresItem featuresAddItem;
	featuresSprite sizeMain;

	String* pathTexture = new String;
	*pathTexture = texturePaths[idTexturePaths::itemsPath];

	int numberItem = idItem::grassItem;

	featuresAddItem.init("Grass", numberItem, idCategoryItem::block, false);
	featuresAddItem.defineToughness(false, 1);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_GRASS_BRICK, PIXEL_Y_GRASS_BRICK);

	addType.damageItem[cuttingDamage] = 0;
	addType.damageItem[crushingDamage] = 1;
	addType.damageItem[unlifeDamage] = 0;

	addType.initListDestroy(list.none);

	addType.initIdsAddObject(grass, NONE_OBJECT , NONE_SHOOT);

	addType.maxAmount = 4;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain);

	typesItem[numberItem] = addType;
	
	delete pathTexture;
}

void initWeapon(TypeItem *typesItem,  listDestroyObjectsAndBlocks &list)
{
	TypeItem addType;

	featuresItem featuresAddItem;
	featuresSprite sizeMain;

	String* pathTexture = new String;
	*pathTexture = texturePaths[idTexturePaths::itemsPath];

	int numberItem = idItem::stoneKnifeItem;

	featuresAddItem.init("Stone knife", numberItem, idCategoryItem::weapon, true);
	featuresAddItem.defineToughness(true, 128);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_STONE_KNIFE, PIXEL_Y_STONE_KNIFE);

	addType.damageItem[cuttingDamage] = 18;
	addType.damageItem[crushingDamage] = 1;
	addType.damageItem[unlifeDamage] = 0;

	addType.initListDestroy(list.stoneKnife);

	addType.initIdsAddObject(NONE_BLOCK, NONE_OBJECT , NONE_SHOOT);

	addType.maxAmount = 1;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain);

	typesItem[numberItem] = addType;

	// железный меч
	numberItem = idItem::ironSwordItem;

	featuresAddItem.init("Iron sword", numberItem, idCategoryItem::weapon, true);
	featuresAddItem.defineToughness(true, 512);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_IRON_SWORD, PIXEL_Y_IRON_SWORD);

	addType.damageItem[cuttingDamage] = 32;
	addType.damageItem[crushingDamage] = 4;
	addType.damageItem[unlifeDamage] = 0;

	addType.initListDestroy(list.none);

	addType.initIdsAddObject(NONE_BLOCK, NONE_OBJECT , NONE_SHOOT);

	addType.maxAmount = 1;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain);

	typesItem[numberItem] = addType;

	// Серебрянный меч
	numberItem = idItem::silverSwordItem;

	featuresAddItem.init("Silver  sword", numberItem, idCategoryItem::weapon, true);
	featuresAddItem.defineToughness(true, 5000);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_SILVER_SWORD, PIXEL_Y_SILVER_SWORD);

	addType.damageItem[cuttingDamage] = 45;
	addType.damageItem[crushingDamage] = 5;
	addType.damageItem[unlifeDamage] = 75;

	addType.initListDestroy(list.none);

	addType.initIdsAddObject(NONE_BLOCK, NONE_OBJECT , NONE_SHOOT);

	addType.maxAmount = 1;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain);

	typesItem[numberItem] = addType;
	/////////////////////////////
	// Деревянная дубина
	numberItem = idItem::woodClubItem;

	featuresAddItem.init("Wood club", numberItem, idCategoryItem::weapon, false);
	featuresAddItem.defineToughness(true, 128);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_WOOD_CLUB, PIXEL_Y_WOOD_CLUB);

	addType.damageItem[cuttingDamage] = 0;
	addType.damageItem[crushingDamage] = 18;
	addType.damageItem[unlifeDamage] = 0;

	addType.initListDestroy(list.none);

	addType.initIdsAddObject(NONE_BLOCK, NONE_OBJECT , NONE_SHOOT);

	addType.maxAmount = 1;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain);

	typesItem[numberItem] = addType;

	// железная дубина
	numberItem = idItem::ironClubItem;

	featuresAddItem.init("Iron club", numberItem, idCategoryItem::weapon, false);
	featuresAddItem.defineToughness(true, 512);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_IRON_CLUB, PIXEL_Y_IRON_CLUB);

	addType.damageItem[cuttingDamage] = 0;
	addType.damageItem[crushingDamage] = 32;
	addType.damageItem[unlifeDamage] = 0;

	addType.initListDestroy(list.none);

	addType.initIdsAddObject(NONE_BLOCK, NONE_OBJECT , NONE_SHOOT);

	addType.maxAmount = 1;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain);

	typesItem[numberItem] = addType;

	delete pathTexture;
}

void initDistanseWeapon(TypeItem *typesItem,  listDestroyObjectsAndBlocks &list)
{
	TypeItem addType;

	featuresItem featuresAddItem;
	featuresSprite sizeMain;

	String* pathTexture = new String;
	*pathTexture = texturePaths[idTexturePaths::itemsPath];

	int numberItem = idItem::pistolItem;

	featuresAddItem.init("Pistol" , numberItem , idCategoryItem::distanceWeapon , false);
	featuresAddItem.defineToughness(true , 128);

	sizeMain.init(SIZE_ITEM , SIZE_ITEM , PIXEL_X_PISTOL_ITEM , PIXEL_Y_PISTOL_ITEM);

	addType.damageItem[cuttingDamage] = 1;
	addType.damageItem[crushingDamage] = 5;
	addType.damageItem[unlifeDamage] = 0;

	addType.initListDestroy(list.none);

	addType.initIdsAddObject(NONE_BLOCK , NONE_OBJECT , pistolShoot);

	addType.maxAmount = 1;
	addType.Init(*pathTexture , featuresAddItem ,
							 sizeMain);

	typesItem[numberItem] = addType;

	// ружьё
	numberItem = idItem::rifleItem;

	featuresAddItem.init("Rifle" , numberItem , idCategoryItem::distanceWeapon , true);
	featuresAddItem.defineToughness(true , 512);

	sizeMain.init(SIZE_ITEM , SIZE_ITEM , PIXEL_X_RIFLE_ITEM , PIXEL_Y_RIFLE_ITEM);

	addType.damageItem[cuttingDamage] = 20;
	addType.damageItem[crushingDamage] = 20;
	addType.damageItem[unlifeDamage] = 0;

	addType.initListDestroy(list.none);

	addType.initIdsAddObject(NONE_BLOCK , NONE_OBJECT , rifleShoot);

	addType.maxAmount = 1;
	addType.Init(*pathTexture , featuresAddItem ,
							 sizeMain);

	typesItem[numberItem] = addType;
	// тяжёлое ружьё
	numberItem = idItem::heavyRifleItem;

	featuresAddItem.init("Heavy rifle" , numberItem , idCategoryItem::distanceWeapon , true);
	featuresAddItem.defineToughness(true , 512);

	sizeMain.init(SIZE_ITEM , SIZE_ITEM , PIXEL_X_HEAVY_RIFLE_ITEM , PIXEL_Y_HEAVY_RIFLE_ITEM);

	addType.damageItem[cuttingDamage] = 35;
	addType.damageItem[crushingDamage] = 35;
	addType.damageItem[unlifeDamage] = 0;

	addType.initListDestroy(list.none);

	addType.initIdsAddObject(NONE_BLOCK , NONE_OBJECT , heavyRifleShoot);

	addType.maxAmount = 1;
	addType.Init(*pathTexture , featuresAddItem ,
							 sizeMain);

	typesItem[numberItem] = addType;
	// тяжёлое ружьё
	numberItem = idItem::bulletItem;

	featuresAddItem.init("Bullet" , numberItem , idCategoryItem::other , false);
	featuresAddItem.defineToughness(false , 512);

	sizeMain.init(SIZE_ITEM , SIZE_ITEM , PIXEL_X_BULLET_ITEM , PIXEL_Y_BULLET_ITEM);

	addType.damageItem[cuttingDamage] = 0;
	addType.damageItem[crushingDamage] = 1;
	addType.damageItem[unlifeDamage] = 0;

	addType.initListDestroy(list.none);

	addType.initIdsAddObject(NONE_BLOCK , NONE_OBJECT , NONE_SHOOT);

	addType.maxAmount = 32;
	addType.Init(*pathTexture , featuresAddItem ,
							 sizeMain);

	typesItem[numberItem] = addType;
}

void initTools(TypeItem *typesItem,  listDestroyObjectsAndBlocks &list)
{
	TypeItem addType;

	featuresItem featuresAddItem;
	featuresSprite sizeMain;

	String* pathTexture = new String;
	*pathTexture = texturePaths[idTexturePaths::itemsPath];

	int numberItem = idItem::ironBackHoerItem;

	featuresAddItem.init("Iron backhoe", numberItem, idCategoryItem::backhoe, false);
	featuresAddItem.defineToughness(true, 512);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_IRON_BACKHOE, PIXEL_Y_IRON_BACKHOE);

	addType.damageItem[cuttingDamage] = 1;
	addType.damageItem[crushingDamage] = 10;
	addType.damageItem[unlifeDamage] = 0;

	addType.initListDestroy(list.backhoe);

	addType.initIdsAddObject(air, NONE_OBJECT , NONE_SHOOT);

	addType.maxAmount = 1;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain);

	typesItem[numberItem] = addType;
	typesItem[numberItem] = typesItem[numberItem];
	/////////////////////////////////////////////////////////
	// Кирки
	// Каменная кирка
	numberItem = idItem::stonePickaxItem;

	featuresAddItem.init("Stone pickax", numberItem, idCategoryItem::pickax, false);
	featuresAddItem.defineToughness(true, 128);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_STONE_PICKAX, PIXEL_Y_STONE_PICKAX);

	addType.damageItem[cuttingDamage] = 10;
	addType.damageItem[crushingDamage] = 6;
	addType.damageItem[unlifeDamage] = 0;

	addType.initListDestroy(list.pickax);

	addType.initIdsAddObject(air, NONE_OBJECT , NONE_SHOOT);

	addType.maxAmount = 1;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain);

	typesItem[numberItem] = addType;

	// Железная кирка
	numberItem = idItem::ironPickaxItem;

	featuresAddItem.init("Iron pickax", numberItem, idCategoryItem::pickax, false);
	featuresAddItem.defineToughness(true, 512);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_IRON_PICKAK, PIXEL_Y_IRON_PICKAK);

	addType.damageItem[cuttingDamage] = 18;
	addType.damageItem[crushingDamage] = 12;
	addType.damageItem[unlifeDamage] = 0;

	addType.initListDestroy(list.pickax);

	addType.initIdsAddObject(air, NONE_OBJECT , NONE_SHOOT);

	addType.maxAmount = 1;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain);

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

	addType.damageItem[cuttingDamage] = 8;
	addType.damageItem[crushingDamage] = 8;
	addType.damageItem[unlifeDamage] = 0;

	addType.initListDestroy(list.axe);

	addType.initIdsAddObject(air, NONE_OBJECT , NONE_SHOOT);

	addType.maxAmount = 1;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain);

	typesItem[numberItem] = addType;
	// Железный топор
	numberItem = idItem::ironAxeItem;

	featuresAddItem.init("Iron axe", numberItem, idCategoryItem::axe, false);
	featuresAddItem.defineToughness(true, 512);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_IRON_AXE, PIXEL_Y_IRON_AXE);

	addType.damageItem[cuttingDamage] = 18;
	addType.damageItem[crushingDamage] = 18;
	addType.damageItem[unlifeDamage] = 0;

	addType.initListDestroy(list.axe);

	addType.initIdsAddObject(air, NONE_OBJECT , NONE_SHOOT);

	addType.maxAmount = 1;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain);

	typesItem[numberItem] = addType;


	delete pathTexture;
}

void initFoods(TypeItem *typesItem,  listDestroyObjectsAndBlocks &list)
{
	TypeItem addType;

	featuresItem featuresAddItem;
	featuresSprite sizeMain;

	String* pathTexture = new String;
	*pathTexture = texturePaths[idTexturePaths::itemsPath];

	int numberItem = idItem::mushroomItem;

	featuresAddItem.init("Mushroom", numberItem, idCategoryItem::food, false);
	featuresAddItem.defineToughness(false, 4);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_MUSHROOM, PIXEL_Y_MUSHROOM);

	addType.damageItem[cuttingDamage] = 0;
	addType.damageItem[crushingDamage] = 1;
	addType.damageItem[unlifeDamage] = 0;

	addType.initListDestroy(list.none);

	addType.initIdsAddObject(NONE_BLOCK, NONE_OBJECT , NONE_SHOOT);

	addType.maxAmount = 16;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain);

	typesItem[numberItem] = addType;
	/////////////////////////////////////
	// Яблоко
	numberItem = idItem::appleItem;

	featuresAddItem.init("Apple", numberItem, idCategoryItem::food, false);
	featuresAddItem.defineToughness(false, 4);

	sizeMain.init(SIZE_ITEM, SIZE_ITEM, PIXEL_X_APPLE, PIXEL_Y_APPLE);

	addType.damageItem[cuttingDamage] = 0;
	addType.damageItem[crushingDamage] = 1;
	addType.damageItem[unlifeDamage] = 0;

	addType.initListDestroy(list.none);

	addType.initIdsAddObject(NONE_BLOCK, NONE_OBJECT, NONE_SHOOT);

	addType.maxAmount = 16;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain);

	typesItem[numberItem] = addType;

	/////////////////////////////
	// Стеклянная бытылка с водой
	numberItem = idItem::healthPotionItem;

	featuresAddItem.init("Health potion" , numberItem , idCategoryItem::healthPotion , false);
	featuresAddItem.defineToughness(false , 100);

	sizeMain.init(SIZE_ITEM , SIZE_ITEM , PIXEL_X_HEALTH_POTION , PIXEL_Y_HEALTH_POTION);

	addType.damageItem[cuttingDamage] = 0;
	addType.damageItem[crushingDamage] = 2;
	addType.damageItem[unlifeDamage] = 0;

	addType.initIdsAddObject(NONE_BLOCK , NONE_OBJECT , NONE_SHOOT);

	addType.maxAmount = 16;
	addType.Init(*pathTexture , featuresAddItem ,
							 sizeMain);

	typesItem[numberItem] = addType;

	delete pathTexture;
}

void initEmptyItem(TypeItem *typesItem,  listDestroyObjectsAndBlocks &list)
{
	////////////////////////////////////////////////v
	// Переменные для записывания данных
	TypeItem addType;

	featuresItem featuresAddItem;
	featuresSprite sizeMain;

	int numberItem = idItem::emptyItem;

	String* pathTexture = new String;
	*pathTexture = texturePaths[idTexturePaths::itemsPath];

	featuresAddItem.init("Empty", numberItem, idCategoryItem::other, false);
	featuresAddItem.defineToughness(false, 1);

	sizeMain.init(0, 0, 0, 0);

	addType.damageItem[cuttingDamage] = 0;
	addType.damageItem[crushingDamage] = 1;
	addType.damageItem[unlifeDamage] = 0;

	addType.initListDestroy(list.none);

	addType.initIdsAddObject(NONE_BLOCK, NONE_OBJECT , NONE_SHOOT);

	addType.maxAmount = 1;
	addType.Init(*pathTexture, featuresAddItem,
							 sizeMain);

	typesItem[numberItem] = addType;
	/////////////////////////////
	delete pathTexture;
}

void TypeItem::initIdsAddObject(int idBlock, int idObject, int idShoot)
{
	idAdd[idBlockForUse] = idBlock;
	idAdd[idUnlideOnjectForUse] = idObject;
	idAdd[idAddShoot] = idShoot;
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

void TypeItem::initListDestroy(std::vector<int> &idsNature)
{
	destroy = &idsNature;
}

////////////////////////////////////////////////////////////////////
// Виды объектов
void TypeItem::Init(String filenameTexture, featuresItem featuresAddItem,
										featuresSprite featuresSprite)
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

	switch (features.category) {
	case idCategoryItem::block:
		idAdd[idUnlideOnjectForUse] = -1;
		break;
	case idCategoryItem::unlifeObject:
		idAdd[idBlockForUse] = -1;
	default:
		idAdd[idUnlideOnjectForUse] = -1;
		idAdd[idBlockForUse] = -1;
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