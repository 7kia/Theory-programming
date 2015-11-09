#pragma once
#include <vector>

struct sizeSprite
{
	int width;
	int height;
	void init(int w, int h);
};

struct pixelPosSprite
{
	int x;
	int y;
	void init(int xPos, int yPos);
};
struct featuresSprite
{
	sizeSprite size;
	pixelPosSprite pixPos;
	void init(int w, int h, int xPixPos, int yPixPos);
};


struct objectDropItems
{
	std::vector<int> minCountItems;
	std::vector<int> maxCountItems;
	std::vector<int> dropItems;
	void addItem( int min, int max, int id);
	void init(objectDropItems drop);
	void clear();
};