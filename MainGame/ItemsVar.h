#pragma once
#include <SFML\Graphics.hpp>

#include "BlocksVar.h"

const int MAX_ITEMS = 256;
const int AMOUNT_TYPES_ITEM = 15;

const sf::Vector2f scaleItems = { 0.75f, 0.75f };
const sf::Vector2f normalSize = { 1.34f, 1.34f };

const int SIZE_ITEM = SIZE_BLOCK;

// stoneItem - Камень
const int PIXEL_X_SMALL_STONE = SIZE_ITEM * 2;
const int PIXEL_Y_SMALL_STONE = SIZE_ITEM;

// mushroom - гриБ
const int PIXEL_X_MUSHROOM = 0;
const int PIXEL_Y_MUSHROOM = SIZE_ITEM;

// planks - доски
const int PIXEL_X_PLANKS = SIZE_ITEM;
const int PIXEL_Y_PLANKS = SIZE_ITEM;

// dirt - земля
const int PIXEL_X_DIRT = 0;
const int PIXEL_Y_DIRT = SIZE_ITEM * 2;

// sand - песок
const int PIXEL_X_SAND = 0;
const int PIXEL_Y_SAND = SIZE_ITEM * 3;

// logOak ladder - деревянная лестница
const int PIXEL_X_WOOD_LADDER = SIZE_ITEM * 2;
const int PIXEL_Y_WOOD_LADDER = SIZE_ITEM * 2;

// strone brick - каменные кирпичи
const int PIXEL_X_STONE_BRICK = SIZE_ITEM * 3;
const int PIXEL_Y_STONE_BRICK = SIZE_ITEM;

// grass brick - блок земли с травой
const int PIXEL_X_GRASS_BRICK = SIZE_ITEM;
const int PIXEL_Y_GRASS_BRICK = SIZE_ITEM * 2;

// log Oak - дубовое бревно
const int PIXEL_X_LOG_OAK = 0;
const int PIXEL_Y_LOG_OAK = 0;

// stone pickax - каменная кирка
const int PIXEL_X_STONE_PICKAX = SIZE_ITEM * 3;
const int PIXEL_Y_STONE_PICKAX = SIZE_ITEM * 3;

// stone axe - каменный топор
const int PIXEL_X_STONE_AXE = SIZE_ITEM * 5;
const int PIXEL_Y_STONE_AXE = SIZE_ITEM * 3;

// ДОБАВЛЕНИЕ ПРЕДМЕТА

typedef enum
{
	// ДОБАВЛЕНИЕ ПРЕДМЕТА
	stoneItem,// Камень
	planksBlockItem,
	dirtItem,
	grassItem,
	sandItem,
	woodLadderItem,
	stoneBrickItem,
	mushroom,
	logOakItem,
	stonePickaxItem,
	stoneAxeItem,
	emptyItem
} idItem;

typedef enum
{
	other,
	food,
	block,
	pickax,
	axe
} idCategoryItem;