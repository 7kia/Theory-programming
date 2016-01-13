#pragma once
#include <SFML\Graphics.hpp>

#include "../GlobalVar.h"

const int MAX_ITEMS = 256;

const int shiftAngleUseItem = 2;
const sf::Vector2f scaleOutItems = { 0.75f, 0.75f };
const sf::Vector2f scaleUseItems = { 0.5f, 0.5f };
const sf::Vector2f normalSize = { 1.f, 1.f };
const sf::Vector2f SCALE_AWARD_ITEMS = { 2.f, 2.f };
const int SIZE_ITEM = SIZE_BLOCK;

const int PIXEL_X_SMALL_STONE = SIZE_ITEM * 2;
const int PIXEL_Y_SMALL_STONE = SIZE_ITEM;

const int PIXEL_X_MUSHROOM = 0;
const int PIXEL_Y_MUSHROOM = SIZE_ITEM;

const int PIXEL_X_PLANKS = SIZE_ITEM;
const int PIXEL_Y_PLANKS = SIZE_ITEM;

const int PIXEL_X_WOOD_LADDER = SIZE_ITEM * 2;
const int PIXEL_Y_WOOD_LADDER = SIZE_ITEM * 2;

const int PIXEL_X_STONE_BRICK = SIZE_ITEM * 3;
const int PIXEL_Y_STONE_BRICK = SIZE_ITEM;

const int PIXEL_X_GRASS_BRICK = SIZE_ITEM;
const int PIXEL_Y_GRASS_BRICK = SIZE_ITEM * 2;

const int PIXEL_X_LOG_OAK = 0;
const int PIXEL_Y_LOG_OAK = 0;

const int PIXEL_X_STONE_PICKAX = SIZE_ITEM * 3;
const int PIXEL_Y_STONE_PICKAX = SIZE_ITEM * 3;

const int PIXEL_X_STONE_AXE = SIZE_ITEM * 5;
const int PIXEL_Y_STONE_AXE = SIZE_ITEM * 3;

const int PIXEL_X_HEALTH_POTION = SIZE_ITEM * 10;
const int PIXEL_Y_HEALTH_POTION = SIZE_ITEM * 2;

const int PIXEL_X_STONE_KNIFE = SIZE_ITEM * 4;
const int PIXEL_Y_STONE_KNIFE = SIZE_ITEM * 3;

const int PIXEL_X_WOOD_CLUB = SIZE_ITEM * 6;
const int PIXEL_Y_WOOD_CLUB = SIZE_ITEM * 3;

const int PIXEL_X_IRON_BACKHOE = SIZE_ITEM * 2;
const int PIXEL_Y_IRON_BACKHOE = SIZE_ITEM * 4;

const int PIXEL_X_IRON_PICKAK = SIZE_ITEM * 3;
const int PIXEL_Y_IRON_PICKAK = SIZE_ITEM * 4;

const int PIXEL_X_IRON_SWORD = SIZE_ITEM * 4;
const int PIXEL_Y_IRON_SWORD = SIZE_ITEM * 4;

const int PIXEL_X_SILVER_SWORD = SIZE_ITEM * 4;
const int PIXEL_Y_SILVER_SWORD = SIZE_ITEM * 5;

const int PIXEL_X_IRON_AXE = SIZE_ITEM * 5;
const int PIXEL_Y_IRON_AXE = SIZE_ITEM * 4;

const int PIXEL_X_IRON_CLUB = SIZE_ITEM * 6;
const int PIXEL_Y_IRON_CLUB = SIZE_ITEM * 4;

const int PIXEL_X_APPLE = SIZE_ITEM * 6;
const int PIXEL_Y_APPLE = 0;

const int PIXEL_X_SEADLING_OAK_ITEM = SIZE_ITEM * 5;
const int PIXEL_Y_SEADLING_OAK_ITEM = SIZE_ITEM;

const int PIXEL_X_SEADLING_APPLE_ITEM = SIZE_ITEM * 5;
const int PIXEL_Y_SEADLING_APPLE_ITEM = SIZE_ITEM * 2;

const int PIXEL_X_PISTOL_ITEM = SIZE_ITEM * 7;
const int PIXEL_Y_PISTOL_ITEM = SIZE_ITEM * 4;

const int PIXEL_X_RIFLE_ITEM = SIZE_ITEM * 7;
const int PIXEL_Y_RIFLE_ITEM = SIZE_ITEM * 5;

const int PIXEL_X_HEAVY_RIFLE_ITEM = SIZE_ITEM * 7;
const int PIXEL_Y_HEAVY_RIFLE_ITEM = SIZE_ITEM * 6;

const int PIXEL_X_BULLET_ITEM = SIZE_ITEM * 7;
const int PIXEL_Y_BULLET_ITEM = SIZE_ITEM * 7;
// ƒŒ¡¿¬À≈Õ»≈ œ–≈ƒÃ≈“¿


const int DISTANSE_BETWEEN_AWARD_ITEMS = SIZE_ITEM;

namespace idItem {
	enum
	{
		// ƒŒ¡¿¬À≈Õ»≈ œ–≈ƒÃ≈“¿
		emptyItem,
		airItem,
		// ¡ÎÓÍË
		grassItem,
		logOakItem,
		stoneItem,
		stoneBrickItem,
		planksBlockItem,
		woodLadderItem,
		// —‡ÊÂÌˆ˚
		seadlingOakItem,
		seadlingApple,
		// ≈‰‡
		mushroomItem,
		appleItem,
		// »ÌÒÚÛÏÂÌÚ˚
		stonePickaxItem,
		stoneAxeItem,
		ironBackHoerItem,
		ironAxeItem,
		ironPickaxItem,
		// ÃÂ˜Ë
		stoneKnifeItem,
		ironSwordItem,
		silverSwordItem,
		// ƒÛ·ËÌ˚
		woodClubItem,
		ironClubItem,
		// –ÛÊ¸ˇ
		pistolItem,
		rifleItem,
		heavyRifleItem,
		bulletItem,
		
		healthPotionItem,

		amountItem
	};
}

const int AMOUNT_TYPES_ITEM = idItem::amountItem;

typedef enum
{
	other,
	food,
	block,
	unlifeObject,
	pickax,
	healthPotion,
	weapon,
	distanceWeapon,
	axe,
	backhoe,
	amounCategory
} idCategoryItem;