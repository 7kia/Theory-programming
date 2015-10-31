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
#define HeightMap 2
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
		inputString[i] = inputChar;
	}
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

