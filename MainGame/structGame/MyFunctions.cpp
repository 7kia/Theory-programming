#include "MyFunctions.h"

using namespace sf;
using namespace std;

float Math::distansePoints(Vector2f firstPoint, Vector2f secondPoint)
{
	return sqrt( (firstPoint.x - secondPoint.x) * (firstPoint.x - secondPoint.x)
							+ (firstPoint.y - secondPoint.y) * (firstPoint.y - secondPoint.y));
}

Vector2f Math::vectorDirection(Vector2f firstPoint, Vector2f secondPoint)
{
	return { (secondPoint.x - firstPoint.x) ,
		(secondPoint.y - firstPoint.y) };
}

std::string Math::intToString(int inputNumber)
{
	std::string outputString;
	std::stringstream ss;
	ss << inputNumber;
	ss >> outputString;

	return outputString;
}

int Math::stringToInt(std::string inputString)
{
	int outputNumber;
	std::stringstream ss;
	ss << inputString;
	ss >> outputNumber;
	return outputNumber;
}

sf::Vector2f Math::getNormalVector(sf::Vector2f inputVector)
{
	float length = sqrt((inputVector.x * inputVector.x)
											+ (inputVector.y * inputVector.y));
	return sf::Vector2f(inputVector.x / length, inputVector.y / length);
}


string Math::toStringCharacter(int firstNumber, int secondNumber) {
	string firstString = 	intToString(firstNumber);
	string secondString = intToString(secondNumber);

	return firstString + DIVIDE_SYMBOL + secondString;
}

size_t Math::computeMiddleString(Text &text)
{
	size_t sizeString = text.getString().getSize();
	unsigned int shift = 0;
	if(sizeString % 2)
	{
		shift = text.getCharacterSize() / 2;
	}
	return (sizeString * text.getCharacterSize() / 4) + shift;// TODO
}

size_t Math::computeSizeString(Text &text)
{
	return text.getString().getSize() * text.getCharacterSize();// TODO
}

int Math::inMapCoordinate(float number)
{
	return int(number / SIZE_BLOCK);
}

Vector2i Math::inMapCoordinate(Vector2f pos)
{
	return{ inMapCoordinate(pos.x), inMapCoordinate(pos.y) };
}

void g_Functions::cleanIntArray(int* array, int size)
{
	for (int i = 0; i < size; i++)
	{
		array[i] = 0;
	}
}

bool g_Functions::checkDiaposon(int number , int start , int end)
{
	return (start < number) && (number < end);
}


void g_Functions::defineOriginInMiddleString(Text& text)
{
	size_t widthText = text.getCharacterSize() * text.getString().getSize();
	Vector2f origin = { float(widthText) / 4 , float(text.getCharacterSize()) };
	text.setOrigin(origin);
}


bool g_Functions::isInListBlocks(vector<wchar_t> &listObjects , wchar_t block) {
		size_t size = listObjects.size();
		if (size) {
			for (size_t i = 0; i < size; i++) {
				if (block == listObjects[i]) {
					return true;
				}
			}

	}

	return false;
}

bool g_Functions::isInListIds(int id , vector<wchar_t> &listIds) {
		size_t size = listIds.size();
		if (size) {
			for (size_t i = 0; i < size; i++) {
				if (id == listIds[i]) {
					return true;
				}
			}
		}

	return false;
}

bool g_Functions::isInListObjects(vector<int> &listObjects , int id) {
		size_t size = listObjects.size();
		if (size) {
			for (size_t i = 0; i < size; i++) {
				if (id == listObjects[i]) {
					return true;
				}
			}

	}

	return false;
}

bool g_Functions::isInListShoots(vector<int> &listObjects , int id) {
	size_t size = listObjects.size();
	if (size) {
		for (size_t i = 0; i < size; i++) {
			if (id == listObjects[i]) {
				return true;
			}
		}

	}

	return false;
}

void g_Functions::addIdDeleteInList(int id , std::vector<int> &list)
{
	if (!g_Functions::isInListObjects(list , id)) {
		int count = 0;
		while (count < list.size()) {
			if (list[count] > id) 				{
				count++;
				continue;
			}
			break;
		}
		list.insert(list.begin() + count, id);
	}
}