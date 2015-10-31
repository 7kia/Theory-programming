// MapGenerator1.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream> //cin cout setlocale

using namespace std;

#define border1 3
#define LongMap 25//размер карты высота
#define WidthMap 40 + border1//размер карты ширина 
#define HeightMap 4
#define sizeTile 32

void writeMap(const char *fileName)
{
	FILE *pMapFile;
	errno_t eMapFile = fopen_s(&pMapFile, fileName, "w");

	wchar_t inputChar; 
	wchar_t inputString[40 + border1];
	wchar_t inputString2[40 + border1];
	int countLevel;


	// Создание 1 строки
	for (size_t i = 0; i < WidthMap - border1; i++)
	{
		inputChar = u'\x010';
		inputChar += 1;
		inputString[i] = inputChar;
	}
	/////////////////////////////////////////////

	inputString[0] = u'\x010';

	inputString[1] = u'\x011';


	inputString[2] = u'\x012';


	inputString[3] = u'\x013';


	inputString[4] = u'\x014';


	inputString[5] = u'\x015';
	

	inputString[6] = u'\x016';


	inputString[7] = u'\x017';



	inputString[8] = u'\x021';
	/////////////////////////////////////////////
	inputString[WidthMap - border1] = u'"';
	inputString[WidthMap - border1 + 1] = u'\n';
	inputString[WidthMap - border1 + 2] = u'\0';

	// Создание 2 строки
	for (size_t i = 0; i < WidthMap - border1; i++)
	{
		inputChar = u'\x020';
		inputString2[i] = inputChar;
	}
	inputString2[WidthMap - border1] = u'"';
	inputString2[WidthMap - border1 + 1] = u'\n';
	inputString2[WidthMap - border1 + 2] = u'\0';

	// Запись в файл
	if (pMapFile)
	{
		for (size_t i = 0; i < HeightMap; i++)
		{
			countLevel = 0;
			///*
			while (!feof(pMapFile) && countLevel < LongMap)
			{	
				if (i)
				{
					fputws(inputString2, pMapFile);
				}
				else
				{
					fputws(inputString, pMapFile);
				}
				

				
				countLevel++;
			}
			fputwc(inputString[WidthMap - border1 + 1], pMapFile);
		}
	}
	else
	{
		printf("File not find!\n");
	}
	fclose(pMapFile);
}

int main()
{
	writeMap("file.txt");
	getchar();
    return 0;
}

