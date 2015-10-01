#include "Map.h"

void initializeField(Field & field)
{
	field.BLOCK_SIZE = sizeTile;

	field.currentFloorLevel = 0;
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
	field.floorTexture->loadFromFile("recourses\\images\\mapFloor.png");
	field.floorSprite->setTexture(*field.floorTexture);

	field.wallSprite = new Sprite;
	field.wallTexture = new Texture;
	field.wallTexture->loadFromFile("recourses\\images\\mapWall.png");
	field.wallSprite->setTexture(*field.wallTexture);
}



//////////////////////////////////////////////////////////////////////
// Данные блоков
void Field::dataBlocks()
{
	charBlocks[idBlocks::grass] = u'\x010';
	coordinateBloks[idBlocks::grass][0] = 0;
	coordinateBloks[idBlocks::grass][1] = 0;

	charBlocks[idBlocks::dirt] = u'\x011';
	coordinateBloks[idBlocks::dirt][0] = 0;
	coordinateBloks[idBlocks::dirt][1] = BLOCK_SIZE;

	charBlocks[idBlocks::stone] = u'\x012';
	coordinateBloks[idBlocks::stone][0] = 0;
	coordinateBloks[idBlocks::stone][1] = BLOCK_SIZE * 2;

	charBlocks[idBlocks::water] = u'\x013';
	coordinateBloks[idBlocks::water][0] = BLOCK_SIZE;
	coordinateBloks[idBlocks::water][1] = 0;

	charBlocks[idBlocks::woodBoard] = u'\x014';
	coordinateBloks[idBlocks::woodBoard][0] = BLOCK_SIZE * 2;
	coordinateBloks[idBlocks::woodBoard][1] = 0;
}
//////////////////////////////////////////////////////////////////////

void Field::setTypeSprite(int &l, int &i, int &j)
{
	if (l == currentFloorLevel)
	{
		setSprite(floorSprite, l, i, j);
	}
	else
	{
		setSprite(wallSprite, l, i, j);
	}

}

void Field::setSprite(Sprite *sprite, int &l, int &i, int &j)
{
	if (dataMap[l][i][j] == charBlocks[idBlocks::grass])
	{
		sprite->setTextureRect(IntRect(coordinateBloks[idBlocks::grass][0], coordinateBloks[idBlocks::grass][1], BLOCK_SIZE, BLOCK_SIZE));
	}
	else if (dataMap[l][i][j] == charBlocks[idBlocks::dirt])
	{
		sprite->setTextureRect(IntRect(coordinateBloks[idBlocks::dirt][0], coordinateBloks[idBlocks::dirt][1], BLOCK_SIZE, BLOCK_SIZE));
	}
	else if (dataMap[l][i][j] == charBlocks[idBlocks::stone])
	{
		sprite->setTextureRect(IntRect(coordinateBloks[idBlocks::stone][0], coordinateBloks[idBlocks::stone][1], BLOCK_SIZE, BLOCK_SIZE));
	}
	else if (dataMap[l][i][j] == charBlocks[idBlocks::water])
	{
		sprite->setTextureRect(IntRect(coordinateBloks[idBlocks::water][0], coordinateBloks[idBlocks::water][1], BLOCK_SIZE, BLOCK_SIZE));
	}
	else if (dataMap[l][i][j] == charBlocks[idBlocks::woodBoard])
	{
		sprite->setTextureRect(IntRect(coordinateBloks[idBlocks::woodBoard][0], coordinateBloks[idBlocks::woodBoard][1], BLOCK_SIZE, BLOCK_SIZE));
	}
	else
	{
		sprite->setTextureRect(IntRect(0, 0, 0, 0));
	}

	sprite->setPosition(j * BLOCK_SIZE, i * BLOCK_SIZE);
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