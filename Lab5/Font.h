#pragma once
#include <SFML/Graphics.hpp>

const int NUMBER_TEXT_STRING = 2;

const int SIZE_NORMAL_TEXT = 16;
const int SIZE_SMALL_TEXT = 12;

typedef enum {
	arrowGui,
	plusGui,
	minusGui,
	amountPathGui
} idPathGui;

const sf::String path[idPathGui::amountPathGui] =
{
	"recourses\\Arrow.png",
	"recourses\\Plus.png",
	"recourses\\Minus.png"
};

typedef enum {
	pathImage,
	errorText,
	amountTextsGui
} idText;

const sf::String TITLE_PROGRAM = "Image viewer";
const sf::String DIRECTORY_EMPTY = "Directory is empty.";
const sf::String FAILED_LOAD = "Failed load!";
const sf::String BIG_IMAGE = "Big image!";
const sf::String INVALID_PATH = "Invalid path!";

struct TextProgram {
	sf::Font *font;
	sf::Text *texts;
};

void initializeTexts(TextProgram &textProgram);
