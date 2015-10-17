#pragma once
#include <SFML\Graphics.hpp>

const int MAX_ITEMS = 256;
const int AMOUNT_TYPES_ITEM = 15;

const sf::Vector2f scaleItems = { 0.5f, 0.5f };
const sf::Vector2f normalSize = { 2.f, 2.f };
//
// smallStoneItem - камешек
const int WIDTH_SMALL_STONE = 34;
const int HEIGHT_SMALL_STONE = 24;

// mushroom - гриЅ
const int WIDTH_MUSHROOM = 21;
const int HEIGHT_MUSHROOM = 17;
const int PIXEL_X_MUSHROOM = 0;
const int PIXEL_Y_MUSHROOM = HEIGHT_SMALL_STONE;

typedef enum
{
	smallStoneItem,// камешек
	mushroom,
	emptyItem
} idItem;