#pragma once
#include <SFML/Graphics.hpp>
#include "Font.h"

const int WIDTH_GUI_ELEMENT = 44;
const int HEIGHT_GUI_ELEMENT = 44;
const int PIXEL_X_GUI = 0;
const int PIXEL_Y_GUI = 0;

const int SHIFT_ARROWS = 8;
const int SHIFT_ZOOM = 8;

struct GUI
{
	sf::Texture* textureArrow;
	sf::Sprite* arrowLeft;
	sf::Sprite* arrowRight;
	void createArrows();

	sf::Texture* texturePlus;
	sf::Sprite* plus;

	sf::Texture* textureMinus;
	sf::Sprite* minus;
	void createZoomButtons();
};

void initializeGUI(GUI &gui);
