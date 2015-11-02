#include "Map.h"

using namespace sf;
using namespace std;

void initializeField(Field & field)
{
	field.charBlocks = new wchar_t[NUMBER_TYPE_BLOCKS];
	field.coordinateBloks = new int[NUMBER_TYPE_BLOCKS][NUMBER_COORDINATES];

	field.BLOCK_SIZE = SIZE_BLOCK;

	////////////////////////////////////////////
	// Загрузка карты
	field.dataMap = new wchar_t[HEIGHT_MAP][LONG_MAP][WIDTH_MAP];

	readMap(field.dataMap, "file.map");
	for (size_t i = 0; i < HEIGHT_MAP; i++)
	{
		for (size_t j = 0; j < LONG_MAP; j++)
		{
			//printf("%ws\n", field.dataMap[i][j]);
		}
	}
	////////////////////////////////////////////

	field.initializeDataBlocks();

	field.floorSprite = new Sprite;
	field.floorTexture = new Texture;
	field.floorTexture->loadFromFile(texturePaths[idTexturePaths::mapFloor]);
	field.floorSprite->setTexture(*field.floorTexture);

	field.wallSprite = new Sprite;
	field.wallTexture = new Texture;
	field.wallTexture->loadFromFile(texturePaths[idTexturePaths::mapWall]);
	field.wallSprite->setTexture(*field.wallTexture);
}

//////////////////////////////////////////////////////////////////////
// Данные блоков
void Field::initializeDataBlocks()
{
	charBlocks[idBlocks::air] = u'\x020';

	//////////////////////////////////
	// Символьное обозначение
	// Текстурные координаты x
	// Текстурные координаты y
	//////////////////////////////////
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

	charBlocks[idBlocks::logOak] = u'\x015';
	coordinateBloks[idBlocks::logOak][0] = BLOCK_SIZE * 3;
	coordinateBloks[idBlocks::logOak][1] = 0;

	charBlocks[idBlocks::planksBlock] = u'\x016';
	coordinateBloks[idBlocks::planksBlock][0] = BLOCK_SIZE * 2;
	coordinateBloks[idBlocks::planksBlock][1] = 0;

	charBlocks[idBlocks::stoneBrick] = u'\x017';
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
	if (l == personLevelFloor - 1) {
		floorSprite->setColor(DOWN_VIEW);
		setSprite(floorSprite, l, i, j);
		wallSprite->setTextureRect(IntRect(0, 0, 0, 0));
	}
	else if (l == personLevelFloor)
	{
		floorSprite->setColor(NORMAL_VIEW);
		setSprite(floorSprite, l, i, j);
		wallSprite->setTextureRect(IntRect(0, 0, 0, 0));
	}
	else if (l == personLevelFloor + 1)
	{
		wallSprite->setColor(NORMAL_VIEW);
		setSprite(wallSprite, l, i, j);
		floorSprite->setTextureRect(IntRect(0, 0, 0, 0));
	}
	else if (l == personLevelFloor + 2) {
		wallSprite->setColor(UP_VIEW);
		setSprite(wallSprite, l, i, j);
		floorSprite->setTextureRect(IntRect(0, 0, 0, 0));
	}
};

String Field::findCharBlocks(wchar_t block)
{
	for (int i = 1; i < idBlocks::amountKnowBlocks; i++) {
		if (block == charBlocks[i]) {
			return namesBlocks[i];
		}
		
	}
	return namesBlocks[idBlocks::unknow];
}

/*

*/
int Field::findIdBlock(wchar_t block)
{
	for (int i = 1; i < idBlocks::amountKnowBlocks; i++) {
		if (block == charBlocks[i]) {
			return i + shiftForItem;
		}

	}
	return idBlocks::unknow;
};

//////////////////////////////////////////////////////
// Отрисовка блоков
void Field::setSprite(Sprite *sprite, int l, int i, int j)
{
	// Обработка блоков
	int id(2);// потому-что 0 - unknow, 1 - air
	for (id = 2; id < idBlocks::amountKnowBlocks; id++)
	{
		if (dataMap[l][i][j] == charBlocks[id])
		{
			sprite->setTextureRect(IntRect(coordinateBloks[id][0], coordinateBloks[id][1], BLOCK_SIZE, BLOCK_SIZE));
			id = 0;
			break;
		}
	}

	// Неизвестные блоки и воздух обрабатываем отдельно
	if(dataMap[l][i][j] == charBlocks[idBlocks::air])
	{
		sprite->setTextureRect(IntRect(0, 0, 0, 0));
	}
	else if(id == idBlocks::amountKnowBlocks)
	{
		int unknowXPos = coordinateBloks[idBlocks::unknow][0];
		int unknowYpos = coordinateBloks[idBlocks::unknow][1];
		sprite->setTextureRect(IntRect(unknowXPos, unknowYpos, BLOCK_SIZE, BLOCK_SIZE));
	}

	sprite->setPosition(j * BLOCK_SIZE, i * BLOCK_SIZE);
}
//////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Открытие карты
void readMap(wchar_t(*dataMap)[LONG_MAP][WIDTH_MAP], const char *fileName)
{
	FILE *pMapFile;
	errno_t eMapFile = fopen_s(&pMapFile, fileName, "r");

	const int amountHelpSymblos = 4;
	wchar_t buff[amountHelpSymblos];
	int countLevel;

	// Если файл открыт
	if (pMapFile)
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
////////////////////////////////////////////////////////////////////////////////
// Запись карты
void writeMap(wchar_t(*dataMap)[LONG_MAP][WIDTH_MAP])
{
	FILE *pMapFile;
	errno_t eMapFile = fopen_s(&pMapFile, "map.txt", "w");// TODO

	const int amountHelpSymblos = 4;
	int countLevel;

	// Если файл открыт
	if (pMapFile) {
		for (size_t i = 0; i < HEIGHT_MAP; i++) {
			countLevel = 0;
			while (!feof(pMapFile) && countLevel < LONG_MAP) {
				fputws(dataMap[i][countLevel], pMapFile);
				//fgetws(buff, amountHelpSymblos, pMapFile);//Пропускаем остальную часть строки
				countLevel++;
			}
			//fgetws(buff, amountHelpSymblos, pMapFile);//Пропускаем строку
		}

	} else {

		printf("File not find!\n");
	}
}
////////////////////////////////////////////////////////////////////////////////