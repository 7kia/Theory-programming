#pragma once
#include "CreateGui.h"

struct GUI
{// ���������� gui

	sf::Texture textureGui[amoundIdGuiTexture];

	panels panels;

	barHungry hungry;
	barThirst thirst;
	barMainFeatures mainFeatures;
	itemFeatures itemFeatures;

	// ������ �� �����
	sf::Text *textGui[numberTextReference];

	void renderTextDeath(MainPerson &mainPerson, sf::Vector2f position, sf::RenderWindow &window, TextGame &textGame);
	void setPositionGui(sf::RenderWindow &window, MainPerson &mainPerson, std::vector<Enemy>& enemy, TextGame &textGame);
	~GUI();
};

void initializeGUI(GUI &gui, TextGame &textGame);

