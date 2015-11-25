#pragma once
#include <SFML/Graphics.hpp>
#include <windows.h>

const sf::Vector2f SIZE_INDICATORS = { 30, 3 };
const sf::Vector2f SIZE_MINUTE_ARROW = { 120, 3 };
const sf::Vector2f SIZE_SECOND_ARROW = { 120, 1 };
const sf::Vector2f SIZE_HOUR_ARROW = { 80, 5 };
const float RADIUSE_CLOCK = 200.f;
const float RADIUSE_MIDDLE = 15.f;

const int ARROW_OUTLINE_THIKNESS = 2;
const int BORDER_THIKNESS = 5;

const int NUMBER_SECOND = 60;
const float NUMBER_HOUR = 12;

const int FULL_CIRCLE_DEGREES = 360;
const float CIRCLE_QUARTER = FULL_CIRCLE_DEGREES / 4;

const unsigned int DEFAULT_WIDTH_WINDOW = (RADIUSE_CLOCK + BORDER_THIKNESS) * 2;
const unsigned int DEFAULT_HEIGHT_WINDOW = DEFAULT_WIDTH_WINDOW;
const sf::Vector2u SIZE_WINDOW = { DEFAULT_WIDTH_WINDOW , DEFAULT_HEIGHT_WINDOW };
const sf::Vector2f CENTER_WINDOW = { float(SIZE_WINDOW.x / 2) , float(SIZE_WINDOW.y / 2) };

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

	sf::RectangleShape indicatorShape;

	void initializeArrows();
	void initializeCircles();
	void initializeIndicators();

	void initialize();

	void update();

	void draw(sf::RenderWindow& window);
	void drawArrows(sf::RenderWindow& window);
	void drawIndicators(sf::RenderWindow& window);
};

void initializeClock(programClock &clock);
