#include "blockConstuction.h"
#include "Animation.h"

using namespace sf;
using namespace std;

void variablesFirstStep::reset()
{
	idBlock = 0;
	angleBreak = 0.f;
	countRotations = 0;
}

void variablesSecondStep::reset()
{
	idDirection = 0;
	direction = directions[idDirection];
	timeMove = 0.f;
	zoomPlus = true;
}

void stateColor::init(float time, bool increase)
{
	timeUpdate = time;
	needIncrease = increase;
}

blockConstuction::blockConstuction()
{
	for (int i = 0; i < AMOUNT_BLOCKS; i++) {
		block[i].setSize(DEFAULT_SIZE_BLOCK);
		block[i].setFillColor(DEFAULT_FILL_COLOR);

		block[i].setOutlineThickness(THIKNESS_BLOCKS);
		block[i].setOutlineColor(THIKNESS_COLOR);

		block[i].setPosition(CENTER_WINDOW.x, CENTER_WINDOW.y);
	}

	setOrigin();
	defineDirectionsMove();
	defineUpdateColor();
}

void blockConstuction::setOrigin()
{
	float yPosition;
	float shiftStartPosition = -(DEFAULT_SIZE_BLOCK.y + DISTANSE_BETWEEN_BLOCKS) * (AMOUNT_BLOCKS / 2);
	for (int i = 0; i < AMOUNT_BLOCKS; i++) {
		yPosition = shiftStartPosition + (DEFAULT_SIZE_BLOCK.y + DISTANSE_BETWEEN_BLOCKS) * i;
		block[i].setOrigin(DEFAULT_SIZE_BLOCK.x / 2 + shiftOrigin.x, yPosition + DEFAULT_SIZE_BLOCK.y / 2 + shiftOrigin.y);
	}
}

void blockConstuction::defineDirectionsMove()
{
	float shift = variablesSecond.shift;
	Vector2f &direction = variablesSecond.direction;
	vector<Vector2f> &directions = variablesSecond.directions;


	Vector2f dir = { shift / 2, 0 };
	directions.push_back(dir);

	dir = { -shift * 0.75f, -shift / 4 };
	directions.push_back(dir);
	dir = { -shift * 0.75f, shift / 4 };
	directions.push_back(dir);
	dir = { shift * 0.75f, shift / 4 };
	directions.push_back(dir);
	dir = { shift * 0.75f, -shift / 4 };
	directions.push_back(dir);

	dir = { -shift / 2, 0 };
	directions.push_back(dir);

	direction = directions[0];
}

void blockConstuction::defineStepAnimation(float deltaTime)
{
	if (doFirstStep) {
		firstStep(deltaTime);
	}
	else if (doSecondStep) {
		secondStep(deltaTime);
		clockingBlocks();
	}
	else
	{
		thirdStep();
	}
}

void blockConstuction::updatePosition()
{
	Vector2f posFirst = block[0].getPosition();
	for (int i = 1; i < AMOUNT_BLOCKS; i++) {
		block[i].setPosition(posFirst);
	}
}

void blockConstuction::clockingBlocks()
{
	trasformation transformPrevious;
	for (int i = 1; i < AMOUNT_BLOCKS; i++) {
		transformPrevious.rotate = block[i - 1].getRotation();
		transformPrevious.scale = block[i - 1].getScale();

		block[i].setRotation(transformPrevious.rotate);
		block[i].setScale(transformPrevious.scale);
	}
}

void blockConstuction::update(float deltaTime)
{
	defineStepAnimation(deltaTime);
	updatePosition();
}

void blockConstuction::scaleConstruction()
{
	float &currentScale = variablesSecond.currentScale;
	bool &zoomPlus = variablesSecond.zoomPlus;
	int &idDirection = variablesSecond.idDirection;

	if (zoomPlus) {
		currentScale += SCALE;
	}
	else {
		currentScale -= SCALE;
	}
	block[0].setScale(currentScale, currentScale);
}

void blockConstuction::resetColor(Uint8 &value, const Uint8  defaultValue)
{
	if (value > defaultValue) {
		value -= 1;
	}
	else if (value < defaultValue) {
		value += 1;
	}
}

void blockConstuction::resetColorBlocks()
{
	Color currentColor;
	for (int i = 0; i < AMOUNT_BLOCKS; i++) {

		currentColor = block[i].getFillColor();

		resetColor(currentColor.r, DEFAULT_FILL_COLOR.r);
		resetColor(currentColor.g, DEFAULT_FILL_COLOR.g);
		resetColor(currentColor.b, DEFAULT_FILL_COLOR.b);

		if (currentColor == DEFAULT_FILL_COLOR) {
			doFirstStep = true;
			doSecondStep = true;
		}
		else {
			block[i].setFillColor(currentColor);
		}
	}
}

void blockConstuction::defineUpdateColor()
{
	modeRed.init(TIME_UPDATE_RED_COLOR, true);
	modeGreen.init(TIME_UPDATE_GREEN_COLOR, true);
	modeBlue.init(TIME_UPDATE_BLUE_COLOR, true);
}

void blockConstuction::updateColors(float deltaTime)
{
		Color currentColor = block[0].getFillColor();

		conditionUpdateColor = variablesFirst.idBlock > 2;
		updateColor(modeRed, currentColor.g, deltaTime);

		conditionUpdateColor = variablesFirst.idBlock > 3;
		updateColor(modeBlue,
								currentColor.b, deltaTime);

		conditionUpdateColor = variablesFirst.idBlock > 4;
		updateColor(modeGreen, currentColor.r, deltaTime);

		for (int i = 0; i < AMOUNT_BLOCKS; i++) {
			block[i].setFillColor(currentColor);
		}
}

void blockConstuction::updateColor(stateColor &stateColor,
																	 Uint8 &value, float deltaTime)
{
	if (conditionUpdateColor) {
		stateColor.currentTime += deltaTime;

		if (stateColor.currentTime > stateColor.timeUpdate) {

			if (stateColor.needIncrease) {
				if (value + SHIFT_COLOR < 255) {
					value += SHIFT_COLOR;
				}
				else {
					stateColor.needIncrease = false;
				}
			}
			else {
				if (value - SHIFT_COLOR > 0) {
					value -= SHIFT_COLOR;
				}
				else {
					stateColor.needIncrease = true;
				}
			}

			stateColor.currentTime = 0.f;
		}

	}
}

void blockConstuction::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < AMOUNT_BLOCKS; i++)
	{
		window.draw(block[i]);
	}
}

void blockConstuction::anisochronousRotate()
{
	variablesFirstStep &var = variablesFirst;
	int &idBlock = var.idBlock;
	float &angleBreak = var.angleBreak;
	int &countRotations = var.countRotations;

	float currentAngle = block[idBlock].getRotation();
	if (currentAngle < angleBreak) {
		block[idBlock].rotate(ROTATE_BLOCKS * (idBlock + 1));
	}
	else {

		block[idBlock].setRotation(angleBreak);
		idBlock++;
		if (idBlock > AMOUNT_BLOCKS - 1) {

			idBlock = 0;
			angleBreak += 90.f;
			countRotations++;

			if (countRotations > 2) {
				variablesFirst.reset();
				doFirstStep = false;
				doSecondStep = true;
			}

		}
	}
}
