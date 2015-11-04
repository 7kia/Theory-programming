#include <SFML\Graphics.hpp>

#include "BlocksVar.h"
#include "UnlifeObject.h"
#include "Items.h"

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

	wchar_t (*dataMap)[LONG_MAP][WIDTH_MAP];// �����
	int countBlocks = 0;
	wchar_t (*charBlocks);// ���������� ����������� ������
	int (*coordinateBloks)[NUMBER_COORDINATES];// ���������� ����������
	//const sf::String (*nameBlocks) = namesBlocks;

	sf::Sprite *floorSprite;
	sf::Texture *floorTexture;

	sf::Sprite *wallSprite;
	sf::Texture *wallTexture;

	void initializeDataBlocks();// ������ ������
	void setSprite(sf::Sprite *sprite, int l, int i, int j);// ������� �������
	void setTypeSprite(int personLevelFloor, int l, int i, int j);// ������ ��� ��� �����?
	sf::String findCharBlocks(wchar_t block);
	int findIdBlock(wchar_t block);
};

void initializeField(Field & field);
void readMap(wchar_t(*dataMap)[LONG_MAP][WIDTH_MAP], const char *fileName);
void writeMap(wchar_t(*dataMap)[LONG_MAP][WIDTH_MAP]);// TODO