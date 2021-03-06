#pragma once
#include "GuiVar.h"
#include "GuiBarMainFeatures.h"

struct itemFeatures
{
	sf::Sprite cutSprite;
	sf::Sprite crashSprite;
	sf::Sprite unlifeSprite;
	sf::Sprite hungrySprite;
	sf::Sprite thirstSprite;
	void renderValueMiddle(std::string string, sf::Text* text, sf::Vector2f &position, sf::RenderWindow &window);
	void renderIconWithScale(sf::Sprite &sprite, sf::Vector2f position, sf::RenderWindow &window);
	void renderBar(sf::Sprite &sprite, sf::Vector2f position, sf::RenderWindow &window);
	void renderNameItem(::Entity& mainPerson, sf::Vector2f &position, featuresWindow features,
											TextGame &textGame);
	void renderFeatures(::Entity& mainPerson, featuresWindow features,
											TextGame &textGame, barMainFeatures &bars);

};