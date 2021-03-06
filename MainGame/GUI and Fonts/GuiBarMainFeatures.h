#pragma once
#include "../structGame/CommonStructs.h"
#include "GuiVar.h"

struct barMainFeatures
{
	sf::Sprite bar;
	sf::Sprite levelHealth;
	sf::Sprite levelStamina;
	sf::Sprite levelMana;
	void renderBar(int &current, int& max, sf::Sprite &sprite, sf::Vector2f scale, featuresSprite &sizes,
								 TextGame &textGame, sf::Vector2f &position, sf::RenderWindow &window);
	void render(int &current, int& max, sf::Sprite &sprite, sf::Vector2f scale,
							featuresSprite &sizes, sf::Vector2f &position, sf::RenderWindow &window);
	void renderText(int &current, int& max, sf::Vector2f scale,
									sf::Vector2f &position, sf::RenderWindow &window, TextGame &textGame);

	void renderTextEnemy(Entity & enemy, int & current, int & max, int shift,
											 sf::RenderWindow & window, TextGame & textGame);

	void renderDamageForEnemy(Entity & enemy, TextGame & textGame, sf::RenderWindow & window, int shift);

	void renderBarMainPerson(Entity &mainPerson, int & current, int & max, int shift, sf::Sprite &sprite, featuresSprite & sizes,
													 featuresWindow features, TextGame & textGame);
	void renderBarEnemy(Entity & enemy, int & current, int & max, int shift, sf::Sprite &sprite,
											featuresSprite & sizes, TextGame & textGame, RenderWindow & window);
};

