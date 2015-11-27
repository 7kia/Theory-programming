#include "CommonStructs.h"

using namespace std;


void sizeSprite::init(int w, int h)
{
	width = w;
	height = h;
}

void pixelPosSprite::init(int xPos, int yPos)
{
	x = xPos;
	y = yPos;
}

void featuresSprite::init(int w, int h, int xPixPos, int yPixPos)
{
	size.width = w;
	size.height = h;
	pixPos.x = xPixPos;
	pixPos.y = yPixPos;
}

void objectDropItems::addItem(int min, int max, int id)
{
	minCountItems.push_back(min);
	maxCountItems.push_back(max);
	dropItems.push_back(id);
}

void objectDropItems::init(objectDropItems drop)
{
	size_t size = drop.dropItems.size();
	for (int i = 0; i < size; i++) {
		dropItems.push_back(drop.dropItems[i]);
		minCountItems.push_back(drop.minCountItems[i]);
		maxCountItems.push_back(drop.maxCountItems[i]);
	}

}

void objectDropItems::clear()
{
	dropItems.clear();
	minCountItems.clear();
	maxCountItems.clear();
}
