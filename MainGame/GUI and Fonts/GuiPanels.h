#pragma once
#include "GuiVar.h"
#include "GuiItemFeatures.h"
#include "GuiBarMainFeatures.h"

struct infoAboutSelect
{
	sf::Texture Texture;
	sf::Sprite sprite;
	void render(sf::Vector2f position, sf::RenderWindow &window, TextGame &textGame);
};

struct panelQuickAccess
{
	sf::Sprite spritePanel;
	sf::Sprite spriteSelect;
	void renderPanel(sf::Vector2f position, sf::RenderWindow& window);
	void renderSelect(::Entity &mainPerson, featuresWindow features);
	void renderAmountItem(int amount, sf::Vector2f pos, TextGame &textGame, featuresWindow features);
	void renderItems(::Entity &mainPerson, featuresWindow features,
									 TextGame &textGame, barMainFeatures &bars, itemFeatures &itemFeatures);
};

struct panel
{
	sf::Sprite sprite;
	bool draw = false;
	void setPosition(sf::Vector2f position);
};

struct panels
{
	infoAboutSelect infoAboutSelect;
	panelQuickAccess panelQuickAccess;
	panel itemInfoOverPanel;
	panel awardPanel;
	panel menuPanel;
	void renderItemPanel(Vector2f position, RenderWindow& window);
};