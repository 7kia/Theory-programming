#include <SFML\Graphics.hpp>

#include "GlobalVar.h"

using namespace sf;

struct Field
{
	int BLOCK_SIZE = sizeTile;

	wchar_t (*dataMap)[LongMap][WidthMap];
	wchar_t charBlocks[256];
	int coordinateBloks[256][2];

	Sprite *floorSprite;
	Texture *floorTexture;

	Sprite *wallSprite;
	Texture *wallTexture;

	void dataBlocks();// ������ ������
	void setSprite(Sprite *sprite, int l, int i, int j);// ������� �������
	void setTypeSprite(int personLevelFloor, int l, int i, int j);// ������ ��� ��� �����?
	void resetSprites();
};

void initializeField(Field & field);
void readMap(wchar_t(*dataMap)[LongMap][WidthMap], const char *fileName);