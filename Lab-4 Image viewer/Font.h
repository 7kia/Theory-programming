#pragma once
#include <SFML/Graphics.hpp>

const int NUMBER_TEXT_STRING = 2;

const int SIZE_NORMAL_TEXT = 16;
const int SIZE_SMALL_TEXT = 12;

typedef enum {
	arrowGui,
	amountPath
} idPath;

const sf::String path[idPath::amountPath] =
{
	"recourses\\Arrow.png",
};

typedef enum {
	pathImage,
	currentImageGui,
	amountTextsGui
} idText;

const sf::String TITLE_PROGRAM = "Image viewer";
const sf::String NO_IMAGE = "No images";

struct TextProgram {
	sf::Font *font;
	sf::Text *texts;
};

void initializeTexts(TextProgram &textProgram);
