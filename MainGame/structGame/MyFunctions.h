#pragma once
#include <iostream>
#include <string>
#include <sstream>// Для перевода числа в строку
#include <vector>

#include "../GlobalVar.h"

const char DIVIDE_SYMBOL = '/';

const int RESET_VALUE = -1;
const sf::Vector2i RESET_VECTOR_2I = { RESET_VALUE, RESET_VALUE };
const sf::Vector3i RESET_VECTOR_3I = { RESET_VALUE, RESET_VALUE, RESET_VALUE };

const sf::Vector2f RESET_VECTOR_2F = { float(RESET_VALUE), float(RESET_VALUE) };

const sf::Vector2i ZERO_VECTOR_2I = { 0, 0 };
const sf::Vector2f ZERO_VECTOR_2F = { 0.f, 0.f };

struct Math
{
	Math() = delete;

	static float distansePoints(sf::Vector2f firstPoint , sf::Vector2f secondPoint);
	static sf::Vector2f vectorDirection(sf::Vector2f firstPoint , sf::Vector2f secondPoint);

	static std::string toStringCharacter(int firstNumber , int secondNumber);

	static size_t computeMiddleString(sf::Text &text);
	static size_t computeSizeString(sf::Text &text);

	static int inMapCoordinate(float number);
	static sf::Vector2i inMapCoordinate(sf::Vector2f pos);

	static std::string intToString(int inputNumber);
	static int stringToInt(std::string inputString);

	static sf::Vector2f getNormalVector(sf::Vector2f inputVector);
};

struct g_Functions
{
	g_Functions() = delete;

	static void defineOriginInMiddleString(sf::Text &text);

	static bool isInListBlocks(std::vector<wchar_t>& listObjects , wchar_t block);
	static bool isInListIds(int id , std::vector<wchar_t>& listIds);
	static bool isInListObjects(std::vector<int>& listObjects , int id);
	static bool isInListShoots(std::vector<int>& listObjects , int id);

	static void cleanIntArray(int* array , int size);

	static bool checkDiaposon(int number , int start , int end);
};
