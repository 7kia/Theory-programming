#include "MyFunctions.h"

using namespace sf;
using namespace std;

float distansePoints(Vector2f firstPoint, Vector2f secondPoint)
{
	return sqrt( (firstPoint.x - secondPoint.x) * (firstPoint.x - secondPoint.x)
							+ (firstPoint.y - secondPoint.y) * (firstPoint.y - secondPoint.y));
}

Vector2f vectorDirection(Vector2f firstPoint, Vector2f secondPoint)
{
	return { (secondPoint.x - firstPoint.x) ,
		(secondPoint.y - firstPoint.y) };
}

void intToString(int &inputNumber, string &inputString) {
	std::stringstream ss;
	ss << inputNumber;
	ss >> inputString;
}

void stringToInt(int &inputNumber, string &inputString) {
	std::stringstream ss;
	ss << inputString;
	ss >> inputNumber;
}

string toStringCharacter(int firstNumber, int secondNumber) {
	string firstString;
	string secondString;

	intToString(firstNumber, firstString);
	intToString(secondNumber, secondString);

	return firstString + DIVIDE_SYMBOL + secondString;
}

size_t computeMiddleString(Text &text)
{
	size_t sizeString = text.getString().getSize();
	unsigned int shift = 0;
	if(sizeString % 2)
	{
		shift = text.getCharacterSize() / 2;
	}
	return (sizeString * text.getCharacterSize() / 4) + shift;// TODO
}

size_t computeSizeString(Text &text)
{
	return text.getString().getSize() * text.getCharacterSize();// TODO
}

void defineOriginInMiddleString(Text& text)
{
	size_t widthText = text.getCharacterSize() * text.getString().getSize();
	Vector2f origin = { float(widthText) / 4 , float(text.getCharacterSize()) };
	text.setOrigin(origin);
}

int inMapCoordinate(float number)
{
	return int(number / SIZE_BLOCK);
}

Vector2i inMapCoordinate(Vector2f pos)
{
	return{ inMapCoordinate(pos.x), inMapCoordinate(pos.y) };
}