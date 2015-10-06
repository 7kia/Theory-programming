#include "Map.h"

using namespace sf;

void initializeField(Field & field)
{
	field.BLOCK_SIZE = sizeTile;

	////////////////////////////////////////////
	// Загрузка карты
	field.dataMap = new wchar_t[HeightMap][LongMap][WidthMap];

	readMap(field.dataMap, "file.map");
	for (size_t i = 0; i < HeightMap; i++)
	{
		for (size_t j = 0; j < LongMap; j++)
		{
			printf("%ws\n", field.dataMap[i][j]);
		}
	}
	////////////////////////////////////////////

	field.dataBlocks();

	field.floorSprite = new Sprite;
	field.floorTexture = new Texture;
	field.floorTexture->loadFromFile(pathFloor);
	field.floorSprite->setTexture(*field.floorTexture);

	field.wallSprite = new Sprite;
	field.wallTexture = new Texture;
	field.wallTexture->loadFromFile(pathWall);
	field.wallSprite->setTexture(*field.wallTexture);
}

//////////////////////////////////////////////////////////////////////
// Данные блоков
void Field::dataBlocks()
{
	charBlocks[idBlocks::air] = u'\x020';

	charBlocks[idBlocks::grass] = u'\x010';
	coordinateBloks[idBlocks::grass][0] = 0;
	coordinateBloks[idBlocks::grass][1] = 0;

	charBlocks[idBlocks::dirt] = u'\x011';
	coordinateBloks[idBlocks::dirt][0] = 0;
	coordinateBloks[idBlocks::dirt][1] = BLOCK_SIZE;

	charBlocks[idBlocks::stone] = u'\x012';
	coordinateBloks[idBlocks::stone][0] = 0;
	coordinateBloks[idBlocks::stone][1] = BLOCK_SIZE * 2;

	charBlocks[idBlocks::sand] = u'\x013';
	coordinateBloks[idBlocks::sand][0] = 0;
	coordinateBloks[idBlocks::sand][1] = BLOCK_SIZE * 3;

	charBlocks[idBlocks::water] = u'\x014';
	coordinateBloks[idBlocks::water][0] = BLOCK_SIZE;
	coordinateBloks[idBlocks::water][1] = 0;

	charBlocks[idBlocks::woodBoard] = u'\x015';
	coordinateBloks[idBlocks::woodBoard][0] = BLOCK_SIZE * 2;
	coordinateBloks[idBlocks::woodBoard][1] = 0;

	charBlocks[idBlocks::stoneBrick] = u'\x016';
	coordinateBloks[idBlocks::stoneBrick][0] = BLOCK_SIZE;
	coordinateBloks[idBlocks::stoneBrick][1] = BLOCK_SIZE * 2;


	charBlocks[idBlocks::woodLadder] = u'\x021';
	coordinateBloks[idBlocks::woodLadder][0] = BLOCK_SIZE * 2;
	coordinateBloks[idBlocks::woodLadder][1] = BLOCK_SIZE;



	coordinateBloks[idBlocks::unknow][0] = BLOCK_SIZE * 7;
	coordinateBloks[idBlocks::unknow][1] = BLOCK_SIZE * 7;

}
//////////////////////////////////////////////////////////////////////

void Field::setTypeSprite(int personLevelFloor, int l, int i, int j)
{
	if (l == personLevelFloor)
	{
		setSprite(floorSprite, l, i, j);
	}
	else if (l == personLevelFloor + 1)
	{
		setSprite(wallSprite, l, i, j);
	}

}

void Field::setSprite(Sprite *sprite, int l, int i, int j)
{
	int id(2);
	for (id = 2; id < idBlocks::amountKnowBlocks; id++)
	{
		if (dataMap[l][i][j] == charBlocks[id])
		{
			sprite->setTextureRect(IntRect(coordinateBloks[id][0], coordinateBloks[id][1], BLOCK_SIZE, BLOCK_SIZE));
			id = 0;
			break;
		}
	}

	// Воздух отдельно обрабатывакм
	if(dataMap[l][i][j] == charBlocks[idBlocks::air])
	{
		sprite->setTextureRect(IntRect(0, 0, 0, 0));
	}
	else if(id == idBlocks::amountKnowBlocks)
	{
		sprite->setTextureRect(IntRect(coordinateBloks[idBlocks::unknow][0], coordinateBloks[idBlocks::unknow][1], BLOCK_SIZE, BLOCK_SIZE));
	}


	sprite->setPosition(j * BLOCK_SIZE, i * BLOCK_SIZE);
}

void Field::resetSprites()
{
	floorSprite->setTextureRect(IntRect(0, 0, 0, 0));
	wallSprite->setTextureRect(IntRect(0, 0, 0, 0));
}

void readMap(wchar_t(*dataMap)[LongMap][WidthMap], const char *fileName)
{
	FILE *pMapFile;
	errno_t eMapFile = fopen_s(&pMapFile, fileName, "r");

	//const int size(50);
	wchar_t buff[4];
	int countLevel;

	if (pMapFile)
	{
		for (size_t i = 0; i < HeightMap; i++)
		{
			countLevel = 0;
			while (!feof(pMapFile) && countLevel < LongMap)
			{
				fgetws(dataMap[i][countLevel], WidthMap, pMapFile);
				fgetws(buff, 3, pMapFile);//Пропускаем остальную часть строки
				countLevel++;
			}
			fgetws(buff, 4, pMapFile);//Пропускаем строку

		}

	}
	else
	{
		printf("File not find!\n");
	}
}