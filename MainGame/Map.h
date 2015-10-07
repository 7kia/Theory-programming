#include <SFML\Graphics.hpp>

#include "GlobalVar.h"

struct Field
{
	int BLOCK_SIZE = sizeTile;

	wchar_t (*dataMap)[LongMap][WidthMap];// Карта
	wchar_t charBlocks[256];// символьное обозначение блоков
	int coordinateBloks[256][2];// текстурные координаты

	sf::Sprite *floorSprite;
	sf::Texture *floorTexture;

	sf::Sprite *wallSprite;
	sf::Texture *wallTexture;

	void initializeDataBlocks();// Данные блоков
	void setSprite(sf::Sprite *sprite, int l, int i, int j);// Окраска спрайта
	void setTypeSprite(int personLevelFloor, int l, int i, int j);// Красим пол или стены?
};

void initializeField(Field & field);
void readMap(wchar_t(*dataMap)[LongMap][WidthMap], const char *fileName);