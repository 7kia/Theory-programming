#pragma once
#include <SFML\Graphics.hpp>

#include "../Map/BlocksVar.h"

const int MAX_ITEMS = 256;

const int shiftAngleUseItem = 2;
const sf::Vector2f scaleOutItems = { 0.75f, 0.75f };
const sf::Vector2f scaleUseItems = { 0.5f, 0.5f };
const sf::Vector2f normalSize = { 1.f, 1.f };

const int SIZE_ITEM = SIZE_BLOCK;

// stoneItem - ������
const int PIXEL_X_SMALL_STONE = SIZE_ITEM * 2;
const int PIXEL_Y_SMALL_STONE = SIZE_ITEM;

// mushroomItem - ����
const int PIXEL_X_MUSHROOM = 0;
const int PIXEL_Y_MUSHROOM = SIZE_ITEM;

// planks - �����
const int PIXEL_X_PLANKS = SIZE_ITEM;
const int PIXEL_Y_PLANKS = SIZE_ITEM;

// dirt - �����
const int PIXEL_X_DIRT = 0;
const int PIXEL_Y_DIRT = SIZE_ITEM * 2;

// sand - �����
const int PIXEL_X_SAND = 0;
const int PIXEL_Y_SAND = SIZE_ITEM * 3;

// logOak ladder - ���������� ��������
const int PIXEL_X_WOOD_LADDER = SIZE_ITEM * 2;
const int PIXEL_Y_WOOD_LADDER = SIZE_ITEM * 2;

// strone brick - �������� �������
const int PIXEL_X_STONE_BRICK = SIZE_ITEM * 3;
const int PIXEL_Y_STONE_BRICK = SIZE_ITEM;

// grass brick - ���� ����� � ������
const int PIXEL_X_GRASS_BRICK = SIZE_ITEM;
const int PIXEL_Y_GRASS_BRICK = SIZE_ITEM * 2;

// log Oak - ������� ������
const int PIXEL_X_LOG_OAK = 0;
const int PIXEL_Y_LOG_OAK = 0;

// stone pickax - �������� �����
const int PIXEL_X_STONE_PICKAX = SIZE_ITEM * 3;
const int PIXEL_Y_STONE_PICKAX = SIZE_ITEM * 3;

// stone axe - �������� �����
const int PIXEL_X_STONE_AXE = SIZE_ITEM * 5;
const int PIXEL_Y_STONE_AXE = SIZE_ITEM * 3;

// glass bottle - ���������� �������
const int PIXEL_X_GLASS_BOTTLE = SIZE_ITEM * 6;
const int PIXEL_Y_GLASS_BOTTLE = SIZE_ITEM * 2;

// glass bottle with water - ���������� ������� � �����
const int PIXEL_X_GLASS_BOTTLE_WITH_WATER = SIZE_ITEM * 7;
const int PIXEL_Y_GLASS_BOTTLE_WITH_WATER = SIZE_ITEM * 2;

// wood bukket - �����
const int PIXEL_X_WOOD_BUKKET = SIZE_ITEM * 8;
const int PIXEL_Y_WOOD_BUKKET = SIZE_ITEM * 2;

// wood bukket with water - ����� � �����
const int PIXEL_X_WOOD_BUKKET_WITH_WATER = SIZE_ITEM * 9;
const int PIXEL_Y_WOOD_BUKKET_WITH_WATER = SIZE_ITEM * 2;

// wood bukket with water - ����� � �����
const int PIXEL_X_HEALTH_POTION = SIZE_ITEM * 10;
const int PIXEL_Y_HEALTH_POTION = SIZE_ITEM * 2;

// stone knife - �������� ���
const int PIXEL_X_STONE_KNIFE = SIZE_ITEM * 4;
const int PIXEL_Y_STONE_KNIFE = SIZE_ITEM * 3;

// wood club - ���������� ������
const int PIXEL_X_WOOD_CLUB = SIZE_ITEM * 6;
const int PIXEL_Y_WOOD_CLUB = SIZE_ITEM * 3;

// iton backhoe - �������� ������
const int PIXEL_X_IRON_BACKHOE = SIZE_ITEM * 2;
const int PIXEL_Y_IRON_BACKHOE = SIZE_ITEM * 4;

// iton pickax - �������� ������
const int PIXEL_X_IRON_PICKAK = SIZE_ITEM * 3;
const int PIXEL_Y_IRON_PICKAK = SIZE_ITEM * 4;

// iton sword - �������� ������
const int PIXEL_X_IRON_SWORD = SIZE_ITEM * 4;
const int PIXEL_Y_IRON_SWORD = SIZE_ITEM * 4;

// iton sword - �������� ������
const int PIXEL_X_SILVER_SWORD = SIZE_ITEM * 4;
const int PIXEL_Y_SILVER_SWORD = SIZE_ITEM * 5;

// iton sword - �������� ������
const int PIXEL_X_IRON_AXE = SIZE_ITEM * 5;
const int PIXEL_Y_IRON_AXE = SIZE_ITEM * 4;

// iton sword - �������� ������
const int PIXEL_X_IRON_CLUB = SIZE_ITEM * 6;
const int PIXEL_Y_IRON_CLUB = SIZE_ITEM * 4;


// raw meat wolf - ����� ���� �����
const int PIXEL_X_RAW_MEAT_WOLF = SIZE_ITEM * 6;
const int PIXEL_Y_RAW_MEAT_WOLF = SIZE_ITEM;

// roast meat wolf - �������� ���� �����
const int PIXEL_X_ROAST_MEAT_WOLF = SIZE_ITEM * 7;
const int PIXEL_Y_ROAST_MEAT_WOLF = SIZE_ITEM;

// raw meat wolf - ����� ���� �����
const int PIXEL_X_APPLE = SIZE_ITEM * 6;
const int PIXEL_Y_APPLE = 0;

// seedling oak - ������� ����
const int PIXEL_X_SEADLING_OAK_ITEM = SIZE_ITEM * 5;
const int PIXEL_Y_SEADLING_OAK_ITEM = SIZE_ITEM;

// seedling apple - ������� ������
const int PIXEL_X_SEADLING_APPLE_ITEM = SIZE_ITEM * 5;
const int PIXEL_Y_SEADLING_APPLE_ITEM = SIZE_ITEM * 2;
// ���������� ��������

namespace idItem {
	enum
	{
		// ���������� ��������
		emptyItem,
		airItem,
		// �����
		grassItem,
		dirtItem,
		sandItem,
		logOakItem,
		stoneItem,
		stoneBrickItem,
		planksBlockItem,
		woodLadderItem,
		// �������
		seadlingOakItem,
		seadlingApple,
		// ���
		mushroomItem,
		rawMeatWolfItem,
		roastMeatWolfItem,
		appleItem,
		// �����������
		stonePickaxItem,
		stoneAxeItem,
		ironBackHoerItem,
		ironAxeItem,
		ironPickaxItem,
		// ����
		stoneKnifeItem,
		ironSwordItem,
		silverSwordItem,
		// ������
		woodClubItem,
		ironClubItem,
		// ������ � ����� � ���
		glassBottleItem,
		glassbukketWithWater,
		woodBukketItem,
		woodBukketWithWaterItem,

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
	bottleEmpty,
	bottleWithWater,
	healthPotion,
	bukketWithWater,
	bukketEmpty,
	weapon,
	axe,
	backhoe,
	amounCategory
} idCategoryItem;