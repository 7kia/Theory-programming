#include <SFML\Graphics.hpp>

#include "BlocksVar.h"
#include "UnlifeObject.h"

const sf::String namesBlocks[idBlocks::amountKnowBlocks] =
{
	"Unknow",
	"Air",
	"Grass",
	"Dirt",
	"Sand",
	"Water",
	"Log oak",
	"Stone",
	"Stone brick",
	"Planks",
	"Wood ladder"
};

struct Field
{
	int BLOCK_SIZE;

	wchar_t (*dataMap)[LONG_MAP][WIDTH_MAP];// Карта
	int countBlocks = 0;
	wchar_t (*charBlocks);// символьное обозначение блоков
	int (*coordinateBloks)[NUMBER_COORDINATES];// текстурные координаты
	//const sf::String (*nameBlocks) = namesBlocks;

	sf::Sprite *floorSprite;
	sf::Texture *floorTexture;

	sf::Sprite *wallSprite;
	sf::Texture *wallTexture;

	void initializeDataBlocks();// Данные блоков
	void setSprite(sf::Sprite *sprite, int l, int i, int j);// Окраска спрайта
	void setTypeSprite(int personLevelFloor, int l, int i, int j);// Красим пол или стены?
	sf::String findCharBlocks(wchar_t block);
	int findIdBlock(wchar_t block);
};

void initializeField(Field & field);
void readMap(wchar_t(*dataMap)[LONG_MAP][WIDTH_MAP], const char *fileName);
void writeMap(wchar_t(*dataMap)[LONG_MAP][WIDTH_MAP]);// TODO