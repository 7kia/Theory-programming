#pragma once
#include "CreateGui.h"

struct GUI
{// добавление gui

	sf::Texture widgetsTexture;
	panels panels;

	sf::Texture textureBar;
	barHungry hungry;
	barThirst thirst;
	barMainFeatures mainFeatures;
	itemFeatures itemFeatures;

	// —сылки на текст
	sf::Text *textGui[numberTextReference];

	void renderTextDeath(MainPerson &mainPerson, sf::Vector2f position, sf::RenderWindow &window, TextGame &textGame);
	void setPositionGui(sf::RenderWindow &window, MainPerson &mainPerson, std::vector<Enemy>& enemy, TextGame &textGame);
	~GUI();
};

void initializeGUI(GUI &gui, TextGame &textGame);

