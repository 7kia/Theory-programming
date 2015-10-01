#include <SFML\Graphics.hpp>

#define border1 1
#define LongMap 25//размер карты высота
#define WidthMap 40 + border1//размер карты ширина 
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

	int currentFloorLevel;// Начиная с какого мы рисуем

	Sprite *floorSprite;
	Texture *floorTexture;

	Sprite *wallSprite;
	Texture *wallTexture;

	void dataBlocks();// Данные блоков
	void setSprite(Sprite *sprite, int &l, int &i, int &j);// Окраска спрайта
	void setTypeSprite(int &l, int &i, int &j);// Красим пол или стены?
};

void initializeField(Field & field);
void readMap(wchar_t(*dataMap)[LongMap][WidthMap], const char *fileName);