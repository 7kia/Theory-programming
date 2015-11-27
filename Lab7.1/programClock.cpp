#include "programClock.h"

using namespace sf;

void programClock::initializeArrows()
{
	minuteArrow.setSize(SIZE_MINUTE_ARROW);
	minuteArrow.setFillColor(sf::Color::Blue);
	minuteArrow.setOutlineThickness(ARROW_OUTLINE_THIKNESS);
	minuteArrow.setOutlineColor(sf::Color::Black);
	minuteArrow.setPosition(CENTER_WINDOW);

	secondArrow.setSize(SIZE_SECOND_ARROW);
	secondArrow.setFillColor(sf::Color::Red);
	secondArrow.setOutlineThickness(ARROW_OUTLINE_THIKNESS);
	secondArrow.setOutlineColor(sf::Color::Black);
	secondArrow.setPosition(CENTER_WINDOW);

	hourArrow.setSize(SIZE_HOUR_ARROW);
	hourArrow.setFillColor(sf::Color::Green);
	hourArrow.setOutlineThickness(ARROW_OUTLINE_THIKNESS);
	hourArrow.setOutlineColor(sf::Color::Black);
	hourArrow.setPosition(CENTER_WINDOW);
}

void programClock::initializeCircles()
{
	borderClock.setRadius(RADIUSE_CLOCK);
	borderClock.setFillColor(sf::Color::White);
	borderClock.setOrigin(borderClock.getRadius(), borderClock.getRadius());
	borderClock.setOutlineThickness(BORDER_THIKNESS);
	borderClock.setOutlineColor(sf::Color::Black);
	borderClock.setPosition(CENTER_WINDOW);

	middleClock.setRadius(RADIUSE_MIDDLE);
	middleClock.setFillColor(sf::Color::Black);
	middleClock.setOrigin(middleClock.getRadius(), middleClock.getRadius());
	middleClock.setPosition(CENTER_WINDOW);
}

void programClock::initializeIndicators()
{
	indicatorShape.setSize(SIZE_INDICATORS);
	indicatorShape.setFillColor(sf::Color::Black);
	indicatorShape.setPosition(CENTER_WINDOW);

	indicatorShape.setOrigin(SIZE_INDICATORS.x - RADIUSE_CLOCK, 0);
}



programClock::programClock()
{
	initializeArrows();
	initializeCircles();
	initializeIndicators();

	secondAngle = FULL_CIRCLE_DEGREES / NUMBER_SECOND;
	minuteAngle = secondAngle * 5;
	hourAngle = FULL_CIRCLE_DEGREES / NUMBER_HOUR;
}

void programClock::update()
{
	GetLocalTime(&time);
	float secondRotate = secondAngle * float(time.wSecond);
	float minuteRotate = minuteAngle * float(time.wMinute) / NUMBER_SECOND;

	secondArrow.setRotation(secondRotate - CIRCLE_QUARTER);
	minuteArrow.setRotation(secondRotate / NUMBER_SECOND + float(time.wMinute) * secondAngle - CIRCLE_QUARTER);
	hourArrow.setRotation(minuteRotate + float(time.wHour) * hourAngle - CIRCLE_QUARTER);

}

void programClock::draw(sf::RenderWindow& window)
{
	window.draw(borderClock);

	drawArrows(window);
	drawIndicators(window);

	window.draw(middleClock);
}

void programClock::drawArrows(sf::RenderWindow& window)
{
	window.draw(minuteArrow);
	window.draw(secondArrow);
	window.draw(hourArrow);
}

void programClock::drawIndicators(sf::RenderWindow& window)
{
	for (int i = 0; i < NUMBER_HOUR; i++) {
		indicatorShape.setRotation(i * (FULL_CIRCLE_DEGREES / NUMBER_HOUR));
		window.draw(indicatorShape);
	}
}

