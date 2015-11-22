#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <windows.h>

#include "Font.h"

const unsigned int DEFAULT_WIDTH_WINDOW = 500;
const unsigned int DEFAULT_HEIGHT_WINDOW = 500;
const sf::Vector2u SIZE_WINDOW = { DEFAULT_WIDTH_WINDOW , DEFAULT_HEIGHT_WINDOW };
const sf::Vector2f CENTER_WINDOW = { float(SIZE_WINDOW.x / 2) , float(SIZE_WINDOW.y / 2) };

const int SHIFT_ARROWS = 8;

const sf::Vector2f SIZE_MINUTE_ARROW = { 120, 1 };
const sf::Vector2f SIZE_SECOND_ARROW = { 120, 3 };
const sf::Vector2f SIZE_HOUR_ARROW = { 80, 5 };
const float RADIUSE_CLOCK = 200.f;
const float RADIUSE_MIDDLE = 15.f;

const int ARROW_OUTLINE_THIKNESS = 2;
const int BORDER_THIKNESS = 5;

struct programClock
{
	SYSTEMTIME time;

	float secondAngle;
	float minuteAngle;
	float hourAngle;

	sf::RectangleShape minuteArrow;
	sf::RectangleShape hourArrow;
	sf::RectangleShape secondArrow;

	sf::CircleShape borderClock;
	sf::CircleShape middleClock;

	void init();

	void update();
	void initArrows();
	void initCircles();
	void initNumbers();
	void render(sf::RenderWindow& window);
};

void initializeClock(programClock &clock);
