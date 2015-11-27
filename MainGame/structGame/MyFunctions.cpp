#include "MyFunctions.h"

using namespace sf;
using namespace std;

float distansePoints(Vector2f firstPoint, Vector2f secondPoint)
{
	return sqrt( (firstPoint.x - secondPoint.x) * (firstPoint.x - secondPoint.x)// ÈÑÏÐÀÂÜ
							+ (firstPoint.y - secondPoint.y) * (firstPoint.y - secondPoint.y));
}

Vector2f vectorDirection(Vector2f firstPoint, Vector2f secondPoint)
{
	return { (secondPoint.x - firstPoint.x) ,/// distansePoints(firstPoint, secondPoint)
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
	return text.getString().getSize() * text.getCharacterSize() / 4;// TODO
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