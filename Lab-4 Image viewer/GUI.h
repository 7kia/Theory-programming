#pragma once
#include <SFML/Graphics.hpp>

#include "Font.h"

const int WIDTH_ARROW_GUI = 44;
const int HEIGHT_ARROW_GUI = 44;
const int PIXEL_X_ARROW_GUI = 0;
const int PIXEL_Y_ARROW_GUI = 0;

struct GUI
{
	sf::Texture* textureArrow;
	sf::Sprite* arrowLeft;
	sf::Sprite* arrowRight;
};

void initializeGUI(GUI &gui);
