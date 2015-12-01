#include <SFML\Graphics.hpp>

#include "BlocksVar.h"
#include "../UnlifeObject/UnlifeObject.h"

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
	int BLOCK_SIZE;

	wchar_t (*dataMap)[LONG_MAP][WIDTH_MAP];// �����
	int countBlocks = 0;
	int (*idsNature);
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