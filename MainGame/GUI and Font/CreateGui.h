#pragma once
#include "GuiPanels.h"

struct barHungry
{
	sf::Sprite lowHungry;
	sf::Sprite highHungry;
	sf::Sprite levelHungry;
	void renderBar(int& current, int& max, sf::Vector2f centerWindow, sf::Vector2u sizeWindow,
								 sf::RenderWindow& window);
	void renderHigh(sf::Vector2f &pos, sf::Vector2u sizeWindow, sf::RenderWindow &window);
	void renderLevel(int& current, int& max, sf::Vector2f& pos, sf::RenderWindow& window);
	void renderLow(sf::Vector2f& pos, sf::Vector2f centerWindow,
								 sf::Vector2u sizeWindow, sf::RenderWindow& window);
};

struct barThirst
{
	sf::Sprite bottle;
	sf::Sprite levelThirst;
	void renderBar(int& current, int& max, sf::Vector2f centerWindow, sf::Vector2u sizeWindow,
								 sf::RenderWindow& window);
};

void createGUITexture(Texture &texture, sf::String fileName);

void createGUI(sf::Sprite &itemInfoOverPanel, Texture &texture);
void createGUI(infoAboutSelect &gui);
void createGUI(panelQuickAccess &gui, Texture *texture);
void createPanels(panels &gui, Texture &texture);

void createGUI(barHungry &gui, Texture *texture);
void createGUI(barThirst &gui, Texture *texture);
void createGUI(barMainFeatures &gui, Texture *texture);
void createGUI(itemFeatures &gui, Texture *textureWidgets, Texture *textureBars);