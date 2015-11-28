#pragma once
#include <SFML/Graphics.hpp>
#include <windows.h>


const float DEFAULT_WIDTH_WINDOW = 800;
const float DEFAULT_HEIGHT_WINDOW = 600;
const sf::Vector2f SIZE_WINDOW = { DEFAULT_WIDTH_WINDOW , DEFAULT_HEIGHT_WINDOW };
const sf::Vector2f CENTER_WINDOW = { float(SIZE_WINDOW.x / 2) , float(SIZE_WINDOW.y / 2) };

const int AMOUNT_BLOCKS = 7;

const sf::Vector2f DEFAULT_SIZE_BLOCK = { 25.f, 25.f };
const sf::Color DEFAULT_FILL_COLOR(255, 0, 0, 255);
const float DISTANSE_BETWEEN_BLOCKS = 15.f;
const float THIKNESS_BLOCKS = 3.f;
const sf::Color THIKNESS_COLOR = sf::Color::Black;

const float ROTATE_PER_FRAME = 5.0f;
const sf::Vector2f zeroVector = { 0.f, 0.f };

const float SCALE = 0.008f;

enum curremtTransform
{
	move,
	scale,
	rotate,
	amendColor
};

struct trasformation
{
	float rotate;
	sf::Vector2f scale;

};

struct blockConstuction
{
	sf::RectangleShape block[AMOUNT_BLOCKS];
	sf::Vector2f shiftOrigin = zeroVector;

	int idOriginBlock = 0;
	int countCircle = 0;
	void resetCountCircle();

	blockConstuction();
	void setOrigin();
	void updatePosition();


	// Animation.cpp
	bool conditionFirstStep;
	void firstStep(float &deltaTime);

	bool doSecondStep = true;

	float timeMove = 0.f;
	float timeUpdateDirection = 2.f;
	float shift = 2.f;
	int idDirection = 0;
	bool zoomPlus = true;
	sf::Vector2f direction;
	std::vector<sf::Vector2f> directions;
	float currentScale = 1.f;
	void secondStep(float &deltaTime);
	//
	bool increaseRed = true;
	bool increaseGreen = true;
	bool increaseBlue = true;

	float timerRedColor = 0.f;
	float timerGreenColor = 0.f;
	float timerBlueColor = 0.f;

	float timeUpdateRedColor = 0.05f;
	float timeUpdateGreeenColor = 0.1f;
	float timeUpdateBlueColor = 0.2f;
	void update(float &deltaTime);
	void updateColors(float &deltaTime);

	bool conditionUpdateColor;
	void updateColor(float &timeCurrent, float timeUpdate, bool &increase, sf::Uint8 &value, float &deltaTime);



	void draw(sf::RenderWindow& window);

	void rotateRelativeBlock(int id);
	void rotate(sf::Vector2f origin);
	void resetRotate();
};

