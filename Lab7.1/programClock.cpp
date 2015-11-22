#include "programClock.h"

using namespace sf;

void programClock::init()
{
	minuteArrow.setSize(SIZE_MINUTE_ARROW);
	minuteArrow.setFillColor(sf::Color::White);
	minuteArrow.setOutlineThickness(ARROW_OUTLINE_THIKNESS);
	minuteArrow.setOutlineColor(sf::Color::Black);
	minuteArrow.setPosition(CENTER_WINDOW);

	secondArrow.setSize(SIZE_SECOND_ARROW);
	secondArrow.setFillColor(sf::Color::White);
	secondArrow.setOutlineThickness(ARROW_OUTLINE_THIKNESS);
	secondArrow.setOutlineColor(sf::Color::Black);
	secondArrow.setPosition(CENTER_WINDOW);

	hourArrow.setSize(SIZE_HOUR_ARROW);
	hourArrow.setFillColor(sf::Color::White);
	hourArrow.setOutlineThickness(ARROW_OUTLINE_THIKNESS);
	hourArrow.setOutlineColor(sf::Color::Black);
	hourArrow.setPosition(CENTER_WINDOW);

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

void programClock::render(sf::RenderWindow& window)
{
	window.draw(borderClock);

	window.draw(minuteArrow);
	window.draw(secondArrow);
	window.draw(hourArrow);

	window.draw(middleClock);
}

void initializeClock(programClock &clock)
{
	clock.init();
}

