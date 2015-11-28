#include "blockConstuction.h"
#include "Animation.h"

using namespace sf;


void blockConstuction::resetCountCircle()
{
	countCircle = 0;
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

	conditionFirstStep = false;

	Vector2f direction = { shift, shift / 2 };
	directions.push_back(direction);
	direction = { -shift, -shift / 2 };
	directions.push_back(direction);
	direction = { -shift / 3, -shift / 3 };
	directions.push_back(direction);
	direction = { -shift, shift };
	directions.push_back(direction);
	direction = { shift, -shift };
	directions.push_back(direction);
	direction = { shift / 3, shift / 3 };
	directions.push_back(direction);
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

void blockConstuction::updatePosition()
{
	Vector2f posFirst = block[0].getPosition();
	for (int i = 1; i < AMOUNT_BLOCKS; i++) {
		block[i].setPosition(posFirst);

	}
}

void blockConstuction::update(float &deltaTime)
{
	if (conditionFirstStep) {
		firstStep(deltaTime);
		conditionFirstStep = countCircle < 8;

	}
	else if(doSecondStep)
	{
		
		secondStep(deltaTime);
	}

	updatePosition();

	Vector2f posPrevious;
	trasformation transformPrevious;
	for (int i = 1; i < AMOUNT_BLOCKS; i++) {
		posPrevious = block[i - 1].getPosition();

		transformPrevious.rotate = block[i - 1].getRotation();
		transformPrevious.scale = block[i - 1].getScale();

		block[i].setRotation(transformPrevious.rotate);
		block[i].setScale(transformPrevious.scale);
		//block[i].setRotation(transformPrevious.g);
		//block[i].getTransform();
		//block[i].setPosition(CENTER_WINDOW.x, yPosition);
	}
}

void blockConstuction::updateColors(float &deltaTime)
{
		Color currentColor = block[0].getFillColor();

		conditionUpdateColor = countCircle > 2;
		updateColor(timerGreenColor, timeUpdateGreeenColor, increaseGreen,
								currentColor.g, deltaTime);

		conditionUpdateColor = countCircle > 3;
		updateColor(timerBlueColor, timeUpdateBlueColor, increaseBlue,
								currentColor.b, deltaTime);

		conditionUpdateColor = countCircle > 4;
		updateColor(timerRedColor, timeUpdateRedColor, increaseRed,
								currentColor.r, deltaTime);

		for (int i = 0; i < AMOUNT_BLOCKS; i++) {
			block[i].setFillColor(currentColor);
		}
}

void blockConstuction::updateColor(float &timeCurrent, float timeUpdate, bool &increase,
																	 Uint8 &value, float &deltaTime)
{
	if (conditionUpdateColor) {
		timeCurrent += deltaTime;

		if (timeCurrent > timeUpdate) {

			if (increase) {
				if (value + 4 < 255) {
					value += 4;
				}
				else {
					increase = false;
				}
			}
			else {
				if (value - 4 > 0) {
					value -= 4;
				}
				else {
					increase = true;
				}
			}

			timeCurrent = 0.f;
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

void blockConstuction::rotateRelativeBlock(int id)
{
	float shift = (DEFAULT_SIZE_BLOCK.y + DISTANSE_BETWEEN_BLOCKS) * (id + AMOUNT_BLOCKS / 2);
	Vector2f rotation = { 0.f, DEFAULT_SIZE_BLOCK.y * 2 + shift - CENTER_WINDOW.y };

	rotate(rotation);
}

void blockConstuction::rotate(sf::Vector2f origin)
{
	Vector2f originFirstBlock = block[0].getOrigin();
	shiftOrigin = { -origin.x, -origin.y };

	block[0].setOrigin(origin);
	setOrigin();

	float previousRotate = block[0].getRotation();
	block[0].setRotation(previousRotate + ROTATE_PER_FRAME);

	if(block[0].getRotation() == 0.f)
	{
		countCircle++;
		printf("circle %d\n", countCircle);
	}

}

void blockConstuction::resetRotate()
{
	if (shiftOrigin != zeroVector) {
		shiftOrigin = zeroVector;
	}
}