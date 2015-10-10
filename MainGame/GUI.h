#pragma once
#include <SFML/Graphics.hpp>
#include "GlobalVar.h"
#include "Font.h"

const int numberTextReference = 4;

struct GUI
{
	// »нформаци€ о выделеном блоке
	sf::Sprite *infoSelectBlockSprite;
	sf::Texture *infoSelectBlockTexture;
	int widthInfo;
	int heightInfo;

	// —сылки на текст
	sf::Text *textGui[numberTextReference];

	void setPositionGui(sf::RenderWindow &window, TextGame &textGame);
};

void initializeGUI(GUI &gui, TextGame &textGame);
