#include "Map.h"
#include "../Recourses.h"

using namespace sf;
using namespace std;

Field::Field()
{
	readMap("file.map");
	initializeDataBlocks();
	initializeSpriteBlocks();
}

void Field::initializeSpriteBlocks()
{
	floorTexture.loadFromFile(texturePaths[idTexturePaths::mapFloorPath]);
	floorSprite.setTexture(floorTexture);

	wallTexture.loadFromFile(texturePaths[idTexturePaths::mapWallPath]);
	wallSprite.setTexture(wallTexture);
}

void Field::initializeDataBlocks()
{
	charBlocks[idBlocks::air] = u'\x020';
	idsNature[idBlocks::air] = idNatureObject::Unbreaking;

	charBlocks[idBlocks::grass] = u'\x010';
	coordinateBloks[idBlocks::grass][0] = 0;
	coordinateBloks[idBlocks::grass][1] = 0;
	idsNature[idBlocks::grass] = idNatureObject::groundNature;
	toughness[idBlocks::grass] = 40;

	charBlocks[idBlocks::dirt] = u'\x011';
	coordinateBloks[idBlocks::dirt][0] = 0;
	coordinateBloks[idBlocks::dirt][1] = SIZE_BLOCK;
	idsNature[idBlocks::dirt] = idNatureObject::groundNature;
	toughness[idBlocks::dirt] = 40;

	charBlocks[idBlocks::stone] = u'\x012';
	coordinateBloks[idBlocks::stone][0] = 0;
	coordinateBloks[idBlocks::stone][1] = SIZE_BLOCK * 2;
	idsNature[idBlocks::stone] = idNatureObject::stoneNature;
	toughness[idBlocks::stone] = 360;

	charBlocks[idBlocks::sand] = u'\x013';
	coordinateBloks[idBlocks::sand][0] = 0;
	coordinateBloks[idBlocks::sand][1] = SIZE_BLOCK * 3;
	idsNature[idBlocks::sand] = idNatureObject::sandNature;
	toughness[idBlocks::sand] = 20;

	charBlocks[idBlocks::water] = u'\x014';
	coordinateBloks[idBlocks::water][0] = SIZE_BLOCK;
	coordinateBloks[idBlocks::water][1] = 0;
	idsNature[idBlocks::water] = idNatureObject::waterNature;
	toughness[idBlocks::water] = 1;

	charBlocks[idBlocks::logOak] = u'\x015';
	coordinateBloks[idBlocks::logOak][0] = SIZE_BLOCK * 3;
	coordinateBloks[idBlocks::logOak][1] = 0;
	idsNature[idBlocks::logOak] = idNatureObject::woodNature;
	toughness[idBlocks::logOak] = 160;

	charBlocks[idBlocks::planksBlock] = u'\x016';
	coordinateBloks[idBlocks::planksBlock][0] = SIZE_BLOCK * 2;
	coordinateBloks[idBlocks::planksBlock][1] = 0;
	idsNature[idBlocks::planksBlock] = idNatureObject::woodNature;
	toughness[idBlocks::planksBlock] = 220;

	charBlocks[idBlocks::stoneBrick] = u'\x017';
	coordinateBloks[idBlocks::stoneBrick][0] = SIZE_BLOCK;
	coordinateBloks[idBlocks::stoneBrick][1] = SIZE_BLOCK * 2;
	idsNature[idBlocks::stoneBrick] = idNatureObject::stoneNature;
	toughness[idBlocks::stoneBrick] = 600;

	charBlocks[idBlocks::woodLadder] = u'\x018';
	coordinateBloks[idBlocks::woodLadder][0] = SIZE_BLOCK * 2;
	coordinateBloks[idBlocks::woodLadder][1] = SIZE_BLOCK;
	idsNature[idBlocks::woodLadder] = idNatureObject::woodNature;
	toughness[idBlocks::woodLadder] = 100;

	charBlocks[idBlocks::borderBlock] = u'\x019';
	coordinateBloks[idBlocks::borderBlock][0] = SIZE_BLOCK * 6;
	coordinateBloks[idBlocks::borderBlock][1] = SIZE_BLOCK * 7;
	idsNature[idBlocks::borderBlock] = idNatureObject::Unbreaking;
	toughness[idBlocks::borderBlock] = 1;

	coordinateBloks[idBlocks::unknow][0] = SIZE_BLOCK * 7;
	coordinateBloks[idBlocks::unknow][1] = SIZE_BLOCK * 7;
	idsNature[idBlocks::unknow] = idNatureObject::stoneNature;
	toughness[idBlocks::unknow] = 10;
}

void Field::setTypeSprite(int personLevelFloor, int l, int i, int j)
{
	if (l == personLevelFloor - 1) {
		floorSprite.setColor(DOWN_VIEW);
		setSprite(floorSprite, l, i, j);
		wallSprite.setTextureRect(IntRect(0, 0, 0, 0));
	}
	else if (l == personLevelFloor)
	{
		floorSprite.setColor(NORMAL_VIEW);
		setSprite(floorSprite, l, i, j);
		wallSprite.setTextureRect(IntRect(0, 0, 0, 0));
	}
	else if (l == personLevelFloor + 1)
	{
		wallSprite.setColor(NORMAL_VIEW);
		setSprite(wallSprite, l, i, j);
		floorSprite.setTextureRect(IntRect(0, 0, 0, 0));
	}
	else if (l == personLevelFloor + 2) {
		wallSprite.setColor(UP_VIEW);
		setSprite(wallSprite, l, i, j);
		floorSprite.setTextureRect(IntRect(0, 0, 0, 0));
	}
};

String Field::findCharBlocks(wchar_t block)
{
	for (int i = idBlocks::air; i < idBlocks::amountKnowBlocks; i++) {
		if (block == charBlocks[i]) {
			return namesBlocks[i];
		}
		
	}
	return namesBlocks[idBlocks::unknow];
}

int Field::findIdBlock(wchar_t block)
{
	for (int i = idBlocks::air; i < idBlocks::amountKnowBlocks; i++) {
		if (block == charBlocks[i]) {
			return i + shiftForItem;
		}

	}
	return idBlocks::unknow;
};

void Field::setSprite(Sprite &sprite, int l, int i, int j)
{
	int id;
	for (id = idBlocks::air + 1; id < idBlocks::amountKnowBlocks; id++)
	{
		if (dataMap[l][i][j] == charBlocks[id])
		{
			sprite.setTextureRect(IntRect(coordinateBloks[id][0], coordinateBloks[id][1], SIZE_BLOCK, SIZE_BLOCK));
			id = 0;
			break;
		}
	}

	// Неизвестные блоки и воздух обрабатываем отдельно
	if(dataMap[l][i][j] == charBlocks[idBlocks::air])
	{
		sprite.setTextureRect(IntRect(0, 0, 0, 0));
	}
	else if(id == idBlocks::amountKnowBlocks)
	{
		int unknowXPos = coordinateBloks[idBlocks::unknow][0];
		int unknowYpos = coordinateBloks[idBlocks::unknow][1];
		sprite.setTextureRect(IntRect(unknowXPos, unknowYpos, SIZE_BLOCK, SIZE_BLOCK));
	}

	sprite.setPosition(float(j * SIZE_BLOCK), float(i * SIZE_BLOCK));
}

void Field::readMap(const char *fileName)
{
	FILE *pMapFile;
	errno_t eMapFile = fopen_s(&pMapFile, fileName, "r");

	const int amountHelpSymblos = 4;
	wchar_t buff[amountHelpSymblos];
	int countLevel;

	if (eMapFile == 0)
	{
		for (size_t i = 0; i < HEIGHT_MAP; i++)
		{
			countLevel = 0;
			while (!feof(pMapFile) && countLevel < LONG_MAP)
			{
				fgetws(dataMap[i][countLevel], WIDTH_MAP, pMapFile);
				fgetws(buff, amountHelpSymblos, pMapFile);//Пропускаем остальную часть строки
				countLevel++;
			}
			fgetws(buff, amountHelpSymblos, pMapFile);//Пропускаем строку
		}

	}
	else
	{
		printf("File not find!\n");
	}
}