#include <SFML\Graphics.hpp>

#define border1 1
#define LongMap 25//������ ����� ������
#define WidthMap 40 + border1//������ ����� ������ 
#define HeightMap 2
#define sizeTile 32

using namespace sf;

typedef enum
{
	grass,
	dirt,
	water,
	wood,
	stone,
	woodBoard
} idBlocks;

struct Field
{
	int BLOCK_SIZE;

	wchar_t (*dataMap)[LongMap][WidthMap];
	wchar_t charBlocks[256];
	int coordinateBloks[256][2];

	int currentFloorLevel;// ������� � ������ �� ������

	Sprite *floorSprite;
	Texture *floorTexture;

	Sprite *wallSprite;
	Texture *wallTexture;

	void dataBlocks();// ������ ������
	void setSprite(Sprite *sprite, int &l, int &i, int &j);// ������� �������
	void setTypeSprite(int &l, int &i, int &j);// ������ ��� ��� �����?
};

void initializeField(Field & field);
void readMap(wchar_t(*dataMap)[LongMap][WidthMap], const char *fileName);