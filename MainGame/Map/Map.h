#include <SFML\Graphics.hpp>

#include "BlocksVar.h"
#include "../UnlifeObject/UnlifeObject.h"
#include "../Recourses.h"

const sf::Color UP_VIEW(255, 255, 255, 150);
const sf::Color NORMAL_VIEW(255, 255, 255, 255);
const sf::Color DOWN_VIEW(127, 127, 127, 255);

const sf::String namesBlocks[idBlocks::amountKnowBlocks] =
{
	"Unknow",
	"Air",
	"Grass",
	"Dirt",
	"Sand",
	"Log oak",
	"Stone",
	"Stone brick",
	"Planks",
	"Wood ladder",
	"Water"
};

struct Field
{
	Field();

	wchar_t dataMap[HEIGHT_MAP][LONG_MAP][WIDTH_MAP];// Карта
	int countBlocks = 0;
	int idsNature[NUMBER_TYPE_BLOCKS];
	wchar_t charBlocks[NUMBER_TYPE_BLOCKS];// символьное обозначение блоков
	int coordinateBloks[NUMBER_TYPE_BLOCKS][NUMBER_COORDINATES];// текстурные координаты
	int toughness[NUMBER_TYPE_BLOCKS];

	sf::Sprite floorSprite;
	sf::Texture floorTexture;

	sf::Sprite wallSprite;
	sf::Texture wallTexture;

	void initializeDataBlocks();
	void initializeSpriteBlocks();
	void setSprite(sf::Sprite &sprite, int l, int i, int j);// Окраска спрайта
	void readMap(const char* fileName);
	void setTypeSprite(int personLevelFloor, int l, int i, int j);// Красим пол или стены?
	sf::String findCharBlocks(wchar_t block);
	int findIdBlock(wchar_t block);
};
