#pragma once
#include <SFML/Graphics.hpp>

const float DEFAULT_WIDTH_WINDOW = 800;
const float DEFAULT_HEIGHT_WINDOW = 600;
const sf::Vector2f SIZE_WINDOW = { DEFAULT_WIDTH_WINDOW , DEFAULT_HEIGHT_WINDOW };
const sf::Vector2f CENTER_WINDOW = { float(SIZE_WINDOW.x / 2) , float(SIZE_WINDOW.y / 2) };

const int AMOUNT_BLOCKS = 7;

const sf::Vector2f DEFAULT_SIZE_BLOCK = { 15.f, 15.f };
const sf::Color DEFAULT_FILL_COLOR(255, 0, 0, 255);
const float DISTANSE_BETWEEN_BLOCKS = 15.f;
const float THIKNESS_BLOCKS = 3.f;
const sf::Color THIKNESS_COLOR = sf::Color::Black;

const float ROTATE_PER_FRAME = 5.0f;
const sf::Vector2f ZERO_VECTOR = { 0.f, 0.f };
const float ROTATE_BLOCKS = 1.f;
const float SCALE = 0.005f;
const sf::Uint8 SHIFT_COLOR = 10;

const float TIME_UPDATE_RED_COLOR = 0.05f;
const float TIME_UPDATE_GREEN_COLOR = 0.1f;
const float TIME_UPDATE_BLUE_COLOR = 0.2f;

const float TIME_UPDATE_DIRECTION = 2.f;
const float SHIFT = 2.f;

struct trasformation
{
	float rotate;
	sf::Vector2f scale;
};

struct variablesFirstStep
{
	int idBlock = 0;
	float angleBreak = 0.f;
	int countRotations = 0;
	void reset();
};

struct variablesSecondStep {
	float timeMove = 0.f;
	float timeUpdateDirection = TIME_UPDATE_DIRECTION;
	float shift = 2.f;
	int idDirection = 0;
	bool zoomPlus = true;
	sf::Vector2f direction;
	std::vector<sf::Vector2f> directions;
	float currentScale = 1.f;
	void reset();
};


struct stateColor
{
	float currentTime = 0.f;
	float timeUpdate = 0.f;
	bool needIncrease = false;
	void init(float time, bool increase);
};

struct blockConstuction
{
	sf::RectangleShape block[AMOUNT_BLOCKS];
	sf::Vector2f shiftOrigin = ZERO_VECTOR;

	blockConstuction();
	void setOrigin();
	void defineDirectionsMove();

	stateColor modeRed;
	stateColor modeGreen;
	stateColor modeBlue;
	bool conditionUpdateColor;
	void defineUpdateColor();

	void updateColor(stateColor &stateColor, sf::Uint8 &value, float deltaTime);
	void updateColors(float deltaTime);

	void defineStepAnimation(float deltaTime);
	void updatePosition();
	void clockingBlocks();
	void update(float deltaTime);

	void draw(sf::RenderWindow& window);

	void anisochronousRotate();

	// Animation.cpp
	variablesFirstStep variablesFirst;
	bool doFirstStep = true;
	void firstStep(float deltaTime);

	variablesSecondStep variablesSecond;
	bool doSecondStep = true;
	void scaleConstruction();
	void secondStep(float deltaTime);

	void resetColor(sf::Uint8 &value, const sf::Uint8 defaultValue);
	void resetColorBlocks();
	void thirdStep();

};

