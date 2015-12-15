#pragma once
#include "../GlobalVar.h"

<<<<<<< HEAD
const sf::Vector2i ZERO_VECTOR_2I = { 0, 0 };
=======
const sf::Vector2f ZERO_VECTOR = { 0.f, 0.f };
>>>>>>> master

float distansePoints(sf::Vector2f firstPoint, sf::Vector2f secondPoint);
sf::Vector2f vectorDirection(sf::Vector2f firstPoint, sf::Vector2f secondPoint);

void intToString(int &inputNumber, std::string &inputString);
void stringToInt(int &inputNumber, std::string &inputString);
std::string toStringCharacter(int firstNumber, int secondNumber);

size_t computeMiddleString(sf::Text &text);
size_t computeSizeString(sf::Text &text);
void defineOriginInMiddleString(sf::Text &text);