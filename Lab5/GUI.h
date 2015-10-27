#pragma once
#include <SFML/Graphics.hpp>

#include "Font.h"

const int WIDTH_GUI_ELEMENT = 44;
const int HEIGHT_GUI_ELEMENT = 44;
const int PIXEL_X_GUI = 0;
const int PIXEL_Y_GUI = 0;

struct GUI
{
	sf::Texture* textureArrow;
	sf::Sprite* arrowLeft;
	sf::Sprite* arrowRight;

	sf::Texture* texturePlus;
	sf::Sprite* plus;

	sf::Texture* textureMinus;
	sf::Sprite* minus;
};

void initializeGUI(GUI &gui);
