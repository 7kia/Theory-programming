#pragma once
// Для поиска файлов
#include <iostream>// ИСПРАВЬ
#include <windows.h>

#include <string>

// Для динамических списков
#include <list>     // подключаем заголовок списка
#include <iterator> // заголовок итераторов

#include "Font.h"
#include "GUI.h"

const int DEFAULT_WIDTH_WINDOW = 800;
const int DEFAULT_HEIGHT_WINDOW = 600;

const float SHIFT_VIEW = 200.f;

const sf::Color COLOR_GREY(150, 150, 150, 255);
const int AMOUNT_FORMATS = 4;
const int SIZE_STRING = 256;
const char MASK[] = "*.";
const char formats[AMOUNT_FORMATS][SIZE_STRING] = {
	"png",
	"jpeg",
	"jpg",
	"bmp"
};
//const char* formats[AMOUNT_FORMATS] = { "png", "jpeg", "bmp" };
typedef enum {
	currentImage,
	folder,
	amountPaths
} idPathUpdate;

struct Program
{
	sf::RenderWindow *window;
	sf::String currentTitle;
	TextProgram *textProgram;

	sf::View view;

	GUI* gui;
	std::list<std::string>* pathsImages;
	char* mask;
	char* formats[AMOUNT_FORMATS];
	void searchImage(const char *path);

	std::list<std::string>::iterator currentPath;
	sf::String newPath;
	sf::Texture* textureCurrentImage;
	sf::Sprite* currentImage;
	sf::Vector2u* sizeImage;
	sf::Vector2f* scaleImage;
	sf::Vector2f* sourseScale;

	float dX = 0.f;
	float dY = 0.f;

	int xMouse, yMouse;
	bool isShift;

	unsigned int widthMainWindow = DEFAULT_WIDTH_WINDOW;
	unsigned int heightMainWindow = DEFAULT_HEIGHT_WINDOW;
};
void initializeImage(Program & program);
void setPositionGui(Program & program);

void actionLeft(Program & program);
void actionRight(Program & program);

void updateView(Program & program, const sf::Time & deltaTime);

void actionZoomPlus(Program & program);
void actionZoomMinus(Program & program);

void initializeProgram(Program & program);
void destroyProgram(Program & program);