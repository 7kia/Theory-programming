#pragma once
// Для поиска файлов
#include <iostream>// ИСПРАВЬ
#include <fstream>

#include <windows.h>

#include <string>

#include "Font.h"
#include "programClock.h"

const unsigned int DEFAULT_WIDTH_WINDOW = 500;
const unsigned int DEFAULT_HEIGHT_WINDOW = 500;
const sf::Vector2u SIZE_WINDOW = { DEFAULT_WIDTH_WINDOW , DEFAULT_HEIGHT_WINDOW };

const float SPEED_SHIFT = 5.f;

const float SCALE_IMAGE = 0.25f;
const float SOURCE_SIZE = 1.f;

const std::string TITLE_PROGRAM = "Clock";
const sf::Color COLOR_GREY(122, 122, 122, 255);
struct Program
{
	sf::RenderWindow window;
	
	TextProgram textProgram;

	programClock Clock;
};

void initializeProgram(Program & program);
void setPositionClock(Program & program);
void destroyProgram(Program & program);