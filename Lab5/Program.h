#pragma once
// Для поиска файлов
#include <iostream>// ИСПРАВЬ
#include <fstream>

#include <windows.h>

#include <string>

// Для динамических списков
#include <list>     // подключаем заголовок списка
#include <iterator> // заголовок итераторов

#include "Font.h"
#include "GUI.h"

const int K_BITE = 1024;
const int MEGA_BITE = 1024 * K_BITE;
const int MAX_SIZE = 4 * MEGA_BITE;

const int DEFAULT_WIDTH_WINDOW = 800;
const int DEFAULT_HEIGHT_WINDOW = 600;

const float SHIFT_VIEW = 400.f;

const float NORMAL_SCALE = 1.f;
const float MAX_SCALE = 3.f;

const float SPEED_SHIFT = 5.f;

const float SCALE_IMAGE = 0.25f;
const float SOURCE_SIZE = 1.f;

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

typedef enum {
	currentImage,
	folder,
	amountPaths
} idPath;

struct Program
{
	sf::RenderWindow *window;
	sf::String currentTitle;
	bool isZoom;
	TextProgram *textProgram;

	sf::Vector2f oldPositionMouse, newPositionMouse;
	float scale = 1.f;

	GUI* gui;
	std::list<std::string>* pathsImages;
	char* mask;
	void searchImages();
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


	void setPositionsArrows(sf::Vector2i centerWindow, sf::Vector2u sizeWindow);
	void setPositionsZoomButtons(sf::Vector2u centerWindow);
	void setPositionErrorText(sf::Vector2i centerWindow);
};
void initializeImage(Program & program);
void setPositionGui(Program & program);

void actionLeft(Program & program);
void actionRight(Program & program);

void updateView(Program & program, const sf::Time & deltaTime);

void actionZoomPlus(Program & program, sf::Vector2f posMouse);
void actionZoomMinus(Program & program, sf::Vector2f posMouse);

void initializeProgram(Program & program);
void destroyProgram(Program & program);