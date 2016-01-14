#pragma once
#include "CreateGui.h"

struct GUI
{

	sf::Texture textureGui[amoundIdGuiTexture];

	panels panels;

	barHungry hungry;
	barMainFeatures mainFeatures;
	itemFeatures itemFeatures;

	// —сылки на текст
	sf::Text *textGui[numberTextReference];

	void renderTextDeath(Entity &mainPerson, sf::Vector2f position, sf::RenderWindow &window, TextGame &textGame);
	void setPositionGui(sf::RenderWindow &window, Entity &mainPerson, std::vector<Entity>& enemy, TextGame &textGame);
	void setHealthBars(featuresWindow &featuresWindow, Entity &mainPerson ,
										 std::vector<Entity>& enemy , TextGame &textGame);
	void setStaminaBars(featuresWindow &featuresWindow , Entity &mainPerson ,
										 std::vector<Entity>& enemy , TextGame &textGame);

	~GUI();
};

void initializeGUI(GUI &gui, TextGame &textGame);

