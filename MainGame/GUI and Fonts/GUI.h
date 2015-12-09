#pragma once
#include "CreateGui.h"

struct GUI
{// добавление gui

	sf::Texture textureGui[amoundIdGuiTexture];

	panels panels;

	barHungry hungry;
	barThirst thirst;
	barMainFeatures mainFeatures;
	itemFeatures itemFeatures;

	// —сылки на текст
	sf::Text *textGui[numberTextReference];

	void renderTextDeath(MainPerson &mainPerson, sf::Vector2f position, sf::RenderWindow &window, TextGame &textGame);
	void setPositionGui(sf::RenderWindow &window, MainPerson &mainPerson, sf::View &view, std::vector<Entity>& enemy, TextGame &textGame);
	~GUI();
};

void initializeGUI(GUI &gui, TextGame &textGame);

